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
        for j, value in enumerate(values):
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
            total_output_error = sum(outputs_error)
            errors.append(total_output_error)

            # --- backward --- #
            if total_output_error > EPSILON:

                aes = list()
                deltas = list()

                for layer_idx, layer in enumerate(reversed(weights)):

                    aes.append(list())
                    deltas.append(list())

                    if layer_idx == 0:
                        for neuron_idx, neuron_weights in enumerate(layer):

                            dE_dO = output[neuron_idx] - correct[neuron_idx]
                            dO_dS = fn.act_derivative(
                                layers_activations[-1][neuron_idx])

                            aes[layer_idx].append(dE_dO * dO_dS)
                            delta = aes[layer_idx][neuron_idx] * \
                                layers_activations[-1][neuron_idx]

                            deltas[layer_idx].append(delta)

                    elif layer_idx != len(weights):

                        for neuron_idx, neuron in enumerate(layer):
                            pass

                        for neuron_idx, neuron_weights in enumerate(layer):
                            deltas[layer_idx].append(neuron_weights * ae)

                # ---- correcting ---- #
                for delta_idx, delta in enumerate(reversed(deltas)):
                    for neuron_idx in range(len(delta)):
                        weights[delta_idx][neuron_idx] -= alpha * \
                            delta[neuron_idx]

        alpha *= 0.999
        loop_count += 1

        print(loop_count, max(errors))

        if loop_count % 100 == 0:
            np.save(CACHEPATH, weights, allow_pickle=True)

        if loop_count > 500:
            print("Too more loops, exit.")
            break
        if max(errors) < EPSILON:
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
