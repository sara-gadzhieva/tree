#ifndef TREE_H
#define TREE_H
#include <iosfwd>
namespace utils {
namespace tree {

template <typename T>
class Tree;

template <typename T>
class Node {
        T value;
        Node<T> *left,*right,*parent;
        friend class Tree<T>;
        public:
        Node(T num);
        };

template <typename T>
class Tree {
        Node<T> *root;
        void clear(Node<T>* p);
        void f2(std::ofstream &fout);
public:
        Tree();
        ~Tree();
        bool search(T num);
        bool add(T num,std::ofstream &fout);
        bool del(T num,std::ofstream &fout);
        };

extern template class Node<int>;
extern template class Node<double>;
extern template class Tree<int>;
extern template class Tree<double>;

} 
} 
#endif 
