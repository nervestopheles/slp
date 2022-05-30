import cv2 as cv
import numpy as np
from envs import MSIZE


class Img():
    def __init__(self, path):
        self.shape = int(path[-5])
        self.vec = cv.imread(path, cv.IMREAD_GRAYSCALE, ).astype(
            np.float).reshape(MSIZE).transpose() / 255.0
