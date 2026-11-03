#include "tree.h"
#include <fstream>
#include <queue>
#include <utility>
namespace utils {
namespace tree {

template <typename T>
Node<T>::Node(T num):value(num),left(nullptr),right(nullptr),parent(nullptr) {}

template <typename T>
void Tree<T>::f2(std::ofstream &fout) {
        if(!root) {
                fout<<"<div align=\"center\">дерево пусто</div>"<<std::endl;
                return;
                }
        Node<T>* arr[200];
        for(int i=0;i<200;i++) arr[i]=nullptr;
        std::queue<std::pair<int,Node<T>*>> q;
        q.push({0,root.get()});
        int max_idx=0;
        while(!q.empty()) {
                int idx=q.front().first;
                Node<T>* p=q.front().second;
                q.pop();
                if(idx>=200) continue;
                arr[idx]=p;
                if(idx>max_idx) max_idx=idx;
                if(p->left) q.push({idx*2+1,p->left.get()});
                if(p->right) q.push({idx*2+2,p->right.get()});
                }
        int full=0;
        while(full<max_idx) full=full*2+2;
        fout<<"<div class=\"mermaid\" align=\"center\" style=\"padding-bottom: 10px; margin-bottom: 10px; border-bottom: 2px solid black\">"<<std::endl;
        fout<<"graph TD"<<std::endl;
        for(int i=0;i<=full;i++) {
                if(arr[i]) fout<<i<<"[\""<<arr[i]->value<<"\"]"<<std::endl;
                }
        for(int i=0;i<=full;i++) {
                if(!arr[i]) continue;
                int left=i*2+1;
                int right=i*2+2;
                if(left<=full) {
                        if(arr[left]) fout<<i<<"---"<<left<<std::endl;
                        else fout<<i<<"~~~"<<left<<":::hidden"<<std::endl;
                        }
                if(right<=full) {
                        if(arr[right]) fout<<i<<"---"<<right<<std::endl;
                        else fout<<i<<"~~~"<<right<<":::hidden"<<std::endl;
                        }
                }
        fout<<"classDef hidden display: none;"<<std::endl;
        fout<<"</div>"<<std::endl;
        }

template <typename T>
Tree<T>::Tree():root(nullptr) {}

template <typename T>
std::unique_ptr<Node<T>> Tree<T>::copy(const Node<T>* p,Node<T>* parent) {
        if(!p) return nullptr;
        std::unique_ptr<Node<T>> new_node=std::make_unique<Node<T>>(p->value);
        new_node->parent=parent;
        new_node->left=copy(p->left.get(),new_node.get());
        new_node->right=copy(p->right.get(),new_node.get());
        return new_node;
        }

template <typename T>
Tree<T>::Tree(const Tree<T> &other):root(copy(other.root.get(),nullptr)) {}

template <typename T>
Tree<T>::~Tree() {}

template <typename T>
Tree<T>& Tree<T>::operator=(const Tree<T> &other) {
        if(this==&other) return *this;
        root=copy(other.root.get(),nullptr);
        return *this;
        }

template <typename T>
bool Tree<T>::search(T num) {
        Node<T> *current=root.get();
        while(current) {
                if(num==current->value) return true;
                if(num<current->value) current=current->left.get();
                else current=current->right.get();
                }
        return false;
        }

template <typename T>
bool Tree<T>::add(T num, std::ofstream &fout) {
        std::unique_ptr<Node<T>> new_obb=std::make_unique<Node<T>>(num);
        if(root==nullptr) {
                root=std::move(new_obb);
                }
        else {
                Node<T> *current=root.get();
                while(true) {
                        if(num<=current->value) {
                                if(current->left!=nullptr) current=current->left.get();
                                else {
                                        new_obb->parent=current;
                                        current->left=std::move(new_obb);
                                        break;
                                        }
                        }
                        else {
                                if(current->right!=nullptr) current=current->right.get();
                                else {
                                        new_obb->parent=current;
                                        current->right=std::move(new_obb);
                                        break;
                                        }
                                }
                        }
                }
        fout<<"<div align=\"center\">"<<std::endl;
        fout<<"в дерево добавлен элемент "<<num<<std::endl;
        fout<<"</div>"<<std::endl;
        f2(fout);
        return true;
        }

template <typename T>
bool Tree<T>::del(T num,std::ofstream &fout) {
        Node<T> *current=root.get();
        while(current && current->value!=num) {
                if(num<current->value) current=current->left.get();
                else current=current->right.get();
                }
        if(!current) return false;
        if(current->left) {
                Node<T> *max=current->left.get();
                while(max->right) max=max->right.get();
                current->value=max->value;
                Node<T> *max_parent=max->parent;
                std::unique_ptr<Node<T>> &place=(max_parent->left.get()==max)?max_parent->left:max_parent->right;
                std::unique_ptr<Node<T>> max_left=std::move(max->left);
                if(max_left) max_left->parent=max_parent;
                place=std::move(max_left);
                }
        else {
                Node<T> *current_parent=current->parent;
                std::unique_ptr<Node<T>> child=std::move(current->right);
                if(child) child->parent=current_parent;
                if(!current_parent) root=std::move(child);
                else if(current_parent->left.get()==current) current_parent->left=std::move(child);
                else current_parent->right=std::move(child);
                }
        fout<<"<div align=\"center\">"<<std::endl;
        fout<<"из дерева удален элемент "<<num<<std::endl;
        fout<<"</div>"<<std::endl;
        f2(fout);
        return true;
        }

template class Node<int>;
template class Node<double>;
template class Tree<int>;
template class Tree<double>;

} 
} 
