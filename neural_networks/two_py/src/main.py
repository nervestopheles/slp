import os
import glob

import numpy as np
from random import shuffle

import foo as fn
from envs import *
from img import Img


def main():

    opt = fn.read_options()
    weights = load_weights(CACHEPATH)

    if not opt.learn is None:
        imgs = np.asarray(load_imgs(opt.learn))

    # corrects outputs
    corrects = np.zeros((OL, OL), dtype=float)
    for value in range(10):
        corrects[value][value] = 1

    # --------------

    # --------------

    np.save(CACHEPATH, weights, allow_pickle=True)

    print("Exit")


def load_weights(path):
    if os.path.exists(path+".npy"):
        weights = np.load(path+".npy", allow_pickle=True)
        print("Load saved weights.")
    else:
        weights = fn.gen_weights()
        print("Initializing new weights.")
    return weights


def load_imgs(path):
    files = glob.glob(path + "/*.img*.bmp")
    imgs = list()
    for img in files:
        imgs.append(Img(img))
    return imgs


if __name__ == "__main__":
    main()
