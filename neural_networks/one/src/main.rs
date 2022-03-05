pub mod consts;
pub mod img;
pub mod math;
pub mod neuron;

use crate::consts::*;
use crate::img::*;
use crate::neuron::*;

use rand::prelude::SliceRandom;
use std::path::Path;

const MODE_LEARNING: &str = "--learn";
const MODE_INCREASE: &str = "--inc";
const MODE_DECREASE: &str = "--dec";

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

    // TODO: инициализировать массив нейронов
    let mut neurons: Vec<Neuron> = {
        let mut neurons: Vec<Neuron> = vec![];
        let weights_paths: [&str; 11] = WEIGHTS_FILES_PATH;
        for path in weights_paths {
            let mut neuron = Neuron::new(MATRIX_SIZE, MATRIX_SIZE);
            if Path::new(path).exists() {
                neuron.shape_read(path);
                neuron.weights_read(path);
            } else {
                std::fs::File::create(path).expect(EPERM_DEN);
                neuron.weights_init(path);
                if mode != RunMode::Learning {
                    neuron.weights_write_bin();
                    neuron.weights_write_bmp();
                }
            };
            neurons.push(neuron);
        }
        neurons
    };

    let mut eras: u64 = 0;
    let mut errors: u64 = 0;
    let mut correcting: u64 = 1;

    match mode {
        RunMode::Normal => {
            for path in args.iter() {
                let img: Img = Img::new(path, MATRIX_SIZE, MATRIX_SIZE);
                // let nps: Vec<f32> = vec![0.0; SHAPES.len()]; /* neuron powers */
                // let nas: Vec<f32> = vec![0.0; SHAPES.len()]; /* neuron activations */
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
                    Image shape: {}\n
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
        RunMode::Learning => {
            let mut imgs: Vec<Img> = {
                let files = get_files(vec![IMG_FILES_PATH.to_string()]);
                let mut imgs: Vec<Img> = vec![];
                for path in files.iter() {
                    imgs.push(Img::new(path, MATRIX_SIZE, MATRIX_SIZE));
                }
                imgs
            };

            let mut rng = rand::thread_rng();
            while correcting != 0 {
                eras += 1;
                correcting = 0;
                imgs.shuffle(&mut rng);

                for img in imgs.iter() {
                    let mut nps: Vec<f32> = vec![];
                    let mut nas: Vec<f32> = vec![];

                    for (idx, neuron) in neurons.iter_mut().enumerate() {
                        nps.push(neuron.power(&img.matrx));
                        nas.push(Neuron::activation(&nps[idx]));
                        if neuron.shape == img.shape && nas[idx] < INCREASE_VALUE {
                            neuron.weights_correction(&nas[idx], &INCREASE_VALUE, &img.matrx, ALPHA);
                            correcting += 1;
                            errors += 1;
                        } else if neuron.shape != img.shape && nas[idx] > DECREASE_VALUE {
                            neuron.weights_correction(&nas[idx], &DECREASE_VALUE, &img.matrx, ALPHA);
                            correcting += 1;
                            errors += 1;
                        }
                    }
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
        println!("All errors: {}", &errors);
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
