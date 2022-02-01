import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
from matplotlib.widgets import Slider, Button

#visualization of the starting positions vs the coordinate lines in 2D

_tupes = []
for x in range(0, 5):
    for y in range(0, 5):
        _tupes.append((x/5, y/5))

#heavy lifting for dist will be in c++..
def dist(t):
    return 1/5

_tupesCenter = [(x[0] + dist(_tupes)/2, x[1] + dist(_tupes)/2) for x in _tupes]

for x in range(0, 5) :
    _tupes.append((x/5, 1))
    _tupes.append((1, x/5))
_tupes.append((1, 1))

plt.scatter(*zip(*_tupes), color='blue')
plt.scatter(*zip(*_tupesCenter), color='red', linewidths=.7)
plt.show()