#include <iostream>
#include <queue>
#include <fstream>

class Node {
        int value;
        Node *left,*right,*parent;
        friend class Tree;
        public:
        Node(int num);
        };
Node::Node(int num):value(num),left(nullptr),right(nullptr),parent(nullptr) {}

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
bool Tree::del(int num,std::ofstream &fout)  {
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
void f1(std::ofstream &fout) {
        fout<<"<!DOCTYPE html>"<<std::endl;
        fout<<"<html lang=\"ru\">"<<std::endl;
        fout<<"<head>"<<std::endl;
        fout<<"<meta charset=\"UTF-8\">"<<std::endl;
        fout<<"<title>Дерево поиска</title>"<<std::endl;
        fout<<"<script type=\"module\">"<<std::endl;
        fout<<"import mermaid from \"https://cdn.jsdelivr.net/npm/mermaid@10/dist/mermaid.esm.min.mjs\";"<<std::endl;
        fout<<"mermaid.initialize({ startOnLoad: true,"<<std::endl;
        fout<<"flowchart: {"<<std::endl;
        fout<<"useMaxWidth: false,"<<std::endl;
        fout<<"curve: 'linear',"<<std::endl;
        fout<<"nodeSpacing: 30,"<<std::endl;
        fout<<"rankSpacing: 30"<<std::endl;  
        fout<<"}"<<std::endl;  
        fout<<"});"<<std::endl;  
        fout<<"</script>"<<std::endl;  
        fout<<"</head>"<<std::endl;
        fout<<"<body>"<<std::endl;
        }

void f3(std::ofstream &fout) {
        fout<<"</body>"<<std::endl;  
        fout<<"</html>"<<std::endl;
        }

int main() {
        std::ofstream fout("output.html");
        if(!fout.is_open()) {
                std::cout<<"ошибка открытия файла"<<std::endl;
                return 1;
                }
        f1(fout);
        Tree a;
        int choice, x;
        while (1) {
                std::cout<<"1 - добавить элемент"<<std::endl;
                std::cout<<"2 - удалить элемент"<<std::endl;
                std::cout<<"3 - поиск элемента"<<std::endl;
                std::cout<<"4 - выход из программы"<<std::endl;
                std::cin>>choice;
        switch (choice) {
        case 1:
            std::cout<<"введите значение элемента для добавления: ";
            std::cin>>x;
            if (a.add(x,fout)) std::cout<<"элемент добавлен"<<std::endl;
            else std::cout<<"ошибка при добавлении"<<std::endl;
            break;
        case 2:
            std::cout<<"введите значение элемента для удаления: ";
            std::cin>>x;
            if (a.del(x,fout)) std::cout<<"элемент удалён"<<std::endl;
            else std::cout<<"элемент не найден"<<std::endl;
            break;
                case 3:
                        std::cout<<"введите значение элемента для поиска: ";
                        std::cin>>x;
                        if (a.search(x)) std::cout<<"элемент найден"<<std::endl;
                        else std::cout<<"элемент не найден"<<std::endl;
                        break;
        case 4:
            f3(fout);
            fout.close();
            return 0;
        default:
            std::cout<<"введите число от 1 до 4"<<std::endl;
        }
    }
    f3(fout);
    return 0;
}
