#include <stdio.h>

typedef struct {
  int data;
  void *next;
} Node;
Node *head = NULL;

void user_prompt() {
  printf("1. Add a node to the list.\n");
  printf("2. Remove a node from the list.\n");
  printf("3. Insert a node to a position in the list.\n");
  printf("4. Quit.\n");
  printf("Enter input: ");
}

Node *search(Node *list, int k) {
    Node* res = list->next;
    while(res != NULL && res->data != k) {
        res = res->next;
    }
    return res;
}

void insert(Node *list, Node *k) {
    k->next = list->next;
}

int main(int argc, char **argv) {
  int choice = -1;
  while (choice != 4) {
    user_prompt();
    scanf("%d", &choice);
    switch (choice) {
    case 1:
      break;
    case 2:
      break;
    case 3:
      break;
    case 4:
      break;
    default:
      printf("Invalid input.\n");
    }
  }
}
