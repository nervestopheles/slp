use crate::envs::SHAPES;
use regex::Regex;

#[derive(Clone)]
pub struct Img {
    pub path: String,
    pub shape: char,
    pub matrx: Vec<Vec<f32>>,
}

impl Img {
    pub fn new(path: &String, width: usize, height: usize) -> Self {
        let mut img = Self {
            path: path.clone(),
            shape: ' ',
            matrx: vec![vec![0.0f32; width]; height],
        };
        img.image_read(&path);
        img.shape_read(&path);
        img
    }

    fn shape_read(&mut self, path: &str) {
        if !Regex::new(r".*\.img.\.bmp").unwrap().is_match(path) {
            return;
        }

        let lenth = path.len();
        for (idx, chr) in path.chars().enumerate() {
            if idx == lenth - ".bmp".len() - 1 && SHAPES.contains(&chr)
            /* read shape in file name like 01.img(0).bmp */
            {
                self.shape = chr;
            }
        }
    }

    fn image_read(&mut self, path: &str) {
        let bmp = bmp::open(std::path::Path::new(path)).unwrap_or_else(|e| {
            panic!("Failed to open: {}", e);
        });
        for (x, rows) in self.matrx.iter_mut().enumerate() {
            for (y, value) in rows.iter_mut().enumerate() {
                let px = bmp.get_pixel(x as u32, y as u32);
                *value = (px.r as f32 * px.g as f32 * px.b as f32) / (255.0 * 255.0 * 255.0);
            }
        }
    }
}
