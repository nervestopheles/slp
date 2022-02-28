pub mod other;
use other::*;

pub mod weights;
use weights::*;

pub mod imgs;
use imgs::*;

use rand::prelude::SliceRandom;

const MODE_LEARNING: &str = "--learn";
const MODE_INCREASE: &str = "--inc";
const MODE_DECREASE: &str = "--dec";

/* For sigmoid activation func */
// const INCREASE_VALUE: f32 = 0.9;
// const DECREASE_VALUE: f32 = 0.1;

/* For binary step activation func */
const INCREASE_VALUE: f32 = 1.0;
const DECREASE_VALUE: f32 = 0.0;

#[derive(PartialEq)]
enum RunMode {
    Normal,
    Increase,
    Decrease,
    Learning,
}

fn main() {
    let mut args: Vec<String> = std::env::args().skip(1).collect();
    let mode: RunMode = if args.len() != 0 {
        match args[0].as_str() {
            MODE_INCREASE => RunMode::Increase,
            MODE_DECREASE => RunMode::Decrease,
            MODE_LEARNING => RunMode::Learning,
            _ => RunMode::Normal,
        }
    } else {
        prog_exit();
    };

    if mode != RunMode::Normal && mode != RunMode::Learning {
        args.remove(0);
        if args.len() == 0 {
            prog_exit();
        };
    }

    let weights_path = std::path::Path::new(WEIGHTS_FILE_PATH);
    let mut weights = vec![vec![0 as f32; MATRIX_SIZE]; MATRIX_SIZE];
    {
        if weights_path.exists() {
            weights_read(weights_path, &mut weights);
        } else {
            std::fs::File::create(WEIGHTS_FILE_PATH).expect(EPERM_DEN);
            weights_init(&mut weights);
            if mode != RunMode::Learning {
                weights_write_bin(WEIGHTS_FILE_PATH, &weights);
                weights_write_bmp(&weights);
            }
        };
    }

    let correct_value = match mode {
        RunMode::Increase => INCREASE_VALUE,
        RunMode::Decrease => DECREASE_VALUE,
        _ => 0.0,
    };

    let mut input: Vec<Vec<f32>> = vec![vec![0 as f32; MATRIX_SIZE]; MATRIX_SIZE];

    let mut eras: u64 = 0;
    let mut errors: u64 = 0;
    let mut correcting: u64 = 1;

    match mode {
        RunMode::Normal => {
            for path in args.iter() {
                image_read(path, &mut input);
                let np = neuron_power(&input, &weights);
                let na = activation(&np);
                println!(
                    "\
                    Image name: {}\n\
                    Neuron power: {:.4}\n\
                    Neuron activation value: {:.4}\n\
                ",
                    path, &np, &na
                );
            }
        }
        RunMode::Increase => {
            for path in args.iter() {
                image_read(path, &mut input);
                let mut np = neuron_power(&input, &weights);
                let mut na = activation(&np);
                while (100.0 * na).round() / 100.0 < correct_value {
                    weight_correction(&na, &correct_value, &input, &mut weights);
                    np = neuron_power(&input, &weights);
                    na = activation(&np);
                    errors += 1;
                }
            }
        }
        RunMode::Decrease => {
            for path in args.iter() {
                image_read(path, &mut input);
                let mut np = neuron_power(&input, &weights);
                let mut na = activation(&np);
                while (100.0 * na).round() / 100.0 > correct_value {
                    weight_correction(&na, &correct_value, &input, &mut weights);
                    np = neuron_power(&input, &weights);
                    na = activation(&np);
                    errors += 1;
                }
            }
        }
        RunMode::Learning => {
            let files: Vec<String> = {
                let mut files: Vec<String> = vec![];
                for path in [INCREASES_PATH, DECREASES_PATH] {
                    for obj in std::fs::read_dir(path).unwrap() {
                        files.push(obj.unwrap().path().display().to_string());
                    }
                }
                files
            };

            let mut imgs = {
                let mut imgs: Vec<Img> = vec![Img::default(MATRIX_SIZE, MATRIX_SIZE); files.len()];
                for (idx, path) in files.iter().enumerate() {
                    if regex::Regex::new(r"x.*.bmp").unwrap().is_match(path) {
                        imgs[idx].shape = ImgShape::Cross;
                    } else if regex::Regex::new(r"o.*.bmp").unwrap().is_match(path) {
                        imgs[idx].shape = ImgShape::NonCross;
                    } else {
                        imgs.remove(idx);
                        continue;
                    }
                    image_read(path, &mut imgs[idx].matrx);
                    imgs[idx].path = path.clone();
                }
                imgs
            };

            let mut rng = rand::thread_rng();
            while correcting != 0 {
                eras += 1;
                correcting = 0;
                imgs.shuffle(&mut rng);

            /*
                #[cfg(debug_assertions)]
                {
                    let mut debug_print = String::new();
                    for img in imgs.iter() {
                        debug_print.push_str(img.path.as_str());
                        debug_print.push('\n');
                    }
                    println!("Era: {}\n{}", eras, debug_print);
                }
            */

                for img in imgs.iter() {
                    let np = neuron_power(&img.matrx, &weights);
                    let na = activation(&np);
                    let na_round = (100.0 * na).round() / 100.0;

                    let mut correction = |correct_value: f32| {
                        weight_correction(&na, &correct_value, &img.matrx, &mut weights);
                        correcting += 1;
                        errors += 1;
                    };

                    if img.shape == ImgShape::Cross {
                        if na_round < INCREASE_VALUE {
                            correction(INCREASE_VALUE);
                        }
                    } else {
                        if na_round > DECREASE_VALUE {
                            correction(DECREASE_VALUE);
                        }
                    }
                }
            }
        }
    }

    if mode != RunMode::Normal {
        weights_write_bin(WEIGHTS_FILE_PATH, &weights);
        weights_write_bmp(&weights);
        println!("Counts of eras: {}", &eras);
        println!("All errors: {}", &errors);
    }
}
