pub struct Post {
    content: String,
}

pub struct DraftPost {
    content: String,
}

impl Post {
    pub fn new() -> DraftPost {
        DraftPost {
            content: String::new(),
        }
    }

    pub fn content(&self) -> &str {
        &self.content
    }
}

impl DraftPost {
    pub fn add_text(&mut self, text: &str) {
        self.content.push_str(text);
    }

    pub fn request_review(self) -> PendingReviewPost {
        PendingReviewPost {
            content: self.content,
            count: 0,
        }
    }
}

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

    pub fn reject(self) -> DraftPost {
        DraftPost {
            content: self.content,
        }
    }
}