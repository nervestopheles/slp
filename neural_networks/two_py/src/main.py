import os
import glob

import numpy as np
from random import shuffle

import foo as fn
from envs import *
from img import Img

opt = fn.read_options()


def learning(path):

    alpha = ALPHA
    weights = fn.load_weights(CACHEPATH)

    imgs = np.asarray(fn.load_imgs(path))

    corrects = np.zeros((OL, OL), dtype=float)
    for i, values in enumerate(corrects):
        for j, _ in enumerate(values):
            if i != j:
                corrects[i][j] = 0
            else:
                corrects[i][j] = 1

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
                out = output.argmax()
            else:
                out = None

            max_error = max(outputs_error)
            errors.append(max_error)

            # --- backward --- #
            if out != img.shape or max_error < 0.01:

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

        alpha *= DECRAISE
        loop_count += 1

        errors = np.array(errors)

        print(loop_count,  max(errors), min(errors), errors.mean())

        if loop_count % 50 == 0:
            np.save(CACHEPATH, weights, allow_pickle=True)

        if loop_count >= MAXERAS:
            print("Too more loops, exit.")
            break
        if errors.mean() < EPSILON:
            print("Learning complete.")
            break

    # --------------

    np.save(CACHEPATH, weights, allow_pickle=True)

    print("Exit")


def testing(path):

    weights = fn.load_weights(CACHEPATH)
    imgs = np.asarray(fn.load_imgs(path))

    errors = 0

    for img in imgs:
        outputs = fn.forward(weights, img)[-1]

        if max(outputs) > 0.45:
            out = outputs.argmax()
        else:
            out = None

        print(f"Image: {img.shape}")
        print(f"Out: {out}")
        print()

        if img.shape != out:
            errors += 1

    print(f"Errors: {errors}, per length: {len(imgs)}")


def predict(path):

    weights = fn.load_weights(CACHEPATH)
    img = Img(path)

    outputs = fn.forward(weights, img)[-1]

    if max(outputs) > 0.45:
        out = outputs.argmax()
    else:
        out = None

    print(f"Out: {out}")


if __name__ == "__main__":
    if not opt.predict is None:
        predict(opt.predict)
    elif not opt.learn is None:
        learning(opt.learn)
    elif not opt.test is None:
        testing(opt.test)
    else:
        print("Dont work?")
        print("Run with '-h' flags =)")
