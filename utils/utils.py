import matplotlib.pyplot as plt
import numpy as np

def scatter_label_points(X,y, ax=None, title=''):
    if ax is None:
        fig, ax = plt.subplots(1, figsize=(11, 7))
    colormap = np.array(['r', 'g', 'b'])
    ax.scatter(X[:,0], X[:,1], s=200, c=colormap[y],alpha=0.5)
    ax.set_title(title)

