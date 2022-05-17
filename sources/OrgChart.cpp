#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
#include <algorithm>
#include <queue>
#include <stack>
#include "OrgChart.hpp"
using namespace std;

namespace ariel{
    OrgChart& OrgChart::add_root(const std::string& name)
    {   //adds a root to the OrgChart
    //if name is empty, throw exception
        if(name == "")
            throw std::invalid_argument("name cannot be empty");
        
        Node *new_node = new Node(name);
        this->root = new_node;
        this->size = 1;
        return *this;
    }
    OrgChart& OrgChart::add_sub(const std::string& parent, const std::string& child)
    { // adds a sub to the OrgChart
    //if parent or chiled is empty, throw exception
    // if parent not found, throw exception
        this->iter_data.clear();
        if(root == NULL){
            throw std::invalid_argument("parent not found");
            return *this;
        }
        if(parent == "")
            throw std::invalid_argument("parent cannot be empty");
        if(child == "")
            throw std::invalid_argument("child cannot be empty");
        std::queue<Node*> q;
        q.push(root);
        while(!q.empty()){
            Node* temp = q.front();
            if (temp->get_name() == parent){
                temp->add_sub(new Node(child));
                this->size++;
                return *this;
            }
            q.pop();
            for(size_t i = 0; i < temp->size(); i++){
                q.push(temp->get_sub()[i]);
            }
        }
        throw std::invalid_argument("parent not found");
    }
    void OrgChart::level_order(Node* root){
        //sets the OrgChart in level order
        //push it to queue for the levels 
        if(root == NULL)
            return;
        iter_data.push_back(*root);
        std::queue<Node*> q;
        q.push(root);
        while(!q.empty()){
            Node* temp = q.front();
            q.pop();
            for(size_t i = 0; i < temp->size(); i++){
                q.push(temp->get_sub()[i]);
                iter_data.push_back(*temp->get_sub()[i]);
            }
        }
    }
    void OrgChart::rev_level_order(Node* root){
        //sets the OrgChart in reverse level order
        //push it to a stack to reverse it (from right to left children) not like queue
        if(root == NULL)
            return;
        iter_data.push_back(*root);
        std::stack<Node*> q;
        q.push(root);
        while(!q.empty()){
            Node* temp = q.top();
            q.pop();
            for(size_t i = 0; i < temp->size(); i++){
                q.push(temp->get_sub()[i]);
                iter_data.push_back(*temp->get_sub()[i]);
            }
        }
        reverse(iter_data.begin(), iter_data.end());
    }
    void OrgChart::pre_order(struct Node* node){
        //sets the OrgChart in pre order
    if (node == NULL)
        return;
    iter_data.push_back(*node);    
    for (size_t i = 0; i < node->size(); i++)
        this->pre_order(node->get_sub()[i]);
    /* then print the data of node */
    
    }
    void OrgChart::create_iter_data(int opt){
        switch (opt)
        {
        case 1://call level order
            this->level_order(this->root);
            break;
        
        case 2://call reverse level order
            this->rev_level_order(this->root);

            break;
        
        case 3://call pre order
            this->pre_order(this->root);
            break;
        }
    }

    std::ostream& operator<<(std::ostream& s, OrgChart& oc){
        /*print like this:
            p 
            p->c1
            p->c2
            p->c1->g1
            p->c1->g2
        */
        cout << "OrgChart:" << endl;
        if(oc.root == NULL)
            return s;
        std::queue<OrgChart::Node*> q;
        std::queue<string> q2;
        int i = 1;
        q.push(oc.root);
        q2.push(oc.root->get_name());
        s << oc.root->get_name() << endl;
        while(!q.empty()){
            OrgChart::Node* temp = q.front();
            q.pop();
            string temp_name = q2.front();
            q2.pop();
            for(size_t i = 0; i < temp->size(); i++){
                q.push(temp->get_sub()[i]);
                string temp_name2 = temp_name + "->" + temp->get_sub()[i]->get_name();
                s << temp_name2 << endl;
                q2.push(temp_name2);
            }
        }
        
        return s;

    }

}