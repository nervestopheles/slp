use std::io::Read;
use std::io::Write;

mod algorithms;
mod games;

fn main() {
    clear();
    println!("Hello, its slp project!\n");

    loop {
        prog_list();
        print!("Choice the programm: ");

        let mut choise: String = String::new();
        std::io::stdout().flush().expect("stdout flush error");
        std::io::stdin()
            .read_line(&mut choise)
            .expect("stdin read line error");

        let choise: i32 = match choise.trim().parse() {
            Ok(n) => n,
            Err(_) => {
                clear();
                println!("Bad choice, repeat.\n");
                continue;
            }
        };

        match choise {
            11 => {
                clear();
                games::guess_the_number();
                std::io::stdin().bytes().next();
                clear();
            }
            12 => {
                clear();
                games::snow_generator();
                std::io::stdin().bytes().next();
                clear();
            }
            21 => {
                clear();
                algorithms::fibonacci_numbers();
                std::io::stdin().bytes().next();
                clear();
            }
            22 => {
                clear();
                algorithms::fahrenheit_converter();
                std::io::stdin().bytes().next();
                clear();
            }
            _ => {
                println!("\nGoodbye ^^");
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
    println!("Enter another number to exit.");
}

fn clear() {
    print!("\x1B[2J\x1B[1;1H"); /* clear linux terminal */
}
