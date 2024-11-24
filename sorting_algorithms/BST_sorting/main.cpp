// ASSIGNMENT III: Sorting an array using inorder traversal in a BST

#include <iostream>
#include <vector>
using namespace std;

struct Node {
  int data;
  Node *left;
  Node *right;
};

class BST {
private:
  Node *root;
  Node *insert(Node *root, int val) {
    if (root != nullptr) {
      if (val < root->data) {
        root->left = insert(root->left, val);
      } else {
        root->right = insert(root->right, val);
      }

      return root;
    }

    Node *node = new Node;
    node->data = val;
    node->left = node->right = nullptr;

    return node;
  }

  void inorder(Node *root) {
    if (root != nullptr) {
      inorder(root->left);
      cout << root->data << " ";
      inorder(root->right);
    }
  }

public:
  BST() : root(nullptr) {};

  void insert(int val) { root = insert(root, val); }
  void inorder() {
    inorder(root);
    cout << "\n";
  }
};

int main() {
  vector<int> a = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
  cout << "Unsorted:\n";
  for (auto &i : a)
    cout << i << " ";
  cout << "\n";

  BST bst;
  cout << "Sorted:\n";
  for (auto &i : a)
    bst.insert(i);
  bst.inorder();
}
