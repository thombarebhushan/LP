/*
Implement depth first search algorithm and Breadth First Search algorithm,
Use an undirected graph and develop a recursive algorithm for searching 
all the vertices of a graph or tree data structure.
*/
#include <bits/stdc++.h>
using namespace std;
class Node{
    public:
    int data;
    Node* left;
    Node* right;
    Node(int data1){
        data = data1;
        left = NULL;
        right = NULL;
    }
};
Node* creationOfTree(Node* &root){
    int data = 0;
    cout << "Enter Data : ";cin >> data;
    if(data == -1) return NULL;
    root = new Node(data); 
    cout << "Enter Data to Be inserted in the left of the " << data << ": " << endl;
    root -> left = creationOfTree(root -> left);
    cout << "Enter Data to Be inserted in the right of the " << data << ": " <<endl;
    root -> right = creationOfTree(root -> right);
    return root;
}
void levelOrder(Node* &root){
    queue <Node*> q;
    q.push(root);
    q.push(NULL);
    while(!q.empty()){
        Node* temp = q.front();
        q.pop();
        if(temp == NULL){
            cout << endl;
            if(!q.empty()){
                q.push(NULL);
            }
        }
        else{
            cout << temp -> data << " ";
            if(temp -> left) q.push(temp -> left);
            if(temp -> right) q.push(temp -> right);
        }
    }
    return ;
}
Node* creationOfBST(Node* &root, int data){
    if(root == NULL){
        root = new Node(data);
    }
    else if(root -> data > data){
        root -> left = creationOfBST(root -> left , data);
    }
    else root -> right = creationOfBST(root -> right , data);
    return root;
}
void takeInput(Node* &root){
    int data = 0;
    cout << "Enter Data : "; cin >> data;
    while(data != -1){
        creationOfBST(root , data);
        cout << "Enter Data : "; cin >> data;
    }
    return ;
}
void preorder(Node* root){
    if(!root) return ;
    cout << root -> data << " ";
    preorder(root -> left);
    preorder(root -> right);
}
int main(){
    Node* root = NULL;
    int temp = 1;
    while(temp){
        cout << "--------------------------------------" << endl;
        cout << "Enter 1 to Create Binary Tree " << endl;
        cout << "Enter 2 to Create Binary Search Tree " << endl;
        cout << "Enter 3 to Print LevelOrder Traversal " << endl;
        cout << "Enter 4 to Print PreOrder Traversal " << endl;
        cout << "Enter 5 to Exit " << endl;
        cout << "--------------------------------------" << endl;
        int choice = 1;
        cout << "Enter your from above choice : "; cin >> choice;
        if(choice == 1){
            creationOfTree(root);
            char ch ;
            cout << "Do you want to continue : (y/n) : "; cin >> ch;
            if(ch == 'y' or ch == 'Y') temp = 1;
            else{
                temp = 0;
                cout << "Exited" << endl;
                return 0;
            }
        }
        else if(choice == 2){
            takeInput(root);
            char ch ;
            cout << "Do you want to continue : (y/n) : "; cin >> ch;
            if(ch == 'y' or ch == 'Y') temp = 1;
            else{
                temp = 0;
                cout << "Exited" << endl;
                return 0;
            }
        }
        else if(choice == 3){
            levelOrder(root);
            char ch ;
            cout << "Do you want to continue : (y/n) : "; cin >> ch;
            if(ch == 'y' or ch == 'Y') temp = 1;
            else{
                temp = 0;
                cout << "Exited" << endl;
                return 0;
            }
        }
        else if(choice == 4){
            preorder(root);
            cout << endl;
            char ch ;
            cout << "Do you want to continue : (y/n) : "; cin >> ch;
            if(ch == 'y' or ch == 'Y') temp = 1;
            else{
                temp = 0;
                cout << "Exited" << endl;
                return 0;
            }
        }
        else{
            cout << "Exited" << endl; 
            return 0;
        }
    }
    return 0;
}
//Input For Binary Tree 3 4 7 -1 -1 9 -1 -1 5 -1 -1
//Input For BST 77 81 36 19 78 55 91 1 -1