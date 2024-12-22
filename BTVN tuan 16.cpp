// Ben phai: >=
#include <iostream>
using namespace std;

struct AVL { // Cay AVL
    int data; 
    AVL* left;
    AVL* right;
    int level; 

    AVL(int value) {
        data = value;
        left = right = NULL;
        level = 1;
    }
};

int getLevel(AVL* node) {
    return node ? node->level : 0;
}

// Cap nhat level cua nut
void updateLevel(AVL* node) {
    if (node) {
        node->level = 1 + max(getLevel(node->left), getLevel(node->right)); // Lon hon bac cua nut trai/phai 1 bac
    }
}

// Do lech
int getBalance(AVL* node) {
    return getLevel(node->left) - getLevel(node->right);
}

// Cay lech trai -> Xoay phai
AVL* rotateRight(AVL* node) {
    AVL* newRoot = node->left;
    node->left = newRoot->right;
    newRoot->right = node;

    updateLevel(node);
    updateLevel(newRoot);

    return newRoot;
}

// Cay lech phai -> Xoay trai
AVL* rotateLeft(AVL* node) {
    AVL* newRoot = node->right;
    node->right = newRoot->left;
    newRoot->left = node;

    updateLevel(node);
    updateLevel(newRoot);

    return newRoot;
}

// Xoay kep 
AVL* rotateLeftRight(AVL* node) {
    node->left = rotateLeft(node->left);
    return rotateRight(node);
}

// Xoay kep 
AVL* rotateRightLeft(AVL* node) {
    node->right = rotateRight(node->right);
    return rotateLeft(node);
}

// Them nut
AVL* addNode(AVL* root, int value) {
    if (root == NULL) {
        return new AVL(value);
    }

    // Them trai/ phai
    if (value < root->data) {
        root->left = addNode(root->left, value);
    }
    else {
        // Neu trung lap, them vao ben phai
        root->right = addNode(root->right, value);
    }

    updateLevel(root);

    int balance = getBalance(root);

    if (balance > 1) { // Cay lech trai
        if (value < root->left->data) {
            return rotateRight(root); // Xoay phai
        }
        else {
            return rotateLeftRight(root); // Xoay kep
        }
    }

    if (balance < -1) { // Cay lech phai
        if (value > root->right->data) {
            return rotateLeft(root); // Xoay trai
        }
        else {
            return rotateRightLeft(root); // Xoay kep
        }
    }

    return root; // Cay sau khi duoc can bang
}

// Duyet trung
void inorder(AVL* root) {
    if (root) {
        inorder(root->left);
        cout << root->data << " ";
        inorder(root->right);
    }
}

int main() {
    AVL* root = NULL;
    int Nguyet[] = {17, 23, 201, 98, 67, 83, 13, 23, 10, 191, 84, 58};

    // Them nut
    for (int i = 0; i < 12; i++) {
        root = addNode(root, Nguyet[i]);
    }

    // Duyet trung
    cout << "Mang sau khi sap xep la: ";
    inorder(root);
    cout << endl;

    return 0;
}
