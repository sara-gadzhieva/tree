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
void f2(ofstream &fout) {
	if(!root) {
		fout<<"<div align=\"center\">дерево пусто</div>"<<endl;
		return;
		}
	node* arr[200];
	for(int i=0;i<200;i++) arr[i]=nullptr;
	queue<pair<int,node*>> q;
	q.push({0,root});
	int max_idx=0;
	while(!q.empty()) {
		int idx=q.front().first;
		node* p=q.front().second;
		q.pop();
		if(idx>=200) continue;
		arr[idx]=p;
		if(idx>max_idx) max_idx=idx;
		if(p->left) q.push({idx*2+1,p->left});
		if(p->right) q.push({idx*2+2,p->right});
		}
	int full=0;
	while(full<max_idx) full=full*2+2;
	fout<<"<div class=\"mermaid\" align=\"center\" style=\"padding-bottom: 10px; margin-bottom: 10px; border-bottom: 2px solid black\">"<<endl;
	fout<<"graph TD"<<endl;
	for(int i=0;i<=full;i++) {
		if(arr[i]) fout<<i<<"[\""<<arr[i]->value<<"\"]"<<endl;
		}
	for(int i=0;i<=full;i++) {
		if(!arr[i]) continue;
		int left=i*2+1;
		int right=i*2+2;
		if(left<=full) {
			if(arr[left]) fout<<i<<"---"<<left<<endl;
			else fout<<i<<"~~~"<<left<<":::hidden"<<endl;
			}
		if(right<=full) {
			if(arr[right]) fout<<i<<"---"<<right<<endl;
			else fout<<i<<"~~~"<<right<<":::hidden"<<endl;
			}
		}
	fout<<"classDef hidden display: none;"<<endl;
	fout<<"</div>"<<endl;
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
	bool add(int num, ofstream &fout) { 
		node *new_obb=new(nothrow) node(num);
		if(!new_obb) return false;
		if(root==nullptr) {
			root=new_obb;
			}
		else {
			node *current=root;
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
		fout<<"<div align=\"center\">"<<endl;
		fout<<"в дерево добавлен элемент "<<new_obb->value<<endl;
		fout<<"</div>"<<endl;
		f2(fout);
		return true;
	}
	bool del(int num,ofstream &fout) {
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
			if(max->parent->left==max) max->parent->left=max->left;
			else max->parent->right=max->left;
			if(max->left) max->left->parent=max->parent;
			delete max;
			}
		else {
			node *child=current->right;
			if(!current->parent) root=child;
			else if(current->parent->left==current) current->parent->left=child;
			else current->parent->right=child;
			if(child) child->parent=current->parent;
			delete current;
			}
		fout<<"<div align=\"center\">"<<endl;
		fout<<"из дерева удален элемент "<<num<<endl;
		fout<<"</div>"<<endl;
		f2(fout);
		return true;
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
	fout<<"<body>"<<endl;
	}
	
void f3(ofstream &fout) {
	fout<<"</body>"<<endl;  
	fout<<"</html>"<<endl;
	}

int main() {
	ofstream fout("output.html");
	if(!fout.is_open()) {
		cout<<"ошибка открытия файла"<<endl;
		return 1;
		}
	f1(fout);
	tree a;
	int choice, x;
	while (1) {
		cout<<"1 - добавить элемент"<<endl;
		cout<<"2 - удалить элемент"<<endl;
		cout<<"3 - поиск элемента"<<endl;
		cout<<"4 - выход из программы"<<endl;
		cin>>choice;
        switch (choice) {
        case 1:
            cout<<"введите значение элемента для добавления: ";
            cin>>x;
            if (a.add(x,fout)) cout<<"элемент добавлен"<<endl;
            else cout<<"ошибка при добавлении"<<endl;
            break;
        case 2:
            cout<<"введите значение элемента для удаления: ";
            cin>>x;
            if (a.del(x,fout)) cout<<"элемент удалён"<<endl;
            else cout<<"элемент не найден"<<endl;
            break;
		case 3:
			cout<<"введите значение элемента для поиска: ";
			cin>>x;
			if (a.search(x)) cout<<"элемент найден"<<endl;
			else cout<<"элемент не найден"<<endl;
			break;
        case 4:
            f3(fout);
            fout.close();
            return 0;
        default:
            cout<<"введите число от 1 до 4"<<endl;
        }
    }
    f3(fout);
    return 0;
}

