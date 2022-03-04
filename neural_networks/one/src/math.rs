pub fn sigmoid(x: &f32) -> f32 {
    1.0 / (1.0 + (-x).exp())
}

pub fn siqmoid_derivative(sigmoid: &f32) -> f32 {
    sigmoid * (1.0 - sigmoid)
}
