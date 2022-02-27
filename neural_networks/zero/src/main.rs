pub mod other;
use other::*;

pub mod weights;
use weights::*;

const MODE_LEARNING: &str = "--learn";
const MODE_INCREASE: &str = "--inc";
const MODE_DECREASE: &str = "--dec";

const INCREASE_VALUE: f32 = 0.9;
const DECREASE_VALUE: f32 = 0.1;

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
            weights_write_bin(WEIGHTS_FILE_PATH, &weights);
            weights_write_bmp(&weights);
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
            let get_files = |path: &str| -> Vec<String> {
                let mut files: Vec<String> = vec![];
                for obj in std::fs::read_dir(path).unwrap() {
                    files.push(obj.unwrap().path().display().to_string());
                }
                files
            };
            let get_matrxs = |files: &Vec<String>| -> Vec<Vec<Vec<f32>>> {
                let mut matrxs: Vec<Vec<Vec<f32>>> =
                    vec![vec![vec![0.0; MATRIX_SIZE]; MATRIX_SIZE]; files.len()];
                for (idx, path) in files.iter().enumerate() {
                    image_read(path, &mut matrxs[idx]);
                }
                matrxs
            };

            let increases_files: Vec<String> = get_files(INCREASES_PATH);
            let increases_matrxs: Vec<Vec<Vec<f32>>> = get_matrxs(&increases_files);

            let decreases_files: Vec<String> = get_files(DECREASES_PATH);
            let decrases_matrxs: Vec<Vec<Vec<f32>>> = get_matrxs(&decreases_files);

            while correcting != 0 {
                correcting = 0;
                for matrx in increases_matrxs.iter() {
                    let np = neuron_power(&matrx, &weights);
                    let na = activation(&np);
                    // Произвожу округление 'na' для избежания ошибки представления float чисел.
                    if (100.0 * na).round() / 100.0 < INCREASE_VALUE {
                        weight_correction(&na, &INCREASE_VALUE, matrx, &mut weights);
                        correcting += 1;
                        errors += 1;
                    }
                }
                for matrx in decrases_matrxs.iter() {
                    let np = neuron_power(&matrx, &weights);
                    let na = activation(&np);
                    // Произвожу округление 'na' для избежания ошибки представления float чисел.
                    if (100.0 * na).round() / 100.0 > DECREASE_VALUE {
                        weight_correction(&na, &DECREASE_VALUE, matrx, &mut weights);
                        correcting += 1;
                        errors += 1;
                    }
                }
                eras += 1;
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
