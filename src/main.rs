mod weights;
use weights::*;

mod other;
use other::*;

const WEIGHTS_FILE_PATH: &str = "/home/soma/tmp/weights.bin";
const MATRIX_SIZE: usize = 80;

//TODO:
//  1. коррекция весов

fn main() {
    let args: Vec<String> = std::env::args().skip(1).collect();
    if args.len() < 1 {
        println!("Null input. Plese enter path to bmp file.");
        std::process::exit(0);
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
        let neuron = neuron_power(&input, &weights);
        println!("Neuron power: {}", neuron);
        println!("Neuron activation value: {}", activation(neuron));
        println!()
    }

    weights_write(WEIGHTS_FILE_PATH, weights);
    println!("Sayonara.");
}
