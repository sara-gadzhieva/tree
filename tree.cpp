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
           void clear(node* p){
        if(!p) return;
        clear(p->left);
        clear(p->right) ;
        delete p;
        
        }
        public:
        tree():root(nullptr) {} 
        ~tree ()  {
        clear(root);
        }
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
  void show() {
    if (!root) {
        cout<<"дерево пусто\n";
        return;
    }

    queue<node*> q;
    q.push(root);

    int idx = 1;  
  cout<<"("<<idx<<", "<<root->value<<") ";

    int sled_vetk=2;

    while (!q.empty()) {
        int count = q.size(); 
        int pos = sled_vetk;

        for (int i=0; i<count; i++) {
            node* cur = q.front();
            q.pop();

            if (cur->left) {
                cout <<"("<< pos <<", "<< cur->left->value <<") ";
                q.push(cur->left);
            }
            pos++;
            if (cur->right) {
                cout <<"("<<pos<<", "<<cur->right->value<<") ";
                q.push(cur->right);
            }
            pos++;
        }
        sled_vetk=pos;
    }

    cout<<endl;
}
        };
int main() {
        tree a;
        a.add(4);
        a.add(3);
        a.add(10);
        a.add(11);
        
        
        a.show();
        return 0;
        }
