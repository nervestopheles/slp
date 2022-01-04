use std::io::Write;

pub fn foo() {
    const ERR: &str = "Common Error.";

    let fahrenheit: f32 = loop {
        print!("Enter temperature in Fahrenheit: ");
        std::io::stdout().flush().expect(ERR);

        let mut fahrenheit: String = String::new();
        std::io::stdin().read_line(&mut fahrenheit).expect(ERR);

        break match fahrenheit.trim().parse() {
            Ok(num) => num,
            Err(_) => {
                println!("Wrong input.");
                println!("Please repeat");
                continue;
            }
        };
    };

    let celsius: f32 = 5.0 * (fahrenheit - 32.0) / 9.0;
    println!("In Celsius: {}", celsius);
}
