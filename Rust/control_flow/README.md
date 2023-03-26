### Chapter03 Common Programming Concepts

In Rust, the return value of the function is synonymous with the value of the final expression in the block of the body of a function. 

### Chapter04 Understanding Ownership

When a variable goes out of scope, Rust calls a special function for us. This function is called drop

In addition, there’s a design choice that’s implied by this: **Rust will never automatically create “deep” copies of your data**.Therefore, any automatic copying can be assumed to be inexpensive in terms of runtime performance.

When a variable that *includes data on the heap* goes out of scope, the value will be cleaned up by drop unless ownership of the data has been moved to another variable.
 
We also cannot have a mutable reference while we have an immutable one to the same value.

Recall from the borrowing rules that if we have an immutable reference to something, we cannot also take a mutable reference.

The type of s here is &str: it’s a slice pointing to that specific point of the binary. This is also why string literals are immutable; &str is an immutable reference.
