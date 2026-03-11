## Clean Architecture


#### Chap4. STRUCTURED PROGRAMMING

NO GOTO!


#### Chap5. OBJECT-ORIENTED PROGRAMMING

###### ENCAPSULATION

通过釆用封装特性，我们可以把一组相关联的数据和函数圈起来，便圈外的代码只能看见部分函数，数据则完全不可见。譬如在实际应用中，类（class）中的公共函数和私有成员变量就是这样。



point.h

```c
struct Point;
struct Point* makePoint(double x, double y);
double distance (struct Point *p1, struct Point *p2);
```
point.c

```c

#include "point.h"
#include <stdlib.h>
#include <math.h>

struct Point {
  double x,y;
};

struct Point* makepoint(double x, double y) {
  struct Point* p = malloc(sizeof(struct Point));
  p->x = x;
  p->y = y;
  return p;
}

double distance(struct Point* p1, struct Point* p2) {
  double dx = p1->x - p2->x;
  double dy = p1->y - p2->y;
  return sqrt(dx*dx+dy*dy);
}


```

###### INHERITANCE 

简而言之，继承的主要作用是让我们可以在某个作用域内对外部定义的某一组变量与函数进行覆盖。

point.h

```c
struct NamedPoint;

struct NamedPoint* makeNamedPoint(double x, double y, char* name);
void setName(struct NamedPoint* np, char* name);
char* getName(struct NamedPoint* np);

```

point.c

```c
#include "namedPoint.h"
#include <stdlib.h>

struct NamedPoint {
  double x,y;
  char* name;
};

struct NamedPoint* makeNamedPoint(double x, double y, char* name) {
  struct NamedPoint* p = malloc(sizeof(struct NamedPoint));
  p->x = x;
  p->y = y;
  p->name = name;
  return p;
}

void setName(struct NamedPoint* np, char* name) {
  np->name = name;
}

char* getName(struct NamedPoint* np) {
  return np->name;
}

```

main.c

```c
#include "point.h"
#include "namedPoint.h"
#include <stdio.h>

int main(int ac, char** av) {
  struct NamedPoint* origin = makeNamedPoint(0.0, 0.0, "origin");
  struct NamedPoint* upperRight = makeNamedPoint  (1.0, 1.0, "upperRight");
  printf("distance=%f\n",
    distance(
             (struct Point*) origin,
             (struct Point*) upperRight));
}

```


请仔细观察 main 函数，这里 NamedPoint 数据结构是被当作 Point 数据结构的一个衍生体來使用的。之所以可以这样做，是因为 NamedPoint 结构体的前两个成员的顺用与 Point 结构休的完全一致。简单来说，NamedPoint 之所以可以被伪装成 Point 来使用，是因为 NamedPoint 是 Point 结构体的一个超集，同两者共同成员的顺序也是一样的。



###### POLYMORPHISM

```c
#include <stdio.h>

void copy() {
  int c;
  while ((c=getchar()) != EOF)
    putchar(c);
}

```

综上所述，我们认为面向对象编程其实是对程序间接控制权的转移进行了约束


####### DEPENDENCY INVERSION 依赖反转

如你所见，main 函数为了调用高层函数，它就必须能够看到这个函数所在模块。在 C 中，我们会通过 #include 来实现，在 Java 中则通过 import 来实现，而在 C# 中则用的是 using 语句。总之，每个函数的调用方都必须要引用被调用方所在的模块。

事实上，通过利用面向编程语言所提供的这种安全便利的多态实现，无论我们面对怎样的源代码级别的依赖关系，都可以将其反转。

通过这种方法，软件架构师可以完全控制采用了面向对象这种编程方式的系统中所有的源代码依赖关系，而不再受到系统控制流的限制。不管哪个模块调用或者被调用，软件架构师都可以随意更改源代码依赖关系。


What is OO? There are many opinions and many answers to this question. To the software architect, however, the answer is clear: OO is the ability, through the use of polymorphism, to gain absolute control over every source code dependency in the system. It allows the architect to create a plugin architecture, in which modules that contain high-level policies are independent of modules that contain low-level details. The low-level details are relegated to plugin modules that can be deployed and developed independently from the modules that contain high-level policies.

#### Chap6. FUNCTIONAL PROGRAMMING

这句话有点出人意料：函数式编程语言中的变量（Variable）是不可变（Not Vary）的。

为什么不可变性是软件架构设计需要考虑的重点呢？为什么软件架构师要操心变量的可变性呢？答案显而易见：所有的竞争问题、死锁问题、并发更新问题都是由可变变量导致的。如果变量永远不会被更改，那就不可能产生竞争或者并发更新问题。如果锁状态是不可变的，那就永远不会产生死锁问题。


这里的要点是：一个架构设计良好的应用程序应该将状态修改的部分和不需要修改状态的部分隔离成单独的组件，然后用合适的机制来保护可变量。

###### EVENT SOURCING

举个简单的例子，假设某个银行应用程序需要维护客户账户余额信息，当它放行存取款事务时，就要同时负责修改余额记录。如果我们不保存具体账户余额，仅仅保存事务日志，那么当有人想查询账户余额时。我们就将全部交易记录取出，并且每次都得从最开始到当下进行累计。当然，这样的设计就不需要维护任何可变变量了。


This is the idea behind event sourcing.Event sourcing is a strategy wherein we store the transactions, but not the state. When state is required, we simply apply all the transactions from the beginning of time. Of course, we can take shortcuts. For example, we can compute and save the state every midnight. 

Then, when the state information is required, we need compute only the transactions since midnight.

###### CONCLUSION

- Structured programming is discipline imposed upon direct transfer of control.
- Object-oriented programming is discipline imposed upon indirect transfer of control.
- Functional programming is discipline imposed upon variable assignment.

- 结构化编程是对程序控制权的直接转移的限制。
- 面向对象编程是对程序控制权的间接转移的限制。
- 函数式编程是对程序中赋值操作的限制。

Software—the stuff of computer programs—is composed of sequence, selection, iteration, and indirection. Nothing more. Nothing less.


### Part4. DESIGN PRINCIPLES

The goal of the principles is the creation of mid-level software structures that:
- Tolerate change,
- Are easy to understand, and
- Are the basis of components that can be used in many software systems.


在这一部分中，我们会逐章地详细讨论每个设计原则，下面先来做一个简单摘要。

- SRP: The Single Responsibility Principle An active corollary to Conway’s law: The best structure for a software system is heavily influenced by the social structure of the organization that uses it so that each software module has one, and only one, reason to change.
- OCP: The Open-Closed Principle Bertrand Meyer made this principle famous in the 1980s. The gist is that for software systems to be easy to change, they must be designed to allow the behavior of those systems to be changed by adding new code, rather than changing existing code.
- LSP: The Liskov Substitution Principle Barbara Liskov’s famous definition of subtypes, from 1988. In short, this principle says that to build software systems from interchangeable parts, those parts must adhere to a contract that allows those parts to be substituted one for another.
- ISP: The Interface Segregation Principle This principle advises software designers to avoid depending on things that they don’t use.
- DIP: The Dependency Inversion Principle The code that implements high-level policy should not depend on the code that implements low-level details. Rather, details should depend on policies.




- SRP：单一职责原则。 该设计原则是某于康威圧律（Conway's Law）的一个推论——一个软件系统的最佳结构高度依赖于开发这个系统的组织的内部结构。这样，每个软件模块都有且只有一个需要被改变的理由。
- OCP：开闭原则。 该设计原则是由 Bertrand Meyer 在 20 世纪 80 年代大力推广的，其核心要素是：如果软件系统想要更容易被改变，那么其设计就必须允许新增代码来修改系统行为，而非只能靠修改原来的代码。
- LSP：里氏替换原则。 该设计原则是 Barbara Liskov 在 1988 年提出的一个著名的子类型定义。简单来说，这项原则的意思是如果想用可替换的组件来构建软件系统，那么这些组件就必须遵守同一个约定，以便让这些组件可以相互替换。
- ISP：接口隔离原则。 这项设计原则主要告诫软件设计师应该在设计中避免不必要的依赖。
- DIP：依赖反转原则。 该设计原则指出高层策略性的代码不应该依赖实现底层细节的代码，恰恰相反，那些实现底层细节的代码应该依赖高层策略性的代码。


#### Chap7. SRP: THE SINGLE RESPONSIBILITY PRINCIPLE

A module should be responsible to one, and only one, actor.
任何一个软件模块都应该只对某一类行为者负责。

