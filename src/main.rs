extern crate bmp;
extern crate rand;

use rand::Rng;
use std::{
    io::{BufReader, BufWriter, Read, Write},
    path::Path,
};

fn main() {
    let w_file = "./w.bin";
    let mut w: Vec<Vec<f32>> = vec![vec![0.0; 250]; 250];

    if !Path::new(w_file).exists() {
        std::fs::File::create(w_file).expect("create file error. permission denied?");
        // for i in 0..250 {
        //     for j in 0..250 {
        //         w[i][j] = rand::thread_rng().gen_range(-0.3..=0.3);
        //     }
        // }
    } else {
        let descrypt = std::fs::File::options()
            .read(true)
            .open(w_file)
            .expect("not found");
        let mut reader_buf = BufReader::new(descrypt);

        let mut buf: [u8; 4] = [0; 4];
        for i in 0..250 {
            for j in 0..250 {
                reader_buf.read(&mut buf).expect("read err");
                let float = f32::from_ne_bytes(buf);
                w[i][j] = float;
            }
        }
    }

    // let mut w: Vec<Vec<f32>> = vec![vec![0.0; 250]; 250];
    // for i in 0..250 {
    //     for j in 0..250 {
    //         w[i][j] = rand::thread_rng().gen_range(-0.3..=0.3);
    //     }
    // }

    let bmp = bmp::open("/home/soma/Work/Learning/NeuroNetwork/images/1.bmp").unwrap_or_else(|e| {
        panic!("Failed to open: {}", e);
    });
    let mut image: Vec<Vec<f32>> = vec![vec![0.0; 250]; 250];
    for i in 0..250 {
        for j in 0..250 {
            image[i][j] = if bmp.get_pixel(i as u32, j as u32).r > 1 {
                1.0
            } else {
                0.0
            };
        }
    }

    let mut activate: f64 = 0.0;
    for i in 0..250 {
        for j in 0..250 {
            activate = activate + image[i][j] as f64 * w[i][j] as f64;
        }
    }
    println!("A: {}", activate);

    println!("this is X? {}", activation(activate));

    // // print img in console
    // for i in 0..250 {
    //     for j in 0..250 {
    //         print!("{}", image[i][j]);
    //     }
    //     println!();
    // }
    let write_descrtypt = std::fs::File::options()
        .write(true)
        .open(w_file)
        .expect("open file error");

    let mut writer_buf = BufWriter::new(&write_descrtypt);
    for i in w {
        for j in i {
            writer_buf.write(&j.to_le_bytes()).expect("repres error");
        }
    }

    drop(writer_buf);
    drop(write_descrtypt);
}

fn init_weight(size: usize) -> Vec<Vec<f32>> {
    let mut weight = vec![vec![0 as f32; size]];
    let mut rng = rand::thread_rng();
    for i in 0..size {
        for j in 0..size {
            weight[i][j] = rng.gen_range(-0.3..=0.3);
        }
    }
    return weight;
}

fn activation(n: f64) -> bool {
    if n >= 1.0 {
        return true;
    } else {
        return false;
    };
}