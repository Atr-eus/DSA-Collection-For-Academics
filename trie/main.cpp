// ASSIGNMENT I: Create a Trie

#include <iostream>
#include <string>
using namespace std;

struct Node {
  Node *children[26];
  bool end_of_word;

  Node() {
    for (int i = 0; i < 26; ++i) {
      children[i] = nullptr;
    }
  }
};

class Trie {
  Node *root;
  void display(Node *node, string pre) {
    if (node->end_of_word) {
      cout << pre << "\n";
    }

    for (int i = 0; i < 26; ++i) {
      if (node->children[i]) {
        display(node->children[i], pre + char(i + 'a'));
      }
    }
  }

public:
  Trie() : root(new Node()) {};

  void insert(string word) {
    Node *node = root;

    for (const auto &x : word) {
      int idx = x - 'a';
      if (node->children[idx] == nullptr) {
        node->children[idx] = new Node();
      }
      node = node->children[idx];
    }

    node->end_of_word = true;
  }

  bool search(string word) {
    Node *node = root;

    for (const auto &x : word) {
      int idx = x - 'a';
      if (node->children[idx] == nullptr) {
        return false;
      }
      node = node->children[idx];
    }

    return node->end_of_word;
  }

  void display() { display(root, ""); }
};

int main() {
  Trie trie;

  trie.insert("apple");
  trie.insert("angry");
  trie.insert("banana");
  trie.insert("cat");
  trie.insert("diarrhea");
  trie.insert("bottom");
  trie.insert("orange");

  trie.display();

  if (trie.search("cat")) {
    cout << "'cat' found\n";
  } else {
    cout << "'cat' not found\n";
  }
  if (trie.search("dog")) {
    cout << "'dog' found\n";
  } else {
    cout << "'dog' not found\n";
  }
}
