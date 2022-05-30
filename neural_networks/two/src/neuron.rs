pub struct Neuron {
    pub shape: char,
    weights: Vec<Vec<f32>>,
    path: String, // path to weights
}

impl Neuron {
    pub fn new(width: usize, height: usize) -> Self {
        Self {

        }
    }

    pub fn activation(x: &f32) -> f32 {
        1.0 / (1.0 + (-x).exp()) // sigmoid func
    }

    pub fn activation_derivative(/* activation output */ x: &f32) -> f32 {
        x * (1.0 - x) // sigmoid derivative func
    }
}