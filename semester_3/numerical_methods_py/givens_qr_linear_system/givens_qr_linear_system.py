import numpy as np

np.set_printoptions(precision=4, suppress=True, linewidth=150)

A = np.array([
    [ 6,  0, -2,  0, -1],
    [ 0,  5,  0, -2,  0],
    [-2,  0,  4,  0, -1],
    [ 0, -2,  0,  3,  0],
    [-1,  0, -1,  0,  3],
], dtype=float)
n = len(A)


def num(v):
    return f"{round(v, 4) + 0.0:g}"


def vec_text(v):
    return "[" + " ".join(num(t) for t in v) + "]"


def mat_text(M):
    cells = [[num(t) for t in row] for row in M]
    w = max(len(c) for row in cells for c in row)
    w += 1 - w % 2
    rows = ["[ " + "   ".join(c.center(w) for c in row) + " ]" for row in cells]
    return "[" + "\n ".join(rows) + "]"


def system_to_text(A, f):
    lines = []
    for i in range(n):
        text = ""
        for j in range(n):
            a = A[i, j]
            if a == 0:
                continue
            term = f"{abs(a):g}·x{j+1}"
            if not text:
                text = ("-" if a < 0 else "") + term
            else:
                text += (" - " if a < 0 else " + ") + term
        lines.append(f"{text} = {f[i]:g}")
    return lines


def sqrt_method(A, f):
    S = np.zeros((n, n))
    d = np.zeros(n)
    log = []

    for i in range(n):
        taken = sum(S[k, i] ** 2 * d[k] for k in range(i))
        t = A[i, i] - taken
        d[i] = 1.0 if t >= 0 else -1.0
        S[i, i] = np.sqrt(abs(t))
        row = [f"t = {num(A[i, i])} - {num(taken)} = {num(t)}  ->  "
               f"d{i+1} = {d[i]:+.0f},  s{i+1}{i+1} = √{num(abs(t))} = {num(S[i, i])}"]

        for j in range(i + 1, n):
            ssum = sum(S[k, i] * d[k] * S[k, j] for k in range(i))
            S[i, j] = (A[i, j] - ssum) / (S[i, i] * d[i])
            if A[i, j] != 0 or ssum != 0:
                row.append(f"s{i+1}{j+1} = ({num(A[i, j])} - {num(ssum)}) / "
                           f"{num(S[i, i] * d[i])} = {num(S[i, j])}")
        log.append(row)

    y = np.zeros(n)
    for i in range(n):
        y[i] = (f[i] - sum(S[k, i] * y[k] for k in range(i))) / S[i, i]

    x = np.zeros(n)
    for j in range(n - 1, -1, -1):
        ssum = sum(S[j, k] * x[k] for k in range(j + 1, n))
        x[j] = (y[j] - d[j] * ssum) / (d[j] * S[j, j])

    det = np.prod(d * np.diag(S) ** 2)
    return S, d, y, x, det, log


if __name__ == "__main__":
    f = np.array(list(map(float, input(f"Введите {n} чисел правой части через пробел: ").split())))
    if len(f) != n:
        raise SystemExit(f"Нужно ровно {n} чисел")
    if not np.allclose(A, A.T):
        raise SystemExit("Матрица не симметрична, метод квадратного корня не применим")

    S, d, y, x, det, log = sqrt_method(A, f)

    print("\n=== УСЛОВИЕ: решить систему A·x = f ===")
    print("Матрица A:\n" + mat_text(A))
    print("Вектор f:", vec_text(f))
    print("То есть система уравнений:")
    for line in system_to_text(A, f):
        print("  ", line)

    print("\n=== ШАГ 1. Разложение A = Sᵀ·D·S ===")

    print("\nИтог: матрица S (верхняя треугольная):\n" + mat_text(S))
    print("Диагональ D (знаки):", vec_text(d))

    print("\n=== ШАГ 2. Прямой ход: Sᵀ·y = f ===")
    print("Вспомогательный вектор y:", vec_text(y))

    print("\n=== ШАГ 3. Обратный ход: D·S·x = y ===")

    print("\n=== ОТВЕТ ===")
    for i in range(n):
        print(f"  x{i+1} = {num(x[i])}")
    print("\nВектор x =", vec_text(x))
    print(f"Определитель матрицы A: det A = {num(det)}")