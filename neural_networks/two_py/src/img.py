import cv2 as cv
from envs import MSIZE


class Img():
    def __init__(self, path):
        self.shape = path[-5]
        self.matrx = cv.imread(path, cv.IMREAD_GRAYSCALE).reshape(MSIZE)
