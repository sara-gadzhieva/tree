#include "tree.h"
#include <fstream>
#include <new>
#include <queue>
#include <utility>
namespace utils {
namespace tree {

Node::Node(int num):value(num),left(nullptr),right(nullptr),parent(nullptr) {}

void Tree::clear(Node* p) {
        if(!p) return;
        clear(p->left);
        clear(p->right);
        delete p;
        }

void Tree::f2(std::ofstream &fout) {
        if(!root) {
                fout<<"<div align=\"center\">дерево пусто</div>"<<std::endl;
                return;
                }
        Node* arr[200];
        for(int i=0;i<200;i++) arr[i]=nullptr;
        std::queue<std::pair<int,Node*>> q;
        q.push({0,root});
        int max_idx=0;
        while(!q.empty()) {
                int idx=q.front().first;
                Node* p=q.front().second;
                q.pop();
                if(idx>=200) continue;
                arr[idx]=p;
                if(idx>max_idx) max_idx=idx;
                if(p->left) q.push({idx*2+1,p->left});
                if(p->right) q.push({idx*2+2,p->right});
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

Tree::Tree():root(nullptr) {}

Tree::~Tree() {
        clear(root);
        }

bool Tree::search(int num) {
        Node *current=root;
        while(current) {
                if(num==current->value) return true;
                if(num<current->value) current=current->left;
                else current=current->right;
                }
        return false;
        }

bool Tree::add(int num, std::ofstream &fout) {
        Node *new_obb=new(std::nothrow) Node(num);
        if(!new_obb) return false;
        if(root==nullptr) {
                root=new_obb;
                }
        else {
                Node *current=root;
                while(true) {
                        if(num<=current->value) {
                                if(current->left!=nullptr) current=current->left;
                                else {
                                        current->left=new_obb;
                                        new_obb->parent=current;
                                        break;
                                        }
                        }
                        else {
                                if(current->right!=nullptr) current=current->right;
                                else {
                                        current->right=new_obb;
                                        new_obb->parent=current;
                                        break;
                                        }
                                }
                        }
                }
        fout<<"<div align=\"center\">"<<std::endl;
        fout<<"в дерево добавлен элемент "<<new_obb->value<<std::endl;
        fout<<"</div>"<<std::endl;
        f2(fout);
        return true;
        }

bool Tree::del(int num,std::ofstream &fout) {
        Node *current=root;
        while(current && current->value!=num) {
                if(num<current->value) current=current->left;
                else current=current->right;
                }
        if(!current) return false;
        if(current->left) {
                Node *max=current->left;
                while(max->right) max=max->right;
                current->value=max->value;
                if(max->parent->left==max) max->parent->left=max->left;
                else max->parent->right=max->left;
                if(max->left) max->left->parent=max->parent;
                delete max;
                }
        else {
                Node *child=current->right;
                if(!current->parent) root=child;
                else if(current->parent->left==current) current->parent->left=child;
                else current->parent->right=child;
                if(child) child->parent=current->parent;
                delete current;
                }
        fout<<"<div align=\"center\">"<<std::endl;
        fout<<"из дерева удален элемент "<<num<<std::endl;
        fout<<"</div>"<<std::endl;
        f2(fout);
        return true;
        }

}
} 
