#include "SparseMatrixInitializer.h"

SparseMatrixInitializer::SparseMatrixInitializer(unsigned int rows, unsigned int cols) {
    this->rows = rows;
    this->cols = cols;

    this->rowHeaders = new SparseMatrixNode<int>*[rows];
    this->colHeaders = new SparseMatrixNode<int>*[cols];

    for(unsigned int r = 0; r < rows; r++) {
        rowHeaders[r] = NULLPTR;
    }

    for(unsigned int c = 0; c < cols; c++) {
        colHeaders[c] = NULLPTR;
    }
}

SparseMatrixInitializer::~SparseMatrixInitializer() {

}

unsigned int
SparseMatrixInitializer::getRows() const {
    return this->rows;
}

unsigned int
SparseMatrixInitializer::getCols() const {
    return this->cols;
}

SparseMatrixNode<int>**
SparseMatrixInitializer::getRowHeaders() const {
    return this->rowHeaders;
}

SparseMatrixNode<int>**
SparseMatrixInitializer::getColHeaders() const {
    return this->colHeaders;
}



