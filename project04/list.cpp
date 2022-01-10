#include <iostream>
#include <new>
#include "list.h"

List::List() {
    Node *tmp = new Node;
    head = tmp;
    num = 0;
    head -> next = NULL;
}

List::~List() {
    Node *tmp = head;
    while (tmp -> next != NULL) {
        Node *nextpointer = tmp -> next;
        delete tmp;
        tmp = nextpointer;
    }
}

void List::Append(string newword) {
    Node *tmp = head;
    Node *newNode = new Node;
    while (tmp -> next != NULL) {
        tmp = tmp -> next;
    }
    tmp -> next = newNode;
    tmp = tmp -> next;
    tmp -> word = newword;
    tmp -> next = NULL;
    num ++;
}

void List::InsertAt(int pos, string newword) {
    if (pos > num || pos < 0) throw ListBadPosition();
    Node *tmp = head;
    for (int i = 0; i < pos; i++) {
        tmp = tmp -> next;
    }
    Node *nextpointer = tmp -> next;
    Node *newNode = new Node;
    tmp -> next = newNode;
    tmp = tmp -> next;
    tmp -> word = newword;
    tmp -> next = nextpointer;
    num++;
}

void List::Delete(string someword) {
    if (Find(someword)) {
        Node *tmp = head;
        while (tmp -> next != NULL) {
            if (someword == tmp -> next -> word) {
                Node *nextpointer = tmp -> next -> next;
                delete tmp -> next;
                tmp -> next = nextpointer;
                num--;
                return;
            }
            tmp = tmp -> next;
        }
    }
    throw ListNotFound();
}

void List::Replace(string oldword, string newword) {
    if (Find(oldword)) {
        Node *tmp = head;
        while (tmp != NULL) {
            if (oldword == tmp -> word) {
                tmp -> word = newword;
                return;
            }
            tmp = tmp -> next;
        }
    }
    throw ListNotFound();
}

int List::Length() const {
    return num;
}

bool List::Find(string someword) const {
    Node *tmp = head;
    while (tmp != NULL) {
        if (someword == tmp -> word) return true;
        tmp = tmp -> next;
    }
    return false;
}



