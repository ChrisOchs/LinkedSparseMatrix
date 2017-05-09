#include <iostream>

#include "SparseMatrix.h"

#include "MatrixBInitializer.h"
#include "AllOnesInitializer.h"


int main() {
    MatrixBInitializer init(3, 1);
    AllOnesInitializer allOnesInit(1, 3);

    SparseMatrix b(init);
    SparseMatrix ones(allOnesInit);

    SparseMatrix empt(1, 6);

    b.print();

    std::cout<<std::endl;

    ones.print();

    std::cout<<std::endl;

    SparseMatrix* result = b.multiply(&ones);

    if(result != NULLPTR) {
        result->print();
    }
}
