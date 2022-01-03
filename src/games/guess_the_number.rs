use rand::Rng;

fn get_guess_str() -> String {
    let err: &str = "Failed to read line.";
    let mut guess: String = String::new();

    std::io::stdin().read_line(&mut guess).expect(err);
    return guess;
}

pub fn foo() {
    let secret_number: i32 = rand::thread_rng().gen_range(0..99);

    println!("Guess the number!");
    println!("Please input your guess: ");

    loop {
        let guess: i32 = match get_guess_str().trim().parse() {
            Ok(number) => number,
            Err(_) => {
                println!("Wrong input.");
                println!("Go again: ");
                continue;
            }
        };
        if guess == secret_number {
            println!(
                "You win! Your guess({}) == secret({})",
                guess, secret_number
            );
            break;
        } else if guess > secret_number {
            println!("Your guess ({}) is to bigger.", guess);
        } else if guess < secret_number {
            println!("Your guess ({}) is to small.", guess);
        }
    }
}