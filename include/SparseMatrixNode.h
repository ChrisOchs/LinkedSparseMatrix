#ifndef SPARSEMATRIXNODE_H
#define SPARSEMATRIXNODE_H

#define NULLPTR 0

template<class T>
class SparseMatrixNode {

    private:
        T value;

        unsigned int row;
        unsigned int col;

        SparseMatrixNode<T>* rowPtr;
        SparseMatrixNode<T>* colPtr;

    public:
        SparseMatrixNode(T, unsigned int, unsigned int);

        SparseMatrixNode<T>* getRowPtr() const;
        SparseMatrixNode<T>* getColPtr() const;

        T getValue() const;

        bool equals(SparseMatrixNode<T>*) const;

        unsigned int getRow() const;
        unsigned int getCol() const;

        void setRowPtr(SparseMatrixNode<T>*);
        void setColPtr(SparseMatrixNode<T>*);

        virtual ~SparseMatrixNode();

};

template<class T>
SparseMatrixNode<T>::SparseMatrixNode(T value, unsigned int row, unsigned int col) {
    this->value = value;
    this->row = row;
    this->col = col;

    this->rowPtr = NULLPTR;
    this->colPtr = NULLPTR;
}

template<class T>
SparseMatrixNode<T>::~SparseMatrixNode() {

}

template<class T>
T SparseMatrixNode<T>::getValue() const {
    return this->value;
}

template<class T>
unsigned int SparseMatrixNode<T>::getRow() const {
    return this->row;
}

template<class T>
unsigned int SparseMatrixNode<T>::getCol() const {
    return this->col;
}

template<class T>
SparseMatrixNode<T>* SparseMatrixNode<T>::getRowPtr() const {
    return this->rowPtr;
}

template<class T>
SparseMatrixNode<T>* SparseMatrixNode<T>::getColPtr() const {
    return this->colPtr;
}

template<class T>
void SparseMatrixNode<T>::setRowPtr(SparseMatrixNode<T>* rowPtr) {
    this->rowPtr = rowPtr;
}

template<class T>
void SparseMatrixNode<T>::setColPtr(SparseMatrixNode<T>* colPtr) {
    this->colPtr = colPtr;
}

template<class T>
bool SparseMatrixNode<T>::equals(SparseMatrixNode<T>* other) const {
    return this->value == other->value && this->row == other->row && this->col == other->col;
}

#endif // SPARSEMATRIXNODE_H
