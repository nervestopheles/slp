pub const IMG_FILES_PATH: &str = "./.tmp/images";
pub const SHAPES: [char; 10] = ['0', '1', '2', '3', '4', '5', '6', '7', '8', '9'];

pub const MSIZE: usize = 80*80; // input matrix size

pub const H1: usize = 8; // count of neurons on first layer
pub const H2: usize = 12; // count of neurons on second layer
pub const OL: usize = 10; // count of neurons on output layer

pub const _UPPERB: f32 = 0.8; // upper bound
pub const _LOWERB: f32 = 0.2; // lower bound

static mut _ALPHA: f32 = 0.1; // learning speed
