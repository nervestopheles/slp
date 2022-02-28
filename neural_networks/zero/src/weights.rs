// use crate::other::*;

use rand::Rng;
use std::io::{BufReader, BufWriter, Read, Write};

pub const EPERM_DEN: &str = "Create or open weight file error.\n\
                            Permission denied?";

pub const WEIGHTS_FILE_PATH: &str = "./.tmp/weights.bin";
pub const WEIGHTS_BMP_PATH: &str = "./.tmp/weights.bmp";

pub const INCREASES_PATH: &str = "./.tmp/learning/crosses";
pub const DECREASES_PATH: &str = "./.tmp/learning/other";

pub const MATRIX_SIZE: usize = 80;
pub const ALPHA: f32 = 0.8;

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
    let mut px = bmp::Pixel::new(0, 0, 0);
    let mut img = bmp::Image::new(MATRIX_SIZE as u32, MATRIX_SIZE as u32);
    for (x, vectors) in weights.iter().enumerate() {
        for (y, value) in vectors.iter().enumerate() {
            if *value > 0.0 {
                let positive: u8 = (value * 255.0).round() as u8;
                px.r = 0;
                px.g = positive;
                px.b = positive;
            } else {
                let negative: u8 = (value * -255.0).round() as u8;
                px.r = negative;
                px.g = 0;
                px.b = 0;
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
    let delta = correct_value - na;
    // let _derivative = activation_derivative(na);
    for (i, vectors) in input.iter().enumerate() {
        for (j, value) in vectors.iter().enumerate() {
            if *value != 0.0 {
                weights[i][j] += ALPHA * delta * value /* * 2.0 * _derivative */;
            }
        }
    }
}
