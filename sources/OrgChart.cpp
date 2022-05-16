//
// Created by itamarq on 5/15/22.
//

#include "OrgChart.hpp"

namespace ariel {
    OrgChart &OrgChart::add_root(string const &rootName) {
        if (head) {
            free();
        }

        Node *newHead = new Node(rootName);
        clearVectors();
        this->levelOrder.push_back(newHead->key);
        this->reverseLevelOrder.push_back(newHead->key);
        this->preOrder.push_back(newHead->key);

        this->head = newHead;
        return *this;
    }

    OrgChart &OrgChart::add_sub(string const &superiorName, string const &subordinateName) {
        validateIsInChart(*this, superiorName, subordinateName);
        updateVectors();
        return *this;
    }

    bool OrgChart::contains(const string &name) {
        queue<Node *> queue;
        queue.push(this->head);
        while (!queue.empty()) {
            Node *currentNode = queue.front();
            queue.pop();
            if (currentNode->key == name) {
                return true;
            }
            Node *currentLeftMostSon = currentNode->leftMostSon;
            if (currentLeftMostSon == NULL) {
                continue;
            }
            while (currentLeftMostSon != NULL) {
                queue.push(currentLeftMostSon);
                currentLeftMostSon = currentLeftMostSon->next;
            }
        }
        return false;
    }

    void OrgChart::free() {
        queue<Node *> queue;
        queue.push(head);
        while (!queue.empty()) {
            Node *currentNode = queue.front();
            queue.pop();
            Node *currentLeftMostSon = currentNode->leftMostSon;
            if (currentLeftMostSon == NULL) {
                continue;
            }
            while (currentLeftMostSon != NULL) {
                queue.push(currentLeftMostSon);
                currentLeftMostSon = currentLeftMostSon->next;
            }
            delete currentNode;
        }
    }

    vector<string>::iterator OrgChart::begin() {
        return begin_level_order();
    }

    vector<string>::iterator OrgChart::end() {
        return end_level_order();
    }

    void OrgChart::updateVectors() {
        clearVectors();
        updateLevelOrderVector();
        updateReverseLevelOrderVector();
        updatePreOrderVector();
    }

    void OrgChart::updateLevelOrderVector() {
        queue<Node *> queue;
        queue.push(head);
        while (!queue.empty()) {
            Node *currentNode = queue.front();
            levelOrder.push_back(currentNode->key);
            queue.pop();
            Node *currentLeftMostSon = currentNode->leftMostSon;
            if (currentLeftMostSon == NULL) {
                continue;
            }
            while (currentLeftMostSon != NULL) {
                queue.push(currentLeftMostSon);
                currentLeftMostSon = currentLeftMostSon->next;
            }
        }

    }

    void OrgChart::updateReverseLevelOrderVector() {
        if (head == NULL) {
            throw logic_error("OrgChart is Not Initialized");
        }
        queue<Node *> queue;
        stack<Node *> stack;
        queue.push(head);
        while (!queue.empty()) {
            Node *currentNode = queue.front();
            stack.push(currentNode);
            queue.pop();
            if (!currentNode->leftMostSon && !currentNode->rightMostSon) {
                continue;
            }
            if (currentNode->leftMostSon && !currentNode->rightMostSon) {
                queue.push(currentNode->leftMostSon);
                continue;
            }
            Node *currentSon = currentNode->rightMostSon;
            while (currentSon != NULL) {
                queue.push(currentSon);
                currentSon = currentSon->prev;
            }
        }
        while (!stack.empty()) {
            Node *currentNode = stack.top();
            reverseLevelOrder.push_back(currentNode->key);
            stack.pop();
        }
    }

    void OrgChart::updatePreOrderVector() {
        recursionForPreOrder(this->preOrder, head);
    }

    void recursionForPreOrder(vector<string> &preOrderVector, Node *node) {
        if (node == NULL) {
            return;
        }
        preOrderVector.push_back(node->key);
        Node *currentSon = node->leftMostSon;
        while (currentSon != NULL) {
            recursionForPreOrder(preOrderVector, currentSon);
            currentSon = currentSon->next;
        }
    }

    vector<string>::iterator OrgChart::begin_level_order() {
        return levelOrder.begin();
    }

    vector<string>::iterator OrgChart::end_level_order() {
        return levelOrder.end();
    }

    vector<string>::iterator OrgChart::begin_reverse_order() {
        return reverseLevelOrder.begin();
    }

    vector<string>::iterator OrgChart::end_reverse_order() {
        return reverseLevelOrder.end();
    }

    vector<string>::iterator OrgChart::begin_preorder() {
        return preOrder.begin();
    }

    vector<string>::iterator OrgChart::end_preorder() {
        return preOrder.end();
    }

    void OrgChart::clearVectors() {
        this->levelOrder.clear();
        this->reverseLevelOrder.clear();
        this->preOrder.clear();
    }

    void validateIsInChart(OrgChart const &orgChart, string const &superiorName, string const &subordinateName) {
        queue<Node *> queue;
        queue.push(orgChart.head);
        while (!queue.empty()) {
            Node *currentNode = queue.front();
            queue.pop();
            if (currentNode->key == superiorName) {
                currentNode->addSon(subordinateName);
                return;
            }
            Node *currentLeftMostSon = currentNode->leftMostSon;
            if (currentLeftMostSon == NULL) {
                continue;
            }
            while (currentLeftMostSon != NULL) {
                queue.push(currentLeftMostSon);
                currentLeftMostSon = currentLeftMostSon->next;
            }
        }

        throw logic_error(
                "The Superior To Which You Are Trying To Add A Subordinate Does Not Exist In The Organization!\n");
    }
}
