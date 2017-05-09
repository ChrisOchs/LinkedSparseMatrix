#ifndef MATRIXBINITIALIZER_H
#define MATRIXBINITIALIZER_H

#include "SparseMatrixInitializer.h"

class MatrixBInitializer: public SparseMatrixInitializer
{
    public:
        MatrixBInitializer(unsigned int, unsigned int);

        virtual ~MatrixBInitializer();

        virtual void initialize();
};

#endif // MATRIXBINITIALIZER_H
