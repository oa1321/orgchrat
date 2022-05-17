#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
#include <algorithm>
#include "OrgChart.hpp"
#include "doctest.h"
using namespace std;
using namespace ariel;

TEST_CASE("OrgChart::add_root") {
    /*------------------
    check if you can add a root 
    check if name is empty raise exception
    check if you can add to it
    ------------------*/
    OrgChart organization;
    CHECK_THROWS(organization.add_root(""));
    CHECK_NOTHROW(organization.add_root("root"));
    for(auto x : organization){
        CHECK_EQ(x.get_name() , "root");
    }
    for (int i = 0; i < 100; i++) {
        CHECK_NOTHROW(organization.add_sub("root", "child" + to_string(i)));
    }

}
TEST_CASE("OrgChart::add_sub") {
    /*------------------
    check if you can add a sub
    check if parent not found raise exception
    check if you can add to it
    ------------------*/
    OrgChart organization;
    CHECK_NOTHROW(organization.add_root("root"));
    for (int i = 0; i < 100; i++) {
        CHECK_NOTHROW(organization.add_sub("root", "child" + to_string(i)));
    }
    for (int i = 0; i < 100; i++) {
        CHECK_NOTHROW(organization.add_sub("child" + to_string(i), "cheild son" + to_string(i)+ "."+ to_string(i)));
    }
    for (int i = 0; i < 100; i++) {
        CHECK_NOTHROW(organization.add_sub("cheild son" + to_string(i)+ "."+ to_string(i), "cheild grandson" + to_string(i)+ "."+ to_string(i)+ "."+ to_string(i)));
    }
    CHECK_THROWS(organization.add_sub("root", ""));
    CHECK_THROWS(organization.add_sub("", "child"));
    CHECK_THROWS(organization.add_sub("", ""));
    for (int i = 0; i < 100; i++) {
        CHECK_THROWS(organization.add_sub("root2", "child" + to_string(i)));
    }
}    
TEST_CASE("OrgChart::level_order") {
    /*------------------
    check if level order works
    ------------- -----*/
    OrgChart organization;
    CHECK_NOTHROW(organization.add_root("root"));
    CHECK_NOTHROW(organization.add_sub("root", "child1"));
    CHECK_NOTHROW(organization.add_sub("root", "child2"));
    CHECK_NOTHROW(organization.add_sub("root", "child3"));
    CHECK_NOTHROW(organization.add_sub("child1", "child1.1"));
    CHECK_NOTHROW(organization.add_sub("child1", "child1.2"));
    vector<string> iter_data = {"root", "child1", "child2", "child3", "child1.1", "child1.2"};
    size_t i = 0;
    for (auto x = organization.begin_level_order(); x != organization.end_level_order(); ++x) {
        CHECK_EQ(x->get_name(), iter_data[i]);
        i++;
    }
    CHECK_NOTHROW(organization.add_sub("child1.2", "child1.2.1"));
    i = 0;
    vector<string> iter_data1 = {"root", "child1", "child2", "child3", "child1.1", "child1.2", "child1.2.1"};
    for (auto x = organization.begin_level_order(); x != organization.end_level_order(); ++x) {
        CHECK_EQ(x->get_name(), iter_data1[i]);
        i++;
    }
}
TEST_CASE("OrgChart::rev_level_order") {
    /*------------------
    check if level order works
    ------------- -----*/
    OrgChart organization;
    CHECK_NOTHROW(organization.add_root("root"));
    CHECK_NOTHROW(organization.add_sub("root", "child1"));
    CHECK_NOTHROW(organization.add_sub("root", "child2"));
    CHECK_NOTHROW(organization.add_sub("root", "child3"));
    CHECK_NOTHROW(organization.add_sub("child1", "child1.1"));
    CHECK_NOTHROW(organization.add_sub("child1", "child1.2"));
    vector<string> iter_data = {"root", "child1", "child2", "child3", "child1.1", "child1.2"};
    reverse(iter_data.begin(), iter_data.end());
    size_t i = 0;
    for (auto x = organization.begin_reverse_order(); x != organization.reverse_order(); ++x) {
        CHECK_EQ(x->get_name(), iter_data[i]);
        i++;
    }
    CHECK_NOTHROW(organization.add_sub("child1.2", "child1.2.1"));
    i = 0;
    vector<string> iter_data1 = {"root", "child1", "child2", "child3", "child1.1", "child1.2", "child1.2.1"};
    reverse(iter_data1.begin(), iter_data1.end());
    for (auto x = organization.begin_reverse_order(); x != organization.reverse_order(); ++x) {
        CHECK_EQ(x->get_name(), iter_data1[i]);
        i++;
    }
}
TEST_CASE("OrgChart::pre_order") {
    /*------------------
    check if level order works
    ------------- -----*/
    OrgChart organization;
    CHECK_NOTHROW(organization.add_root("root"));
    CHECK_NOTHROW(organization.add_sub("root", "child1"));
    CHECK_NOTHROW(organization.add_sub("root", "child2"));
    CHECK_NOTHROW(organization.add_sub("root", "child3"));
    CHECK_NOTHROW(organization.add_sub("child1", "child1.1"));
    CHECK_NOTHROW(organization.add_sub("child1", "child1.2"));
    vector<string> iter_data = {"root", "child1", "child1.1", "child1.2", "child2", "child3"};
    size_t i = 0;
    for (auto x = organization.begin_preorder(); x != organization.end_preorder(); ++x) {
        CHECK_EQ(x->get_name(), iter_data[i]);
        i++;
    }
    CHECK_NOTHROW(organization.add_sub("child1.2", "child1.2.1"));
    i = 0;
    vector<string> iter_data1 = {"root", "child1", "child1.1", "child1.2", "child1.2.1", "child2", "child3"};
    for (auto x = organization.begin_preorder(); x != organization.end_preorder(); ++x) {
        CHECK_EQ(x->get_name(), iter_data1[i]);
        i++;
    }

}
TEST_CASE("for each "){
        /*------------------
    check if level order works
    ------------- -----*/
    OrgChart organization;
    CHECK_NOTHROW(organization.add_root("root"));
    CHECK_NOTHROW(organization.add_sub("root", "child1"));
    CHECK_NOTHROW(organization.add_sub("root", "child2"));
    CHECK_NOTHROW(organization.add_sub("root", "child3"));
    CHECK_NOTHROW(organization.add_sub("child1", "child1.1"));
    CHECK_NOTHROW(organization.add_sub("child1", "child1.2"));
    vector<string> iter_data = {"root", "child1", "child2", "child3", "child1.1", "child1.2"};
    size_t i = 0;
    for (auto x : organization) {
        CHECK_EQ(x.get_name(), iter_data[i]);
        i++;
    }
    CHECK_NOTHROW(organization.add_sub("child1.2", "child1.2.1"));
    i = 0;
    vector<string> iter_data1 = {"root", "child1", "child2", "child3", "child1.1", "child1.2", "child1.2.1"};
    for (auto x : organization) {
        CHECK_EQ(x.get_name(), iter_data1[i]);
        i++;
    }
}
TEST_CASE("add before root is set"){
    OrgChart organization;
    CHECK_THROWS(organization.add_sub("root", "chisld1"));
    CHECK_THROWS(organization.add_sub("roo1t", "chailad1"));
    CHECK_THROWS(organization.add_sub("eroot", "chaild1"));
    CHECK_THROWS(organization.add_sub("rdoot", "cfhild1"));
    CHECK_THROWS(organization.add_sub("rooft", "childs1"));
    CHECK_THROWS(organization.add_sub("rosot", "chisld1"));
    CHECK_THROWS(organization.add_sub("roaot", "chilfd1"));

}
TEST_CASE("set root more then one time"){
    OrgChart organization;
    CHECK_NOTHROW(organization.add_root("root"));
    for(auto x : organization){
        CHECK_EQ(x.get_name() , "root");
    }
    CHECK_NOTHROW(organization.add_root("root1"));
    for(auto x : organization){
        CHECK_EQ(x.get_name() , "root1");
    }
    CHECK_NOTHROW(organization.add_root("root2"));
    for(auto x : organization){
        CHECK_EQ(x.get_name() , "root2");
    }

}