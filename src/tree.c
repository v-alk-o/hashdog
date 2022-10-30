#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tree.h"


Node* new_tree()
{
	return NULL;
}


Node* new_node(char* cleartext, char* hash)
{
	Node* node = malloc(sizeof(Node));
	if(node != NULL)
	{
		node->cleartext = malloc(strlen(cleartext)+1);
		if(node->cleartext != NULL)
			strcpy(node->cleartext, cleartext);
		
		node->hash = malloc(strlen(hash)+1);
		if(node->hash != NULL)
			strcpy(node->hash, hash);
		
		node->left  = NULL;
		node->right = NULL;
	}
	return node;
}


void insert_node(Node** root_ptr, char* cleartext, char* hash)
{
	Node* root = *root_ptr;
	
	if(root == NULL)
	{
		*root_ptr = new_node(cleartext, hash);
		return;
	}

	int compare = strcmp(hash, root->hash);
	
	if(compare < 0)
		insert_node(&root->left, cleartext, hash);
	else if(compare > 0)
		insert_node(&root->right, cleartext, hash);
	else
		return;
}


char* find_node(Node* root, char* hash)
{
	if(root == NULL)
		return NULL;

	int compare = strcmp(hash, root->hash);

	if(compare < 0)
		return find_node(root->left, hash);
	else if(compare > 0)
		return find_node(root->right, hash);
	else
		return root->cleartext;
}


void free_tree(Node* root)
{
	if(root != NULL)
	{
		free_tree(root->left);
		free_tree(root->right);
		free(root->cleartext);
		free(root->hash);
		free(root);
	}
}