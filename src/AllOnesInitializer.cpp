#include "AllOnesInitializer.h"

#include "SparseMatrixUtilities.h"

AllOnesInitializer::AllOnesInitializer(unsigned int rows, unsigned int cols)
    : SparseMatrixInitializer(rows, cols) {

}

AllOnesInitializer::~AllOnesInitializer() {

}

void
AllOnesInitializer::initialize() {

    const unsigned int ROWS = this->getRows();
    const unsigned int COLS = this->getCols();

    for(unsigned int r = 1; r <= ROWS; r++) {
        for(unsigned int c = 1; c <= COLS; c++) {
            insertValue(1, r, c, this->rowHeaders, this->colHeaders);
        }
    }
}


