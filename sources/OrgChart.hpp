#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator> 
#include <cstddef>
namespace ariel {
    
    class OrgChart {
        private:
        class Node{
                private:
                    std::string name;
                    std::vector <Node*> sub;
                public:
                    Node(const std::string& name1): name(name1){}//constructor gets a name
                    void add_sub(Node* sub_node) { //add a child to the node
                        sub.push_back(sub_node);
                    }   
                    std::string get_name() const { // get the name of the node
                        return name;
                    }
                    std::vector<Node*> get_sub() const { //get child list
                        return sub;
                    }
                    int size() const { //size of the child list
                        return sub.size();
                    }
                    friend std::ostream& operator<<(std::ostream& outs, const Node& node){ // print the node name (<< operator)
                        outs << node.name;
                        return outs;
                    }
            };
            Node* root = nullptr;
            size_t size = 0;
            std::vector<Node> iter_data;
        public:
            OrgChart& add_root(const std::string& name);// replace the root name
            OrgChart& add_sub(const std::string& parent, const std::string& child);// add a child to a parent meening adding one job in the org chart under the parent job

            struct Iterator 
            {
                using value_type        = Node;
                using pointer           = Node*;  
                using reference         = Node&; 
                
                Iterator(pointer ptr) : current_ptr(ptr) {} // constructor
                reference operator*() const { return *current_ptr; }//* operator
                pointer operator->() { return current_ptr; }//-> operator

                 // Prefix increment
                Iterator& operator++() { current_ptr++; return *this; }  
                friend bool operator!= (const Iterator& a, const Iterator& b) { return a.current_ptr != b.current_ptr; }; // != operator
                //check the pointer equality and not value
                private:
                    pointer current_ptr;
            };
            void level_order(Node* root);//level order traversal
            void rev_level_order(Node* root);//reverse level order traversal
            void pre_order(Node* root);//pre order traversal
            void create_iter_data(int opt);//create the iter_data vector opt == 1 for level order, opt == 2 for reverse order, opt == 3 for preorder
            Iterator begin() { //for for each return the start 
                 iter_data.clear();
                 create_iter_data(1);
                 return Iterator(&iter_data[0]); 
            }
            Iterator end()   { //for for each return the start
                return Iterator(&iter_data[this->size]);
            } 
            Iterator begin_level_order() { //begin level order iterator
                 iter_data.clear();
                 create_iter_data(1);
                 return Iterator(&iter_data[0]); 
            }
            Iterator end_level_order()   { //end level order iterator
                return Iterator(&iter_data[this->size]);
            }

            Iterator begin_reverse_order() { //begin reverse order iterator
                 iter_data.clear();
                 create_iter_data(2);
                 return Iterator(&iter_data[0]); 
            }
            Iterator reverse_order()   { //end reverse order iterator
                return Iterator(&iter_data[this->size]);
            } 
            Iterator begin_preorder() {  //begin preorder iterator
                 iter_data.clear();
                 create_iter_data(3);
                 return Iterator(&iter_data[0]); 
            }
            Iterator end_preorder()   {  //end preorder iterator
                return Iterator(&iter_data[this->size]);
            } 

            friend std::ostream& operator<<(std::ostream&, OrgChart&);//the output operator

    };
}
