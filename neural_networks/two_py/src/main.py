import os
import glob

import numpy as np
from random import shuffle

import foo as fn
from envs import *
from img import Img


def main():

    alpha = ALPHA
    opt = fn.read_options()
    weights = load_weights(CACHEPATH)

    if not opt.learn is None:
        imgs = np.asarray(load_imgs(opt.learn))

    corrects = np.zeros((OL, OL), dtype=float)
    for i, values in enumerate(corrects):
        for j, _ in enumerate(values):
            if i != j:
                corrects[i][j] = 0.01
            else:
                corrects[i][j] = 0.99

    # --------------

    loop_count = 0

    while True:
        shuffle(imgs)
        errors = list()

        for img in imgs:
            # --- forward --- #
            layers_sums = list()
            layers_activations = list()

            for layer_idx, layer in enumerate(weights):
                if layer_idx == 0:
                    layers_sums.append(layer.dot(img.vec))
                else:
                    layers_sums.append(
                        layer.dot(layers_activations[layer_idx-1]))
                layers_activations.append(
                    fn.activation(layers_sums[layer_idx]))

            # ---- output error ---- #
            output = layers_activations[-1]
            correct = corrects[img.shape]
            outputs_error = 0.5 * np.square(correct - output)

            if max(output) > 0.5:
                out = np.where(output == max(output))
            else:
                out = None

            max_error = max(outputs_error)
            errors.append(max_error)

            # --- backward --- #
            if out != img.shape:

                gradients = list()

                for layer_idx, layer in enumerate(reversed(weights)):

                    if layer_idx == 0:
                        dE_dO = correct - output
                    else:
                        dE_dO = np.sum(
                            gradients[layer_idx-1] * weights[-layer_idx], axis=0)

                    dO_dS = fn.act_derivative(
                        layers_activations[-(layer_idx+1)])

                    if layer_idx+1 == len(weights):
                        dS_dW = img.vec
                    else:
                        dS_dW = layers_activations[-(layer_idx+2)]

                    gradients.append(list())
                    for idx in range(len(layer)):
                        gradients[layer_idx].append(
                            np.array(dE_dO[idx] * dO_dS[idx] * dS_dW))

                # ---- correcting ---- #
                for layer_idx, gradient in enumerate(reversed(gradients)):
                    weights[layer_idx] += alpha * np.array(gradient)

        alpha *= 0.99
        loop_count += 1

        errors = np.array(errors)

        print(loop_count,  max(errors), min(errors), errors.mean())

        if loop_count % 50 == 0:
            np.save(CACHEPATH, weights, allow_pickle=True)

        if loop_count >= 1000:
            print("Too more loops, exit.")
            break
        if errors.mean() < EPSILON:
            print("Learning complete.")
            break

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
