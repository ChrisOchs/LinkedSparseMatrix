#ifndef SPARSEMATRIXINITIALIZER_H
#define SPARSEMATRIXINITIALIZER_H

#include "SparseMatrixNode.h"

class SparseMatrixInitializer {

    private:
        unsigned int rows;
        unsigned int cols;

    protected:
        SparseMatrixNode<int>** rowHeaders;
        SparseMatrixNode<int>** colHeaders;

    public:
        SparseMatrixInitializer(unsigned int, unsigned int);
        virtual ~SparseMatrixInitializer();

        virtual void initialize() = 0;

        unsigned int getRows() const;
        unsigned int getCols() const;

        SparseMatrixNode<int>** getRowHeaders() const;
        SparseMatrixNode<int>** getColHeaders() const;
};

#endif // SPARSEMATRIXINITIALIZER_H
