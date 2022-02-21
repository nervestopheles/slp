mod weights;
use weights::*;

mod other;
use other::*;

fn main() {
    let mut input: Vec<Vec<f32>> = vec![vec![0 as f32; MATRIX_SIZE]; MATRIX_SIZE];
    image_read(IMG_FILE_PATH, &mut input);

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

    let neuron = neuron_power(&input, &weights);
    println!("Neuron power: {}", neuron);
    println!("This is X? {}", activation(neuron));

    weights_write(WEIGHTS_FILE_PATH, weights);
    println!("Sayonara.");
}
