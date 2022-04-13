import numpy as np
import matplotlib.pyplot as plt
from matplotlib import ticker


def f(x, y):
    return 100*(y - x*x)**2 + (1 - x)**2


def H(x, y):
    return np.matrix([[1200 * x * x - 400 * y + 2, -400 * x],
                      [-400 * x, 200]])


def grad(x, y):
    return np.matrix([[2*x - 2 + 400*(x * (x*x - y))],
                      [200 * (y - x*x)]])


def delta_grad(x, y):
    g = grad(x, y)

    alpha = 0.002
    delta = alpha * g
    return delta


# ----- Рисование контурных линий -----
# Количество данных
n = 256
# Определить х, у
x = np.linspace(-1, 1.1, n)
y = np.linspace(-0.1, 1.1, n)

# Генерировать данные сетки
X, Y = np.meshgrid(x, y)

plt.figure()
# Заполните цвет линии контура, 8 - линия контура, разделенная на несколько частей
plt.contourf(X, Y, f(X, Y), 5, alpha=0, cmap=plt.cm.hot)
# Нарисовать контурные линии
C = plt.contour(X, Y, f(X, Y), 8, locator=ticker.LogLocator(), colors='black', linewidth=0.01)
# Нарисовать данные контура
plt.clabel(C, inline=True, fontsize=10)
# ---------------------

x = np.matrix([[-0.2],
               [ 0.4]])

tol = 0.00001
xv = [x[0, 0]]
yv = [x[1, 0]]

plt.plot(x[0, 0], x[1, 0], marker='o')

for t in range(6000):
    delta = delta_grad(x[0, 0], x[1, 0])
    if abs(delta[0, 0]) < tol and abs(delta[1, 0]) < tol:
        break
    x = x - delta
    xv.append(x[0, 0])
    yv.append(x[1, 0])

plt.plot(xv, yv, label='tail for f(x1,x2)')
# plt.plot(xv, yv, label='track', marker='o')
plt.xlabel('x1')
plt.ylabel('x2')
plt.title('Gradient descent visualization. Lab 3. v 23.')
plt.legend()
plt.show()
