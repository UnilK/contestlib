use std::io::Write;

struct Cin {
    buffer: Vec<String>
}

impl Cin {
    fn read<T: std::str::FromStr>(&mut self) -> T {
        loop {
            match self.buffer.pop() {
                Some(x) => {
                    return x.parse().ok().expect("parse failed");
                }
                None => {
                    let mut input = String::new();
                    std::io::stdin().read_line(&mut input).expect("read failed");
                    self.buffer = input.split_whitespace().rev().map(String::from).collect();
                }
            }
        }
    }
}

fn main(){
    
    let mut cin = Cin{ buffer: Vec::new(), };
    let cout = &mut std::io::BufWriter::new(std::io::stdout());

    let n: i32 = cin.read();
    
    write!(cout, "{}", n).ok();
}
