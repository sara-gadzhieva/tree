///промежуточный результат
///изменена индексация элементов дерева(начало с 0) в функции show, добавлена функция удаления элемента и функции записи текста в html файл "output.html"

#include <iostream>
#include <queue>
#include <fstream>
using namespace std;

class node {
	int value;
	node *left,*right,*parent;
	friend class tree;
	public:
	node(int num):value(num),left(nullptr),right(nullptr),parent(nullptr) {}
	};
	
class tree {
	node *root;
	void clear(node* p) {
        if(!p) return;
        clear(p->left);
        clear(p->right);
        delete p;
        }
	public:
	tree():root(nullptr) {} 
	~tree() {
		clear(root);
		}
	bool search(int num) { 
		node *current=root;
		while(current) {
			if(num==current->value) return true;
			if(num<current->value) current=current->left;
			else current=current->right;
			}
		return false;
		}
	bool add(int num) { 
		node *new_obb=new(nothrow) node(num);
		if(!new_obb) return false;
		if(root==nullptr) {
			root=new_obb;
			///cout<<"в дерево добавлен элемент "<<new_obb->value<<endl;
			return true;
			}
		node *current=root;
		while(true) {
			if(num<=current->value) {
				if(current->left!=nullptr) current=current->left;
				else {
					current->left=new_obb;
					new_obb->parent=current;
					///cout<<"в дерево добавлен элемент "<<new_obb->value<<endl;
					return true;
					}
				}
			else {
				if(current->right!=nullptr) current=current->right;
				else {
					current->right=new_obb;
					new_obb->parent=current;
					///cout<<"в дерево добавлен элемент "<<new_obb->value<<endl;
					return true;
					}
				}
			}
		}
	bool del(int num) {
		node *current=root;
		while(current && current->value!=num) {
			if(num<current->value) current=current->left;
			else current=current->right;
			}
		if(!current) return false;
        if(current->left) {
            node *max=current->left;
            while(max->right) max=max->right;
            current->value=max->value;
			///дописать (связи)
            }
		else {
            node *child=current->right;
            if(!current->parent) root=child;
            else if(current->parent->left==current) current->parent->left=child;
            else current->parent->right=child;
            if(child) child->parent=current->parent;
            delete current;
			}
		return true;
		}
	void show() {
		if (!root) {
			cout<<"дерево пусто"<<endl;
			return;
			}
		queue<pair<int, node*>> q;
		q.push({0, root}); 
		while (!q.empty()) {
			int idx=q.front().first;
			node* p=q.front().second;
			q.pop();
			cout<<"("<<idx<<", "<<p->value<< ")"<<endl;
			if (p->left) q.push({idx*2+1, p->left});       
			if (p->right) q.push({idx*2+2, p->right});  
			}
		cout<<endl;
		}
	};
	
void f1(ofstream &fout) {
	fout<<"<!DOCTYPE html>"<<endl;
	fout<<"<html lang=\"ru\">"<<endl;
	fout<<"<head>"<<endl;
	fout<<"<meta charset=\"UTF-8\">"<<endl;
	fout<<"<title>Дерево поиска</title>"<<endl;
	fout<<"<script type=\"module\">"<<endl;
	fout<<"import mermaid from \"https://cdn.jsdelivr.net/npm/mermaid@10/dist/mermaid.esm.min.mjs\";"<<endl;
	fout<<"mermaid.initialize({ startOnLoad: true,"<<endl;
	fout<<"flowchart: {"<<endl;
	fout<<"useMaxWidth: false,"<<endl;
	fout<<"curve: 'linear',"<<endl;
	fout<<"nodeSpacing: 30,"<<endl;
	fout<<"rankSpacing: 30"<<endl;	
	fout<<"}"<<endl;	
	fout<<"});"<<endl;	
	fout<<"</script>"<<endl;	
	fout<<"</head>"<<endl;
	}
	
void f2(ofstream &fout) {
	fout<<"<body>"<<endl;
	fout<<"</body>"<<endl;	
	}

void f3(ofstream &fout) {
	fout<<"</html>"<<endl;
	}

int main() {
	ofstream fout("output.html");
	if(!fout.is_open()) {
		cout<<"ошибка открытия файла"<<endl;
		return 1;
		}
	tree a;
	a.add(10);
	a.add(6);
	a.add(20);
	a.add(3);
	a.add(7);
	a.add(25);
	a.add(23);
	a.add(40);
	a.show();
	f1(fout);
	f2(fout);
	f3(fout);
	return 0;
	}

