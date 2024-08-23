### Three Kinds of Structures
- **Component-and-connector (C&C) structures**
	- Component-and-connector (C&C) structures focus on the way the elements interact with each other at runtime to carry out the system’s functions. They describe how the system is structured as a set of elements that have runtime behavior (components) and interactions (connectors). Components are the principal units of computation and could be services, peers, clients, servers, filters, or many other types of runtime element. Connectors are the communication vehicles among components, such as call-return, process synchronization operators, pipes, or others. C&C structures help answer questions such as the following:
		- What are the major executing components and how do they interact at runtime?
		- What are the major shared data stores?
		- Which parts of the system are replicated?
		- How does data progress through the system?
		- Which parts of the system can run in parallel?
		- Can the system’s structure change as it executes and, if so, how?
	- ![[Pasted image 20240821134930.png]]
- **Module structures** 
	- Module structures partition systems into implementation units, which in this book we call modules. Module structures show how a system is structured as a set of code or data units that have to be constructed or procured. Modules are assigned specific computational responsibilities and are the basis of work assignments for programming teams. In any module structure, the elements are modules of some kind (perhaps classes, packages, layers, or merely divisions of functionality, all of which are units of implementation). Modules represent a static way of considering the system. Modules are assigned areas of functional responsibility; there is less emphasis in these structures on how the resulting software manifests itself at runtime. Module implementations include packages, classes, and layers. Relations among modules in a module structure include uses, generalization (or “is-a”), and “is part of.” Figures 1.3 and 1.4 show examples of module elements and relations, respectively, using the Unified Modeling Language (UML) notation.
	- Module structures allow us to answer questions such as the following:
		- What is the primary functional responsibility assigned to each module?
		- What other software elements is a module allowed to use?
		- What other software does it actually use and depend on?
		- What modules are related to other modules by generalization or specialization (i.e.,
inheritance) relationships?
	- ![[Pasted image 20240821135729.png]]
- **Allocation structures**
	- Allocation structures establish the mapping from software structures to the system’s nonsoftware structures, such as its organization, or its development, test, and execution environments. Allocation structures answer questions such as the following:
		- Which processor(s) does each software element execute on?
		- In which directories or files is each element stored during development, testing, and system building? 
		- What is the assignment of each software element to development teams?

![[Pasted image 20240821141002.png]]

#### Some Useful Module Structures
- **Decomposition structure**
	- The units are modules that are related to each other by the “is-a-submodule-of” relation, showing how modules are decomposed into smaller modules recursively until the modules are small enough to be easily understood. Modules in this structure represent a common starting point for design, as the architect enumerates what the units of software will have to do and assigns each item to a module for subsequent (more detailed) design and eventual implementation. Modules often have products (such as interface specifications, code, and test plans) associated with them.
	- ![[Pasted image 20240821141647.png]]
- **Uses structure**
	- In this important but often overlooked structure, the units are also modules, and perhaps classes. The units are related by the uses relation, a specialized form of dependency. One unit of software uses another if the correctness of the first requires the presence of a correctly functioning version (as opposed to a stub) of the second. The uses structure is used to engineer systems that can be extended to add functionality, or from which useful functional subsets can be extracted. 
	- ![[Pasted image 20240821141712.png]]
- **Layer structure**
	-  The modules in this structure are called layers. A layer is an abstract “virtual machine” that provides a cohesive set of services through a managed interface. Layers are allowed to use other layers in a managed fashion; in strictly layered systems, a layer is only allowed to use a single other layer. This structure imbues a system with portability—that is, the ability to change the underlying virtual machine. Figure 1.7 shows a layer structure of the UNIX System V operating system.
	- ![[Pasted image 20240821141809.png]]
- **Class (or generalization) structure**
	- The modules in this structure are called classes, and they are related through an “inherits-from” or “is-an-instance-of” relation. This view supports reasoning about collections of similar behavior or capability and parameterized differences. The class structure allows one to reason about reuse and the incremental addition of functionality. If any documentation exists for a project that has followed an object-oriented analysis and design process, it is typically this structure. Figure 1.8 shows a generalization structure taken from an architectural expert tool.
	- ![[Pasted image 20240821142603.png]]
- **Data model**
	- The data model describes the static information structure in terms of data entities and their relationships. For example, in a banking system, entities will typically include Account, Customer, and Loan. Account has several attributes, such as account number, type (savings or checking), status, and current balance. A relationship may dictate that one customer can have one or more accounts, and one account is associated with one or more customers. Figure 1.9 shows an example of a data model.
	- ![[Pasted image 20240821143103.png]]
	

 > **Work assignment structure** 
 > This structure assigns responsibility for implementing and integrating the modules to the teams that will carry out these tasks. Having a work assignment structure be part of the architecture makes it clear that the decision about who does the work has architectural as well as management implications. The architect will know the expertise required on each team. Amazon’s decision to devote a single team to each of its microservices, for example, is a statement about its work assignment structure. **On large development projects, it is useful to identify units of functional commonality and assign those to a single team, rather than having them be implemented by everyone who needs them**. This structure will also determine the major communication pathways among the teams: regular web conferences, wikis, email lists, and so forth.
![[Pasted image 20240821144251.png]]

#### 1.3 What Makes a “Good” Architecture?
We divide our observations into two clusters: process recommendations and product (or
structural) recommendations. 
###### **Our process recommendations are as follows:**
1. A software (or system) architecture should be the product of a single architect or a small group of architects with an identified technical leader. This approach is important to give the architecture its conceptual integrity and technical consistency. This recommendation holds for agile and open source projects as well as “traditional” ones. There should be a strong connection between the architects and the development team, to avoid “ivory tower,” impractical designs.
2. The architect (or architecture team) should, on an ongoing basis, base the architecture on a prioritized list of well-specified quality attribute requirements. These will inform the tradeoffs that always occur. Functionality matters less.
3. The architecture should be documented using views. (A view is simply a representation of one or more architectural structures.) The views should address the concerns of the most important stakeholders in support of the project timeline. This might mean minimal documentation at first, with the documentation then being elaborated later. Concerns usually are related to construction, analysis, and maintenance of the system, as well as education of new stakeholders.
4. The architecture should be evaluated for its ability to deliver the system’s important quality attributes. This should occur early in the life cycle, when it returns the most benefit, and repeated as appropriate, to ensure that changes to the architecture (or the environment for which it is intended) have not rendered the design obsolete.
5. The architecture should lend itself to incremental implementation, to avoid having to integrate everything at once (which almost never works) as well as to discover problems early. One way to do this is via the creation of a “skeletal” system in which the communication paths are exercised but which at first has minimal functionality. This skeletal system can be used to “grow” the system incrementally, refactoring as necessary.
###### **Our structural rules of thumb are as follows:**
1. The architecture should feature well-defined modules whose functional responsibilities are assigned on the principles of information hiding and separation of concerns. The information-hiding modules should encapsulate things likely to change, thereby insulating the software from the effects of those changes. Each module should have a well- defined interface that encapsulates or “hides” the changeable aspects from other software that uses its facilities. These interfaces should allow their respective development teams to work largely independently of each other.
2. Unless your requirements are unprecedented—possible, but unlikely—your quality attributes should be achieved by using well-known architectural patterns and tactics (described in Chapters 4 through 13) specific to each attribute.
3. The architecture should never depend on a particular version of a commercial product or tool. If it must, it should be structured so that changing to a different version is straightforward and inexpensive.
4. Modules that produce data should be separate from modules that consume data. This tends to increase modifiability because changes are frequently confined to either the production or the consumption side of data. If new data is added, both sides will have to change, but the separation allows for a staged (incremental) upgrade.
5. Don’t expect a one-to-one correspondence between modules and components. For example, in systems with concurrency, multiple instances of a component may be running in parallel, where each component is built from the same module. For systems with multiple threads of concurrency, each thread may use services from several components, each of which was built from a different module.
6. Every process should be written so that its assignment to a specific processor can be easily changed, perhaps even at runtime. This is a driving force in the increasing trends toward virtualization and cloud deployment, as we will discuss in Chapters 16 and 17.
7. The architecture should feature a small number of simple component interaction patterns. That is, the system should do the same things in the same way throughout. This practice will aid in understandability, reduce development time, increase reliability, and enhance modifiability.
8. The architecture should contain a specific (and small) set of resource contention areas, whose resolution is clearly specified and maintained. For example, if network utilization is an area of concern, the architect should produce (and enforce) for each development team guidelines that will result in acceptable levels of network traffic. If performance is a concern, the architect should produce (and enforce) time budgets.

## 第7章 可集成性

![[Pasted image 20240822100000.png]]


**可集成性策略**

- **限制依赖**
  - 封装
  - 使用中介
  - 限制通信路径
  - 遵循标准
  - 抽象公共服务

- **适应**
  - 发现
  - 定制接口
  - 配置行为

- **协调**
  - 编排
  - 管理资源

**图 7.3** 可集成性策略


## 第8章 可修改性
##### **如何变更**？
- 可以在实现期间（通过修改源代码）、编译期间（使用编译时开关）、生成期间（通过选择库）、配置设置期间（通过一系列技术，包括参数设置）或执行期间（通过参数设置、插件、分配给硬件等）进行更改。

##### 可修改性细分
- **_可扩展性_** 是关于容纳更多的东西。在性能方面，可扩展性意味着添加更多资源。两种性能可伸缩性是水平可伸缩性和垂直可伸缩性。水平可伸缩性（横向扩展）是指向逻辑单元添加更多资源，例如将另一台服务器添加到服务器群集。垂直可伸缩性（纵向扩展）是指向物理单元添加更多资源，例如向单台计算机添加更多内存。
- **_可变性_** 是指系统及其支持工件（如代码、需求、测试计划和文档）支持以预先计划的方式生成一组彼此不同的变体的能力。
- **_可移植性_** 是指将构建为在一个平台上运行的软件更改为在不同平台上运行的难易程度。
- **_位置独立性_** 是指两个分布式软件交互，并且在运行时之前不知道其中一个或两个部分的位置的情况。或者，这些片段的位置可能会在运行时更改。在分布式系统中，服务通常部署到任意位置，这些服务的客户端必须动态发现其位置。此外，分布式系统中的服务在部署到某个位置后，通常必须使其位置可被发现。设计系统时具有位置独立性意味着位置易于修改，对系统其余部分的影响最小。
##### 复杂性度量
为了理解可修改性，我们从软件设计中一些最早和最基本的复杂性度量开始 - **耦合**和**内聚**
- **耦合**
	- 通常，影响一个模块的变更比影响多个模块的变更更容易且成本更低。但是，如果两个模块的职责以某种方式重叠，那么单个变更很可能会同时影响它们。我们可以通过测量对一个模块的修改传播到另一个模块的概率来量化这种重叠。这种关系称为 _耦合_，高度耦合是可修改性的敌人。减少两个模块之间的耦合将降低影响任何一个模块的任何修改的预期成本。减少耦合的策略是在两个高度耦合的模块之间**放置各种中介**的策略。
- **内聚**
	- _内聚力_ 用于衡量**模块职责的相关性**。非正式地，它衡量模块的“目的统一性”。目的的统一可以通过影响模块的更改方案来衡量。模块的内聚力是影响职责的变更方案也会影响其他（不同）职责的概率。内聚力越高，给定变更影响多个模块的可能性就越低。高内聚力有利于可改性；低内聚力则对它不利。如果模块 A 的内聚力较低，则可以通过移除不受预期变更影响的职责来改善内聚力。
- **减小尺寸、增加内聚力、减少耦合和延迟绑定时间**
- ![[Pasted image 20240821161334.png]]

---

**可修改性策略**

增加内聚力
- 拆分模块
- 重新分配职责

降低耦合度
- 封装
- 使用中介
- 抽象通用服务
- 限制依赖

推迟绑定
- 组件替换
- 绑定时间参数化
- 切面
- 配置时间绑定
- 资源文件
- 发现
- 解释参数
- 共享存储库
- 多态性

---
## 第15章 软件接口

##### 操作、事件和属性
所提供接口的资源由操作、事件和属性组成。
- _**操作**_ 被调用以将控制和数据传输到元素进行处理。大多数操作也会返回一个结果。操作可能会失败，作为接口的一部分，应该明确参与者如何检测错误，无论是作为输出的一部分发出信号还是通过一些专用的异常处理通道。
- **_事件_**——通常是异步的——可能在接口中进行描述。传入的事件可以表示从队列中接收的消息，或者要处理的流元素的到达。主动元素——那些不是被动等待被其他元素调用的元素——会产生传出事件，用于向监听者（或订阅者）通知元素内部发生的有趣事情。
- 接口的一个重要方面是元数据，例如访问权限、度量单位或格式假设。这种接口元数据的另一个名称是**属性**。正如本章开头的引述所强调的，属性值可以影响操作的行为。属性值也会根据元素的状态影响元素的行为。
##### 接口演进
- **_弃用_**。弃用意味着移除一个接口。弃用接口的最佳实践是向元素的参与者发出广泛通知。从理论上讲，此警告会给参与者留出时间来适应接口的移除。但实际上，许多参与者不会提前进行调整，而是在接口被移除时才发现已弃用。弃用接口的一种技术是引入一个错误代码，表示此接口将在（特定日期）被弃用或者此接口已被弃用。
- **_版本控制_**。多个接口通过保留旧接口并添加新接口来支持演进。当不再需要旧接口或已决定不再支持它时，可以弃用旧接口。这就要求参与者指定其正在使用的接口版本。
- **_扩展_**。扩展接口意味着保持原始接口不变，并向接口添加体现所需更改的新资源。[图 15.1(a)](https://github.com/suseme/arc_n_p/blob/4th-cn/ch15.md#ch15fig01)展示了原始接口。如果扩展与原始接口不存在任何不兼容，那么元素可以直接实现外部接口，如图[15.1(b)](https://github.com/suseme/arc_n_p/blob/4th-cn/ch15.md#ch15fig01)所示。相反，如果扩展引入了一些不兼容，那么元素就需要有一个内部接口，并添加一个中介来在外部接口和内部接口之间进行转换，如图[15.1(c)](https://github.com/suseme/arc_n_p/blob/4th-cn/ch15.md#ch15fig01)所示。作为不兼容的一个示例，假设原始接口假定公寓号码包含在地址中，但扩展接口将公寓号码作为一个单独的参数分离出来。内部接口会将公寓号码作为一个单独的参数。然后，如果从中介从原始接口被调用，它会解析地址以确定任何公寓号码，而中介会将包含在单独参数中的公寓号码原封不动地传递给内部接口。
###### 接口设计原则
这里重点介绍了一些接口的额外设计原则：

- **_最小意外原则_**。接口的行为应当与参与者的预期保持一致。名称在这里起作用：一个恰当命名的资源能给参与者一个关于该资源用途的良好提示。
- **_小接口原则_**。如果两个元素需要交互，让它们交换尽可能少的信息。
- **_统一访问原则_**。避免通过接口泄露实现细节。对于参与者来说，无论资源如何实现，都应以相同的方式访问资源。例如，参与者不应知道一个值是从缓存中返回、通过计算得出，还是从某些外部源新获取的。
- **_不要重复自己原则_**。接口应当提供一组可组合的原语，而不是许多实现相同目标的冗余方式。
一致性是设计清晰接口的一个重要方面。作为架构师，您应该建立并遵循关于资源如何命名、API 参数如何排序以及如何处理错误的约定。当然，并非所有接口都在架构师的控制之下，但在可能的范围内，同一架构的所有元素的接口设计应当保持一致。如果接口遵循底层平台的约定或开发者所期望的编程语言习惯，他们也会很欣赏。然而，一致性不仅仅是赢得开发者的好感，还将有助于最大程度地减少因误解而导致的开发错误数量。

- 对于失败的异步交互，可能会触发诸如超时之类的错误事件。