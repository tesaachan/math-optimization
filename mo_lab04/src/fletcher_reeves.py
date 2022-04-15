# Метод сопряженных градиентов (Флетчера-Ривза)
import numpy as np
from scipy import optimize

def fletcher_reeves(x0, h, e, f):
    xv, yv = [x0[0]], [x0[1]]
    xcur = np.array(x0)
    xv.append(xcur[0]), yv.append(xcur[1])
    n = len(x0)
    k = 0
    prevgrad, grad = 1, optimize.approx_fprime(xcur, f, e**4)
    dk = -grad
    while (any([abs(grad[i]) > e**2 for i in range(n)]) and k < h):
        if (k % n == 0):
            dk = -grad
        else: 
            bk = (np.linalg.norm(grad)**2)/(np.linalg.norm(prevgrad)**2)
            dk = -grad + bk*dk
        tk = optimize.minimize_scalar(lambda t: f(xcur+dk*t), bounds=(0,)).x
        xcur = xcur + tk*dk
        xv.append(xcur[0]), yv.append(xcur[1])
        prevgrad, grad = grad, optimize.approx_fprime(xcur, f, e**4)
        k += 1
    return (xcur, k + 1, (xv, yv))
