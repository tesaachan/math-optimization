import numpy as np
import matplotlib.pyplot as plt
from matplotlib import ticker
from sys import argv
from coordinate_descent import coordinate_descent
from simplex import simplex

fcount = [0]

def f(x):
    fcount[0] += 1
    return 3*(x[0]**4) - x[0]*x[1] + x[1]**4 - 7*x[0] - 8*x[1] + 2

if __name__ == "__main__":
    x0 = [41.52, -23.4]
    e = 0.000001

    if len(argv) > 1:
        if argv[1] == "coord":
            res = coordinate_descent(x0, e, f)
            print("x = {}\ny = {}".format(*res[0]))
            print("computed f:", fcount[0])
        elif argv[1] == "simplex":
            res = simplex(x0, 2.0, e, 0.5, f)
            print("x = {}\ny = {}".format(*res[0]))
            print("computed f:", fcount[0]//3 - len(res[1][0]))
        print("iter:", len(res[1][0]))

    if len(argv) > 2 and argv[2] == "plot":
        (xv, yv) = (res[1][0], res[1][1])
        n = 256
        size = max((abs(x0[0]//10) + 1)*10, (abs(x0[1]//10) + 1)*10)
        x = np.linspace(-1*size, 1.1*size, n)
        y = np.linspace(-1.1*size, 1.1*size, n)
        xy = np.meshgrid(x, y)
        plt.figure()
        plt.contourf(xy[0], xy[1], f(xy), 5, alpha=1)
        cont = plt.contour(xy[0], xy[1], f(xy), 8, \
        locator=ticker.LogLocator(), colors='black', linewidth=0.01)
        plt.clabel(cont, inline=True, fontsize=10)

        plt.plot(x0[0], x0[1], marker='o')
        plt.plot(xv, yv, label='tail for f(x1,x2)')
        plt.xlabel('x1')
        plt.ylabel('x2')
        plt.title('Coordinate & s1mple visualization. Lab 4. v 23.')
        plt.legend()
        plt.show()
