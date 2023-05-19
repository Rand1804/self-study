// use state_pattern::blog::Post;

// fn main() {
//     let mut post = Post::new();

//     post.add_text("I ate a salad for lunch today");
//     assert_eq!("", post.content());

//     post.request_review();
//     assert_eq!("", post.content());
//     post.add_text(" for dinner");



//     post.approve();
//     post.approve();
//     assert_eq!("I ate a salad for lunch today", post.content());
// }



use state_pattern::blog_type::Post;


fn main() {
    let mut post = Post::new();

    post.add_text("I ate a salad for lunch today");

    let post = post.request_review();

    let post = post.reject();
    
    let mut post = post.request_review();

    post.consent();
    post.consent();


    let post = post.approve().unwrap();
    assert_eq!("I ate a salad for lunch today", post.content());
}


