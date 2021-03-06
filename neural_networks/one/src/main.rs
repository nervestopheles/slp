pub mod consts;
pub mod img;
pub mod math;
pub mod neuron;

use crate::consts::*;
use crate::img::*;
use crate::neuron::*;

use rand::prelude::SliceRandom;
use rayon::prelude::*;
use std::path::Path;

const MODE_LEARNING_SYNC: &str = "--learn";
const MODE_LEARNING_ASYNC: &str = "--learn-async";
const MODE_INCREASE: &str = "--inc";
const MODE_DECREASE: &str = "--dec";

#[derive(PartialEq)]
enum RunMode {
    Normal,
    Increase,
    Decrease,
    LearningSync,
    LearningAsync,
}

fn main() {
    let mut args: Vec<String> = std::env::args().skip(1).collect();
    let mode: RunMode = if args.len() != 0 {
        match args[0].as_str() {
            MODE_INCREASE => RunMode::Increase,
            MODE_DECREASE => RunMode::Decrease,
            MODE_LEARNING_SYNC => RunMode::LearningSync,
            MODE_LEARNING_ASYNC => RunMode::LearningAsync,
            _ => RunMode::Normal,
        }
    } else {
        prog_exit();
    };

    if mode != RunMode::Normal && mode != RunMode::LearningSync && mode != RunMode::LearningAsync {
        args.remove(0);
        if args.len() == 0 {
            prog_exit();
        };
    }

    let mut neurons: Vec<Neuron> = vec![];
    {
        let weights_paths: [&str; 10] = WEIGHTS_FILES_PATH;
        for path in weights_paths {
            let mut neuron = Neuron::new(MATRIX_SIZE, MATRIX_SIZE);
            if Path::new(path).exists() {
                neuron.shape_read(path);
                neuron.weights_read(path);
            } else {
                std::fs::File::create(path).expect(EPERM_DEN);
                neuron.weights_init(path);
                if mode != RunMode::LearningSync {
                    neuron.weights_write_bin();
                    neuron.weights_write_bmp();
                }
            };
            neurons.push(neuron);
        }
    };

    use std::sync::{Arc, Mutex};

    let mut eras: u64 = 0;
    let errors = Arc::new(Mutex::new(0));
    let correcting = Arc::new(Mutex::new(0));

    match mode {
        RunMode::Normal => {
            for path in args.iter() {
                let img: Img = Img::new(path, MATRIX_SIZE, MATRIX_SIZE);
                let mut buf: f32;
                let mut answ_acti: f32 = 0.0; // neuron activation
                let mut answ_char: char = 'E'; // input shape
                for neuron in neurons.iter() {
                    buf = Neuron::activation(&neuron.power(&img.matrx));
                    if buf > answ_acti {
                        answ_acti = buf;
                        answ_char = neuron.shape;
                    }
                }
                println!(
                    "\
                    Image name: {}\n\
                    Image shape: {}
                ",
                    path, answ_char
                );
            }
        }
        RunMode::Increase => {
            // for path in args.iter() {
            //     image_read(path, &mut input);
            //     let mut np = neuron_power(&input, &weights);
            //     let mut na = activation(&np);
            //     while (100.0 * na).round() / 100.0 < correct_value {
            //         weight_correction(&na, &correct_value, &input, &mut weights, ALPHA);
            //         np = neuron_power(&input, &weights);
            //         na = activation(&np);
            //         errors += 1;
            //     }
            // }
        }
        RunMode::Decrease => {
            // for path in args.iter() {
            //     image_read(path, &mut input);
            //     let mut np = neuron_power(&input, &weights);
            //     let mut na = activation(&np);
            //     while (100.0 * na).round() / 100.0 > correct_value {
            //         weight_correction(&na, &correct_value, &input, &mut weights, ALPHA);
            //         np = neuron_power(&input, &weights);
            //         na = activation(&np);
            //         errors += 1;
            //     }
            // }
        }
        RunMode::LearningSync => {
            let mut imgs: Vec<Img> = vec![];
            {
                let files = get_files(vec![IMG_FILES_PATH.to_string()]);
                for path in files.iter() {
                    imgs.push(Img::new(path, MATRIX_SIZE, MATRIX_SIZE));
                }
            };

            let mut np: f32;
            let mut na: f32;
            let mut rng = rand::thread_rng();

            loop {
                eras += 1;
                imgs.shuffle(&mut rng);

                for img in imgs.iter() {
                    for neuron in neurons.iter_mut() {
                        np = neuron.power(&img.matrx);
                        na = (1000.0 * Neuron::activation(&np)).round() / 1000.0;
                        if neuron.shape == img.shape && na < INCREASE_VALUE {
                            neuron.weights_correction(&na, &INCREASE_VALUE, &img.matrx, ALPHA);
                            *correcting.lock().unwrap() += 1;
                            *errors.lock().unwrap() += 1;
                        } else if neuron.shape != img.shape && na > DECREASE_VALUE {
                            neuron.weights_correction(&na, &DECREASE_VALUE, &img.matrx, ALPHA);
                            *correcting.lock().unwrap() += 1;
                            *errors.lock().unwrap() += 1;
                        }
                    }
                }
                if *correcting.lock().unwrap() == 0 {
                    break;
                } else {
                    *correcting.lock().unwrap() = 0;
                }
            }
        }
        RunMode::LearningAsync => {
            let mut imgs: Vec<Img> = vec![];
            {
                let files = get_files(vec![IMG_FILES_PATH.to_string()]);
                for path in files.iter() {
                    imgs.push(Img::new(path, MATRIX_SIZE, MATRIX_SIZE));
                }
            };

            let mut rng = rand::thread_rng();

            loop {
                eras += 1;
                imgs.shuffle(&mut rng);

                for img in imgs.iter() {
                    neurons.par_iter_mut().for_each(|neuron| {
                        let np = neuron.power(&img.matrx);
                        let na = (1000.0 * Neuron::activation(&np)).round() / 1000.0;
                        if neuron.shape == img.shape && na < INCREASE_VALUE {
                            neuron.weights_correction(&na, &INCREASE_VALUE, &img.matrx, ALPHA);
                            *correcting.lock().unwrap() += 1;
                            *errors.lock().unwrap() += 1;
                        } else if neuron.shape != img.shape && na > DECREASE_VALUE {
                            neuron.weights_correction(&na, &DECREASE_VALUE, &img.matrx, ALPHA);
                            *correcting.lock().unwrap() += 1;
                            *errors.lock().unwrap() += 1;
                        }
                    })
                }

                if *correcting.lock().unwrap() == 0 {
                    break;
                } else {
                    *correcting.lock().unwrap() = 0;
                }
            }
        }
    }

    if mode != RunMode::Normal {
        for neuron in neurons {
            neuron.weights_write_bin();
            neuron.weights_write_bmp();
        }
        println!("Counts of eras: {}", &eras);
        println!("All errors: {}", errors.lock().unwrap());
    }
}

fn get_files(dirs: Vec<String>) -> Vec<String> {
    let mut files: Vec<String> = vec![];
    for path in dirs {
        for obj in std::fs::read_dir(path).unwrap() {
            files.push(obj.unwrap().path().display().to_string());
        }
    }
    files
}

fn prog_exit() -> ! {
    println!("Null input. Plese enter path to bmp file.");
    std::process::exit(0)
}
