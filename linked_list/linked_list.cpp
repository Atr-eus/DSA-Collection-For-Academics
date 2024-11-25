#include <iostream>
using namespace std;

class Node {
public:
  int data;
  Node *next;

  Node(int d = 0, Node *n = nullptr) {
    data = d;
    next = n;
  }
};

class LinkedList {
  Node *head;

public:
  LinkedList() : head(nullptr) {};

  void unshift(int val) { head = new Node(val, head); }

  void insert_at(int val, int pos) {}

  void push_back(int val) {
    if (head == nullptr) {
      head = new Node(val);
      return;
    }

    Node *node = head;
    while (node->next != nullptr)
      node = node->next;

    node->next = new Node(val);
  }

  void display() {
    Node *node = head;
    while (node->next != nullptr) {
      cout << node->data;
      node = node->next;
      if (node->next != nullptr)
        cout << " -> ";
    }
    cout << "\n";
  }
};

int main() {
  LinkedList ll;
  ll.push_back(1);
  ll.push_back(2);
  ll.push_back(3);
  ll.push_back(4);
  ll.unshift(100);

  ll.display();
}
