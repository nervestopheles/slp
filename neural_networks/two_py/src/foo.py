import sys
import glob
import argparse

import numpy as np

from envs import *
from img import Img


def forward(weights, img):
    layers_sums = list()
    layers_activations = list()

    for layer_idx, layer in enumerate(weights):
        if layer_idx == 0:
            layers_sums.append(layer.dot(img.vec))
        else:
            layers_sums.append(
                layer.dot(layers_activations[layer_idx-1]))
        layers_activations.append(
            activation(layers_sums[layer_idx]))

    return layers_activations


def read_options(args=sys.argv[1:]) -> argparse.Namespace:
    parser = argparse.ArgumentParser()
    parser.add_argument(
        "--predict", help="Get image and testing.", )
    parser.add_argument(
        "--learn", help="Get all image with file format '*.img*.bmp' from folder and learning.")
    parser.add_argument(
        "--test", help="Get all image with file format '*.img*.bmp' from folder and testing.")
    return parser.parse_args(args)


def gen_weights() -> np.ndarray:
    # np.random.seed(1)
    return np.asarray([
        np.random.uniform(-0.3, 0.3, (H1, MSIZE)),  # h1
        np.random.uniform(-0.3, 0.3, (H2, H1)),     # h2
        np.random.uniform(-0.3, 0.3, (OL, H2))      # ol
    ], dtype=object)


def load_weights(path):
    if os.path.exists(path+".npy"):
        weights = np.load(path+".npy", allow_pickle=True)
        print("Load saved weights.")
    else:
        weights = gen_weights()
        print("Initializing new weights.")
    return weights


def load_imgs(path):
    files = glob.glob(path + "/*.img*.bmp")
    imgs = list()
    for img in files:
        imgs.append(Img(img))
    return np.array(imgs)


def activation(x):
    return 1.0 / (1.0 + np.exp(-x))  # sigmoid func


def act_derivative(x):
    return x * (1.0 - x)  # sigmoid derivative func
