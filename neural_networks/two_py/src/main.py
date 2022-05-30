import os
import glob

import numpy as np
from random import shuffle

import foo as fn
from envs import *
from img import Img


def main():

    # init
    alpha = ALPHA
    opt = fn.read_options()

    # load weights
    if os.path.exists(CACHEPATH+".npy"):
        weights = np.load(CACHEPATH+".npy", allow_pickle=True)
        print("Load saved weights.")
    else:
        weights = fn.gen_weights()
        print("Initializing new weights.")

    # load imgs
    if opt.learn is None:
        files = glob.glob(opt.learn+"/*.img*.bmp")
        imgs = list()
        for img in files:
            imgs.append(Img(img))
        imgs = np.asarray(imgs)

    # corrects outputs
    corrects = np.zeros((OL, OL), dtype=float)
    for value in range(10):
        corrects[value][value] = 1

    # --------------

    loop = 0
    mses = np.zeros(len(imgs), dtype=float)

    while True:
        shuffle(imgs)
        for img_num, img in enumerate(imgs):
            activations = list()
            for idx, layers in enumerate(weights):
                if idx == 0:
                    activations.append(fn.activation(layers.dot(img.vec)))
                else:
                    activations.append(fn.activation(
                        layers.dot(activations[idx-1])))

            deltas = np.square(corrects[img.shape] - activations[-1])
            mses[img_num] = deltas.mean()

            if mses[img_num] > EPSILON:
                derivatives = np.array(fn.act_derivative(activations[-1]))

                print()

        loop += 1
        if loop > 1000:
            print("Too more loops on model learning.")
            break
        if mses.max() < EPSILON:
            print("Learning complete.")
            break

    # --------------

    np.save(CACHEPATH, weights, allow_pickle=True)

    print("Exit")


if __name__ == "__main__":
    main()
