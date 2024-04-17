#include <iostream>
#include <Windows.h>
#include <vector>
using namespace std;
class BST {
    struct node {
        int data;
        node* left;
        node* right;
        int height;
    };
    node* root;
    node* makeEmpty(node* t) {
        if (t == NULL)
            return NULL;
        {
            makeEmpty(t->left);
            makeEmpty(t->right);
            delete t;
        }
        return NULL;
    }

    node* insert(int x, node* t)
    {
        if (t == NULL)
        {
            t = new node;
            t->data = x;
            t->left = t->right = NULL;
        }
        else if (x < t->data)
            t->left = insert(x, t->left);
        else if (x > t->data)
            t->right = insert(x, t->right);
        return t;
    }

    node* findMin(node* t)
    {
        if (t == NULL)
            return NULL;
        else if (t->left == NULL)
            return t;
        else
            return findMin(t->left);
    }
    node* remove(int x, node* t) {
        node* temp;
        if (t == NULL)
            return NULL;
        else if (x < t->data)
            t->left = remove(x, t->left);
        else if (x > t->data)
            t->right = remove(x, t->right);
        else if (t->left && t->right)
        {
            temp = findMin(t->right);
            t->data = temp->data;
            t->right = remove(t->data, t->right);
        }
        else
        {
            temp = t;
            if (t->left == NULL)
                t = t->right;
            else if (t->right == NULL)
                t = t->left;
            delete temp;
        }

        return t;
    }

    void inorder(node* t) {
        if (t == NULL)
            return;
        inorder(t->left);
        cout << " -> " << t->data;
        inorder(t->right);
    }

    node* find(node* t, int x) {
        if (t == NULL)
            return NULL;
        else if (x < t->data)
            return find(t->left, x);
        else if (x > t->data)
            return find(t->right, x);
        else
            return t;
    }

    bool isSkewedBT(node* root) {
        int i = 0, j = 0;
        if (root == NULL || (root->left == NULL && root->right == NULL))
            return true;
        if (root->left && root->right)
            return false;
        if (root->left) {
            i++;
            return isSkewedBT(root->left);
        }
        else {
            j++;
        }
        if (i > 0) {
            cout << "Left";
        }
        else if (j > 0) {
            cout << "Right ";
        }
        return isSkewedBT(root->right);
    }
    void preorder(node* root)
    {
        if (root == nullptr) {
            return;
        }
        cout << " -> " << root->data;
        preorder(root->left);
        preorder(root->right);
    }
    void postorder(node* root)
    {
        if (root == nullptr) {
            return;
        }
        postorder(root->right);
        postorder(root->left);
        cout << " -> " << root->data;
    }

    void pushTreeNodes(node* root, vector<node*>& nodes) {
        if (root == nullptr) {
            return;
        }

        pushTreeNodes(root->left, nodes);
        nodes.push_back(root);
        pushTreeNodes(root->right, nodes);
    }

    node* convert(vector<node*>& nodes, int start, int end) {
        if (start > end) {
            return nullptr;
        }
        int mid = (start + end) / 2;
        node* root = nodes[mid];

        root->left = convert(nodes, start, mid - 1);
        root->right = convert(nodes, mid + 1, end);

        return root;
    }
    void balance_tree(node*& root) {

        vector<node*> nodes;
        pushTreeNodes(root, nodes);
        root = convert(nodes, 0, nodes.size() - 1);
    }

    int height(node* node) {
        if (node == NULL)
            return 0;
        return 1 + max(height(node->left), height(node->right));
    }

    node* ll_rotation(node*& t)
    {
        node* u = t->right;
        t->right = u->left;
        u->left = t;
        t->height = max(height(t->left), height(t->right)) + 1;
        u->height = max(height(t->right), t->height) + 1;
        return u;
    }


    bool isAVL(node* root) {
        int lh;
        int rh;
        if (root == NULL)
            return 1;
        lh = height(root->left);
        rh = height(root->right); 
        if (abs(lh - rh) <= 1 && isAVL(root->left) && isAVL(root->right)) return 1;
        return 0;
    }

    int minValue(node* node) {

        struct node* current = node;

        while (current->left != NULL) {
            current = current->left;
        }
        return (current->data);
    }
public:
    BST() {
        root = NULL;
    }

    ~BST() {
        root = makeEmpty(root);
    }

    void insert(int x) {
        root = insert(x, root);
    }
    int findSecondMinimumValue(node* root) {
        if (root == NULL) {
            return -1;
        }
        int val = helper(root, root->data);
        if (val == INT_MAX) {
            return -1;
        }
        return val;
    }
    void printpost() {
        cout << "Data";
        postorder(root);
    }
    int helper(node* node, int minVal) {
        if (node == NULL) {
            return INT_MAX;
        }
        if (node->data < minVal) {
            return node->data;
        }
        int left = helper(node->left, minVal);
        int right = helper(node->right, minVal);
        return min(left, right);
    }
    void PrintSecondMin() {
        cout << "Second Minimum Element : " << findSecondMinimumValue(root) << endl;
    }
    void remove(int x) {
        root = remove(x, root);
    }
   
    void display() {
        cout << "Data";
        inorder(root);
    }
    void search(int x) {
        root = find(root, x);
    }

    void BalancedBST() {
        balance_tree(root);
    }

    void preorderprint() {
        cout << endl;
        cout << "Data";
        preorder(root);
    }
    void skewed(){
        int a = isSkewedBT(root);
        cout << endl;
        if (a == 0) {
            cout << "Tree is NOT Skewed." << endl;;
        }
        else {
            cout << "Tree is Skewed." << endl;;
        }
    }
    void leftrotate() {
        cout << endl << "Left Rotation";
        ll_rotation(root);
    }
    void Print(node* root) {
        cout << "-> " << root;
        if (root->right)
            Print(root->right);
        if (root->left)
            Print(root->left);
    }
    void print() {
        cout << "Data";
        Print(root);
    }
    void AVL() {
        cout << endl;
        int a = isAVL(root);

        if (a == 0) {
            cout << "Tree is NOT AVL." << endl;
        }
        else {
            cout << "Tree is AVL." << endl;
        }
    }
    void minelement() {
        cout << endl << "Minimum Element : " << minValue(root) << endl;
    }
};

int main() {
    BST b;
    b.insert(4);
    b.insert(3);
    b.insert(5);
    b.insert(2);
    b.insert(6);
    b.insert(1);
    b.insert(7);
    b.display();
    cout << endl;
    b.AVL();
    b.skewed();
    b.minelement();
    cout << endl;
    b.PrintSecondMin();
    cout << endl << endl;;
    cout << "Balanced BST ";
    b.BalancedBST();
    b.preorderprint();
    cout << endl;
    b.skewed();
    b.AVL();
    b.minelement();
    cout << endl;
    b.PrintSecondMin();
    cout << endl;
    BST c;
    cout << endl << "New Tree" << endl;
    cout << endl;
    c.insert(20);
    c.insert(15);
    c.insert(10);
    c.insert(5);
    c.insert(3);
    c.insert(25);
    c.display();
    c.leftrotate();
    c.preorderprint();
    cout << endl << endl << endl;
    return 0;
}