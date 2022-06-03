from curses.ascii import isdigit
import cv2
import numpy as np
from envs import HMSIZE, MSIZE, WMSIZE


class Img():
    def __init__(self, path):
        # --- copy paste magic --- #

        # Load image, in grayscale mode, and find edges
        img = cv2.imread(path, cv2.IMREAD_GRAYSCALE)
        thresh = cv2.threshold(
            img, 0, 255, cv2.THRESH_OTSU + cv2.THRESH_BINARY)[1]

        # Find contour and sort by contour area
        cnts = cv2.findContours(
            thresh, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
        cnts = cnts[0] if len(cnts) == 2 else cnts[1]
        cnts = sorted(cnts, key=cv2.contourArea, reverse=True)

        # Find bounding box and extract ROI
        for cnt in cnts:
            x, y, w, h = cv2.boundingRect(cnt)
            ROI = img[y:y+h, x:x+w]
            break

        dimension = (WMSIZE, HMSIZE)
        resized = cv2.resize(ROI, dimension, interpolation=cv2.INTER_AREA)

        # ------------------------ #

        # converting matrix to vector and normilaize
        self.vec = resized.reshape(
            MSIZE).transpose().astype(np.float32) / 255.0

        char = path[-5]
        if isdigit(char):
            self.shape = int(path[-5])
        else:
            self.shape = None
