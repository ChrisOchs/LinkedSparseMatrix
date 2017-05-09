#include "MatrixBInitializer.h"

#include "SparseMatrixUtilities.h"

MatrixBInitializer::MatrixBInitializer(unsigned int rows, unsigned int cols)
    : SparseMatrixInitializer(rows, cols) {

}

MatrixBInitializer::~MatrixBInitializer() {

}

void
MatrixBInitializer::initialize() {

    const unsigned int ROWS = this->getRows();
    const unsigned int COLS = this->getCols();

    for(unsigned int r = 1; r <= ROWS; r++) {
        for(unsigned int c = 1; c <= COLS; c++) {
            //if(r % 2 == 0 || c % 2 == 0) {
                insertValue(r, r, c, this->rowHeaders, this->colHeaders);
            //}
        }
    }
}


