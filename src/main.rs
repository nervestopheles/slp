mod weights;
use weights::*;

mod other;
use other::*;

const WEIGHTS_FILE_PATH: &str = "/home/soma/.tmp/weights.bin";
const MATRIX_SIZE: usize = 80;

const GOOD_VALUE: f32 = 0.8;
const BAD_VALUE: f32 = 0.3;
const ALPHA_VALUE: f32 = 0.15;

// enum Mode {
//     Normal,
//     Increase,
//     Decrease,
// }

fn main() {
    let mut args: Vec<String> = std::env::args().skip(1).collect();
    if args.len() < 1 {
        println!("Null input. Plese enter path to bmp file.");
        std::process::exit(0);
    }

    let learning: bool = if args[0].eq("--learn") { true } else { false };
    if learning {
        args = std::env::args().skip(2).collect();
        if args.len() < 1 {
            println!("Null input. Plese enter path to bmp file.");
            std::process::exit(0);
        }
    }

    let circle: bool = if args[0].eq("--other") { true } else { false };
    if circle {
        args = std::env::args().skip(2).collect();
        if args.len() < 1 {
            println!("Null input. Plese enter path to bmp file.");
            std::process::exit(0);
        }
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

    for arg in &args {
        image_read(arg, &mut input);
        let mut neuron = neuron_power(&input, &weights);
        let mut na = activation(&neuron);

        if learning {
            while na < GOOD_VALUE {
                let delta = na - GOOD_VALUE;
                let derivative = activation_derivative(&neuron);
                for (i, vectors) in input.iter().enumerate() {
                    for (j, _value) in vectors.iter().enumerate() {
                        weights[i][j] =
                            weights[i][j] - ALPHA_VALUE * 2.0 * delta * derivative * input[i][j];
                    }
                }
                neuron = neuron_power(&input, &weights);
                na = activation(&neuron);
            }
        }

        if circle {
            while na > BAD_VALUE {
                let delta = na - BAD_VALUE;
                let derivative = activation_derivative(&neuron);
                for (i, vectors) in input.iter().enumerate() {
                    for (j, _value) in vectors.iter().enumerate() {
                        weights[i][j] =
                            weights[i][j] - ALPHA_VALUE * 2.0 * delta * derivative * input[i][j];
                    }
                }
                neuron = neuron_power(&input, &weights);
                na = activation(&neuron);
            }
        }

        println!("Image name: {}", arg);
        println!("Neuron power: {}", &neuron);
        println!("Neuron activation value: {}", &na);
        println!()
    }

    weights_write(WEIGHTS_FILE_PATH, weights);
    println!("Sayonara.");
}

// fn learn(np: &f32, na: &f32) {
//     let delta = na - GOOD_VALUE;
//     let derivative = activation_derivative(&neuron);
//     for (i, vectors) in input.iter().enumerate() {
//         for (j, _value) in vectors.iter().enumerate() {
//             weights[i][j] = weights[i][j] - ALPHA_VALUE * 2.0 * delta * derivative * input[i][j];
//         }
//     }
//     neuron = neuron_power(&input, &weights);
//     na = activation(&neuron);
// }
