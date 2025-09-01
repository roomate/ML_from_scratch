import matplotlib.pyplot as plt
import numpy as np
import matplotlib.colors as pltcolors
import seaborn as sns


def scatter_label_points(X,y, ax=None, title=''):
    if ax is None:
        fig, ax = plt.subplots(1, figsize=(8, 5))
    colormap = np.array(['r', 'g', 'b'])
    ax.scatter(X[:,0], X[:,1], s=200, c=colormap[y],alpha=0.5)
    ax.set_title(title)


def plotClassification(X, y, model=None, label='',  separatorLabel='Separator', 
            ax=None, bound=[[-1., 1.], [-1., 1.]]):
    """ Plot the SVM separation, and margin """
    colors = ['blue','red']
    labels = [1,-1]
    cmap = pltcolors.ListedColormap(colors)
    if ax is None:
        fig, ax = plt.subplots(1, figsize=(11, 7))
    for k, label in enumerate(labels):
        im = ax.scatter(X[y==label,0], X[y==label,1],  alpha=0.5,label='class '+str(label))

    if model is not None:
        xx = np.array(bound[0])
        plotHyperSurface(ax, bound[0], model, model.b, separatorLabel)
        # Plot margin
        if model.support is not None:
            ax.scatter(model.support[:,0], model.support[:,1], label='Support', s=80, facecolors='none', edgecolors='r', color='r')
            print("Number of support vectors = %d" % (len(model.support)))
            signedDist = model.separating_function(model.support)
            plotHyperSurface(ax, xx, model, -np.min(signedDist) , 'Margin -', linestyle='-.', alpha=0.8)
            plotHyperSurface(ax, xx, model, -np.max(signedDist) , 'Margin +', linestyle='--', alpha=0.8)
            
            margin = (np.max(signedDist) - np.min(signedDist)) / model.norm_f
            ax.set_title('Margin = %.3f' % (margin))
            
        # Plot points on the wrong side of the margin
            totalsignedDist = model.separating_function(X)
            supp_min = X[(totalsignedDist > np.min(signedDist))*(y==-1)]
            supp_max = X[(totalsignedDist < np.max(signedDist))*(y==1)]
            wrong_side_points = np.concatenate([supp_min,supp_max],axis=0)
            
            ax.scatter(wrong_side_points[:,0], wrong_side_points[:,1], label='Beyond the margin', s=80, facecolors='none', 
               edgecolors='grey', color='grey')      
        
    ax.legend(loc='upper left')
    ax.grid()
    ax.set_xlim(bound[0])
    ax.set_ylim(bound[1])
