import sys
import argparse

import numpy as np
from envs import *


def read_options(args=sys.argv[1:]) -> argparse.Namespace:
    parser = argparse.ArgumentParser()
    parser.add_argument(
        "--learn", help="Get all image from folder and learning.")
    return parser.parse_args(args)


def gen_weights() -> np.ndarray:
    return np.array([
        np.random.uniform(-0.3, 0.3, (H1, MSIZE)),  # h1
        np.random.uniform(-0.3, 0.3, (H2, H1)),     # h2
        np.random.uniform(-0.3, 0.3, (OL, H2))      # ol
    ])


def activation(x) -> float:
    return 1.0 / (1.0 + np.exp(-x))  # sigmoid func


def act_derivative(x) -> float:
    return x * (1.0 - x)  # sigmoid derivative func
