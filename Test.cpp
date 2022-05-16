//
// Created by itamarq on 5/16/22.
//
#include "doctest.h"
#include "sources/OrgChart.hpp"

using namespace ariel;
using namespace std;

TEST_CASE ("Demo Tests") {
    OrgChart organization;
    organization.add_root("CEO");
            CHECK(organization.contains("CEO"));
    organization.add_sub("CEO", "CTO");
            CHECK(organization.contains("CTO"));
    organization.add_sub("CEO", "CFO");
            CHECK(organization.contains("CFO"));
    organization.add_sub("CEO", "COO");
            CHECK(organization.contains("COO"));
    organization.add_sub("CTO", "VP_SW");
            CHECK(organization.contains("VP_SW"));
    organization.add_sub("COO", "VP_BI");
            CHECK(organization.contains("VP_BI"));
    string output;
    for (auto it = organization.begin_level_order(); it != organization.end_level_order(); ++it) {
        output += (*it) += " ";
    }
            CHECK_EQ(output, "CEO CTO CFO COO VP_SW VP_BI ");
    output.clear();
    for (auto it = organization.begin_reverse_order(); it != organization.end_reverse_order(); ++it) {
        output += (*it) += " ";
    }
            CHECK_EQ(output, "VP_SW VP_BI CTO CFO COO CEO ");
    output.clear();
    for (auto it = organization.begin_preorder(); it != organization.end_preorder(); ++it) {
        output += (*it) += " ";
    }
            CHECK_EQ(output, "CEO CTO VP_SW CFO COO VP_BI ");
    output.clear();
    for (auto element: organization) { // this should work like level order
        output += element;
    }
            CHECK_EQ(output, "CEO CTO CFO COO VP_SW VP_BI ");
    output.clear();
    for (auto it = organization.begin_level_order(); it != organization.end_level_order(); ++it) {
        int size = it->size();
        output += to_string(size - 1) += " ";
    }
            CHECK_EQ(output, "3 3 3 3 5 5 ");
            CHECK_THROWS(organization.add_sub("yosii", "avi"));

}

TEST_CASE ("Changing Root") {
    OrgChart organization;
    organization.add_root("CEO");
            CHECK(organization.contains("CEO"));
    organization.add_sub("CEO", "CTO");
            CHECK(organization.contains("CTO"));
    organization.add_sub("CEO", "CFO");
            CHECK(organization.contains("CFO"));
    organization.add_sub("CEO", "COO");
            CHECK(organization.contains("COO"));
    organization.add_sub("CTO", "VP_SW");
            CHECK(organization.contains("VP_SW"));
    organization.add_sub("COO", "VP_BI");
            CHECK(organization.contains("VP_BI"));
    organization.add_root("yossi");
            CHECK_THROWS(organization.add_sub("CEO", "CTO"));
            CHECK_THROWS(organization.add_sub("CEO", "CFO"));
            CHECK_THROWS(organization.add_sub("CEO", "COO"));
            CHECK_THROWS(organization.add_sub("CTO", "VP_SW"));
            CHECK_THROWS(organization.add_sub("COO", "VP_BI"));
            CHECK_NOTHROW(organization.add_sub("yossi", "avi"));
}