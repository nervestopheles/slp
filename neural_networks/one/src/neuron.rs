use rand::Rng;
use std::io::{BufReader, BufWriter, Read, Write};

use crate::consts::EPERM_DEN;
use crate::other::*;

pub struct Neuron {
    shape: usize,
    weights: Vec<Vec<f32>>,
}

impl Neuron {
    pub fn new(shape: usize, size: usize) -> Self {
        Self {
            shape,
            weights: vec![vec![0.0f32; size]; size],
        }
    }

    pub fn weights_init(&self) -> Self {
        let mut rng = rand::thread_rng();
        for vector in self.weights {
            for value in vector {
                value = rng.gen_range(-0.3..=0.3);
            }
        }
        *self
    }

    pub fn weights_read(&self, path: &std::path::Path) -> Self {
        let mut reader = BufReader::new(
            std::fs::File::options()
                .read(true)
                .open(path)
                .expect("Weight file not found?"),
        );
        let mut float_buffer: [u8; 4] = [0; 4]; // f32 size is 4
        for vector in self.weights {
            for value in vector {
                reader
                    .read(&mut float_buffer)
                    .expect("Failed read 4 bytes from weight file.");
                value = f32::from_le_bytes(float_buffer);
            }
        }
        *self
    }

    pub fn weights_write_bin(&self, path: &str) {
        let mut writer = BufWriter::new(
            std::fs::File::options()
                .write(true)
                .open(path)
                .expect(EPERM_DEN),
        );
        for vector in self.weights {
            for value in vector {
                writer
                    .write(&value.to_le_bytes())
                    .expect("Weights as bin write error.");
            }
        }
    }

    pub fn weights_write_bmp(&self, path: &str) {
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
        img.save(path).expect("Weights as bmp write error.");
    }

    pub fn weights_correction(
        &self,
        na: &f32, // neuron activation
        ev: &f32, // expected value of neuron activation
        input: &Vec<Vec<f32>>,
        alpha: f32, // learning speed
    ) {
        let delta = ev - na;
        let derivative = activation_derivative(na);
        for (i, vectors) in input.iter().enumerate() {
            for (j, iv /* input value */) in vectors.iter().enumerate() {
                if *iv != 0.0 {
                    self.weights[i][j] += alpha * delta * iv * derivative;
                }
            }
        }
    }
}
