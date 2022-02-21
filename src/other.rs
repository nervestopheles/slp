pub fn activation(n: f64) -> bool {
    if n >= 1.0 {
        return true;
    } else {
        return false;
    };
}

pub fn image_read(path: &str, matrix: &mut Vec<Vec<f32>>) {
    let path = std::path::Path::new(path);
    let bmp = bmp::open(path).unwrap_or_else(|e| {
        panic!("Failed to open: {}", e);
    });
    for (x, rows) in matrix.iter_mut().enumerate() {
        for (y, point) in rows.iter_mut().enumerate() {
            *point = if bmp.get_pixel(x as u32, y as u32).r > 1 {
                1.0
            } else {
                0.0
            }
        }
    }
}

pub fn neuron_power(input: &Vec<Vec<f32>>, weights: &Vec<Vec<f32>>) -> f64 {
    let mut neuron: f64 = 0.0;
    for (i, rows) in input.iter().enumerate() {
        for (j, value) in rows.iter().enumerate() {
            neuron += *value as f64 * weights[i][j] as f64;
        }
    }
    return neuron;
}
