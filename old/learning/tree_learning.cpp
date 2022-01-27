//
// Created by Admin on 10/01/2022.
//

#include <vector>
#include <iostream>
#include <algorithm>

struct Node{
    int val;
    Node* left_child = nullptr;
    Node* right_child = nullptr;
};

void build_tree(Node* node, const std::vector<int> &data){
    // base case, if data contains only 1 element
    if(data.size() == 1){
        node -> val = data[0];
        return;
    }
    // get the middle element of the data
    node -> val = data[data.size()/2];
    // create two sub vectors
    std::vector<int> left_data(data.begin(), data.begin() + (data.size()/2));
    std::vector<int> right_data(data.begin() + (data.size()/2) + 1, data.end());
    // initialise children
    if(!left_data.empty()) {
        node->left_child = new Node;
        build_tree(node -> left_child, left_data);
    }
    if(!right_data.empty()) {
        node->right_child = new Node;
        build_tree(node->right_child, right_data);
    }
}

void print_tree(Node* node){
    // call function until left child is null
    if(node -> left_child != nullptr) print_tree(node -> left_child);
    // print current node
    std::cout << node -> val << " ";
    // call function until right child is null
    if(node -> right_child != nullptr) print_tree(node -> right_child);
}

bool binary_search(Node* node, int num){
    if(node -> val == num) return true;
    else if(node -> val > num && node -> left_child != nullptr) binary_search(node -> left_child, num);
    else if(node -> val < num && node -> right_child != nullptr) binary_search(node -> right_child, num);
    else return false;
}

int main(){
    srand(time(NULL));
    Node* root = new Node;
    std::vector<int> a;
    for(int i = 0; i < 1000; i++){
        a.push_back(rand()%1000+0);
    }
    std::sort(a.begin(), a.end());
    build_tree(root, a);
    print_tree(root);
    int value = 300;
    std::cout << "\nThe result of the search for the value: " << value << " = " << binary_search(root, value) << '\n';
}