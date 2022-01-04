use rand::Rng;
use std::io::Write;

pub fn foo() {
    let ts: termsize::Size = termsize::get().unwrap();
    let mut screen = vec![vec![' '; ts.cols as usize]; ts.rows as usize];
    loop {
        print!("\x1B[2J\x1B[1;1H");
        move_snow(&mut screen, &ts);
        gen_snow(&mut screen);
        show_snow(&screen, &ts);
        std::thread::sleep(std::time::Duration::from_millis(150));
    }
}

fn show_snow(screen: &Vec<Vec<char>>, ts: &termsize::Size) {
    for (idx, string) in screen.iter().enumerate() {
        let s: String = string.iter().collect();
        print!("{}", s);
        if idx == ts.rows as usize - 1 {
            std::io::stdout().flush().expect("Output error.");
        } else {
            println!();
        }
    }
}

fn gen_snow(screen: &mut Vec<Vec<char>>) {
    for chr in screen[0].iter_mut() {
        if rand::thread_rng().gen_range(0..100) % 10 == 0 {
            *chr = '*';
        }
    }
}

fn move_snow(screen: &mut Vec<Vec<char>>, ts: &termsize::Size) {
    for i in (0..(ts.rows as usize)).rev() {
        for j in 0..(ts.cols as usize) {
            if screen[i][j] == '*' {
                screen[i][j] = ' ';
                let mut dx = j;
                if rand::thread_rng().gen_range(0..100) % 2 == 0 {
                    if dx == ts.cols as usize - 1 {
                        dx = 0;
                    } else {
                        dx += 1;
                    }
                } else if rand::thread_rng().gen_range(0..100) % 2 == 0 {
                    if dx == 0 {
                        dx = ts.cols as usize - 1;
                    } else {
                        dx -= 1;
                    }
                }
                if i + 1 < ts.rows as usize {
                    screen[i + 1][dx] = '*';
                }
            }
        }
    }
}
