pub const EPERM_DEN: &str = "Create or open weight file error.";

pub const IMG_FILES_PATH: &str = "./.tmp/images";
pub const WEIGHTS_FILES_PATH: [&str; 11] = [
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
    "./.tmp/weights/0.weightsX.bin",
];

pub const WEIGHTS_BMP_PATH: &str = "./.tmp/weights.bmp";

pub const MATRIX_SIZE: usize = 80; // input and weight size
pub const ALPHA: f32 = 0.05; // learning speed

pub const INCREASE_VALUE: f32 = 0.9;
pub const DECREASE_VALUE: f32 = 0.1;

pub const SHAPES: [char; 11] = ['0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'X'];
