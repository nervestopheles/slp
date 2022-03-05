use rand::Rng;
use regex::Regex;
use std::io::{BufReader, BufWriter, Read, Write};

use crate::consts::{EPERM_DEN, SHAPES};
use crate::math::{sigmoid, siqmoid_derivative};

pub struct Neuron {
    pub shape: char,
    weights: Vec<Vec<f32>>,
    weights_path: String,
}

impl Neuron {
    pub fn new(width: usize, height: usize) -> Self {
        Self {
            shape: ' ',
            weights: vec![vec![0.0f32; width]; height],
            weights_path: String::new(),
        }
    }

    pub fn shape_read(&mut self, path: &str) {
        if !Regex::new(r".*\.weights.\.bin").unwrap().is_match(path) {
            return;
        }
        let lenth = path.len();
        for (idx, chr) in path.chars().enumerate() {
            if idx == lenth - ".bin".len() - 1 && SHAPES.contains(&chr)
            /* read shape in file name 01.weights(0).bin */
            {
                self.shape = chr;
            }
        }
        self.weights_path = path.to_string();
    }

    pub fn weights_init(&mut self, path: &str) {
        let mut rng = rand::thread_rng();
        for vector in self.weights.iter_mut() {
            for value in vector {
                *value = rng.gen_range(-0.3..=0.3);
            }
        }
        self.shape_read(path);
    }

    pub fn weights_read(&mut self, path: &str) {
        let mut reader = BufReader::new(
            std::fs::File::options()
                .read(true)
                .open(path)
                .expect("Weight file not found?"),
        );
        let mut float_buffer: [u8; 4] = [0; 4]; // f32 size is 4
        for vector in self.weights.iter_mut() {
            for value in vector {
                reader
                    .read(&mut float_buffer)
                    .expect("Failed read 4 bytes from weight file.");
                *value = f32::from_le_bytes(float_buffer);
            }
        }
    }

    pub fn weights_write_bin(&self) {
        let mut writer = BufWriter::new(
            std::fs::File::options()
                .write(true)
                .open(&self.weights_path)
                .expect(EPERM_DEN),
        );
        for vector in self.weights.iter() {
            for value in vector {
                writer
                    .write(&value.to_le_bytes())
                    .expect("Weights as bin write error.");
            }
        }
    }

    pub fn weights_write_bmp(&self) {
        let size = self.weights.len();
        let mut px = bmp::Pixel::new(0, 0, 0);
        let mut img = bmp::Image::new(size as u32, size as u32);
        for (x, vectors) in self.weights.iter().enumerate() {
            for (y, value) in vectors.iter().enumerate() {
                if *value > 0.0 {
                    let positive = (value * 255.0).round() as u8;
                    px.r = 0;
                    px.g = positive;
                    px.b = positive;
                } else {
                    let negative = (value * -255.0).round() as u8;
                    px.r = negative;
                    px.g = 0;
                    px.b = 0;
                };
                img.set_pixel(x as u32, y as u32, px);
            }
        }
        img.save(format!("{}.bmp", self.weights_path).as_str())
            .expect("Weights as bmp write error.");
    }

    pub fn weights_correction(
        &mut self,
        na: &f32, // neuron activation
        ev: &f32, // expected value of neuron activation
        input: &Vec<Vec<f32>>,
        alpha: f32, // learning speed
    ) {
        let delta = ev - na;
        for (i, vectors) in input.iter().enumerate() {
            for (j, iv /* input value */) in vectors.iter().enumerate() {
                if *iv != 0.0 {
                    self.weights[i][j] += alpha * delta * iv;
                }
            }
        }
    }

    pub fn power(&self, input: &Vec<Vec<f32>>) -> f32 {
        let mut sum: f32 = 0.0;
        for (i, rows) in input.iter().enumerate() {
            for (j, value) in rows.iter().enumerate() {
                sum += *value * self.weights[i][j];
            }
        }
        sum
    }

    pub fn activation(x: &f32) -> f32 {
        sigmoid(x)
    }

    pub fn activation_derivative(x: &f32) -> f32 {
        siqmoid_derivative(x)
    }
}
