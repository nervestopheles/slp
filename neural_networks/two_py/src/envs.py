import os

CACHEPATH = os.getenv('CACHEPATH', './cache.bin')

MSIZE = os.getenv('MATRXSIZE', 80*80)
MAXERAS = os.getenv('MAXERAS', 500)
ALPHA = os.getenv('ALPHA', 0.05)
EPSILON = os.getenv('EPSILON', 0.5)

H1 = os.getenv('H1', 12)
H2 = os.getenv('H2', 16)
OL = os.getenv('OL', 10)
