# -*- coding: utf-8 -*-
"""
Created on Fri Mar 21 12:15:32 2025

@author: hugon
"""

from dataclasses import dataclass
import numpy as np
import matplotlib.pyplot as plt

@dataclass
class Point:
    x: float
    y: float

    def __add__(self, Z):
        P = Point(self.x + Z.x, self.y + Z.y)
        return P

    def __sub__(self, Z):
        P = Point(self.x - Z.x, self.y - Z.y)
        return P

    def __mul__(self, Z):
        return self.x*Z.x + self.y*Z.y

    @staticmethod
    def norm(P):
        return np.sqrt(P.x**2 + P.y**2)

    def prod_vectoriel(self, B, C):
        return (B.x - self.x)*(C.y - self.y) - (B.y - self.y)*(C.x - self.x)

    def angle(self, B, C):
        dist1 = Point.norm(B - self)
        dist2 = Point.norm(C - self)
        return np.arccos((B - self)*(C - self)/(dist1*dist2))
    
    @staticmethod
    def display(L: list):
        X = list(map(lambda P: P.x,L))
        Y = list(map(lambda P: P.y, L))
        plt.scatter(X,Y, marker = '*', color = 'red')
    
    @staticmethod
    def display_convex_hull(L: list):
        X = list(map(lambda P: P.x,L))
        Y = list(map(lambda P: P.y, L))
        plt.xlabel('x')
        plt.ylabel('y')
        plt.plot(X, Y, linestyle = '-', label = 'convex hull')
        plt.legend()



def graham(L: np.ndarray[Point]):
    assert len(L) >= 3, "Error, there should be three points at least"
    stack = []
    def find_pivot(L: np.ndarray[Point]):
        pivot = np.infty
        idx_min = []
        for j, p in enumerate(L):
            if pivot > p.y:
                pivot = p.y
                idx_min = [j]
            elif pivot == p.y:
                idx_min.append(j)
        if len(idx_min) > 1:
            return np.argmin(list(map(lambda p: p.x, L[idx_min])))
        return idx_min[0]

    pivot_idx = find_pivot(L)
    L[0], L[pivot_idx] = L[pivot_idx], L[0]
    pivot = L[0]
    B = pivot + Point(1,0)
    angle_idx = np.argsort(list(map(lambda P: pivot.angle(B, P), L[1:])))
    L = np.append(pivot, L[angle_idx + 1])
    stack.append(L[0]); stack.append(L[1])
    for i in range(2,len(L)):
        while len(stack) >= 2 and stack[-2].prod_vectoriel(stack[-1], L[i]) < 0:
            stack.pop()
        stack.append(L[i])
    stack.append(pivot)
    return stack

if __name__=='__main__':
    np.random.seed(100)
    List_point = np.random.randn(100, 2)*10
    List_point = np.array([Point(l[0], l[1]) for l in List_point])
    
    stack = graham(List_point)
    
    Point.display(List_point)
    Point.display_convex_hull(stack)