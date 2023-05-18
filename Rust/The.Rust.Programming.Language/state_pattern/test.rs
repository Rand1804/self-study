pub struct PendingReviewPost {
    content: String,
    count: u32,
}

pub enum Either<A, B> {
    Left(A),
    Right(B),
}

impl PendingReviewPost {
    pub fn approve(mut self) -> Either<PendingReviewPost, Post> {
        self.count += 1;
        if self.count < 2 {
            Either::Left(self)
        } else {
            Either::Right(Post {
                content: self.content,
            })
        }
    }
}

fn main() {
    let pending = PendingReviewPost {
        content: "String",
        count: 0,
    };

    let post = pending.approve();
}