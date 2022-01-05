use std::io::Write;

mod algorithms;
mod games;

fn main() {
    println!("Hello, its slp project!");

    loop {
        prog_list();
        print!("Choose the programm: ");

        let mut choise: String = String::new();
        std::io::stdout().flush().expect("stdout flush error");
        std::io::stdin().read_line(&mut choise).expect("stdin read line error");

        let choise: i32 = match choise.trim().parse() {
            Ok(n) => {
                println!("your choose: {}", n);
                n
            }
            Err(_) => {
                println!("Bad choose, repeat.");
                continue;
            }
        };

        match choise {
            11 => games::guess_the_number(),
            12 => games::snow_generator(),
            21 => algorithms::fibonacci_numbers(),
            22 => algorithms::fahrenheit_converter(),
            _ => {
                println!("Goodbye ^^");
                break;
            }
        }
    }
}

fn prog_list() {
    println!("Programm list:");
    println!("  Games:");
    println!("    11. Guess the number.");
    println!("    12. Snow generator.");
    println!("  Algorithms:");
    println!("    21. Fibonacci numbers.");
    println!("    22. Fahrenheit converter.");
    println!("Enter another number to exit.")
}
