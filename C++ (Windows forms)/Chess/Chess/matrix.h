#ifndef MATRIX_H
#define MATRIX_H

#include "complex.h"
#include <vector>

using namespace std;

class matrix {
    public:
        vector<vector<complex>> data;
        int N;
        int M;

        matrix(const matrix&);
        matrix(int n, int m, vector<vector<complex>> d);
        matrix(int n, int m);
        matrix(vector<double> d);
        matrix(int n, int m, double from, double to);
        matrix();

        complex& operator()(int row, int column);

        matrix operator+(const complex& other);
        matrix operator+(const matrix& other);
        matrix operator|(const matrix& other);
        matrix operator-(const complex& other);
        matrix operator-(const matrix& other);
        matrix operator*(const matrix& other);
        matrix operator*(const complex& other);
        matrix operator/(const complex& other);
        matrix& operator+=(const matrix& other);
        matrix& operator=(const matrix& other);
        bool operator== (const matrix& other);
        matrix operator-();

        friend std::ostream& operator<< (std::ostream& out, const matrix& x);
        friend std::istream& operator>> (std::istream& in, matrix& x);

        void swapLines(int i1, int i2);
        matrix transpose();
        int toTrinagular();
        complex determinant();
        void toUnit();
        matrix submatrix(int fromCol, int toCol);
        matrix inverse();
        matrix gauss(matrix& A, matrix& b);
        void toExpression();
};
#endif