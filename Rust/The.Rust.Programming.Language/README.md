### Chapter03 Common Programming Concepts

In Rust, the return value of the function is synonymous with the value of the final expression in the block of the body of a function. 

The tuple without any values has a special name, **unit**. This value and its corresponding type are both written () and represent an empty value or an empty return type. Expressions implicitly return the unit value if they don’t return any other value.

### Chapter04 Understanding Ownership

When a variable goes out of scope, Rust calls a special function for us. This function is called drop

In addition, there’s a design choice that’s implied by this: **Rust will never automatically create “deep” copies of your data**.Therefore, any automatic copying can be assumed to be inexpensive in terms of runtime performance.

When a variable that *includes data on the heap* goes out of scope, the value will be cleaned up by drop unless ownership of the data has been moved to another variable.

We also cannot have a mutable reference while we have an immutable one to the same value.

Recall from the borrowing rules that if we have an immutable reference to something, we cannot also take a mutable reference.

The type of s here is &str: it’s a slice pointing to that specific point of the binary. This is also why string literals are immutable; &str is an immutable reference.

### Chapter05 Using Structs to Structure Related Data

Rust has a feature called automatic referencing and dereferencing. When you call a method with object.something(), Rust automatically adds in &, &mut, or * so object matches the signature of the method. 


### Chapter08 Common Collections

This error is due to the way vectors work: because vectors put the values next to each other in memory, adding a new element onto the end of the vector might require allocating new memory and copying the old elements to the new space, if there isn’t enough room to put all the elements next to each other where the vector is currently stored.

Many of the same operations available with Vec<T> are available with String as well, because String is actually implemented as a wrapper around a vector of bytes with some extra guarantees, restrictions, and capabilities.

For that, we use the to_string method, which is available on any type that implements the Display trait, as string literals do.

The reason s1 is no longer valid after the addition, and the reason we used a reference to s2, has to do with the signature of the method that’s called when we use the + operator. The + operator uses the add method, whose signature looks something like this:

```rust
let s3 = s1 + &s2;
fn add(self, s: &str) -> String {}
```

The reason we’re able to use &s2 in the call to add is that the compiler can coerce the &String argument into a &str.When we call the add method, Rust uses a deref coercion, which here turns &s2 into &s2[..].**This statement actually takes ownership of s1, appends a copy of the contents of s2, and then returns ownership of the result.**

A final reason Rust doesn’t allow us to index into a String to get a character is that indexing operations are expected to always take constant time (O(1)). 

Like vectors, hash maps are homogeneous: all of the keys must have the same type as each other, and all of the values must have the same type.

### Chapter09 Error Handling

By default, when a panic occurs, the program starts unwinding, which means Rust walks back up the stack and cleans up the data from each function it encounters.

### Chapter10 Generic Types, Traits, and Lifetimes

The generic Option<T> is replaced with the specific definitions created by the compiler. Because Rust compiles generic code into code that specifies the type in each instance, we pay no runtime cost for using generics.

But we can’t implement external traits on external types. For example, we can’t implement the Display trait on Vec<T> within our aggregator crate, because Display and Vec<T> are both defined in the standard library and aren’t local to our aggregator crate.

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

### Chapter11 Writing Automated Tests

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