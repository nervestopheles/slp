use rand::Rng;
use std::io::{BufReader, BufWriter, Read, Write};

pub const EPERM_DEN: &str = "Create or open weight file error.\nPermission denied?";

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

pub fn weights_write(path: &str, weights: &Vec<Vec<f32>>) {
    let file = std::fs::File::options()
        .write(true)
        .open(path)
        .expect(EPERM_DEN);
    let mut writer = BufWriter::new(file);
    for vector in weights {
        for weight_value in vector {
            writer
                .write(&weight_value.to_le_bytes())
                .expect("File writing error.");
        }
    }
}
