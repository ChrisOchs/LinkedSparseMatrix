#ifndef ALLONESINITIALIZER_H
#define ALLONESINITIALIZER_H

#include "SparseMatrixInitializer.h"

class AllOnesInitializer: public SparseMatrixInitializer
{
    public:
        AllOnesInitializer(unsigned int, unsigned int);

        virtual ~AllOnesInitializer();

        virtual void initialize();
};

#endif // ALLONESINITIALIZER_H
