pub fn activation(x: &f32) -> f32 {
    binary_step(x) as f32
}
pub fn _activation_derivative(x: &f32) -> f32 {
    _siqmoid_derivative(x)
}

fn binary_step(x: &f32) -> i32 {
    if *x > 0.0 {
        1
    } else {
        0
    }
}

fn _sigmoid(x: &f32) -> f32 {
    1.0 / (1.0 + (-x).exp())
}
fn _siqmoid_derivative(sigmoid: &f32) -> f32 {
    sigmoid * (1.0 - sigmoid)
}

pub fn image_read(path: &str, matrix: &mut Vec<Vec<f32>>) {
    let path = std::path::Path::new(path);
    let bmp = bmp::open(path).unwrap_or_else(|e| {
        panic!("Failed to open: {}", e);
    });
    for (x, rows) in matrix.iter_mut().enumerate() {
        for (y, value) in rows.iter_mut().enumerate() {
            let px = bmp.get_pixel(x as u32, y as u32);
            *value = (px.r as f32 * px.g as f32 * px.b as f32) / (255 * 255 * 255) as f32;
        }
    }
}

pub fn neuron_power(input: &Vec<Vec<f32>>, weights: &Vec<Vec<f32>>) -> f32 {
    let mut neuron: f32 = 0.0;
    for (i, rows) in input.iter().enumerate() {
        for (j, value) in rows.iter().enumerate() {
            neuron += *value as f32 * weights[i][j] as f32;
        }
    }
    neuron
}

pub fn prog_exit() -> ! {
    println!("Null input. Plese enter path to bmp file.");
    std::process::exit(0)
}

// pub fn print_info(arg: &String, np: &f32, na: &f32) {
//     println!("Image name: {}", arg);
//     println!("Neuron power: {}", &np);
//     print!("Neuron activation value: {} -> ", &na);
// }
