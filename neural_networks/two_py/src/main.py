import os
import glob

import numpy as np
import cv2 as cv

import foo as fn
from envs import *
from img import Img


def main():

    # pars args
    opt = fn.read_options()

    # load weights
    if os.path.exists(CACHEPATH+".npy"):
        weights = np.load(CACHEPATH+".npy", allow_pickle=True)
        print("Load saved weights.")
    else:
        weights = fn.gen_weights()
        print("Initializing new weights.")

    # load imgs
    if opt.learn != None:
        files = glob.glob(opt.learn+"/*.img*.bmp")
        imgs = []
        for img in files:
            imgs.append(Img(img))
        imgs = np.asarray(imgs)

    print("Debug")

    # --------------

    # --------------

    np.save(CACHEPATH, weights, allow_pickle=True)

    print("Exit")


if __name__ == "__main__":
    main()
