import numpy as np
import matplotlib.pyplot as plt
from sys import argv
from matplotlib import ticker
from fletcher_reeves import fletcher_reeves
from symmetric_rank_one import symmetric_rank_one

fiter = [0]
def f(x):
    fiter[0] += 1 
    return 3*(x[0]**4) - x[0]*x[1] + x[1]**4 - 7*x[0] - 8*x[1] + 2

if __name__ == "__main__":
    (x0, fr, sr1, plot)  = ([0,0], False, False, False)

    if len(argv) > 1:
        fr = True if argv[1] == "fr" else False
        sr1 = True if argv[1] == "sr1" else False
    if len(argv) > 2:
        plot = True if argv[2] == "plot" else False
    if len(argv) > 3:
        x0 = [float(i) for i in argv[-2:]]
    res = fletcher_reeves(x0, 1e3, 0.001, f) if fr \
    else symmetric_rank_one(x0, 0.001, np.eye(2), f) if sr1 \
    else exit()

    print("x1, x2: {:.3f}, {:.3f}\nf(x1, x2): {:.3f}\n".format(*res[0], f(res[0])))
    print("iters: {}\nf calcs: {}\n".format(res[1], fiter[0]))

    if (plot):
        (xv, yv) = (res[2][0], res[2][1])
        n = 256
        size = max((abs(x0[0]//10) + 1)*10, (abs(x0[1]//10) + 1)*10)
        x = np.linspace(-1*size, 1.1*size, n)
        y = np.linspace(-1.1*size, 1.1*size, n)
        xy = np.meshgrid(x, y)
        plt.figure()
        plt.contourf(xy[0], xy[1], f(xy), 5, alpha=1)
        cont = plt.contour(xy[0], xy[1], f(xy), 8, locator=ticker.LogLocator(), colors='black', linewidth=0.01)
        plt.clabel(cont, inline=True, fontsize=10)

        plt.plot(x0[0], x0[1], marker='o')
        plt.plot(xv, yv, label='tail for f(x1,x2)')
        plt.xlabel('x1')
        plt.ylabel('x2')
        plt.title('FR & SR1 visualization. Lab 4. v 23.')
        plt.legend()
        plt.show()
