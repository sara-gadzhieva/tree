#include <iostream>
#include <queue>
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
	public:
	tree():root(nullptr) {} 
	///возможно надо сделать деструктор
	bool search(int num) { ///вроде всё готово
		node *current=root;
		while(current) {
			if(num==current->value) return true;
			if(num<current->value) current=current->left;
			else current=current->right;
			}
		return false;
		}
	bool add(int num) { ///тоже вроде всё готово
		node *new_obb=new(nothrow) node(num);
		if(!new_obb) return false;
		if(root==nullptr) {
			root=new_obb;
			return true;
			}
		node *current=root;
		while(1) {
			if(num<=current->value) {
				if(current->left!=nullptr) current=current->left;
				else {
					current->left=new_obb;
					new_obb->parent=current;
					return true;
					}
				}
			else {
				if(current->right!=nullptr) current=current->right;
				else {
					current->right=new_obb;
					new_obb->parent=current;
					return true;
					}
				}
			}
		}
	void show() { ///сделать
		if(root==nullptr) {
			cout<<"дерево пусто"<<endl;
			return;
			}
		queue<pair<int,node*>>q;
		}
	};
int main() {
	tree a;
	a.add(4);
	a.add(10);
	a.add(5);
	return 0;
	}
