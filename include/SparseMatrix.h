#ifndef SPARSEMATRIX_H
#define SPARSEMATRIX_H

#include "SparseMatrixNode.h"
#include "SparseMatrixInitializer.h"

class SparseMatrix {

    private:
        unsigned int rows;
        unsigned int cols;

        SparseMatrixNode<int>** rowHeaders;
        SparseMatrixNode<int>** colHeaders;

        SparseMatrix* addSub(SparseMatrix*, int) const;

    public:
        SparseMatrix(SparseMatrixInitializer&);
        SparseMatrix(unsigned int, unsigned int);

        void print() const;

        unsigned int getRows() const;
        unsigned int getCols() const;

        bool equals(SparseMatrix*) const;

        SparseMatrix* scalarMultiply(int) const;
        SparseMatrix* add(SparseMatrix*) const;
        SparseMatrix* subtract(SparseMatrix*) const;
        SparseMatrix* multiply(SparseMatrix*) const;
        SparseMatrix* power(int p) const;
        SparseMatrix* transpose() const;

        virtual ~SparseMatrix();
};

#endif // SPARSEMATRIX_H
