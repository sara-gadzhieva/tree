#ifndef TREE_H
#define TREE_H
#include <iosfwd>
#include <memory>
namespace utils {
namespace tree {

template <typename T>
class Tree;

template <typename T>
class Node {
        T value;
        std::unique_ptr<Node<T>> left,right;
        Node<T> *parent;
        friend class Tree<T>;
        public:
        Node(T num);
        };

template <typename T>
class Tree {
        std::unique_ptr<Node<T>> root;
        void f2(std::ofstream &fout);
        std::unique_ptr<Node<T>> copy(const Node<T>* p,Node<T>* parent);
public:
        Tree();
        Tree(const Tree<T> &other);
        ~Tree();
        Tree<T>& operator=(const Tree<T> &other);
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
