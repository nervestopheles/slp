use crate::other::*;

use rand::Rng;
use std::io::{BufReader, BufWriter, Read, Write};

pub const EPERM_DEN: &str = "Create or open weight file error.\nPermission denied?";

pub const WEIGHTS_FILE_PATH: &str = "./.tmp/weights.bin";
pub const WEIGHTS_BMP_PATH: &str = "./.tmp/weights.bmp";

pub const INCREASES_PATH: &str = "./.tmp/images/crosses";
pub const DECREASES_PATH: &str = "./.tmp/images/other";

pub const MATRIX_SIZE: usize = 80;
pub const ALPHA_VALUE: f32 = 0.1;

pub fn weights_init(weights: &mut Vec<Vec<f32>>) {
    let mut rng = rand::thread_rng();
    for vector in weights {
        for weight_value in vector {
            *weight_value = rng.gen_range(-0.3..=0.3);
        }
    }
}

pub fn weights_read(path: &std::path::Path, weights: &mut Vec<Vec<f32>>) {
    let file = std::fs::File::options()
        .read(true)
        .open(path)
        .expect("Weight file not found?");
    let mut reader = BufReader::new(file);
    let mut float_buffer: [u8; 4] = [0; 4];

    for vector in weights {
        for weight_value in vector {
            reader
                .read(&mut float_buffer)
                .expect("Failed read 4 bytes from weight file.");
            *weight_value = f32::from_ne_bytes(float_buffer);
        }
    }
}

pub fn weights_write_bin(path: &str, weights: &Vec<Vec<f32>>) {
    let file = std::fs::File::options()
        .write(true)
        .open(path)
        .expect(EPERM_DEN);
    let mut writer = BufWriter::new(file);
    for vector in weights {
        for weight_value in vector {
            writer
                .write(&weight_value.to_le_bytes())
                .expect("Weights as bin write error.");
        }
    }
}

pub fn weights_write_bmp(weights: &Vec<Vec<f32>>) {
    let mut img = bmp::Image::new(MATRIX_SIZE as u32, MATRIX_SIZE as u32);
    for (x, vectors) in weights.iter().enumerate() {
        for (y, value) in vectors.iter().enumerate() {
            let px = if *value > 0.0 {
                let green: u8 = (value * 255.0).round() as u8;
                bmp::Pixel::new(0, green, 0)
            } else {
                let red: u8 = (value * 255.0 * -1.0).round() as u8;
                bmp::Pixel::new(red, 0, 0)
            };
            img.set_pixel(x as u32, y as u32, px);
        }
    }
    img.save(WEIGHTS_BMP_PATH)
        .expect("Weights as bmp write error.");
}

pub fn weight_correction(
    na: &f32,
    correct_value: &f32,
    input: &Vec<Vec<f32>>,
    weights: &mut Vec<Vec<f32>>,
) {
    let delta = na - correct_value;
    let derivative = activation_derivative(na);
    for (i, vectors) in input.iter().enumerate() {
        for (j, _value) in vectors.iter().enumerate() {
            weights[i][j] -= ALPHA_VALUE * 2.0 * delta * derivative * input[i][j];
        }
    }
}
