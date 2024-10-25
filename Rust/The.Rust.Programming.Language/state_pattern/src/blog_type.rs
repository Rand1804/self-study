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
            approvals: 0,
        }
    }
}

pub struct PendingReviewPost {
    content: String,
    approvals: u32,
}


impl PendingReviewPost {
    pub fn consent(&mut self) {
        self.approvals += 1;
    }

    pub fn approve(self) -> Option<Post> {
        if self.approvals >= 2 {
            Some(
                Post {
                    content: self.content,
                }
            )
        } else {
            None
        }
    }

    pub fn reject(self) -> DraftPost {
        DraftPost {
            content: self.content,
        }
    }
}