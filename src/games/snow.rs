use rand::Rng;

const WIDTH: usize = 80;
const HEIGHT: usize = 24;

fn show(screen: [[char; WIDTH]; HEIGHT]) {
    for string in screen {
        for char in string {
            print!("{}", char);
        }
        println!();
    }
    println!();
}

fn gen_snow(screen: &mut [[char; WIDTH]; HEIGHT]) {
    for chr in screen[0].iter_mut() {
        if rand::thread_rng().gen_range(1..120) % 12 == 0 {
            *chr = '*';
        }
    }
}

fn move_snow(screen: &mut [[char; WIDTH]; HEIGHT]) {
    for j in (0..(HEIGHT)).rev() {
        for i in 0..(WIDTH) {
            if screen[j][i] == '*' {
                screen[j][i] = ' ';

                let mut dx = i;
                if rand::thread_rng().gen_range(0..99) % 3 == 0 {
                    if dx == WIDTH-1 {
                        dx = 0;
                    } else {
                        dx += 1;
                    }
                }
                if rand::thread_rng().gen_range(0..99) % 3 == 0 {
                    if dx == 0 {
                        dx = WIDTH-1;
                    } else {
                        dx -= 1;
                    }
                }
                if j + 1 < HEIGHT {
                    screen[j + 1][dx] = '*';
                }
            }
        }
    }
}

pub fn game() {
    let mut screen = [[' '; WIDTH]; HEIGHT];
    loop {
        print!("\x1B[2J\x1B[1;1H");
        move_snow(&mut screen);
        gen_snow(&mut screen);
        show(screen);
        std::thread::sleep(std::time::Duration::from_millis(100));
    }
}
