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
