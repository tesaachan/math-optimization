import numpy as np
from scipy import optimize
from functools import reduce
import matplotlib.pyplot as plt
from matplotlib import ticker

fcount = [0]

def f(x):
    fcount[0] += 1
    return 3*(x[0]**4) - x[0]*x[1] + x[1]**4 - 7*x[0] - 8*x[1] + 2

def simplex(x0, a, e, d, f):
    xcur = [[[]]]
    xv, yv = [x0[0]], [x0[1]]
    n = len(x0)
    r = a*(np.sqrt(n+1) - 1 + n)/(n*np.sqrt(2))
    s = a*(np.sqrt(n+1) - 1)/(n*np.sqrt(2))
    for i in range(n):
        xcur[0][0].append(x0[i])
    for _ in range(n):
        xcur[0].append([])
    for i in range(n):
        for j in range(n):
            xcur[0][i+1].append(x0[j] + r if j != i else x0[j] + s)
        xv.append(xcur[0][i+1][0]), yv.append(xcur[0][i+1][1])
    xcur[0].sort(key=lambda x: f(x))

    def end_condition(xcur, ind):
        sum = [(f(i) - f(xcur[ind][0]))**2 for i in xcur[ind][1:]]
        return np.sqrt(reduce(lambda x, y: x + y, sum))

    # end = 100
    def shorten_simplex(xcur, ind):
        # if ind == end:
        #     return xcur[ind][0]
        xmain = xcur[ind - 1][0]
        xcur.append([])
        xcur[ind + 1].append(xmain)
        for i in range(1, n + 1):
            xcur[ind + 1].append(
                (np.matrix(xmain) + d*(np.matrix(xcur[ind - 1][i]) - np.matrix(xmain)))
                .tolist()[0]
            )
        return build_new_point(xcur, n, ind + 1)

    def build_new_point(xcur, sep, ind):
        if end_condition(xcur, ind) <= e:
            return xcur[ind][0]
        # if ind == end:
        #     return xcur[ind][0]
        xcur.append([])
        xcur[ind + 1] = xcur[ind][:sep] + xcur[ind][sep + 1:]
        xnew = ((2/n)*reduce(lambda x, y: x + y, np.matrix(xcur[ind + 1])) - \
            np.matrix(xcur[ind][sep])).tolist()[0]
        xv.append(xnew[0]), yv.append(xnew[1])
        xcur[ind + 1].append(xnew)
        xcur[ind + 1].sort(key=lambda x: f(x))
        if xcur[ind + 1][n] == xnew:
            return shorten_simplex(xcur, ind + 2) \
            if sep - 1 == 0 else build_new_point(xcur, sep - 1, ind)
        else:
            return build_new_point(xcur, n, ind + 1)

    ans = build_new_point(xcur, n, 0)
    return (ans, (xv, yv))
