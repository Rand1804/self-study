## Chapter 1 Computer Networks and the Internet

### 1.1 What Is the Internet?

In Internet jargon, all of these devices are called **hosts** or **end systems**.

End systems are connected together by a network of **communication links** and **packet switches**.

We’ll see in Section 1.2 that there are many types of communication links, which are made up of different types of **physical media**, including coaxial cable, copper wire, optical fiber, and radio spectrum. Different links can transmit data at different rates, with the **transmission rate** of a link measured in
bits/second.

The resulting packages of information, known as **packets** in the jargon of computer networks, are then sent through the network to the destination end system, where they are reassembled into the original data.

Both types of switches forward packets toward their ultimate destinations. Link-layer switches are typically used in **access networks**, while routers are typically used in the **network core**. The sequence of communication links and packet switches traversed by a packet from the sending end system to the receiving end system is known as a **route or path** through the network.



### 1.5 Protocol Layers

![image-20240425002531282](assets/image-20240425002531282.png)

- Application Layer

  - such as domain name system(DNS)
  - An application-layer protocol is distributed over multiple end systems, with the application in one end system using the protocol to exchange packets of information with the application in another end system. We’ll refer to this packet of information at the application layer as a **message**.

- Transport Layer

  - The Internet's transport layer transports application-layer messages between application endpoints. In the Internet there are two transport protocols, TCP and UDP, either of which can transport application-layer messages.

    > **TCP** provides a ­connection-oriented service to its applications. This service includes guaranteed delivery of application-layer messages to the destination and flow control (that is, sender/receiver speed matching). TCP also breaks long messages into shorter ­segments and provides a congestion-control mechanism, so that a source throttles its transmission rate when the network is congested. The **UDP** protocol provides a connectionless service to its applications. This is a no-frills service that provides **no reliability, no flow control, and no congestion control**.

  - In this boot, we'll refer to a transport-layer packet as a **segment**.

- Network Layer

  - Although the network layer contains both the **IP protocol** and **numerous routing protocols**, it is often simply referred to as the IP layer, reflecting the fact that IP is the glue that binds the Internet together.
  - The Internet’s network layer is responsible for moving network-layer packets known as **datagrams** from one host to another.
  - The Internet’s network layer also contains **routing protocols** that determine the routes that datagrams take between sources and destinations.

- Link Layer

  - include Ethernet, WiFi
  - The services provided by the link layer depend on the specific link-layer protocol that is employed over the link.
  - The network layer will receive a different service from each of the different link-layer protocols. In this book, we’ll refer to the link-layer packets as **frames**.

- Physical Layer

  - the job of the physical layer is to move the individual bits within the frame from one node to the next.
  - For example, Ethernet has many physical-layer protocols: one for twisted-pair copper wire, another for coaxial cable,

### 1.6 Networks Under Attack

![image-20240425050050281](assets/image-20240425050050281.png)

We should keep in mind that communication among mutually trusted users is the exception rather than the rule. Welcome to the world of modern computer networking!

![123](assets/123.png)

## Chapter 2 Application Layer

![image-20240506020552447](assets/image-20240506020552447.png)

To identify the receiving process, two pieces of information need to be specified: 

1. the address of thehost and (**IP address**)

2. an identifier that specifies the receiving process in the destination host.(**port number**)

### Socket

Recall that a socket is the **interface between the application process and the transport-layer protocol.** The application at the sending side pushes messags through the socket. At the other side of the socket, the transport-layer protocol has the responsibility of getting the messages to the socket of the receiving process.

### Transport Services Available to Applications

1. **Reliable Data Transfer**

   packets can get lost within a computer network. For example, a packet can overflow a buffer in a router, or can be discarded by a host or router after having some of its bits corrupted.

   If a protocol provides such a guaranteed data delivery service, it is said to provide **reliable data transfer**. One important service that a transport-layer protocol can potentially provide to an application is process-to-process reliable data transfer.

2. **Throughput**

   In the context of a communication session between two processes along a network path, is **the rate at which the sending process can deliver bits** to the receiving process.

   Applications that have throughput requirements are said to be **bandwidth-sensitive applications**. If the transport protocol cannot provide this throughput, the application would need to encode at a lower rate (and receive enough throughput to sustain this lower coding rate) or may have to give up, since receiving, say, **half of the needed throughput** is of little or **no use** to this Internet telephony application.

3. **Timing**

   An example guarantee might be that every bit that the sender pumps into the **socket arrives at the receiver’s socket** no more than 100 msec later.

4. **Security**

   In the sending host, a transport protocol can **encrypt** all data transmitted by the sending process, and in the receiving host, the transport-layer protocol can **decrypt the data before delivering** the data to the receiving process.

### 2.1.4 Transport Services Provided by the Internet

#### TCP

![image-20240510082356339](assets/image-20240510082356339.png)

- **Connection-oriented service**. TCP has the client and server **exchange** transport-layer control
  information with each other before the application-level messages begin to flow. This so-called
  **handshaking** procedure alerts the client and server, allowing them to prepare for an onslaught of
  packets.full-duplex connection.When the application finishes sending messages, it must tear down the connection.
- **Reliable data transfer service**. The communicating processes can rely on TCP to deliver all data sent without error and in the proper order. When one side of the application passes a stream of bytes into a socket, it can count on TCP to deliver the same stream of bytes to the receiving socket, with no missing or duplicate bytes.

TCP also includes a congestion-control mechanism, a service for the general welfare of the Internet rather than for the direct benefit of the communicating processes.

Because privacy and other security issues have become critical for many applications, the Internet community has developed an enhancement for TCP, called Secure Sockets Layer (**SSL**).TCP-enhanced-with-SSL not onlydoes everything that traditional TCP does but also provides critical process-to-process security services, including **encryption, data integrity, and end-point authentication**.

#### UDP

UDP is a **no-frills, lightweight transport protocol, providing minimal services**. UDP is connectionless, so there is no handshaking before the two processes start to communicate. UDP provides an unreliable data transfer service—that is, when a process sends a message into a UDP socket, UDP provides no guarantee that the message will ever reach the receiving process. Furthermore, messages that do arrive at the receiving process may arrive out of order.

UDP does not include a congestion-control mechanism, so the sending side of UDP can pump data into the layer below (the network layer) at any rate it pleases.

#### *Services Not Provided by Internet Transport Protocols*

We have already noted that TCP provides reliable end-to-end data transfer. And we also know that TCP can be easily enhanced at the application layer with SSL to provide security services. But in our brief description of TCP and UDP, conspicuously missing was any mention of **throughput** or **timing guarantees**— services not provided by today’s Internet transport protocols.

**In summary**, today’s Internet can often provide satisfactory service to time-sensitive applications, but it cannot provide any timing or throughput guarantees.

thereby circumventing **TCP’s congestion control mechanism** and **packet overheads**.

![image-20240510093956632](assets/image-20240510093956632.png)

### 2.1.5 Application-Layer Protocols

An **application-layer protocol** defines how an application’s processes, running on different end systems, pass messages to each other. 

In particular, an application-layer protocol defines:

- The types of messages exchanged, for example, request messages and response messages
- The syntax of the various message types, such as the fields in the message and how the fields are delineated
- The semantics of the fields, that is, the meaning of the information in the fields
- Rules for determining when and how a process sends messages and responds to messages

The Web application consists of many components, including a standard for **document formats** (that is, HTML), **Web browsers** (for example, Firefox and Microsoft Internet Explorer), **Web servers** (for example, Apache and Microsoft servers), and an **application-layer protocol**.