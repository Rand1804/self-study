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


use state_pattern::blog_type::PendingReviewPost;
use state_pattern::blog_type::Post;
use state_pattern::blog_type::Either;

fn main() {
    let mut post = Post::new();

    post.add_text("I ate a salad for lunch today");

    let post = post.request_review();

    let post = post.reject();
    
    let post = post.request_review();

    let post = post.approve();

    // TODO
    // match post {
    //     Either::Left(pending_review) => {
    //         match pending_review.approve()
    //     },
    //     Either::Right(post) => {post},
    // }


    // assert_eq!("I ate a salad for lunch today", post.content());
}


