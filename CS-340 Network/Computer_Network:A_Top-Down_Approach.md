## Chapter 1 Computer Networks and the Internet

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