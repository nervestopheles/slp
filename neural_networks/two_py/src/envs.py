import os

CACHEPATH = os.getenv('CACHEPATH', './cache.bin')

MAXERAS = os.getenv('MAXERAS', 500)
ALPHA = os.getenv('ALPHA', 0.15)
EPSILON = os.getenv('EPSILON', 0.105)
DECRAISE = os.getenv('DECRAISE', 0.99)

MSIZE = os.getenv('MATRXSIZE', 80*80)
H1 = os.getenv('H1', 16)
H2 = os.getenv('H2', 8)
OL = os.getenv('OL', 10)
