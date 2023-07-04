# The C++ Programming Language

## 2. A Tour of C++: The Basics

### 2.2 The Basics

When we talk about portability of C++ programs, we usually mean portability of source code; that is, the source code can be successfully compiled and run on a variety of systems.

A *declaration* is a statement that introduces a name into the program. It specifies a type for the
named entity:

- A *type* defines a set of possible values and a set of operations (for an object).
- An *object* is some memory that holds a value of some type.
- A *value* is a set of bits interpreted according to a type.
- A *variable* is a named object.

A char variable is of the natural size to hold a character on a given machine (typically an 8-bit byte), and the sizes of other types are quoted in multiples of the size of a char.

- bool      1
- char      1
- int       4
- double    8

Don’t introduce a name until you have a suitable value for it.

> To match the << output operator (**‘‘put to’’**), the >> operator (**‘‘get from’’**) is used for input; cin is the standard input stream.

> In declarations, [] means **‘‘array of’’** and ∗ means **‘‘pointer to.’’**

> In an expression, prefix unary ∗ means **‘‘contents of’’** and prefix unary & means **‘‘address of.’’**

```cpp
void copy_fct()
{
    int v1[10] = {0,1,2,3,4,5,6,7,8,9};
    int v2[10]; // to become a copy of v1
    for (auto i=0; i!=10; ++i) // copy elements
        v2[i]=v1[i];
    // ...
}
```

> This for-statement can be read as ‘‘set i to zero; while i is not 10, copy the ith element and increment i.’’

```cpp
void print()
{
    int v[] = {0,1,2,3,4,5,6,7,8,9};
    for (auto x : v) // for each x in v
        cout << x << '\n';
    for (auto x : {10,21,32,43,54,65})
        cout << x << '\n';
    // ...
}
```

> The first range-for-statement can be read as ‘‘for every element of v, from the first to the last, place a copy in x and print it.’’

```cpp
void increment()
{
    int v[] = {0,1,2,3,4,5,6,7,8,9};
    for (auto& x : v)
        ++x;
    // ...
}
```

> In a declaration, the unary suffix & means **‘‘reference to.’’** A reference is similar to a pointer, except that you don’t need to use a prefix ∗ to access the value referred to by the reference. Also, a reference cannot be made to refer to a different object after its initialization.

When used in declarations,operators (such as &, ∗, and []) are called *declarator operators*:

```cpp
T a[n]; // T[n]: array of n Ts (§7.3)
T∗ p; // T*: pointer to T (§7.2)
T& r; // T&: reference to T (§7.7)
T f(A); // T(A): function taking an argument of type A returning a result of type T (§2.2.1)
```

we give the pointer the value **nullptr** (‘‘the null pointer’’). There is only one nullptr shared by all pointer types:

```cpp
double∗ pd = nullptr;
Link<Record>∗ lst = nullptr; // pointer to a Link to a Record
int x = nullptr; // error : nullptr is a pointer not an integer
```

However, using *nullptr* eliminates potential confusion between integers (such as 0 or NULL) and pointers (such as nullptr).

### 2.3 User-Defined Types

We call the types that can be built from the fundamental types, the const modifier, and the declarator operators *built-in types*.

> The **new** operator allocates memory from an area called the free store (also known as dynamic memory and heap;)

```cpp
void f(Vector v, Vector& rv, Vector∗ pv)
{
    int i1 = v.sz; // access through name
    int i2 = rv.sz; // access through reference
    int i4 = pv−>sz; // access through pointer
}
```

> We use `.` (dot) to access struct members through a name (and through a reference) and `−>` to access struct members through a pointer.

To do that we have to distinguish between the interface to a type (to be used by all) and its implementation (which has access to the otherwise inaccessible data).

The language mechanism for that is called a **class**. A class is defined to have a set of members, which can be data, function, or type members. The interface is defined by the **public** members of a class, and **private** members are accessible only through that interface. For example:

```cpp
class Vector {
    public:
        Vector(int s) :elem{new double[s]}, sz{s} { } // construct a Vector
        double& operator[](int i) { return elem[i]; } // element access: subscripting
        int size() { return sz; }
    private:
        double∗ elem; // pointer to the elements
        int sz; // the number of elements
};
```

Basically, the Vector object is a ‘‘handle’’ containing a pointer to the elements (elem) plus the number of elements (sz).

However, the Vector object itself is always the same size. This is the basic technique for handling varying amounts of information in C++: a fixed-size handle referring to a variable amount of data ‘‘elsewhere’’ (e.g., on the free store allocated by new; §11.2).

> A ‘‘function’’ with the same name as its class is called a **constructor**, that is, a function used to construct objects of a class.

Unlike an ordinary function, a constructor is guaranteed to be used to initialize objects of its class. Thus, defining a constructor eliminates the problem of uninitialized variables for a class.

The constructor initializes the Vector members using **a member initializer list**:

```cpp
Vector(int s) :elem{new double[s]}, sz{s} { }
```

That is, we first initialize elem with a pointer to s elements of type double obtained from the free store. Then, we initialize sz to s.

Access to elements is provided by **a subscript function**, called operator[]. It returns a reference to the appropriate element (a double&).

This declaration would be placed in a file Vector.h, and users will *include* that file, called a *header file*, to access that interface.

### 2.4.3.1 Exceptions

The **out_of_range** type is defined in the standard library and is in fact used by some standard-library container access functions.

### 2.6 Advice

[1] Don’t panic! All will become clear in time; §2.1.
[2] You don’t hav e to know every detail of C++ to write good programs; §1.3.1.
[3] Focus on programming techniques, not on language features; §2.1.

## 3. A Tour of C++: Abstraction Mechanisms

```cpp
class Vector {
    private:
        double∗ elem; // elem points to an array of sz doubles
        int sz;
    public:
        Vector(int s) :elem{new double[s]}, sz{s} // constructor: acquire resources
        {
            for (int i=0; i!=s; ++i) elem[i]=0; // initialize elements
        }

        ˜Vector() { delete[] elem; } // destructor: release resources
        
        double& operator[](int i);
        int size() const;
};
```

> We need a mechanism to ensure that the memory allocated by the constructor is deallocated; that mechanism is a **destructor**: The name of a destructor is the complement operator, ˜, followed by the name of the class; it is the complement of a constructor.

This handle-to-data model is very commonly used to manage data that can vary in size during the lifetime of an object. The technique of acquiring resources in a constructor and releasing them in a destructor, known as Resource Acquisition Is Initialization or RAII, allows us to eliminate ‘‘naked new operations,’’ that is, to avoid allocations in general code and keep them buried inside the implementation of well-behaved abstractions.

## 6. Types and Declarations

### 6.2 Types

The Boolean, character, and integer types are collectively called **integral types**. The integral and floating-point types are collectively called **arithmetic types**. Enumerations and classes (Chapter 16) are called **user-defined** types because they must be defined by users rather than being available for use without previous declaration, the way fundamental types are. In contrast, fundamental types, pointers, and references are collectively referred to as **built-in types**. The standard library provides many user-defined types.

## 7 Pointers, Arrays, and References

```cpp
void f(int∗ pi)
{
    void∗ pv = pi; // ok: implicit conversion of int* to void*
    ∗pv; // error: can’t dereference void*
    ++pv; // error: can’t increment void* (the size of the object pointed to is unknown)
    int∗ pi2 = static_cast<int∗>(pv);// explicit conversion back to int*
    double∗ pd1 = pv; // error
    double∗ pd2 = pi; // error
    double∗ pd3 = static_cast<double∗>(pv); // unsafe (§11.5.2)
    
}
```

Taking a pointer to the element **one beyond the end** of an array is guaranteed to work. This is important for many algorithms (§4.5, §33.1). However, since such a pointer does not in fact point to an element of the array, it may not be used for reading or writing. The result of taking the address of the element before the initial element or beyond one-past-the-last element is undefined and should be avoided. For example:

```cpp
int∗ p4 = v−1; // before the beginning, undefined: don’t do it
int∗ p5 = v+7; // beyond the end, undefined: don’t do it
```

The implicit conversion of an array name to a pointer to the initial element of the array is extensively used in function calls in C-style code. For example:

```cpp
extern "C" int strlen(const char∗); // from <string.h>
void f()
{
    char v[] = "Annemarie";
    char∗ p = v; // implicit conversion of char[] to char*
    strlen(p);
    strlen(v); // implicit conversion of char[] to char*
    v = p; // error: cannot assign to array
}
```

The implicit conversion of the array argument to a pointer means that the size of the array is lost to the called function.

Subscripting a built-in array is defined in terms of the pointer operations + and ∗. For every built-in array a and integer j within the range of a, we have:
`a[j] == ∗(&a[0]+j) == ∗(a+j) == ∗(j+a) == j[a]`

When using a pointer, two objects are involved: the pointer itself and the object pointed to. ‘‘Prefixing’’ a declaration of a pointer with const makes the object, but not the pointer, a constant. To declare a pointer itself, rather than the object pointed to, to be a constant, we use the declarator operator `∗const` instead of plain `∗`. For example:

```cpp
void f1(char∗ p)
{
    char s[] = "Gorm"; 

    const char∗ pc = s; // pointer to constant
    pc[3] = 'g'; // error : pc points to constant
    pc = p;     // OK
    

    char ∗const cp = s; // constant pointer
    cp[3] = 'a'; // OK
    cp = p; // error : cp is constant


    const char ∗const cpc = s; // const pointer to const
    cpc[3] = 'a'; // error : cpc points to constant
    cpc = p; // error : cpc is constant
}
```

The declarator operator that makes a pointer constant is ∗const. There is no const∗ declarator operator, so a const appearing before the ∗ is taken to be part of the base type.