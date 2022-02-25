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
const ALPHA_VALUE: f32 = 0.15;

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
        if args.remove(1).len() == 0 {
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

    let mut input: Vec<Vec<f32>> = vec![vec![0 as f32; MATRIX_SIZE]; MATRIX_SIZE];
    let correct_value = match mode {
        RunMode::Increase => INCREASE_VALUE,
        RunMode::Decrease => DECREASE_VALUE,
        _ => 0.5,
    };

    for arg in &args {
        image_read(arg, &mut input);
        let neuron = neuron_power(&input, &weights);
        let na = activation(&neuron);

        if mode != RunMode::Normal {
            let delta = na - correct_value;
            let derivative = activation_derivative(&neuron);
            for (i, vectors) in input.iter().enumerate() {
                for (j, _value) in vectors.iter().enumerate() {
                    weights[i][j] =
                        weights[i][j] - ALPHA_VALUE * 2.0 * delta * derivative * input[i][j];
                }
            }
        }
        print_info(arg, &neuron, &na);
    }

    weights_write(WEIGHTS_FILE_PATH, weights);
    println!("Sayonara.");
}
