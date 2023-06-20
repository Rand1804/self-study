# The C++ Programming Language

## PartI Introduction

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

To match the << output operator (**‘‘put to’’**), the >> operator (**‘‘get from’’**) is used for input; cin is the standard input stream.

In declarations, [] means **‘‘array of’’** and ∗ means **‘‘pointer to.’’**

In an expression, prefix unary ∗ means **‘‘contents of’’** and prefix unary & means **‘‘address of.’’**

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

This for-statement can be read as ‘‘set i to zero; while i is not 10, copy the ith element and increment i.’’

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

The first range-for-statement can be read as ‘‘for every element of v, from the first to the last, place a copy in x and print it.’’

```cpp
void increment()
{
    int v[] = {0,1,2,3,4,5,6,7,8,9};
    for (auto& x : v)
        ++x;
    // ...
}
```

In a declaration, the unary suffix & means **‘‘reference to.’’** A reference is similar to a pointer, except that you don’t need to use a prefix ∗ to access the value referred to by the reference. Also, a reference cannot be made to refer to a different object after its initialization.

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

The new operator allocates memory from an area called the free store (also known as dynamic memory and heap;)
