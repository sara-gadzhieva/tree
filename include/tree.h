#ifndef TREE_H
#define TREE_H
#include <fstream>
namespace utils {
namespace tree {

class Node {
        int value;
        Node *left,*right,*parent;
        friend class Tree;
public:
        Node(int num);
        };

class Tree {
        Node *root;
        void clear(Node* p);
        void f2(std::ofstream &fout);
public:
        Tree();
        ~Tree();
        bool search(int num);
        bool add(int num,std::ofstream &fout);
        bool del(int num,std::ofstream &fout);
        };

} 
} 
#endif 
