## MCUboot v0.9(b6efee9: Bump to version 0.9.0)

```c
struct flash_area {
    /**
     * This flash area's ID; unique in the system.
     */
    uint8_t fa_id;

    /**
     * ID of the flash device this area is a part of.
     */
    uint8_t fa_device_id;

    uint16_t pad16;

    /**
     * This area's offset, relative to the beginning of its flash
     * device's storage.
     */
    uint32_t fa_off;

    /**
     * This area's size, in bytes.
     */
    uint32_t fa_size;
};



/** Image header.  All fields are in little endian byte order. */
struct image_header {
    uint32_t ih_magic;
    uint16_t ih_tlv_size; /* Combined size of trailing TLVs (bytes). */
    uint8_t  ih_key_id;   /* Which key image is signed with (0xff=unsigned). */
    uint8_t  _pad1;
    uint16_t ih_hdr_size; /* Size of image header (bytes). */
    uint16_t _pad2;
    uint32_t ih_img_size; /* Does not include header. */
    uint32_t ih_flags;    /* IMAGE_F_[...]. */
    struct image_version ih_ver;
    uint32_t _pad3;
};


/** Private state maintained during boot. */
struct boot_loader_state {
    struct {
        struct image_header hdr;
        const struct flash_area *area;
        boot_sector_t *sectors;
        size_t num_sectors;
    } imgs[BOOT_NUM_SLOTS];

    const struct flash_area *scratch_area;

    uint8_t write_sz;
};

```

### boot_go()

```C
#打开3个flash区域,填上area字段
flash_area_open()
#初始化boot_data sectors num_sectors write_sz 字段
boot_read_sectors()->{boot_initialize_area， boot_write_sz};
#读取图像中的头信息，填上hdr字段，至少image0是有的，否则会直接退出
boot_read_image_headers()->boot_read_image_header(i, boot_img_hdr(&boot_data, i));
#测试兼容性（检查两个slot扇区数量一致，且所有扇区大小相同），如果不兼容永远从slot0启动，slot1不可用
if (boot_slots_compatible()) {
    boot_swap_if_needed(&swap_type);
} else {
        swap_type = BOOT_SWAP_TYPE_NONE;
}
```

### boot_swap_if_needed()

```c
/**
 * End-of-image slot structure.
 *
 *  0                   1                   2                   3
 *  0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * ~                        MAGIC (16 octets)                      ~
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * ~                                                               ~
 * ~                Swap status (variable, aligned)                ~
 * ~                                                               ~
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |   Copy done   |     0xff padding (up to min-write-sz - 1)     ~
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |   Image OK    |     0xff padding (up to min-write-sz - 1)     ~
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 */


/*
 * Maintain state of copy progress.
 */
struct boot_status {
    uint32_t idx;         /* Which area we're operating on */
    uint8_t state;        /* Which part of the swapping process are we at */
    uint8_t use_scratch;  /* Are status bytes ever written to scratch? */
};

struct boot_status_table {
    /**
     * For each field, a value of 0 means "any".
     */
    uint8_t bst_magic_slot0;
    uint8_t bst_magic_scratch;
    uint8_t bst_copy_done_slot0;
    uint8_t bst_status_source;
};

/**
 * This set of tables maps swap state contents to boot status location.
 * When searching for a match, these tables must be iterated in order.
 */
static const struct boot_status_table boot_status_tables[] = {
    {
        /*           | slot-0     | scratch    |
         * ----------+------------+------------|
         *     magic | Good       | Any        |
         * copy-done | 0x01       | N/A        |
         * ----------+------------+------------'
         * source: none                        |
         * ------------------------------------'
         */
        .bst_magic_slot0 =      BOOT_MAGIC_GOOD,
        .bst_magic_scratch =    0,
        .bst_copy_done_slot0 =  0x01,
        .bst_status_source =    BOOT_STATUS_SOURCE_NONE,
    },

    {
        /*           | slot-0     | scratch    |
         * ----------+------------+------------|
         *     magic | Good       | Any        |
         * copy-done | 0xff       | N/A        |
         * ----------+------------+------------'
         * source: slot 0                      |
         * ------------------------------------'
         */
        .bst_magic_slot0 =      BOOT_MAGIC_GOOD,
        .bst_magic_scratch =    0,
        .bst_copy_done_slot0 =  0xff,
        .bst_status_source =    BOOT_STATUS_SOURCE_SLOT0,
    },

    {
        /*           | slot-0     | scratch    |
         * ----------+------------+------------|
         *     magic | Any        | Good       |
         * copy-done | Any        | N/A        |
         * ----------+------------+------------'
         * source: scratch                     |
         * ------------------------------------'
         */
        .bst_magic_slot0 =      0,
        .bst_magic_scratch =    BOOT_MAGIC_GOOD,
        .bst_copy_done_slot0 =  0,
        .bst_status_source =    BOOT_STATUS_SOURCE_SCRATCH,
    },

    {
        /*           | slot-0     | scratch    |
         * ----------+------------+------------|
         *     magic | Unset      | Any        |
         * copy-done | 0xff       | N/A        |
         * ----------+------------+------------|
         * source: varies                      |
         * ------------------------------------+------------------------------+
         * This represents one of two cases:                                  |
         * o No swaps ever (no status to read, so no harm in checking).       |
         * o Mid-revert; status in slot 0.                                    |
         * -------------------------------------------------------------------'
         */
        .bst_magic_slot0 =      BOOT_MAGIC_UNSET,
        .bst_magic_scratch =    0,
        .bst_copy_done_slot0 =  0xff,
        .bst_status_source =    BOOT_STATUS_SOURCE_SLOT0,
    },
};

struct boot_swap_state {
    uint8_t magic;  /* One of the BOOT_MAGIC_[...] values. */
    uint8_t copy_done;
    uint8_t image_ok;
};

const uint32_t boot_img_magic[] = {
    0xf395c277,
    0x7fefd260,
    0x0f505235,
    0x8079b62c,
};

/* This is not actually used by mcuboot's code but can be used by apps
 * when attempting to read/write a trailer.
 */
struct image_trailer {
    uint8_t copy_done;
    uint8_t pad1[MAX_FLASH_ALIGN - 1];
    uint8_t image_ok;
    uint8_t pad2[MAX_FLASH_ALIGN - 1];
    uint8_t magic[16];
};

offsetof(struct image_trailer, magic) 

#找到boot_status存储在哪个区，然后读取进行到哪个setor了
boot_read_status(&bs);
	->boot_status_source(void);
		#读取分区的交换状态
		->boot_read_swap_state_by_id(FLASH_AREA_IMAGE_0, &state_slot0);
			#读取并校验image末尾16个字节的magic,赋值boot_swap_state magic image_ok copy_done字段
			->boot_read_swap_state()
	->boot_read_status_bytes
```

### boot_copy_image()

```c
/** Just boot whatever is in slot 0. */
#define BOOT_SWAP_TYPE_NONE     1

/** Swap to slot 1.  Absent a confirm command, revert back on next boot. */
#define BOOT_SWAP_TYPE_TEST     2

/** Swap to slot 1 permanently. */
#define BOOT_SWAP_TYPE_PERM     3

/** Swap back to alternate slot.  A confirm changes this state to NONE. */
#define BOOT_SWAP_TYPE_REVERT   4

/** Swap failed because image to be run is not valid */
#define BOOT_SWAP_TYPE_FAIL     5

/** Swapping encountered an unrecoverable error */
#define BOOT_SWAP_TYPE_PANIC    0xff

#define MAX_FLASH_ALIGN         8

#define BOOT_STATUS_STATE_COUNT 3
#define BOOT_STATUS_MAX_ENTRIES 128

#define BOOT_STATUS_SOURCE_NONE    0
#define BOOT_STATUS_SOURCE_SCRATCH 1
#define BOOT_STATUS_SOURCE_SLOT0   2

#define BOOT_FLAG_IMAGE_OK         0
#define BOOT_FLAG_COPY_DONE        1

#define BOOT_FLAG_SET              0x01
#define BOOT_FLAG_UNSET            0xff
#每次复制仅复制header,image,tlvs
#如果之前的交换操作被中断，则继续交换
boot_copy_image(&bs);
->boot_swap_sectors(first_sector_idx, sz, bs);
```

idx = 2
img_off = 8k

sz = 8k
status for all sectors 128 * 3 *8

copy_done 8
image_ok 8
magic 16
trailer_sz = 3104