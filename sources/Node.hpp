//
// Created by itamarq on 5/15/22.
//

#ifndef EX5_A_NODE_HPP
#define EX5_A_NODE_HPP

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
namespace ariel {
    class Node {
    public:
        string key;
        Node *next = NULL;
        Node *prev = NULL;
        Node *father = NULL;
        Node *leftMostSon = NULL;
        Node *rightMostSon = NULL;

        Node(const string &key) {
            this->key = key;
        }

        void addSon(string const &sonName) {
            Node *sonToAdd = new Node(sonName);
            sonToAdd->father = &*this;
            if (this->leftMostSon == NULL) {
                this->leftMostSon = sonToAdd;
                return;

            }
            if (this->rightMostSon == NULL) {
                this->rightMostSon = sonToAdd;
                sonToAdd->prev = this->leftMostSon;
                this->leftMostSon->next = sonToAdd;
                return;

            }
            Node *currentRightMost = this->rightMostSon;
            this->rightMostSon = sonToAdd;
            currentRightMost->next = sonToAdd;
            sonToAdd->prev = currentRightMost;


        }
    };
}

#endif //EX5_A_NODE_HPP
