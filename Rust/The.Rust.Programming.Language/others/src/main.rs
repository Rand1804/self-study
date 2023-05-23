use std::slice;


fn main() {
    // let mut v = vec![1, 2, 3, 4, 5, 6];

    // let r = &mut v[..];

    // let (a, b) = my_split_at_mut(r, 7);

    // println!("a: {:?}, b: {:?}", a, b);


    let address = 0x01234usize;
    let r = address as *mut i32;

    let values: &[i32] = unsafe { slice::from_raw_parts_mut(r, 10000) };
    // println!("{:?}", values);


}

fn my_split_at_mut(values: &mut [i32], mid: usize) -> (&mut [i32], &mut [i32]) {
    let len = values.len();
    let ptr = values.as_mut_ptr();

    assert!(mid <= len);

    unsafe {
        (
            slice::from_raw_parts_mut(ptr, mid),
            slice::from_raw_parts_mut(ptr.add(mid), len - mid)
        )
    }
}