pub fn foo() {
    const FIRST: usize = 0;
    const SECOND: usize = 1;
    const BUF_SIZE: usize = 90;

    let mut fib_num: [usize; BUF_SIZE] = [0; BUF_SIZE];

    fib_num[FIRST] = FIRST;
    println!("Fib num {} is {}", FIRST + 1, fib_num[FIRST]);

    fib_num[SECOND] = SECOND;
    println!("Fib num {} is {}", SECOND + 1, fib_num[SECOND]);

    for idx in 2..BUF_SIZE {
        fib_num[idx] = fib_num[idx - 1] + fib_num[idx - 2];
        println!("Fib num {} is {}", idx + 1, fib_num[idx]);
    }
}
