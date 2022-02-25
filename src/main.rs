mod weights;
use weights::*;

mod other;
use other::*;

const MODE_INCREASE: &str = "--inc";
const MODE_DECREASE: &str = "--dec";

#[derive(PartialEq)]
enum RunMode {
    Normal,
    Increase,
    Decrease,
}

const WEIGHTS_FILE_PATH: &str = "/home/soma/.tmp/weights.bin";
const MATRIX_SIZE: usize = 80;

const INCREASE_VALUE: f32 = 0.8;
const DECREASE_VALUE: f32 = 0.3;
const ALPHA_VALUE: f32 = 0.17;

fn main() {
    let mut args: Vec<String> = std::env::args().skip(1).collect();
    let mode: RunMode = if args.len() != 0 {
        match args[0].as_str() {
            MODE_INCREASE => RunMode::Increase,
            MODE_DECREASE => RunMode::Decrease,
            _ => RunMode::Normal,
        }
    } else {
        prog_exit();
    };

    if mode != RunMode::Normal {
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
        _ => 0.5,
    };

    let mut input: Vec<Vec<f32>> = vec![vec![0 as f32; MATRIX_SIZE]; MATRIX_SIZE];

    let mut era_count: u64 = 0;
    match mode {
        RunMode::Normal => {
            for arg in args.iter() {
                let (np, na) = work(arg.as_str(), &weights, &mut input);
                print_info(arg, &np, &na);
            }
        }
        RunMode::Increase => {
            for arg in args.iter() {
                image_read(arg, &mut input);
                let mut np = neuron_power(&input, &weights);
                let mut na = activation(&np);
                while na < correct_value {
                    weight_correction(&np, &na, &correct_value, &input, &mut weights);
                    np = neuron_power(&input, &weights);
                    na = activation(&np);
                    era_count += 1;
                }
                print_info(arg, &np, &na);
            }
        }
        RunMode::Decrease => {
            for arg in args.iter() {
                image_read(arg, &mut input);
                let mut np = neuron_power(&input, &weights);
                let mut na = activation(&np);
                while na > correct_value {
                    weight_correction(&np, &na, &correct_value, &input, &mut weights);
                    np = neuron_power(&input, &weights);
                    na = activation(&np);
                    era_count += 1;
                }
                print_info(arg, &np, &na);
            }
        }
    }

    weights_write(WEIGHTS_FILE_PATH, weights);
    if mode != RunMode::Normal {
        println!("Counts of eras: {}", era_count);
    }
}

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
