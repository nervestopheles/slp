pub const EPERM_DEN: &str = "Create or open weight file error.";

pub const SHAPES: [char; 10] = ['0', '1', '2', '3', '4', '5', '6', '7', '8', '9'];

pub const IMG_FILES_PATH: &str = "./.tmp/images";
pub const WEIGHTS_FILES_PATH: [&str; 10] = [
    "./.tmp/weights/0.weights0.bin",
    "./.tmp/weights/0.weights1.bin",
    "./.tmp/weights/0.weights2.bin",
    "./.tmp/weights/0.weights3.bin",
    "./.tmp/weights/0.weights4.bin",
    "./.tmp/weights/0.weights5.bin",
    "./.tmp/weights/0.weights6.bin",
    "./.tmp/weights/0.weights7.bin",
    "./.tmp/weights/0.weights8.bin",
    "./.tmp/weights/0.weights9.bin",
];

pub const WEIGHTS_BMP_PATH: &str = "./.tmp/weights.bmp";

pub const MATRIX_SIZE: usize = 80; // input and weight size
pub const ALPHA: f32 = 0.1; // learning speed

pub const INCREASE_VALUE: f32 = 0.95;
pub const DECREASE_VALUE: f32 = 0.05;
