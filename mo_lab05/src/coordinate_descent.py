import numpy as np
from scipy import optimize

def coordinate_descent(x0, e, f):
    xv, yv = [x0[0]], [x0[1]]
    xcur = np.array([float(i) for i in x0])
    n = len(x0)
    def loop(xcur, i):
        xprev = np.array(xcur)
        tmpf = (lambda x: f([x, xcur[1]])) \
        if i % n == 0 else (lambda x: f([xcur[0], x]))
        xcur[i % n] = optimize.minimize_scalar(tmpf).x
        xv.append(xcur[0]), yv.append(xcur[1])
        return xcur \
        if np.linalg.norm(np.matrix(xcur) - np.matrix(xprev)) <= e \
        else loop(xcur, i + 1)
    return (loop(xcur, 0), (xv, yv))
