pub const EPERM_DEN: &str = "Create or open weight file error.";

pub const WEIGHTS_FILE_PATH: &str = "./.tmp/weights.bin";
pub const WEIGHTS_BMP_PATH: &str = "./.tmp/weights.bmp";

pub const INCREASES_PATH: &str = "./.tmp/learning/crosses";
pub const DECREASES_PATH: &str = "./.tmp/learning/other";

pub const MATRIX_SIZE: usize = 80; // input and weight size
pub const ALPHA: f32 = 0.65; // learning speed

pub const INCREASE_VALUE: f32 = 0.8;
pub const DECREASE_VALUE: f32 = 0.2;
