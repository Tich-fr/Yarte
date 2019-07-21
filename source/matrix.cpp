#include "matrix.h"

#include <algorithm>
#include <cmath>
#include <stdlib.h>

Matrix::Matrix(int l, int c) : line(l), col(c) {
    int n = l * c;
    mat = new double[n];
    for (int i = 0; i < n; i++)
        mat[i] = 0.0;
}

Matrix::Matrix(const Matrix& m) : line(m.line), col(m.col) {
    int n = line * col;
    mat = new double[n];
    for (int i = 0; i < n; i++)
        mat[i] = m.mat[i];
}

Matrix Matrix::Id(int dim) {
    Matrix res(dim, dim);
    for (int i = 0; i < dim; i++)
        res(i,i) = 1;
    return res;
}

Matrix::~Matrix() {
    delete[] mat;
}

Matrix Matrix::cofactor() const {
    int i, j, ii, jj, i1, j1;
    double det;
    Matrix res(line, col);
    Matrix tmp(line-1, col-1);

    for (j = 0; j < line; j++) {
        for (i = 0; i < line; i++) {
            i1 = 0;
            for (ii = 0; ii < line; ii++) {
                if (ii == i)
                    continue;
                j1 = 0;
                for (jj = 0; jj < line; jj++) {
                    if (jj == j)
                        continue;
                    tmp(i1, j1) = get(ii, jj);
                    j1++;
                }
                i1++;
            }
            det = tmp.determinant();
            res(i, j) = pow(-1.0, i + j + 4.0) * det;
        }
    }

    return res;
}

double Matrix::determinant() const {
    int i, j, j1, j2;
    double det = 0;
    Matrix* m;

    if (line < 1 || col < 1) {
        throw "Matrix::determinant : erroneous matrix size" ;
    } else if (line != col) {
        throw "Matrix::determinant : not a square matrix" ;
    } else if (line == 1) { 
        det = get(0,0) ;
    } else if (line == 2) {
        det = get(0,0)*get(1,1) - get(1,0)*get(0,1) ;
    } else {
        m = new Matrix(line-1, line-1);
        for (j1 = 0; j1 < line; j1++) {
            for (i = 1 ; i < line; i++) {
                j2 = 0 ;
                for (j = 0; j < line; j++) {
                    if (j == j1)
                        continue ;
                    m->operator()(i-1,j2) = get(i,j) ;
                    j2++ ;
                }
            }
            det += pow(-1.0, j1 + 2.0) * get(0, j1) * m->determinant() ;
        }
        delete m;
    }

    return det;
}

double Matrix::norm() const {
    double s = 0.0;

    if (line == 1) {
        for (int i = 0; i < col; i++)
            s += pow(get(0,i) ,2.0) ;
        return sqrt(s);
    } else if (col == 1) {
        for (int i = 0; i < line; i++) 
            s += pow(get(i,0) ,2.0) ;
        return sqrt(s);
    } //else
    
    throw "Matrix::norm : erroneous matrix size" ;
    return -1;
}

void Matrix::inverse() {
    Matrix res = this->inversed();
    std::copy(res.mat, res.mat + (line * col), this->mat);
}

void Matrix::normalize() {
    int n = norm();
    for (int i = 0; i < line * col; i++)
        mat[i] /= n;
}

void Matrix::transpose() {
    Matrix res = this->transposed();
    std::copy(res.mat, res.mat + (line * col), this->mat);
}

void Matrix::homogenize(const double n) {
    Matrix res = this->homogenized(n);

    delete[] mat;

    line = res.line ;
    col = res.col ;
    mat = new double[line * col];

    std::copy(res.mat, res.mat + (line * col), this->mat);
}

void Matrix::unhomogenize() {
    Matrix res = this->unhomogenized();

    delete[] mat;

    line = res.line ;
    col = res.col ;
    mat = new double[line * col];

    std::copy(res.mat, res.mat + (line * col), this->mat);
}

Matrix Matrix::inversed() const {
    double det = this->determinant();
    Matrix res = this->cofactor().transposed() / det;
    return res;
}

Matrix Matrix::normalized() const {
    return *this / norm();
}

Matrix Matrix::transposed() const {
    Matrix res(col, line);
    for (int i = 0; i < line; i++) {
        for (int j = 0; j < col; j++)
            res(j,i) = get(i,j);
    }
    return res;
}

Matrix Matrix::homogenized(const double n) const {
   if (col == 1) { // column vector
       Matrix res(line + 1, 1);
       for (int i = 0; i < line; i++)
           res(i,0) = get(i,0);
       res(line,0) = n;
       return res;
   } else if (line == 1) { // line vector
       Matrix res(1, col + 1);
       for (int i = 0; i < col; i++)
           res(0,i) = get(0,i);
       res(0, col) = n;
       return res;
   } else { // matrices
       Matrix res(line + 1, col + 1);
       for (int i = 0; i < line; i++) {
           for (int j = 0; j < col; j++)
               res(i,j) = get(i,j);
       }
       res(line, col) = n;
       return res;
   }
}

Matrix Matrix::unhomogenized() const {
   if (col == 1) { // column vector
       Matrix res(line - 1, 1);
       for (int i = 0; i < res.line; i++)
           res(i,0) = get(i,0);
       return res;
   } else if (line == 1) { // line vector
       Matrix res(1, col - 1);
       for (int i = 0; i < res.col; i++)
           res(0,i) = get(0,i);
       return res;
   } else { // matrices
       Matrix res(line - 1, col - 1);
       for (int i = 0; i < res.line; i++) {
           for (int j = 0; j < res.col; j++)
               res(i,j) = get(i,j);
       }
       return res;
   }
}

Matrix Matrix::operator+ (const Matrix& b) const {
    if (line != b.line || col != b.col) {
        throw "Matrix::ope+ : erroneous matrix size" ;
    }
    Matrix res(line, col);
    for (int i = 0; i < line; i++) {
        for (int j = 0; j < col; j++)
            res(i,j) = get(i,j) + b(i,j);
    }
    return res;
}

Matrix Matrix::operator- (const Matrix& b) const {
    if (line != b.line || col != b.col) {
        throw "Matrix::ope- : erroneous matrix size" ;
    }
    Matrix res(line, col);
    for (int i = 0; i < line; i++) {
        for (int j = 0; j < col; j++)
            res(i,j) = get(i,j) - b(i,j);
    }
    return res;
}


Matrix Matrix::operator/ (const double d) const {
    Matrix res(line, col);
    for (int i = 0; i < line; i++) {
        for (int j = 0; j < col; j++)
            res(i,j) = get(i,j) / d;
    }
    return res;
}

Matrix Matrix::operator* (const double d) const {
    Matrix res(line, col);
    for (int i = 0; i < line; i++) {
        for (int j = 0; j < col; j++)
            res(i,j) = get(i,j) * d;
    }
    return res;
}

Matrix Matrix::operator* (const Matrix& b) const {
    if (col != b.line) {
        throw "Matrix::ope* : erroneous matrix size" ;
    }

    double s;
    int j, k;
    Matrix res(line, b.col);
    for (int i = 0; i < res.line; i++) {
        for (j = 0; j < res.col; j++) {
            s = 0.0;
            for (k = 0; k < col; k++) {
                s += get(i,k) * b(k,j);
            }
            res(i,j) = s;
        }
    }

    return res;
}

Matrix Matrix::cross(const Matrix& b) const {
    if ((line != 1 && col != 1) || (b.line != 1 && b.col != 1))
        throw "Matrix::cross : erroneous matrix size" ;
    if (line != 3) 
        throw "Matrix::cross : erroneous matrix size" ;
    if (b.line != 3)
        throw "Matrix::cross : erroneous matrix size" ;

    Matrix res(1, 3);
    Matrix c(1, 3);
    Matrix e(3, 3);

    if (line != 1)
        c = transposed();
    if (b.line != 1)
        res = b.transposed();
    e(0,1) = -res(0,2);
    e(0,2) = res(0,1);
    e(1,0) = res(0,2);
    e(1,2) = -res(0,0) ;
    e(2,0) = -res(0,1) ;
    e(2,1) = res(0,0);
    res = (c * e).transposed();

    return res;
}

double Matrix::dot(const Matrix& b) const {
    Matrix res;

    if(col == b.col && line == 1 && b.line == 1) 
        res = *this * b.transposed();
    else if(col == b.line && line == 1 && b.col == 1)
        res = *this * b;
    else if(line == b.col && col == 1 && b.line == 1)
        res = b * *this;
    else if (line == b.line && col == 1 && b.col == 1)
        res = this->transposed() * b;
    else
        throw "Matrix::dot : Incompatible matrix sizes" ;

    return res(0,0);
}

Matrix& Matrix::operator= (const Matrix& m) {
    if (this != &m) {
        line = m.line;
        col = m.col;
        int n = line * col;
        if (m.line != line || m.col != col) {
            delete[] mat;
            mat = new double[n];
        }
        std::copy(m.mat, m.mat + n, mat);
    }
    return *this;
}

double Matrix::operator() (int l, int c) const {
    if (l < 0 || l >= line || c < 0 || c >= col)
        throw "Matrix::ope() : Index out of range" ;
    return mat[l * col + c];
}

double& Matrix::operator() (int l, int c) {
    if (l < 0 || l >= line || c < 0 || c >= col)
        throw "Matrix::ope() : Index out of range" ;
    return mat[l * col + c];
}

double Matrix::get(int l, int c) const {
    if (l < 0 || l >= line || c < 0 || c >= col)
        throw "Matrix::get : Index out of range" ;
    return mat[l * col + c];
}

std::ostream& operator<<(std::ostream& out, const Matrix& m) {
    out << "[ ";
    for (int i = 0; i < m.line; i++) {
        for (int j = 0; j < m.col; j++)
            out << m(i,j) << " ";
        if (i != m.line - 1)
            out << std::endl << "  ";
    }
    out << "]";
    return out;
}
