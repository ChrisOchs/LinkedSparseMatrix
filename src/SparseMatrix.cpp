#include <iostream>
#include <iomanip>

#include "SparseMatrix.h"
#include "SparseMatrixUtilities.h"

SparseMatrix::SparseMatrix(SparseMatrixInitializer& initializer) {

    initializer.initialize();

    this->rows = initializer.getRows();
    this->cols = initializer.getCols();

    this->rowHeaders = initializer.getRowHeaders();
    this->colHeaders = initializer.getColHeaders();
}

SparseMatrix::SparseMatrix(unsigned int rows, unsigned int cols) {

    this->rows = rows;
    this->cols = cols;

    this->rowHeaders = new SparseMatrixNode<int>*[rows];
    this->colHeaders = new SparseMatrixNode<int>*[cols];

    for(unsigned int r = 0; r < rows; r++) {
        this->rowHeaders[r] = NULLPTR;
    }

    for(unsigned int c = 0; c < cols; c++) {
        this->colHeaders[c] = NULLPTR;
    }
}

SparseMatrix::~SparseMatrix() {

    for(unsigned int r = 0; r < this->rows; r++) {
        SparseMatrixNode<int>* ptr = this->rowHeaders[r];

        if(ptr != NULLPTR) {
            while(ptr->getRowPtr() != this->rowHeaders[r]) {
                SparseMatrixNode<int>* next = ptr->getRowPtr();

                delete ptr;

                ptr = next;
            }

            delete ptr;
        }
    }

    delete [] this->rowHeaders;
    delete [] this->colHeaders;
}

unsigned int
SparseMatrix::getRows() const {
    return this->rows;
}

unsigned int
SparseMatrix::getCols() const {
    return this->cols;
}

void
SparseMatrix::print() const {

    for(unsigned int r = 0; r < this->rows; r++) {
        SparseMatrixNode<int>* ptr = this->rowHeaders[r];

        if(ptr == NULLPTR) {
            for(unsigned int c = 1; c <= this->cols; c++) {
                std::cout<<std::setw(10)<<0;
            }
        } else {
            for(unsigned int c = 1; c <= this->cols; c++) {
                int value = 0;

                if(ptr->getCol() == c) {
                    value = ptr->getValue();

                    ptr = ptr->getRowPtr();
                }

                std::cout<<std::setw(10)<<value;
            }
        }

        std::cout<<std::endl;
    }
}

bool
SparseMatrix::equals(SparseMatrix* other) const {
    if(this->getRows() != other->getRows() ||
       this->getCols() != other->getCols()) {

        return false;
    }

    for(unsigned int r = 0; r < this->rows; r++) {
        SparseMatrixNode<int>* myPtr = this->rowHeaders[r];
        SparseMatrixNode<int>* otherPtr = other->rowHeaders[r];

        if(myPtr == NULLPTR && otherPtr == NULLPTR) {
            continue;
        }

        if( (myPtr == NULLPTR && otherPtr != NULLPTR) ||
            (otherPtr == NULLPTR && myPtr != NULLPTR)) {

            return false;
        }

        while(myPtr->getRowPtr() != this->rowHeaders[r]) {
            if(!myPtr->equals(otherPtr)) {
                return false;
            }

            myPtr = myPtr->getRowPtr();
            otherPtr = otherPtr->getRowPtr();
        }

        if(!myPtr->equals(otherPtr)) {
            return false;
        }
    }

    return true;
}

SparseMatrix*
SparseMatrix::scalarMultiply(int c) const {

    SparseMatrix* result = new SparseMatrix(this->getRows(), this->getCols());

    for(unsigned int r = 0; r < this->rows; r++) {
        SparseMatrixNode<int>* ptr = this->rowHeaders[r];

        if(ptr == NULLPTR) {
            continue;
        }

        while(ptr->getRowPtr() != this->rowHeaders[r]) {
            insertValue(
                        ptr->getValue() * c,
                        ptr->getRow(),
                        ptr->getCol(),
                        result->rowHeaders,
                        result->colHeaders);
        }

        insertValue(
            ptr->getValue() * c,
            ptr->getRow(),
            ptr->getCol(),
            result->rowHeaders,
            result->colHeaders);
    }

    return result;
}

SparseMatrix*
SparseMatrix::addSub(SparseMatrix* other, int c) const {

    if(this->getRows() != other->getRows() ||
       this->getCols() != other->getCols()) {

        return NULLPTR;
    }

    if(c != -1 && c != 1) {
        return NULLPTR;
    }

    SparseMatrix* result = new SparseMatrix(this->getRows(), this->getCols());

    for(unsigned int r = 0; r < this->rows; r++) {
        SparseMatrixNode<int>* myPtr = this->rowHeaders[r];
        SparseMatrixNode<int>* otherPtr = other->rowHeaders[r];

        if(myPtr == NULLPTR && otherPtr == NULLPTR) {
            continue;
        }

        if(myPtr == NULLPTR) {
            insertValue(
                    c * otherPtr->getValue(),
                    otherPtr->getRow(),
                    otherPtr->getCol(),
                    result->rowHeaders,
                    result->colHeaders);

            while(otherPtr->getRowPtr() != other->rowHeaders[r]) {
                otherPtr = otherPtr->getRowPtr();

                insertValue(
                    c * otherPtr->getValue(),
                    otherPtr->getRow(),
                    otherPtr->getCol(),
                    result->rowHeaders,
                    result->colHeaders);
            }

            continue;
        }

        if(otherPtr == NULLPTR) {
            insertValue(myPtr->getValue(),
                        myPtr->getRow(),
                        myPtr->getCol(),
                        result->rowHeaders,
                        result->colHeaders);

            while(myPtr->getRowPtr() != this->rowHeaders[r]) {
                myPtr = myPtr->getRowPtr();

                insertValue(myPtr->getValue(),
                        myPtr->getRow(),
                        myPtr->getCol(),
                        result->rowHeaders,
                        result->colHeaders);
            }

            continue;
        }

        if(myPtr->getCol() < otherPtr->getCol()) {

            while(myPtr->getRowPtr() != this->rowHeaders[r] && myPtr->getCol() < otherPtr->getCol()) {
                insertValue(myPtr->getValue(),
                        myPtr->getRow(),
                        myPtr->getCol(),
                        result->rowHeaders,
                        result->colHeaders);

                myPtr = myPtr->getRowPtr();
            }
        } else if(otherPtr->getCol() < myPtr->getCol()) {

            while(otherPtr->getRowPtr() != other->rowHeaders[r] && otherPtr->getCol() < myPtr->getCol()) {
                insertValue(
                    c * otherPtr->getValue(),
                    otherPtr->getRow(),
                    otherPtr->getCol(),
                    result->rowHeaders,
                    result->colHeaders);

                otherPtr = otherPtr->getRowPtr();
            }
        }

        if(myPtr->getCol() == otherPtr->getCol()) {
            insertValue(
                myPtr->getValue() + c * otherPtr->getValue(),
                myPtr->getRow(),
                myPtr->getCol(),
                result->rowHeaders,
                result->colHeaders);
        } else {
            insertValue(myPtr->getValue(),
                        myPtr->getRow(),
                        myPtr->getCol(),
                        result->rowHeaders,
                        result->colHeaders);

            insertValue(
                    c * otherPtr->getValue(),
                    otherPtr->getRow(),
                    otherPtr->getCol(),
                    result->rowHeaders,
                    result->colHeaders);
        }

        myPtr = myPtr->getRowPtr();
        otherPtr = otherPtr->getRowPtr();

        while(myPtr != this->rowHeaders[r] && otherPtr != other->rowHeaders[r]){

            if(myPtr->getCol() == otherPtr->getCol()) {

                insertValue(
                    myPtr->getValue() + c * otherPtr->getValue(),
                    myPtr->getRow(),
                    myPtr->getCol(),
                    result->rowHeaders,
                    result->colHeaders);

                myPtr = myPtr->getRowPtr();
                otherPtr = otherPtr->getRowPtr();

            } else if(myPtr->getCol() < otherPtr->getCol()) {

                insertValue(myPtr->getValue(),
                        myPtr->getRow(),
                        myPtr->getCol(),
                        result->rowHeaders,
                        result->colHeaders);

                myPtr = myPtr->getRowPtr();

            } else {

                insertValue(
                    c * otherPtr->getValue(),
                    otherPtr->getRow(),
                    otherPtr->getCol(),
                    result->rowHeaders,
                    result->colHeaders);

                otherPtr = otherPtr->getRowPtr();
            }
        }
    }

    return result;
}

SparseMatrix*
SparseMatrix::multiply(SparseMatrix* other) const {

    if(this->cols != other->rows) {
        return NULLPTR;
    }

    SparseMatrix* result = new SparseMatrix(this->rows, other->cols);

    for(unsigned int r = 0; r < this->rows; r++) {

        SparseMatrixNode<int>* myPtr = this->rowHeaders[r];

        if(myPtr == NULLPTR) {
            continue;
        }

        for(unsigned int c = 0; c < other->cols; c++) {
            SparseMatrixNode<int>* otherPtr = other->colHeaders[c];

            if(otherPtr == NULLPTR) {
                continue;
            }

             if(myPtr->getCol() < otherPtr->getRow()) {
                while(myPtr->getRowPtr() != this->rowHeaders[r] && myPtr->getCol() < otherPtr->getRow()) {
                    myPtr = myPtr->getRowPtr();
                }
            } else if(otherPtr->getRow() < myPtr->getCol()) {
                while(otherPtr->getColPtr() != other->colHeaders[c] && otherPtr->getRow() < myPtr->getCol()) {
                    otherPtr = otherPtr->getColPtr();
                }
            }

            int value = 0;

            if(myPtr->getCol() == otherPtr->getRow()) {
                value = myPtr->getValue() * otherPtr->getValue();
            }

            myPtr = myPtr->getRowPtr();
            otherPtr = otherPtr->getRowPtr();

            while(myPtr != this->rowHeaders[r] && otherPtr != other->colHeaders[c]){

                if(myPtr->getCol() == otherPtr->getRow()) {
                    value += myPtr->getValue() * otherPtr->getValue();

                    myPtr = myPtr->getRowPtr();
                    otherPtr = otherPtr->getRowPtr();
                } else if(myPtr->getCol() < otherPtr->getRow()) {
                    myPtr = myPtr->getRowPtr();
                } else {
                    otherPtr = otherPtr->getColPtr();
                }
            }

            insertValue(value,
                        r + 1,
                        c + 1,
                        result->rowHeaders,
                        result->colHeaders);
        }
    }

    return result;
}

SparseMatrix*
SparseMatrix::add(SparseMatrix* other) const {
    return this->addSub(other, 1);
}

SparseMatrix*
SparseMatrix::subtract(SparseMatrix* other) const {
    return this->addSub(other, -1);
}

SparseMatrix*
SparseMatrix::transpose() const {
    SparseMatrix* result = new SparseMatrix(this->getCols(), this->getRows());

    for(unsigned int r = 0; r < this->rows; r++) {
        SparseMatrixNode<int>* ptr = this->rowHeaders[r];

        if(ptr == NULLPTR) {
            continue;
        }

        while(ptr->getRowPtr() != this->rowHeaders[r]) {
            insertValue(
                        ptr->getValue(),
                        ptr->getCol(),
                        ptr->getRow(),
                        result->rowHeaders,
                        result->colHeaders);
        }

        insertValue(
            ptr->getValue(),
            ptr->getCol(),
            ptr->getRow(),
            result->rowHeaders,
            result->colHeaders);
    }

    return result;
}
