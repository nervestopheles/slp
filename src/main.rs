mod weights;
use weights::*;

mod other;
use other::*;

const MODE_INCREASE: &str = "--inc";
const MODE_DECREASE: &str = "--dec";
const MODE_LEARNING: &str = "--learn";

#[derive(PartialEq)]
enum RunMode {
    Normal,
    Increase,
    Decrease,
    Learning,
}

const WEIGHTS_FILE_PATH: &str = "/home/soma/.tmp/weights.bin";
const MATRIX_SIZE: usize = 80;

const INCREASE_VALUE: f32 = 0.95;
const DECREASE_VALUE: f32 = 0.1;
const ALPHA_VALUE: f32 = 0.05;

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
        };
    }

    let correct_value = match mode {
        RunMode::Increase => INCREASE_VALUE,
        RunMode::Decrease => DECREASE_VALUE,
        _ => 0.0,
    };

    let mut input: Vec<Vec<f32>> = vec![vec![0 as f32; MATRIX_SIZE]; MATRIX_SIZE];

    let mut era_count: u64 = 0;
    match mode {
        RunMode::Normal => {
            for arg in args.iter() {
                let (np, na) = work(arg.as_str(), &weights, &mut input);
                print_info(arg, &np, &na);
                println!("{}", &na);
                println!();
            }
        }
        RunMode::Increase => {
            for arg in args.iter() {
                image_read(arg, &mut input);
                let mut np = neuron_power(&input, &weights);
                let mut na = activation(&np);
                print_info(arg, &np, &na);
                while na < correct_value {
                    weight_correction(&np, &na, &correct_value, &input, &mut weights);
                    np = neuron_power(&input, &weights);
                    na = activation(&np);
                    era_count += 1;
                }
                println!("{}", &na);
                println!();
            }
        }
        RunMode::Decrease => {
            for arg in args.iter() {
                image_read(arg, &mut input);
                let mut np = neuron_power(&input, &weights);
                let mut na = activation(&np);
                print_info(arg, &np, &na);
                while na > correct_value {
                    weight_correction(&np, &na, &correct_value, &input, &mut weights);
                    np = neuron_power(&input, &weights);
                    na = activation(&np);
                    era_count += 1;
                }
                println!("{}", &na);
                println!();
            }
        }
        RunMode::Learning => {
            const INCREASES_PATH: &str = "/home/soma/Work/Learning/NeuroNetwork/images/crosses";
            const DECREASES_PATH: &str = "/home/soma/Work/Learning/NeuroNetwork/images/other";

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

            let mut eras: u64 = 0;
            let mut errors: u64 = 0;
            let mut correcting: u64 = 1;

            while correcting != 0 {
                correcting = 0;
                for matrx in increases_matrxs.iter() {
                    let np = neuron_power(&matrx, &weights);
                    let na = activation(&np);
                    // Произвожу округление 'na' для избежания ошибки представления float чисел.
                    if (100.0 * na).round() / 100.0 < INCREASE_VALUE {
                        weight_correction(&np, &na, &INCREASE_VALUE, matrx, &mut weights);
                        correcting += 1;
                        errors += 1;
                        println!("Inc - np: {}, na: {}", &np, &na);
                    }
                }
                for matrx in decrases_matrxs.iter() {
                    let np = neuron_power(&matrx, &weights);
                    let na = activation(&np);
                    // Произвожу округление 'na' для избежания ошибки представления float чисел.
                    if (100.0 * na).round() / 100.0 > DECREASE_VALUE {
                        weight_correction(&np, &na, &DECREASE_VALUE, matrx, &mut weights);
                        correcting += 1;
                        errors += 1;
                        println!("Dec - np: {}, na: {}", &np, &na);
                    }
                }
                eras += 1;
            }
            println!("Counts of eras: {}", &eras);
            println!("All errors: {}", &errors);
        }
    }

    weights_write(WEIGHTS_FILE_PATH, &weights);
    if mode != RunMode::Normal && mode != RunMode::Learning {
        println!("Counts of eras: {}", era_count);
    }
}

/* ------------ foos ------------*/

fn work(arg: &str, weights: &Vec<Vec<f32>>, input: &mut Vec<Vec<f32>>) -> (f32, f32) {
    let np = {
        image_read(arg, input);
        neuron_power(input, weights)
    };
    let na = activation(&np);
    (np, na)
}

fn weight_correction(
    np: &f32,
    na: &f32,
    correct_value: &f32,
    input: &Vec<Vec<f32>>,
    weights: &mut Vec<Vec<f32>>,
) {
    let delta = na - correct_value;
    let derivative = activation_derivative(np);
    for (i, vectors) in input.iter().enumerate() {
        for (j, _value) in vectors.iter().enumerate() {
            weights[i][j] = weights[i][j] - ALPHA_VALUE * 2.0 * delta * derivative * input[i][j];
        }
    }
}
