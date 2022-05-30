mod img;
mod envs;

use rand::Rng;
use crate::img::Img;
use crate::envs::{H1, H2, MSIZE, OL};

fn main() {
    /* init rnd seed */
    let mut rng = rand::thread_rng();

    /* announcement weights arrays */
    let h1: Vec<Vec<f32>> = vec![vec![0.0; MSIZE]; H1]; // first hidden layer
    let h2: Vec<Vec<f32>> = vec![vec![0.0; H1]; H2]; // second hidden layer
    let ol: Vec<Vec<f32>> = vec![vec![0.0; H2]; OL]; // output layer of neuron

    let mut network = [h1, h2, ol]; // array of layers

    /* init weights arrays */
    for layer in network.iter_mut() {
        for neuron in layer.iter_mut() {
            for weight in neuron.iter_mut() {
                *weight = rng.gen_range(-0.3..=0.3);
            }
        }
    }

    /* init input vectors */
    let mut imgs: Vec<Img> = vec![];
    {
        let files = get_files(vec![IMG_FILES_PATH.to_string()]);
        for path in files.iter() {
            imgs.push(Img::new(path, MSIZE, MSIZE));
        }
    };

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
