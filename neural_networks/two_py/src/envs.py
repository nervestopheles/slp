import os

CACHEPATH = os.getenv('CACHEPATH', './cache.bin')
MAXERAS = os.getenv('MAXERAS', 500)

ALPHA = os.getenv('ALPHA', 0.15)
EPSILON = os.getenv('EPSILON', 0.105)
DECRAISE = os.getenv('DECRAISE', 0.99)

WMSIZE = os.getenv('WMSIZE', 40)
HMSIZE = os.getenv('HMSIZE', 40)
MSIZE = WMSIZE * HMSIZE

H1 = os.getenv('H1', 12)
H2 = os.getenv('H2', 18)
OL = os.getenv('OL', 10)
