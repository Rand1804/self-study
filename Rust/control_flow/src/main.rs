
#[derive(Debug)]
struct Tmp {
    x: i32,
    y: i32
}


let num: i32 = 3;

fn main() {
    let arr = [1, 2, 4];
    take_arr(arr);
    let tmp = Tmp {x: 1, y: 2};
    println!("main{:?}", tmp);
}

fn take_arr(arr: [i32; 3]) {
    println!("{:?}", arr);
}