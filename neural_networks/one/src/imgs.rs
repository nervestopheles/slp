#[derive(Clone, PartialEq)]
pub enum ImgShape {
    Cross,
    NonCross,
    Null,
}

#[derive(Clone)]
pub struct Img {
    pub path: String,
    pub shape: ImgShape,
    pub matrx: Vec<Vec<f32>>,
}

impl Img {
    pub fn default(width: usize, height: usize) -> Self {
        Self {
            path: String::new(),
            shape: ImgShape::Null,
            matrx: vec![vec![0.0; width]; height],
        }
    }
    pub fn new(path: String, shape: ImgShape, matrx: Vec<Vec<f32>>) -> Self {
        Self { path, shape, matrx }
    }
}
