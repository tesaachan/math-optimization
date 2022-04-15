# SR1
import numpy as np
from scipy import optimize

def symmetric_rank_one(x0, e, hess, f):
    xv, yv = [x0[0]], [x0[1]]
    xv.append(x0[0]), yv.append(x0[1])
    k = [0]
    n = len(x0)
    def loop(x0, hess):
        k[0] += 1
        xcur = np.array(x0)
        grad = optimize.approx_fprime(xcur, f, e**4)
        dk = np.array(-hess * np.matrix(grad).transpose()).transpose().squeeze()
        gk = optimize.minimize_scalar(lambda g: f(xcur+dk*g), bounds=(0,)).x
        xprev, xcur = xcur, xcur + gk*dk
        xv.append(xcur[0]), yv.append(xcur[1])
        prevgrad, grad = grad, optimize.approx_fprime(xcur, f, e**4)
        if (any([abs(grad[i]) > e**2 for i in range(n)])):
            dxk = np.matrix(xcur - xprev).transpose()
            dyk = np.matrix(grad - prevgrad).transpose()
            hess = hess + \
            (np.array(dxk - hess*dyk)*np.array(dxk - hess*dyk).transpose()) / \
            (np.array(dxk - hess*dyk).transpose()*dyk)
            return loop(xcur, hess)
        else:
            return (xcur, k[0], (xv, yv))
    return loop(x0, hess)
