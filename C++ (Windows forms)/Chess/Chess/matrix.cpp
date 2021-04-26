#include "matrix.h"

matrix::matrix(const matrix& a) {
    N = a.N;
    M = a.M; 
    data.resize(N);
    for (int i = 0; i < N; ++i) {
        data[i].resize(M);
    }
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            data[i][j] = a.data[i][j];
        }
    }
}

matrix::matrix(int n, int m, vector<vector<complex>> d) {
    N = n;
    M = m;
    data.resize(N);
    for (int i = 0; i < N; ++i) {
        data[i].resize(M);
    }
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            data[i][j] = d[i][j];
        }
    }
}

matrix::matrix(int n, int m) {
    N = n;
    M = m;
    data.resize(N);
    for (int i = 0; i < N; ++i) {
        data[i].resize(M);
    }
}

matrix::matrix(vector<double> v) {
    N = v.size();
    M = 1;
    data.resize(N);
    for (int i = 0; i < N; ++i) {
        data[i].resize(M);
    }
    for(int i = 0; i < N; ++i) data[i][0] = v[i];
}

matrix::matrix(int n, int m, double from, double to) {
    N = n;
    M = m;
    data.resize(N);
    for (int i = 0; i < N; ++i) {
        data[i].resize(M);
    }
    for(int i = 0; i < N; ++i) {
        for(int j = 0; j < M; ++j) {
            data[i][j] = from + (double)((double)rand()/RAND_MAX)*(to-from);
        }
    }
}

matrix::matrix() {
    N = 1;
    M = 1;
    data.resize(1);
    for (int i = 0; i < 1; ++i) {
        data[i].resize(1);
    }
    data[0][0] = 1;
}

void matrix::swapLines(int i1, int i2) {
    complex temp;
    for (int i = 0; i < M; ++i) {
        temp = data[i1][i];
        data[i1][i] = data[i2][i];
        data[i2][i] = temp;
    }
}

matrix matrix::transpose() {
    matrix temp(M, N);
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            temp(j, i) = data[i][j];
        }
    }
    return temp;
}

int matrix::toTrinagular() {
    int swaps = 0;
    int size = M < N ? M : N;
    for (int L1 = 0; L1 < size; ++L1) {
        for (int L2 = L1 + 1; L2 < N; ++L2) {
            complex l1 = data[L1][L1];
            complex l2 = data[L2][L1];

            if (l2 == 0) continue;
            else if (l1 == 0) {
                swapLines(L1, L2);
                ++swaps;
                l1 = data[L1][L1];
                l2 = data[L2][L1];
            }
            complex x = -(l2 / l1);

            for (int i = L1; i < M; ++i) {
                if (i == L1) data[L2][i] = 0;
                else data[L2][i] = data[L2][i] + data[L1][i] * x;
            }
        }
    }
    return swaps;
}

complex matrix::determinant() {
    int swaps = toTrinagular();
    complex ans = data[0][0];
    for (int i = 1; i < N; ++i) {
        ans = ans * data[i][i];
    }
    return (swaps % 2 == 0) ? ans : -ans;
}

void matrix::toUnit() {
    toTrinagular();
    int size = M < N ? M : N;
    for (int L1 = 1; L1 <= size-1; ++L1) {
        for (int L2 = L1 - 1; L2 >= 0; --L2) {
            complex l1 = data[L1][L1];
            complex l2 = data[L2][L1];

            if (l2 == 0) continue;
            if (l1 != 0) {
                complex x = -(l2 / l1);

                for (int i = L1; i < M; ++i) {
                    if (i == L1) data[L2][i] = 0;
                    else data[L2][i] = data[L2][i] + data[L1][i] * x;
                }
            }
        }
    }
    for (int i = 0; i < size; ++i) {
        complex x = data[i][i];
        if (x != 0 && x != 1) {
            for (int j = 0; j < M; ++j) {
                data[i][j] = data[i][j] / x;
            }
        }
    }
}

matrix matrix::submatrix(int fromCol, int toCol) {
    int cols = toCol - fromCol + 1;
    matrix temp(N, cols);
    for (int i = 0; i < N; ++i) {
        for (int j = fromCol - 1; j < toCol; ++j) {
            temp(i, j - fromCol + 1) = data[i][j];
        }
    }
    return temp;
}

matrix matrix::inverse() {
    if (N == M) {
        matrix E(N, N);
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < M; ++j) {
                if (i != j) E(i, j) = 0;
                else E(i, j) = 1;
            }
        }
        matrix a = (*this) | E;
        a.toUnit();
        for (int i = 0; i < a.N; ++i) {
            if (a(i, i) == 0) {
                throw std::invalid_argument("Determinant = 0");
            }
        }
        return a.submatrix(N + 1, 2 * N);
    }
    else {
        throw std::invalid_argument("Invalid matrix dimensions");
    }
}

void matrix::toExpression() {
    string alph = "abcdefghijklmnopqrstuvwxyz";
    string sym = "";
    for (int i = 0; i < N; ++i) {
        bool check = false;
        sym = "";
        for (int j = 0; j < M; ++j) {
            if (check) sym = "+";
            complex temp = data[i][j];
            string var = string(j/alph.size() + 1, alph[j%alph.size()]);
            if (j == M - 1) {
                if(check) cout << "=" << temp << endl;
            }
            else if (temp != 0) {
                if (temp == 1) cout << sym << var;
                else cout << sym << "(" << temp << ")" << var;
                if (!check) check = true;
            }
        }
    }
}

matrix matrix::gauss(matrix& A, matrix& b) {
    if (b.M == 1 && A.N == b.N) {
        matrix temp = A | b;
        cout << endl;
        cout << "Your expression:" << endl;
        temp.toExpression();
        temp.toUnit();
        bool no_sol = false;
        for (int i = temp.N - 1; i >= 0; --i) {
            bool ch = true;
            if (temp(i, temp.M - 1) != 0) {
                for (int j = 0; j < temp.M - 1; ++j) {
                    if (temp(i, j) != 0) {
                        ch = false;
                        break;
                    }
                }
                if (ch) {
                    no_sol = true;
                    break;
                }
            }
        }
        if (!no_sol) {
            cout << "Result:" << endl;
            temp.toExpression();
        }
        else {
            cout << "No solution" << endl;
        }
        return temp;
    }
    throw std::invalid_argument("Invalid matrix dimensions");
}

complex& matrix::operator()(int n, int m) {
    return data[n][m];
}

istream& operator>> (istream& in, matrix& x) {
    try {
        in >> x.N >> x.M;
        x.data.resize(x.N);
        for (int i = 0; i < x.N; ++i) {
            x.data[i].resize(x.M);
        }
        for (int i = 0; i < x.N; ++i) {
            for (int j = 0; j < x.M; ++j) {
                in >> x.data[i][j];
            }
        }
    }
    catch (...) {
        throw std::invalid_argument("Matrix input error");
    }
    return in;
}

ostream& operator<< (ostream& out, const matrix& x) {
    try {
        for (int i = 0; i < x.N; ++i) {
            for (int j = 0; j < x.M; ++j) {
                out << x.data[i][j] << " ";
            }
            out << endl;
        }
    }
    catch (...) {
        throw std::invalid_argument("Matrix output error");
    };
    return out;
}

matrix matrix::operator+(const complex& other) {
    matrix temp(N, M);
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            temp(i, j) = data[i][j] + other;
        }
    }
    return temp;
}

matrix matrix::operator+(const matrix& other) {
    if (N == other.N && M == other.M) {
        matrix temp(N, M);
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < M; ++j) {
                temp(i, j) = data[i][j] + other.data[i][j];
            }
        }
        return temp;
    }
    else {
        throw std::invalid_argument("Invalid matrix dimensions");
    }
}

matrix& matrix::operator+=(const matrix& other) {
    if (N == other.N && M == other.M) {
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < M; ++j) {
                data[i][j] = data[i][j] + other.data[i][j];
            }
        }
        return *this;
    }
    throw std::invalid_argument("Invalid matrix dimensions");
}

matrix matrix::operator|(const matrix& a) {
    if (N == a.N) {
        matrix temp (N, M + a.M);
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < M; ++j) {
                temp(i, j) = data[i][j];
            }
        }
        for (int i = 0; i < N; ++i) {
            for (int j = M; j < M + a.M; ++j) {
                temp(i, j) = a.data[i][j - M];
            }
        }
        return temp;
    }
    else {
        throw std::invalid_argument("Invalid matrix dimensions");
    }
}

matrix matrix::operator-(const complex& other) {
    return (*this)+(-(complex)other);
}

matrix matrix::operator-() {
    matrix temp(N, M);
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            temp(i, j) = -data[i][j];
        }
    }
    return temp;
}

matrix& matrix::operator=(const matrix& other) {
    if (this != &other) {
        N = other.N;
        M = other.M;
        data.resize(N);
        for (int i = 0; i < N; ++i) {
            data[i].resize(M);
            for (int j = 0; j < M; ++j) {
                data[i][j] = other.data[i][j];
            }
        }
    }
    return *this;
}

matrix matrix::operator-(const matrix& other) {
    return (*this + (-(matrix)other));
}

matrix matrix::operator*(const complex& other) {
    matrix temp(N, M);
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            temp(i, j) = data[i][j] * other;
        }
    }
    return temp;
}

matrix matrix::operator/(const complex& other) {
    if ((complex)other != 0) return (*this) * ((complex)1 / other);
    throw std::invalid_argument("divide by zero");
}


bool matrix::operator== (const matrix& other) {
    return (N == other.N && M == other.M && data == other.data);
}

matrix matrix::operator*(const matrix& other) {
    if (M == other.N) {
        matrix temp(N, other.M);
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < other.M; ++j) {
                for (int k = 0; k < M; ++k) {
                    temp(i, j) = temp(i, j) + data[i][k] * other.data[k][j];
                }
            }
        }
        return temp;
    }
    else if (N == other.N && M == other.M) {
        matrix temp(N, M);
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < other.M; ++j) {
                temp(i, j) = data[i][j] * other.data[i][j];
            }
        }
        return temp;
    }
    throw std::invalid_argument("Invalid matrix dimensions");
}
