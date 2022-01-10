/*
CPE 212 project 5
file  bstree.cpp
author Nolan Rogers
Data 11/15/21
*/

#include <iostream>
#include <new>
#include "bstree.h"

template <typename SomeType>
void BSTree<SomeType>::Delete(BSTreeNode<SomeType>*& treePtr, SomeType& item) {
    // find an item in tree, move pointer to item
    while (!(treePtr->data == item)) {
        if (!treePtr->leftPtr && !treePtr->rightPtr) throw NotFoundBSTree();
        else if (treePtr->data > item) treePtr = treePtr->leftPtr;
        else if (treePtr->data < item) treePtr = treePtr->rightPtr;
    }
    // verify item is correct
    if (!(treePtr->data == item)) throw NotFoundBSTree();
}

template <typename SomeType>
void BSTree<SomeType>::DeleteNode(BSTreeNode<SomeType>*& treePtr) {
    // delete node and set predessor to null
    if (treePtr == rootPtr) rootPtr = NULL;
    else {
        BSTreeNode<SomeType> *placeHolder = new BSTreeNode<SomeType>;
        BSTreeNode<SomeType> *previousNode = new BSTreeNode<SomeType>;
        previousNode = rootPtr;
        placeHolder->data = GetPredecessor(treePtr);
        Delete(previousNode, placeHolder->data);
        if (previousNode->leftPtr == treePtr) previousNode->leftPtr = NULL;
        else if (previousNode->rightPtr == treePtr) previousNode->rightPtr = NULL;
    }
    delete treePtr;
}

template <typename SomeType>
void BSTree<SomeType>::Insert(BSTreeNode<SomeType>*& ptr, SomeType item) {
    // insert item item into tree
    BSTreeNode<SomeType> *currPtr = new BSTreeNode<SomeType>;
    BSTreeNode<SomeType> *node = new BSTreeNode<SomeType>;
    currPtr = ptr;
    node->leftPtr = NULL;
    node->rightPtr = NULL;
    // if root ptr, create root ptr
    if (ptr->data == node->data) {
        node->data = item;
        ptr = node;
        return;
    }
    node->data = item;
    while (true) {
        if (currPtr->data == item) throw FoundInBSTree();
        else if (currPtr->data > item) {
            if (!currPtr->leftPtr) {
                currPtr->leftPtr = node;
                return;
            }
            else currPtr = currPtr->leftPtr;
        }
        else if (currPtr->data < item) {
            if(!currPtr->rightPtr) {
                currPtr->rightPtr = node;
                return;
            }
            else currPtr = currPtr->rightPtr;
        }
    }
}

template <typename SomeType>
void BSTree<SomeType>::Destroy(BSTreeNode<SomeType>*& ptr) {
    // delete full tree
    if (!ptr) return;
    Destroy(ptr->leftPtr);
    Destroy(ptr->rightPtr);
    DeleteNode(ptr);
}

template <typename SomeType>
void BSTree<SomeType>::CopyTree(BSTreeNode<SomeType>*& copy, const BSTreeNode<SomeType>* originalTree) {
    // copy tree to new tree
    if (!originalTree) return;
    Insert(copy, originalTree->data);
    CopyTree(copy, originalTree->leftPtr);
    CopyTree(copy, originalTree->rightPtr);
}

template <typename SomeType>
SomeType BSTree<SomeType>::GetPredecessor(BSTreeNode<SomeType>* treePtr) const {
    // get data of previous node
    if (treePtr == rootPtr) return treePtr->data;
    BSTreeNode<SomeType> *currPtr = rootPtr;
    while (currPtr->leftPtr != treePtr && currPtr->rightPtr != treePtr) {
        if (currPtr->data > treePtr->data && currPtr->leftPtr) currPtr = currPtr->leftPtr;
        else if (currPtr->data < treePtr->data && currPtr->rightPtr) currPtr = currPtr->rightPtr;
        else throw NotFoundBSTree();
    }
    return currPtr->data;
}

template <typename SomeType>
int BSTree<SomeType>::CountNodes(BSTreeNode<SomeType>* treePtr) const {
    // count total nodes
    if (!treePtr) return 0;
    
    int size = 0;
    if (treePtr->leftPtr && treePtr->rightPtr) size = 2;
    else if (treePtr->leftPtr || treePtr->rightPtr) size = 1;
    size += CountNodes(treePtr->leftPtr);
    size += CountNodes(treePtr->rightPtr);
    return size;
}

template <typename SomeType>
int BSTree<SomeType>::LevelCount(BSTreeNode<SomeType>* treePtr) const {
    // count total levels
    if (!treePtr) return 0;
    int size = 1;
    if (treePtr->leftPtr && treePtr->rightPtr) size--;
    size += LevelCount(treePtr->leftPtr);
    size += LevelCount(treePtr->rightPtr);
    return size;
}

template <typename SomeType>
int BSTree<SomeType>::FindLevel(BSTreeNode<SomeType>* treePtr, SomeType item) const {
    // find the level of an item
    BSTreeNode<SomeType> *currPtr = rootPtr;
    int counter = 0;
    while (!(currPtr->data == item)) {
        counter++;
        if (!currPtr->leftPtr && !currPtr->rightPtr) throw NotFoundBSTree();
        else if (currPtr->data > item) currPtr = currPtr->leftPtr;
        else if (currPtr->data < item) currPtr = currPtr->rightPtr;
    }
    if (!(currPtr->data == item)) throw NotFoundBSTree();
    return counter;
}

template <typename SomeType>
BSTree<SomeType>::BSTree() {
    // set rootptr to null
    rootPtr = NULL;
}

template <typename SomeType>
BSTree<SomeType>::BSTree(const BSTree<SomeType>& someTree) {
    BSTreeNode<SomeType> *node = new BSTreeNode<SomeType>;
    CopyTree(node, someTree.rootPtr);
    rootPtr = node;
}

template <typename SomeType>
void BSTree<SomeType>::operator=(const BSTree<SomeType>& originalTree) {
    // copy nodes to new tree
    BSTreeNode<SomeType> *node = new BSTreeNode<SomeType>;
    CopyTree(node, originalTree.rootPtr);
    rootPtr = node;
}

template <typename SomeType>
BSTree<SomeType>::~BSTree() {
    // destroy object
    Destroy(rootPtr);
}

template <typename SomeType>
void BSTree<SomeType>::InsertItem(SomeType item) {
    // insert item into tree
    if (IsEmpty()) {
        BSTreeNode<SomeType> *node = new BSTreeNode<SomeType>;
        node->data = item;
        node->leftPtr = NULL;
        node->rightPtr = NULL;
        rootPtr = node;
    } else {
        Insert(rootPtr, item);
    }
}

template <typename SomeType>
SomeType BSTree<SomeType>::DeleteItem(SomeType item) {
    // delete item in tree and return data
    if (IsEmpty()) throw EmptyBSTree();
    BSTreeNode<SomeType> *tmpPtr = new BSTreeNode<SomeType>;
    BSTreeNode<SomeType> *placeHolder = new BSTreeNode<SomeType>;
    BSTreeNode<SomeType> *newNode = new BSTreeNode<SomeType>;
    BSTreeNode<SomeType> *emptyNode = new BSTreeNode<SomeType>;
    tmpPtr = rootPtr;
    Delete(tmpPtr, item);
    placeHolder->data = tmpPtr->data;
    CopyTree(newNode, tmpPtr->leftPtr);
    CopyTree(newNode, tmpPtr->rightPtr);
    Destroy(tmpPtr);
    if (!(newNode->data == emptyNode->data)) {
        if (IsEmpty()) rootPtr = newNode;
        else CopyTree(rootPtr, newNode);
    }
    return placeHolder->data;
}

template <typename SomeType>
void BSTree<SomeType>::MakeEmpty() {
    // clear all tree data
    if (IsEmpty()) return;
    Destroy(rootPtr);
    rootPtr = NULL;
}

template <typename SomeType>
int BSTree<SomeType>::Size() const {
    // return tree size
    if (IsEmpty()) return 0;
    return CountNodes(rootPtr) + 1;
}

template <typename SomeType>
bool BSTree<SomeType>::IsFull() const {return false;}  // there arent containers, return false

template <typename SomeType>
bool BSTree<SomeType>::IsEmpty() const {return !rootPtr;} // check if tree empty

template <typename SomeType>
SomeType BSTree<SomeType>::Min() const {
    // return smallest item in tree
    if (IsEmpty()) throw EmptyBSTree();
    BSTreeNode<SomeType> *currPtr = rootPtr;
    while (currPtr->leftPtr) currPtr = currPtr->leftPtr;
    return currPtr->data;
}

template <typename SomeType>
SomeType BSTree<SomeType>::Max() const {
    // return largest item in tree
    if (IsEmpty()) throw EmptyBSTree();
    BSTreeNode<SomeType> *currPtr = rootPtr;
    while (currPtr->rightPtr) currPtr = currPtr->rightPtr;
    return currPtr->data;
}

template <typename SomeType>
int BSTree<SomeType>::TotalLevels() const {
    // return total levels in tree
    if (IsEmpty()) throw EmptyBSTree();
    int size = 0;
    size += LevelCount(rootPtr);
    return size;
}

template <typename SomeType>
int BSTree<SomeType>::Level(SomeType item) const {
    // find the level of an item in tree
    if (IsEmpty()) throw EmptyBSTree();
    return FindLevel(rootPtr, item);
}