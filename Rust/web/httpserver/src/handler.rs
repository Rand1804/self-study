use http::{
    httprequest::HttpRequest,
    httpresponse::HttpResponse,
};
use serde::{Deserialize, Serialize};
use std::collections::HashMap;
use std::default;
use std::env;
use std::fs;

pub trait Handler {
    fn handle(req: &HttpRequest) -> HttpResponse;
    fn load_file(file_name: &str) -> Option<String> {
        // "CARGO_MANIFEST_DIR" root directory 
        let default_path = format!("{}/public", env!("CARGO_MANIFEST_DIR"));
        let pulic_path = env::var("PUBLIC_PATH").unwrap_or(default_path);
        let full_path = format!("{}/{}", pulic_path, file_name);

        let contents = fs::read_to_string(full_path);
        contents.ok()
    }
}

pub struct StaticPageHandler;
pub struct PageNotFoundHandler;
pub struct WebServiceHandler;

#[derive(Debug)]
