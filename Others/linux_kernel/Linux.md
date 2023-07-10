# 网络

## 网络采用分层的思想

    1. 每一层实现不同的功能，对上层的数据做透明传输
    2. 每一层向上层提供服务，同时使用下层提供的服务

各层典型的协议：

1. 网络接口与物理层

    MAC地址： 48位全球唯一，网络设备的身份标识（标识网卡身份）

    ARP/RARP:
        ARP: 地址解析协议， IP地址----> MAC地址
        RARP： MAC地址---->IP地址

    PPP协议（电话线上网）：拨号协议（GPRS/3G/4G）

2. 网络层：
    IP： Internet protocol(分为IPV4和IPV6)
    ICMP: Internet控制管理协议，ping命令属于ICMP
    IGMP： Internet分组管理协议，广播，组播

3. 传输层：
    TCP：（Transfer Control protocol,传输控制协议）提供面向连接的，一对一的可靠数据传输的协议
    即数据无误，数据无丢失，数据无失序，数据无重复到达的通信
    UDP：（user Datagram Protocol,用户数据报协议） 提供不可靠，无连接的尽力传输协议
    SCTP： 是可靠传输，是TCP的增强版，它能实现多主机，多链路的通信

4. 应用层
    网页访问协议： HTTP/HTTPS
    邮件发送接受协议：POP3（收）/SMTP(发)，IMAP（可接收邮件的一部分）
    FTP,文件传输
    Telnet/SSH: 远程登陆
    嵌入式相关：
        NTP：网络时钟协议
        SNMP:简单网络管理协议（实现对网络设备集中式管理）
        RTP/RTSP:用传输音视频的协议（安防监控）

|Ethernet header(14bytes)|IP header(20bytes)|TCP header(20bytes)|APP header|user data|Ethernet trailer(CRC32,4bytes,硬件产生和校验)|
46-1500bytes

MTU： Max Transfer Unit 最大传输单元（和网络类型相关）
例如：以太网：MTU = 1500
MSS： Maximum Segment Size 最大段大小 网络类型，线路，系统特性相关（实际数据和应用层包头的大小）此例中为1460

## TCP/IP网络编程预备知识

### Socket

- 是一个应用编程接口
- 是一种特殊的文件描述符(everything in Unix is a file),代表着网络编程的一种资源
- 并不仅限于TCP/IP协议
- 面向连接(Transmission Control Protocol - TCP/IP)
- 无连接 (User Datagram Protocol - UDP 和 Inter-network Packet Exchange IPX)

**套接字类型：**

- 流式套接字（SOCK——STREAM）：提供了一个面向连接，可靠的数据传输服务，数据无差错，无重复的发送且按发送的顺序接受。内置流量控制，避免数据流淹没慢的接收方。数据被看作是字节流，无长度限制。（唯一对应TCP）
- 数据报套接字（SOCK——DGRAM）：提供无连接服务。数据包以独立的数据包的形式被发送，不提供无差错保证，数据可能丢失或重复，顺序发送，可能乱序接收。（唯一对应UDP）
- 原始套接字（SOCK——RAM）：可以对较低层次协议如IP,ICMP直接访问。（对应多个协议，发送穿透了传输层）

### IP地址

IP地址分为IPV4和IPV6
    IPV4：采用32位的整数来表示
    IPV6：采用了128位整数来表示
    mobileIPV6：local IP（本地注册的IP）， roam IP（漫游IP）

IPV4地址：
    点分形式： 192.168.7.246
    32位整数

特殊IP地址：
    局域网IP：192.XXX.XXX.XXX 10.XXX.XXX.XXX
    广播IP： xxx.xxx.xxx.255, 255.255.255.255(全网广播)
    组播IP：224.xxx.xxx.xxx~239.xxx.xxx.xxx

### 端口号

    16位的数字（1-65535）
        Well Known Ports： 1～1023 （FTP:21, SSH:22, HTTP:80, HTTPS:443）
        保留端口： 1024～5000（不建议使用）
        可以使用的： 5000～65535
**TCP端口和UDP端口是相互独立的**

网络里面的通信是由IP地址+端口号来决定

### 字节序

字节序是指不同的CPU访问内存中的**多字节数据**时候，存在大小端问题
低对低： 小端   低端内存存放低端数据
低对高： 大端   低端内存存放高端数据

一般来说：
    X86/ARM： 小端
    powerpc/mips, ARM作为路由器时，大端模式

    网络传输的时候采用大端模式

    本地字节序，网络字节序

- 主机字节序到网络字节序
    - u_long htonl(u_long hostlong); (long 4bytes)
    - u_short htons(u_short short);  (short 2bytes)
- 网络字节序到主机字节序
    - u_long ntohl(u_long hostlong);
    - u_short ntohs(u_short short);

IP地址转换函数：
in_addr_t inet_addr(const char *cp);
cp :点分形式的ip地址，结果是32位整数（内部包含了字节序的转换，默认是大端）
特点： 1.仅适应于IPV4
        2.当出错时，返回-1
        3.此函数不能用于255.255.255.255的转换

inet_pton()/inet_ntop()

```c
#include <arpa/inet.h>

int inet_pton(int af, const char *src, void *dst);
```

特点： 1.适用于IPV4和IPV6
        2.能正确的处理255.255.255.255的转换问题
参数：
    1.af:地址协议族（AF_INET或AF_INET6）
    2.src:是一个指针（填写点分形式的IP地址[主要指IPV4]）
    3.dst:转换的结果给到dst

RETURN VALUE
       inet_pton() returns 1 on  success  (network  address  was  successfully  con‐
       verted).  0 is returned if src does not contain a character string represent‐
       ing a valid network address in the specified address family.  If af does  not
       contain  a valid address family, -1 is returned and errno is set to EAFNOSUP‐
       PORT.

inet_ntop(): 把IPV4/IPV6的网络字节序的地址变成本地的字符串形式的IP地址

```c
const char *inet_ntop(int af, const void *restrict src,
                        char dst[restrict .size], socklen_t size);
```
特点： 1.适用于IPV4和IPV6
        2.能正确的处理255.255.255.255的转换问题
参数：
    1.af:地址协议族（AF_INET或AF_INET6）
    2.src:是一个指针（32位网络字节序的IP地址）
    3.dst:输出结果为点分形式的IP地址[主要指IPV4]

RETURN VALUE
       On  success, inet_ntop() returns a non-null
       pointer to dst.  NULL is returned if  there
       was  an  error,  with errno set to indicate
       the error.

### TCP编程api

1.socket()

```c
#include <sys/socket.h>

int socket(int domain, int type, int protocol);
```

参数：
    1. domain
        AF_INET      IPv4 Internet protocols                    ip(7)
        AF_INET6     IPv6 Internet protocols                    ipv6(7)
        AF_UNIX      Local communication                        unix(7)
        AF_LOCAL     Synonym for AF_UNIX
        AF_NETLINK   Kernel user interface device               netlink(7)
        AF_PACKET    Low-level packet interface                 packet(7)
    2.type:
        SOCK_STREAM: 流式套接字，唯一对应于TCP
        SOCK_DGRAM: 数据报套接字，唯一对应着UDP
        SOCK_RAW： 原始套接字
    3.protocol: 一般为0,原始套接字编程时需填充

RETURN VALUE
       On  success,  a file descriptor for the new socket is returned.  On error, -1 is
       returned, and errno is set to indicate the error.
    成功时返回文件描述符，出错时返回为-1

2.bind()

```c
       #include <sys/socket.h>

       int bind(int sockfd, const struct sockaddr *addr,
                socklen_t addrlen);
```

参数：
    sockfd: 通过socket()函数拿到的fd
    addr： 采用struct sockaddr的结构体变量的地址
    addrlen： 地址长度

3.listen()

```c
       #include <sys/socket.h>

       int listen(int sockfd, int backlog);
```

参数：
    sockfd：通过socket()函数拿到的fd
    backlog:同时允许几路客户端和服务器进行正在连接的过程（正在三次握手）
            一般填5,测试得知，ARM最大为8
> 内核中服务器的套接字fd会维护2个链表
    1.正在三次握手的客户端链表（数量=2*backlog+1）
    2.已经建立好连接的客户端链表（已经完成3次握手分配好了newfd）

返回值：
    RETURN VALUE
       On success, zero is returned.  On error, -1 is returned, and errno is set to indicate the error.

4.accept() 阻塞等待客户端连接请求

```c
       #include <sys/socket.h>

       int accept(int sockfd, struct sockaddr *_Nullable restrict addr,
                  socklen_t *_Nullable restrict addrlen);
```

参数：
    sockfd: 经过前面socket()创建并通过bind(),listen(),设置过的fd
    addr和addrlen:

返回值：
    RETURN VALUE
       On  success,  these  system calls return a file descriptor for the accepted socket (a nonnegative integer).  On error, -1 is returned, errno is set to indicate the error, and addrlen is left  unchanged.

5.客户端的连接函数

```c
       #include <sys/socket.h>

       int connect(int sockfd, const struct sockaddr *addr,
                   socklen_t addrlen);
```

connect()函数和服务器bind()函数类似

返回值
RETURN VALUE
       If the connection or binding succeeds, zero is returned.  On error, -1 is returned, and errno is set to indicate the error.

参数：
    sockfd: 通过socket()函数拿到的fd
    addr： 采用struct sockaddr的结构体变量的地址
    addrlen： 地址长度