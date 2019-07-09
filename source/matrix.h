#ifndef MATRIX_H
#define MATRIX_H

/*!
 * \file world.h
 * \author Timothee Chabat
 */

#include <cmath>
#include <iostream>

/*!
 * \class Matrix
 * \brief Allow to perform matrices compuations and operations, ...
 *
 * This class can stop the program if an error is encountered.
 * Inspired by code from Steven Beauchemin
 * */

class Matrix {
    public:
        // constructors / destructors
        /*!
         * \fn Matrix(int, int)
         * \input l : number of line of the matrix
         * \input c : number of column of the matrix
         * */
        Matrix(int l=4, int c=4);
        Matrix(const Matrix& m);
        ~Matrix();

        /*!
         * \fn Id(int)
         * \input dim : dimension of the identity matrix
         * \return an identity matrix
         * */
        static Matrix Id(int dim = 4);

        // usefull meta datas
        Matrix cofactor() const;
        double determinant() const;
        double norm() const;

        // Matrices operations
        // in place
        void inverse();
        void normalize();
        void transpose();
        void homogenize(const double n = 1);
        void unhomogenize();
        // out place
        Matrix normalized() const;
        Matrix inversed() const;
        Matrix transposed() const;
        Matrix homogenized(const double n = 1) const;
        Matrix unhomogenized() const;

        // vector specific operations
        Matrix cross(const Matrix& b) const;
        double dot(const Matrix& b) const;
        
        // basic operations
        Matrix operator+ (const Matrix& b) const;
        Matrix operator- (const Matrix& b) const;
        Matrix operator/ (const double d) const;
        Matrix operator* (const double d) const;
        Matrix operator* (const Matrix& b) const;

        // accessor
        double operator() (int l, int c) const;
        double& operator() (int l, int c);

        // technicals operations
        Matrix& operator= (const Matrix& m);
        friend std::ostream& operator<<(std::ostream& out, const Matrix& m);

    private:
        int line;
        int col;
        double* mat;

        // shortcut to access elements within the class
        double get(int l, int c) const;
};

#endif // MATRIX_H
