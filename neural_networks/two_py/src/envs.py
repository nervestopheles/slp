import os

# path to save/load weights file
CACHEPATH = os.getenv('CACHEPATH', './cache.bin')
MAXERAS = os.getenv('MAXERAS', 500)  # max era loops

ALPHA = os.getenv('ALPHA', 0.5)  # learning rate
EPSILON = os.getenv('EPSILON', 0.005)  # lower error bound
DECRAISE = os.getenv('DECRAISE', 0.999)  # alpha decraise

WMSIZE = os.getenv('WMSIZE', 40)
HMSIZE = os.getenv('HMSIZE', 40)
MSIZE = WMSIZE * HMSIZE  # matrix size

H1 = os.getenv('H1', 280)  # count of neurons on first hidden layer
H2 = os.getenv('H2', 120)  # count of neurons on second hidden layer
OL = os.getenv('OL', 10)  # count of neurons on output layer
