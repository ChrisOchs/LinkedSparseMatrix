#include <iostream>
#include "SparseMatrixUtilities.h"

void insertValue(int value, unsigned int row, unsigned int col, SparseMatrixNode<int>** rowHeaders, SparseMatrixNode<int>** colHeaders) {

    if(value == 0) {
        return;
    }

    SparseMatrixNode<int>* node = new SparseMatrixNode<int>(value, row, col);

    if(rowHeaders[row - 1] == NULLPTR) {
        rowHeaders[row - 1] = node;

        node->setRowPtr(node);
    } else {
        SparseMatrixNode<int>* ptr = rowHeaders[row - 1];

        if(node->getCol() < ptr->getCol()) {

            node->setRowPtr(ptr);

            while(ptr->getRowPtr() != rowHeaders[row - 1]) {
                ptr = ptr->getRowPtr();
            }

            ptr->setRowPtr(node);
            rowHeaders[row - 1] = node;
        } else {

            while(ptr->getRowPtr() != rowHeaders[row - 1] && ptr->getRowPtr()->getCol() < col) {
                ptr = ptr->getRowPtr();
            }

            node->setRowPtr(ptr->getRowPtr());

            ptr->setRowPtr(node);
        }
    }

    if(colHeaders[col - 1] == NULLPTR) {
        colHeaders[col - 1] = node;

        node->setColPtr(node);
    } else {
        SparseMatrixNode<int>* ptr = colHeaders[col - 1];

        if(node->getRow() < ptr->getRow()) {
            node->setColPtr(ptr);

            while(ptr->getColPtr() != colHeaders[col - 1]) {
                ptr = ptr->getColPtr();
            }

            ptr->setColPtr(node);
            colHeaders[col - 1] = node;
        } else {
            while(ptr->getColPtr() != colHeaders[col - 1] && ptr->getColPtr()->getRow() < row) {
                ptr = ptr->getColPtr();
            }

            node->setColPtr(ptr->getColPtr());
            ptr->setColPtr(node);
        }
    }
}
