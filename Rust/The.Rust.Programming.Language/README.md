# [The Rust Programming Language](https://doc.rust-lang.org/book/title-page.html "The Rust Programming Language")

## Chapter03 Common Programming Concepts

In Rust, the return value of the function is synonymous with the value of the final expression in the block of the body of a function.

The tuple without any values has a special name, **unit**. This value and its corresponding type are both written () and represent an empty value or an empty return type. Expressions implicitly return the unit value if they don’t return any other value.

## Chapter04 Understanding Ownership

When a variable goes out of scope, Rust calls a special function for us. This function is called drop

In addition, there’s a design choice that’s implied by this: **Rust will never automatically create “deep” copies of your data**.Therefore, any automatic copying can be assumed to be inexpensive in terms of runtime performance.

When a variable that *includes data on the heap* goes out of scope, the value will be cleaned up by drop unless ownership of the data has been moved to another variable.

We also cannot have a mutable reference while we have an immutable one to the same value.

Recall from the borrowing rules that if we have an immutable reference to something, we cannot also take a mutable reference.

The type of s here is &str: it’s a slice pointing to that specific point of the binary. This is also why string literals are immutable; &str is an immutable reference.

## Chapter05 Using Structs to Structure Related Data

Rust has a feature called automatic referencing and dereferencing. When you call a method with object.something(), Rust automatically adds in &, &mut, or * so object matches the signature of the method.

## Chapter06 Enums and Pattern Matching

Rust also has a pattern we can use when we want a catch-all but don’t want to use the value in the catch-all pattern: `_`is a special pattern that matches any value and does not bind to that value. This tells Rust we aren’t going to use the value, so Rust won’t warn us about an unused variable.

## Chapter08 Common Collections

This error is due to the way vectors work: because vectors put the values next to each other in memory, adding a new element onto the end of the vector might require allocating new memory and copying the old elements to the new space, if there isn’t enough room to put all the elements next to each other where the vector is currently stored.

Many of the same operations available with `Vec<T>` are available with String as well, because String is actually implemented as a wrapper around a vector of bytes with some extra guarantees, restrictions, and capabilities.

For that, we use the to_string method, which is available on any type that implements the Display trait, as string literals do.

The reason s1 is no longer valid after the addition, and the reason we used a reference to s2, has to do with the signature of the method that’s called when we use the + operator. The + operator uses the add method, whose signature looks something like this:

```rust
let s3 = s1 + &s2;
fn add(self, s: &str) -> String {}
```

The reason we’re able to use &s2 in the call to add is that the compiler can coerce the &String argument into a &str.When we call the add method, Rust uses a deref coercion, which here turns &s2 into &s2[..].**This statement actually takes ownership of s1, appends a copy of the contents of s2, and then returns ownership of the result.**

A final reason Rust doesn’t allow us to index into a String to get a character is that indexing operations are expected to always take constant time (O(1)).

Like vectors, hash maps are homogeneous: all of the keys must have the same type as each other, and all of the values must have the same type.

## Chapter09 Error Handling

By default, when a panic occurs, the program starts unwinding, which means Rust walks back up the stack and cleans up the data from each function it encounters.

## Chapter10 Generic Types, Traits, and Lifetimes

*When we use a parameter in the body of the function, we have to declare the parameter name in the signature so the compiler knows what that name means. Similarly, when we use a type parameter name in a function signature, we have to declare the type parameter name before we use it.*

Note that we have to declare T just after impl so we can use T to specify that we’re implementing methods on the type `Point<T>`. By declaring T as a generic type after impl, Rust can identify that the type in the angle brackets in Point is a generic type rather than a concrete type.

The generic `Option<T>` is replaced with the specific definitions created by the compiler. Because Rust compiles generic code into code that specifies the type in each instance, we pay no runtime cost for using generics.

But we can’t implement external traits on external types. For example, we can’t implement the Display trait on `Vec<T>` within our aggregator crate, because Display and `Vec<T>` are both defined in the standard library and aren’t local to our aggregator crate.

The impl Trait syntax lets you concisely specify that a function returns some type that implements the Iterator trait without needing to write out a very long type.However, you can only use impl Trait if you’re returning a single type.Returning either a NewsArticle or a Tweet isn’t allowed due to restrictions around how the impl Trait syntax is implemented in the compiler.

We can also conditionally implement a trait for any type that implements another trait. Implementations of a trait on any type that satisfies the trait bounds are called blanket implementations and are extensively used in the Rust standard library.For example, the standard library implements the ToString trait on any type that implements the Display trait.The impl block in the standard library looks similar to this code:

```rust
impl<T: Display> ToString for T {
    // --snip--
}
```

In practice, it means that the lifetime of the reference returned by the longest function is the same as the smaller of the lifetimes of the values referred to by the function arguments.

Remember, when we specify the lifetime parameters in this function signature, we’re not changing the lifetimes of any values passed in or returned. Rather, we’re specifying that the borrow checker should reject any values that don’t adhere to these constraints.

The compiler uses three rules to figure out the lifetimes of the references when there aren’t explicit annotations. The first rule applies to input lifetimes, and the second and third rules apply to output lifetimes.

**The first rule** is that the compiler assigns a lifetime parameter to each parameter that’s a reference. In other words, a function with one parameter gets one lifetime parameter: fn foo<'a>(x: &'a i32); a function with two parameters gets two separate lifetime parameters: fn foo<'a, 'b>(x: &'a i32, y: &'b i32); and so on.

**The second rule** is that, if there is exactly one input lifetime parameter, that lifetime is assigned to all output lifetime parameters: fn foo<'a>(x: &'a i32) -> &'a i32.

**The third rule** is that, if there are multiple input lifetime parameters, but one of them is &self or &mut self because this is a method, the lifetime of self is assigned to all output lifetime parameters. This third rule makes methods much nicer to read and write because fewer symbols are necessary.

```rust
pub fn notify(item: &(impl Summary + Display)) {}

pub fn notify<T: Summary + Display>(item: &T) {}

fn some_function<T: Display + Clone, U: Clone + Debug>(t: &T, u: &U) -> i32 {}

fn some_function<T, U>(t: &T, u: &U) -> i32
where
    T: Display + Clone,
    U: Clone + Debug,
{}

fn returns_summarizable() -> impl Summary {}
```

## Chapter11 Writing Automated Tests

 The derive attribute generates code that will implement a trait with its own default implementation on the type you’ve annotated with the derive syntax.

 The default behavior of the binary produced by cargo test is to run all the tests in parallel and capture output generated during test runs, preventing the output from being displayed and making it easier to read the output related to the test results.

 The #[cfg(test)] annotation on the tests module tells Rust to compile and run the test code only when you run cargo test, not when you run cargo build.The attribute cfg stands for configuration and tells Rust that the following item should only be included given a certain configuration option.

 As a result, the Rust community has developed guidelines for splitting the separate concerns of a binary program when main starts getting large. This process has the following steps:

- Split your program into a main.rs and a lib.rs and move your program’s logic to lib.rs.
- As long as your command line parsing logic is small, it can remain in main.rs.
- When the command line parsing logic starts getting complicated, extract it from main.rs and move it to lib.rs.

The responsibilities that remain in the main function after this process should be limited to the following:

- Calling the command line parsing logic with the argument values
- Setting up any other configuration
- Calling a run function in lib.rs
- Handling the error if run returns an error

## Chapter13 Functional Language Features: Iterators and Closures

The way a closure captures and handles values from the environment affects which traits the closure implements, and traits are how functions and structs can specify what kinds of closures they can use. Closures will automatically implement one, two, or all three of these Fn traits, in an additive fashion, depending on how the closure’s body handles the values:

1. FnOnce applies to closures that can be called once. All closures implement at least this trait, because all closures can be called. A closure that moves captured values out of its body will only implement FnOnce and none of the other Fn traits, because it can only be called once.
2. FnMut applies to closures that don’t move captured values out of their body, but that might mutate the captured values. These closures can be called more than once.
3. Fn applies to closures that don’t move captured values out of their body and that don’t mutate captured values, as well as closures that capture nothing from their environment. These closures can be called more than once without mutating their environment, which is important in cases such as calling a closure multiple times concurrently.

Each call to next eats up an item from the iterator. We didn’t need to make v1_iter mutable when we used a for loop because the loop took ownership of v1_iter and made it mutable behind the scenes.

## Chapter15 Smart Pointers

Rust, with its concept of ownership and borrowing, has an additional difference between references and smart pointers: while references only borrow data, in many cases, smart pointers own the data they point to.

**Boxes** don’t have performance overhead, other than storing their data on the heap instead of on the stack. But they don’t have many extra capabilities either. You’ll use them most often in these situations:

- When you have a type whose size can’t be known at compile time and you want to use a value of that type in a context that requires an exact size
- When you have a large amount of data and you want to transfer ownership but ensure the data won’t be copied when you do so
- When you want to own a value and you care only that it’s a type that implements a particular trait rather than being of a specific type

```rust
*(y.deref())
```

The reason the deref method returns a reference to a value, and that the plain dereference outside the parentheses in *(y.deref()) is still necessary, is to do with the ownership system. If the deref method returned the value directly instead of a reference to the value, the value would be moved out of self. We don’t want to take ownership of the inner value inside `MyBox<T>` in this case or in most cases where we use the dereference operator.
Note that the `*` operator is replaced with a call to the deref method and then a call to the `*` operator just once, each time we use a `*` in our code. Because the substitution of the `*` operator does not recurse infinitely, we end up with data of type i32, which matches the 5 in assert_eq! in Listing 15-9.

Deref coercion is a convenience Rust performs on arguments to functions and methods, and works only on types that implement the Deref trait. It happens automatically when we pass a reference to a particular type’s value as an argument to a function or method that doesn’t match the parameter type in the function or method definition. A sequence of calls to the deref method converts the type we provided into the type the parameter needs.

When the Deref trait is defined for the types involved, Rust will analyze the types and use Deref::deref as many times as necessary to get a reference to match the parameter’s type. The number of times that Deref::deref needs to be inserted is **resolved at compile time**, so there is no runtime penalty for taking advantage of deref coercion!

Similar to how you use the Deref trait to override the `*` operator on immutable references, you can use the DerefMut trait to override the `*` operator on mutable references.
Rust does deref coercion when it finds types and trait implementations in three cases:

- From &T to &U when T: Deref<Target=U>
- From &mut T to &mut U when T: DerefMut<Target=U>
- From &mut T to &U when T: Deref<Target=U>

In Rust, you can specify that a particular bit of code be run whenever a value goes out of scope, and the compiler will insert this code automatically.

This error message states that we’re not allowed to explicitly call drop. The error message uses the term destructor, which is the general programming term for a function that cleans up an instance. A destructor is analogous to a constructor, which creates an instance. The drop function in Rust is one particular destructor.Rust doesn’t let us call drop explicitly because Rust would still automatically call drop on the value at the end of main. This would cause a double free error because Rust would be trying to clean up the same value twice.We can’t disable the automatic insertion of drop when a value goes out of scope, and we can’t call the drop method explicitly. So, if we need to force a value to be cleaned up early, we use the std::mem::drop function.

You have to enable multiple ownership explicitly by using the Rust type Rc, which is an abbreviation for reference counting.

Note that Rc is only for use in single-threaded scenarios. When we discuss concurrency in Chapter 16, we’ll cover how to do reference counting in multithreaded programs.

In Rust, you can specify that a particular bit of code be run whenever a value goes out of scope, and the compiler will insert this code automatically.

This error message states that we’re not allowed to explicitly call drop. The error message uses the term *destructor*, which is the general programming term for a function that cleans up an instance. A destructor is analogous to a *constructor*, which creates an instance. The drop function in Rust is one particular destructor.Rust doesn’t let us call drop explicitly because Rust would still automatically call drop on the value at the end of main. This would cause a double free error because Rust would be trying to clean up the same value twice.We can’t disable the automatic insertion of drop when a value goes out of scope, and we can’t call the drop method explicitly. So, if we need to force a value to be cleaned up early, we use the std::mem::drop function.

You have to enable multiple ownership explicitly by using the Rust type `Rc<T>`, which is an abbreviation for reference counting.

Note that `Rc<T>` is only for use in single-threaded scenarios. When we discuss concurrency in Chapter 16, we’ll cover how to do reference counting in multithreaded programs.

We could have called a.clone() rather than Rc::clone(&a), but Rust’s convention is to use Rc::clone in this case. The implementation of Rc::clone doesn’t make a deep copy of all the data like most types’ implementations of clone do. The call to Rc::clone only increments the reference count, which doesn’t take much time.

Interior mutability is a design pattern in Rust that allows you to mutate data even when there are immutable references to that data; normally, this action is disallowed by the borrowing rules.

Here is a recap of the reasons to choose `Box<T>`, `Rc<T>`, or `RefCell<T>`:

- `Rc<T>` enables multiple owners of the same data; `Box<T>` and `RefCell<T>` have single owners.
- `Box<T>` allows immutable or mutable borrows checked at compile time; `Rc<T>` allows only immutable borrows checked at compile time;`RefCell<T>`allows immutable or mutable borrows checked at runtime.
- Because `RefCell<T>` allows mutable borrows checked at runtime, you can mutate the value inside the `RefCell<T>` even when the `RefCell<T>` is immutable.

The `RefCell<T>` keeps track of how many `Ref<T>` and `RefMut<T>` smart pointers are currently active. Every time we call borrow, the `RefCell<T>` increases its count of how many immutable borrows are active. When a `Ref<T>` value goes out of scope, the count of immutable borrows goes down by one. Just like the compile-time borrowing rules, `RefCell<T>` lets us have many immutable borrows or one mutable borrow at any point in time.

If you have `RefCell<T>` values that contain `Rc<T>` values or similar nested combinations of types with interior mutability and reference counting, you must ensure that you don’t create cycles; you can’t rely on Rust to catch them.

Strong references are how you can share ownership of an `Rc<T>` instance. Weak references don’t express an ownership relationship, and their count doesn’t affect when an `Rc<T>` instance is cleaned up.

Because the value that `Weak<T>` references might have been dropped, to do anything with the value that a `Weak<T>` is pointing to, you must make sure the value still exists. Do this by calling the upgrade method on a `Weak<T>` instance, which will return an `Option<Rc<T>>`. You’ll get a result of Some if the `Rc<T>` value has not been dropped yet and a result of None if the `Rc<T>` value has been dropped. Because upgrade returns an `Option<Rc<T>>`, Rust will ensure that the Some case and the None case are handled, and there won’t be an invalid pointer.

## Chapter16 Fearless Concurrency

A channel is said to be closed if either the transmitter or receiver half is dropped.

Mutex is an abbreviation for mutual exclusion, as in, a mutex allows only one thread to access some data at any given time.

Mutexes have a reputation for being difficult to use because you have to remember two rules:

- You must attempt to acquire the lock before using the data.
- When you’re done with the data that the mutex guards, you must unlock the data so other threads can acquire the lock.

As you might suspect, `Mutex<T>` is a smart pointer. More accurately, the call to lock returns a smart pointer called MutexGuard, wrapped in a LockResult that we handled with the call to unwrap. The MutexGuard smart pointer implements Deref to point at our inner data; the smart pointer also has a Drop implementation that releases the lock automatically when a MutexGuard goes out of scope, which happens at the end of the inner scope.

When `Rc<T>` manages the reference count, it adds to the count for each call to clone and subtracts from the count when each clone is dropped. But it doesn’t use any concurrency primitives to make sure that changes to the count can’t be interrupted by another thread. This could lead to wrong counts—subtle bugs that could in turn lead to memory leaks or a value being dropped before we’re done with it. What we need is a type exactly like `Rc<T>` but one that makes changes to the reference count in a thread-safe way.

Fortunately, `Arc<T>` is a type like `Rc<T>` that is safe to use in concurrent situations. The a stands for atomic, meaning it’s an atomically reference counted type. *Atomics* are an additional kind of concurrency primitive that we won’t cover in detail here: see the standard library documentation for `std::sync::atomic` for more details. At this point, you just need to know that atomics work like primitive types but are safe to share across threads.

The Send marker trait indicates that ownership of values of the type implementing Send can be transferred between threads. Almost every Rust type is Send, but there are some exceptions, including `Rc<T>`: this cannot be Send because if you cloned an `Rc<T>` value and tried to transfer ownership of the clone to another thread, both threads might update the reference count at the same time. For this reason, `Rc<T>` is implemented for use in single-threaded situations where you don’t want to pay the thread-safe performance penalty.

Any type composed entirely of Send types is automatically marked as Send as well. Almost all primitive types are Send, aside from raw pointers, which we’ll discuss in Chapter 19.

The Sync marker trait indicates that it is safe for the type implementing Sync to be referenced from multiple threads. In other words, any type T is Sync if &T (an immutable reference to T) is Send, meaning the reference can be sent safely to another thread. Similar to Send, primitive types are Sync, and types composed entirely of types that are Sync are also Sync.

## Chapter17 Object-Oriented Programming Features of Rust

Arguably, OOP languages share certain common characteristics, namely objects, encapsulation, and inheritance.

Object-oriented programs are made up of objects. An object packages both data and the procedures that operate on that data. The procedures are typically called methods or operations.

Another aspect commonly associated with OOP is the idea of *encapsulation*, which means that the implementation details of an object aren’t accessible to code using that object. Therefore, the only way to interact with an object is through its public API; code using the object shouldn’t be able to reach into the object’s internals and change data or behavior directly. This enables the programmer to change and refactor an object’s internals without needing to change the code that uses the object.

*Inheritance* is a mechanism whereby an object can inherit elements from another object’s definition, thus gaining the parent object’s data and behavior without you having to define them again.

You would choose inheritance for two main reasons. One is for reuse of code: you can implement particular behavior for one type, and inheritance enables you to reuse that implementation for a different type. You can do this in a limited way in Rust code using default trait method implementations.

The other reason to use inheritance relates to the type system: to enable a child type to be used in the same places as the parent type. This is also called *polymorphism*, which means that you can substitute multiple objects for each other at runtime if they share certain characteristics.

This vector is of type `Box<dyn Draw>`, which is a trait object; it’s a stand-in for any type inside a Box that implements the Draw trait.

The advantage of using trait objects and Rust’s type system to write code similar to code using duck typing is that we never have to check whether a value implements a particular method at runtime or worry about getting errors if a value doesn’t implement a method but we call it anyway. Rust won’t compile our code if the values don’t implement the traits that the trait objects need.

We need to set `state` to `None` temporarily rather than setting it directly with code like `self.state = self.state.request_review();` to get ownership of the `state` value. This ensures `Post` can’t use the old `state` value after we’ve transformed it into a new state.

One downside of the state pattern is that, because the states implement the transitions between states, some of the states are coupled to each other. If we add another state between `PendingReview` and `Published`, such as `Scheduled`, we would have to change the code in `PendingReview` to transition to Scheduled instead.

Another downside is that we’ve duplicated some logic.

## Chapter18 Patterns and Matching

Rust compares the expression against the pattern and assigns any names it finds. So in the `let x = 5;` example, `x` is a pattern that means “bind what matches here to the variable `x`.” Because the name `x` is the whole pattern, this pattern effectively means “bind everything to the variable `x`, whatever the value is.

*refutable* and *irrefutable*

- Patterns that will match for any possible value passed are *irrefutable*
- Patterns that can fail to match for some possible value are refutable.

Function parameters, let statements, and for loops can only accept irrefutable patterns, because the program cannot do anything meaningful when values don’t match. The if let and while let expressions accept refutable and irrefutable patterns, but the compiler warns against irrefutable patterns because by definition they’re intended to handle possible failure: the functionality of a conditional is in its ability to perform differently depending on success or failure.

Rust allows us to use an irrefutable pattern in a `match` with only one arm, but this syntax isn’t particularly useful and could be replaced with a simpler `let` statement.

**The syntax `_x` still binds the value to the variable, whereas `_` doesn’t bind at all.**

**The downside of this additional expressiveness is that the compiler doesn't try to check for exhaustiveness when match guard expressions are involved.**

```rust
    let x = 4;
    let y = false;

    match x {
        4 | 5 | 6 if y => println!("yes"),
        _ => println!("no"),
    }
```

The important part of this example is that the if y match guard applies to 4, 5, and 6, even though it might look like if y only applies to 6.

## Chapter19 Advanced Features

Those superpowers include the ability to:

- Dereference a raw pointer
- Call an unsafe function or method
- Access or modify a mutable static variable
- Implement an unsafe trait
- Access fields of `union`s

Different from references and smart pointers, raw pointers:

- Are allowed to ignore the borrowing rules by having both immutable and mutable pointers or multiple mutable pointers to the same location
- Aren't guaranteed to point to valid memory
- Are allowed to be null
- Don't implement any automatic cleanup

For this, Rust has the keyword extern that facilitates the creation and use of a *Foreign Function Interface* (FFI).

The "C" part defines which *application binary interface* (ABI) the external function uses: the ABI defines how to call the function at the assembly level.

A subtle difference between constants and immutable static variables is that values in a static variable have a fixed address in memory. Using the value will always access the same data. Constants, on the other hand, are allowed to duplicate their data whenever they’re used. Another difference is that static variables can be mutable. Accessing and modifying mutable static variables is unsafe.

*Associated types* connect a type placeholder with a trait such that the trait method definitions can use these placeholder types in their signatures.

```rust
trait Add<Rhs=Self> {
    type Output;

    fn add(self, rhs: Rhs) -> Self::Output;
}
```

The new part is Rhs=Self: this syntax is called **default type parameters**. The Rhs generic type parameter (short for **“right hand side”**) defines the type of the rhs parameter in the add method.

You’ll use default type parameters in two main ways:

- To extend a type without breaking existing code
- To allow customization in specific cases most users won’t need

```rust
<Type as Trait>::function(receiver_if_method, next_arg, ...);
```

For associated functions that aren’t methods, there would not be a receiver: there would only be the list of other arguments.

We mentioned the orphan rule that states we’re only allowed to implement a trait on a type if either the trait or the type are local to our crate. It’s possible to get around this restriction using the newtype pattern, which involves creating a new type in a tuple struct.

*thunk* is a word for code to be evaluated at a later time, so it’s an appropriate name for a closure that gets stored.

Functions that return never are called *diverging functions*.

The formal way of describing this behavior is that expressions of type ! can be coerced into any other type.

Rust needs to know how much memory to allocate for any value of a particular type, and **all values of a type must use the same amount of memory.**

DSTs: dynamically sized types

As such, we can know the size of a &str value at compile time: it’s twice the length of a usize. That is, we always know the size of a &str, no matter how long the string it refers to is. In general, this is the way in which dynamically sized types are used in Rust: they have an extra bit of metadata that stores the size of the dynamic information. The golden rule of dynamically sized types is that we must always put values of dynamically sized types behind a pointer of some kind.

Unlike closures, fn is a type rather than a trait, so we specify fn as the parameter type directly rather than declaring a generic type parameter with one of the Fn traits as a trait bound.

```rust
impl<T> Option<T> {
    pub fn unwrap_or_else<F>(self, f: F) -> T
    where
        F: FnOnce() -> T
    {
        match self {
            Some(x) => x,
            None => f(),
        }
    }
}
```

The term macro refers to a family of features in Rust: declarative macros with `macro_rules!` and three kinds of procedural macros:

- Custom #[derive] macros that specify code added with the derive attribute used on structs and enums
- Attribute-like macros that define custom attributes usable on any item
- Function-like macros that look like function calls but operate on the tokens specified as their argument

Fundamentally, macros are a way of writing code that writes other code, which is known as *metaprogramming*.

The `#[macro_export]` annotation indicates that this macro should be made available whenever the crate in which the macro is defined is brought into scope. Without this annotation, the macro can’t be brought into scope.

```rust
#[macro_export]
macro_rules! vec {
    ( $( $x:expr ),* ) => {
        {
            let mut temp_vec = Vec::new();
            $(
                temp_vec.push($x);
            )*
            temp_vec
        }
    };
}
```

Valid pattern syntax in macro definitions is different than the pattern syntax covered in Chapter 18 because macro patterns are matched against Rust code structure rather than values.

We use a dollar sign (`$`) to declare a variable in the macro system that will contain the Rust code matching the pattern. The dollar sign makes it clear this is a macro variable as opposed to a regular Rust variable.

**Attributes** are metadata about pieces of Rust code; one example is the derive attribute we used with structs in Chapter 5. To change a function into a test function, add `#[test]` on the line before fn. When you run your tests with the cargo test command, Rust builds a test runner binary that runs the annotated functions and reports on whether each test function passes or fails.

*Procedural macros* accept some code as an input, operate on that code, and produce some code as an output rather than matching against patterns and replacing the code with other code as declarative macros do.The three kinds of procedural macros are custom derive, attribute-like, and function-like, and all work in a similar fashion.

The hello_macro_derive function will be called when a user of our library specifies #[derive(HelloMacro)] on a type. This is possible because we’ve annotated the hello_macro_derive function here with proc_macro_derive and specified the name HelloMacro, which matches our trait name; this is the convention most procedural macros follow.

The TokenStream type is defined by the proc_macro crate that is included with Rust and represents a sequence of tokens. This is the core of the macro: the source code that the macro is operating on makes up the input TokenStream, and the code the macro produces is the output TokenStream. The function also has an attribute attached to it that specifies which kind of procedural macro we’re creating.
The returned TokenStream is added to the code that our crate users write, so when they compile their crate, they’ll get the extra functionality that we provide in the modified TokenStream.

Using stringify! also saves an allocation by converting #name to a string literal at compile time.

They’re also more flexible: derive only works for structs and enums; attributes can be applied to other items as well, such as functions.

```rust
#[route(GET, "/")]
fn index() {}
```

The signature of the macro definition function would look like this:

```rust
#[proc_macro_attribute]
pub fn route(attr: TokenStream, item: TokenStream) -> TokenStream {}
```

Here, we have two parameters of type TokenStream. The first is for the contents of the attribute: the `GET`, `"/"` part. The second is the body of the item the attribute is attached to: in this case, `fn index() {}` and the rest of the function’s body.

Function-like macros define macros that look like function calls. Similarly to macro_rules! macros, they’re more flexible than functions; for example, they can take an unknown number of arguments.

```rust
let sql = sql!(SELECT * FROM posts WHERE id=1);
```

This macro would parse the SQL statement inside it and check that it’s syntactically correct, which is much more complex processing than a macro_rules! macro can do.

```rust
#[proc_macro]
pub fn sql(input: TokenStream) -> TokenStream {}
```

## Final Project: Building a Multithreaded Web Server

Connecting to port 80 requires administrator privileges (nonadministrators can listen only on ports higher than 1023).

The reason we might receive errors from the incoming method when a client connects to the server is that we’re not actually iterating over connections. Instead, we’re iterating over **connection attempts**. The connection might not be successful for a number of reasons, many of them operating system specific. For example, many operating systems have a limit to the number of simultaneous open connections they can support; new connection attempts beyond that number will produce an error until some of the open connections are closed.

BufReader adds buffering by managing calls to the std::io::Read trait methods for us.

We need to explicitly match on a slice of request_line to pattern match against the string literal values; match doesn’t do automatic referencing and dereferencing like the equality method does.

The F type parameter also has the trait bound Send and the lifetime bound 'static, which are useful in our situation: we need Send to transfer the closure from one thread to another and 'static because we don’t know how long the thread will take to execute.

```rust
impl ThreadPool {
    // --snip--
    pub fn execute<F>(&self, f: F)
    where
        F: FnOnce() + Send + 'static,
    {
    }
}
```

We still use the () after FnOnce because this FnOnce represents a closure that takes no parameters and returns the unit type (). Just like function definitions, the return type can be omitted from the signature, but even if we have no parameters, we still need the parentheses.

The with_capacity function performs the same task as Vec::new but with an important difference: it preallocates space in the vector. Because we know we need to store size elements in the vector, doing this allocation up front is slightly more efficient than using Vec::new, which resizes itself as elements are inserted.

**Note that if the JoinHandle is dropped (i.e., it goes out of scope and is not explicitly joined), then the associated thread will be detached, meaning that it can continue running even if the main thread has finished execution. If the main thread finishes execution before the detached thread, then the process will exit and the detached thread will also stop running.**
> A detached thread runs independently of the main thread. Once it's started, it cannot be joined (i.e., you cannot wait for its termination). When a detached thread finishes execution, its resources are automatically released back to the system. Detached threads are useful when you want a task to run in the background without needing to manage or communicate with it further.
> On the other hand, an undetached (or joinable) thread can be joined by another thread. "Joining" a thread means waiting for it to finish execution. You might want to join a thread if you need to wait for a result it's computing, or if you need to ensure that some action has been completed before proceeding. If a joinable thread finishes execution but is not joined, its state remains (it becomes a "zombie") and its resources are not released back to the system until it is joined.
> In Rust, all threads are joinable by default. When you spawn a thread, you get a JoinHandle that you can call join on to wait for the thread to finish. If you drop the JoinHandle without calling join, the thread becomes detached.

```rust
type Job = Box<dyn FnOnce() + Send + 'static>;
```

> The dyn keyword is necessary because FnOnce() + Send + 'static is a trait, not a type, and we cannot have a Box of a trait directly, because its size is not known at compile time. However, by using `Box<dyn FnOnce() + Send + 'static>`, we tell Rust to store the data on the heap, and keep a pointer to the data that implements these traits. The dyn keyword tells Rust that it will have to determine the exact method to call based on the actual type at runtime (dynamic dispatch).

After creating a new Job instance using the closure we get in execute, we send that job down the sending end of the channel. We’re calling unwrap on send for the case that sending fails. This might happen if, for example, we stop all our threads from executing, meaning the receiving end has stopped receiving new messages. At the moment, we can’t stop our threads from executing: our threads continue executing as long as the pool exists. The reason we use unwrap is that we know the failure case won’t happen, but the compiler doesn’t know that.

Acquiring a lock might fail if the mutex is in a poisoned state, which can happen if some other thread panicked while holding the lock rather than releasing the lock. In this situation, calling unwrap to have this thread panic is the correct action to take. Feel free to change this unwrap to an expect with an error message that is meaningful to you.

```rust
// Warning: This code compiles and runs but doesn’t result in the desired threading behavior

impl Worker {
    fn new(id: usize, receiver: Arc<Mutex<mpsc::Receiver<Job>>>) -> Worker {
        let thread = thread::spawn(move || {
            while let Ok(job) = receiver.lock().unwrap().recv() {
                println!("Worker {id} got a job; executing.");

                job();
            }
        });

        Worker { id, thread }
    }
}
```

> In Rust, the Mutex type provides a mechanism for ensuring that only one thread accesses some data at any point in time. When a thread locks a mutex (using the lock method), it obtains a MutexGuard object. This object represents the locked mutex and provides access to the data. The mutex stays locked as long as this MutexGuard is around. When the MutexGuard is dropped (goes out of scope), the mutex is automatically unlocked. There is no explicit unlock method; unlocking happens automatically based on the MutexGuard's lifetime.
> This automatic unlocking can be tricky when combined with Rust's while let construct. The while let construct allows you to loop as long as a certain pattern matches. In the case of while let Ok(job) = receiver.lock().unwrap().recv(), the loop continues as long as recv() returns Ok(job). However, the MutexGuard returned by receiver.lock().unwrap() is kept alive for the entire body of the while let loop, meaning the mutex stays locked for the duration of the job() call.
> This is different from the let statement version, let job = receiver.lock().unwrap().recv().unwrap(). In this case, the MutexGuard is dropped immediately after the let statement ends, so the mutex is only locked during the call to recv().unwrap(), not during the call to job().
> The consequence of this is that in the while let version, if job() takes a long time to run, other workers can't receive jobs because the mutex stays locked. In the let statement version, other workers can receive jobs while job() is running, because the mutex is unlocked immediately after receiving a job.

However, **while let (and if let and match)** does not drop temporary values until the end of the associated block.

> In Rust, when the main thread of a program finishes, the whole process is shut down. This includes all threads, regardless of whether they have been detached.
A detached thread is one that is allowed to run independently from the thread that spawned it. In some languages and systems, this might mean that a detached thread could continue running after the main thread has finished. However, in Rust, this is not the case. When the main thread ends, all threads are stopped, regardless of whether they are detached or not.
This is why it's important to make sure that all threads have completed their work before the main thread finishes. If you have threads that are running an infinite loop, you need to provide some way for them to be stopped, or else they could be abruptly terminated when the main thread ends.

string in Rust are not null-terminated

> No, the string b"GET / HTTP/1.1\r\n" does not contain a \0 (null) byte.
The null byte, represented by \0, is used in many programming languages, including C and C++, to mark the end of a string. However, in Rust, strings are not null-terminated, and a null byte is not automatically appended to the end of a string.
If you want to include a null byte in a byte string, you would need to add it explicitly, like this: b"GET / HTTP/1.1\r\n\0". But in your original string, there is no null byte.
