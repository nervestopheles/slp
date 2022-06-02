import os

CACHEPATH = os.getenv('CACHEPATH', './cache.bin')

MAXERAS = os.getenv('MAXERAS', 500)
ALPHA = os.getenv('ALPHA', 0.8)
EPSILON = os.getenv('EPSILON', 0.01)

MSIZE = os.getenv('MATRXSIZE', 80*80)
H1 = os.getenv('H1', 6)
H2 = os.getenv('H2', 8)
OL = os.getenv('OL', 10)
