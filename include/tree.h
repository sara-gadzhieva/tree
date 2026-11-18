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
        explicit Node(T num);
        };

template <typename T>
class Tree {
        std::unique_ptr<Node<T>> root;
        void f2(std::ostream &fout) const;
        std::unique_ptr<Node<T>> copy(const Node<T>* p,Node<T>* parent);
public:
        Tree() noexcept;
        Tree(const Tree<T> &other);
        ~Tree() noexcept;
        Tree<T>& operator=(const Tree<T> &other);
        bool search(T num) const;
        bool add(T num,std::ostream &fout);
        bool del(T num,std::ostream &fout);
        };

extern template class Node<int>;
extern template class Node<double>;
extern template class Tree<int>;
extern template class Tree<double>;
}
}
#endif