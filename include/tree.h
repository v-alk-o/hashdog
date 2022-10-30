#ifndef TREE_H
#define TREE_H

typedef struct Node Node;

struct Node
{
	char* cleartext;
	char* hash;
	Node* left;
	Node* right;
};

Node* new_tree();
Node* new_node(char* cleartext, char* hash);
void insert_node(Node** root_ptr, char* cleartext, char* hash);
char* find_node(Node* root, char* hash);
void free_tree(Node* root);

#endif