//
// Created by itamarq on 5/15/22.
//

#ifndef EX5_A_ORGCHART_HPP
#define EX5_A_ORGCHART_HPP

#include "Node.hpp"
#include <queue>
#include <stack>
using namespace std;
namespace ariel {

    class OrgChart {
    private:
        Node *head = NULL;
        vector<string> levelOrder;
        vector<string> reverseLevelOrder;
        vector<string> preOrder;

        void clearVectors();
        void updateVectors();
        void updateLevelOrderVector();
        void updateReverseLevelOrderVector();
        void updatePreOrderVector();
        void free();

    public:

        OrgChart& add_sub(string const& superiorName, string const& subordinateName);
        OrgChart& add_root(string const& rootName);

        vector<string>::iterator begin();
        vector<string>::iterator end();

        vector<string>::iterator begin_level_order();
        vector<string>::iterator end_level_order();

        vector<string>::iterator begin_reverse_order();
        vector<string>::iterator end_reverse_order();

        vector<string>::iterator begin_preorder();
        vector<string>::iterator end_preorder();

        bool contains(string const& name);

        friend std::ostream & operator << (std::ostream &out, const OrgChart &orgChart);

        friend void validateIsInChart(OrgChart const& orgChart, string const& superiorName, string const& subordinateName);

    };
    void recursionForPreOrder(vector<string>& preOrderVector, Node* node);
}
#endif //EX5_A_ORGCHART_HPP
