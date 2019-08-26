#include "AVL.h"
#include <iostream>

AVLtree::Node::Node(int _key, int _height, Node * _left, Node * _right) :
	key(_key),
	height(_height),
	left(_left),
	right(_right)
{}

AVLtree::AVLtree() :
	root(nullptr)
{}

void AVLtree::push(int k)
{
	root = push(root, k);
}

void AVLtree::pop(int k)
{
	root = pop(root, k);
}

AVLtree::Node* AVLtree::find(int key)
{
	return find(root, key);
}

void AVLtree::printTree(int mode, Node * node)
{
	if (node == nullptr)
		node = root;

	std::cout << node->key << ' ';

	if (node->left)
		printTree(mode, node->left);
	if (node->right)
		printTree(mode, node->right);
}

AVLtree::~AVLtree()
{
	deleteTree(root);
}

AVLtree::Node* AVLtree::push(Node* node, int key)
{
	if (!node) return new Node(key);
	if (key < node->key)
		node->left = push(node->left, key);
	else
		node->right = push(node->right, key);
	return balance(node);
}

AVLtree::Node* AVLtree::pop(Node* node, int key)
{
	if (node == nullptr)
		return nullptr;
	if (key < node->key)
		node->left = pop(node->left, key);
	else if (key > node->key)
		node->right = pop(node->right, key);
	else //  k == p->key 
	{
		Node* left_node = node->left;
		Node* right_node = node->right;
		delete node;
		if (right_node == nullptr) return left_node;
		Node* min = findmin(right_node);
		min->right = removemin(right_node);
		min->left = left_node;
		return balance(min);
	}
	return balance(node);
}

AVLtree::Node* AVLtree::find(Node* node, int key)
{
	if (!node)
		return nullptr;
	if (key < node->key)
		node->left = find(node->left, key);
	else if (key > node->key)
		node->right = find(node->right, key);
	else
		return node;
}

unsigned char AVLtree::height(Node* node)
{
	return node ? node->height : 0;
}

int AVLtree::bfactor(Node* node)
{
	return height(node->right) - height(node->left);
}

void AVLtree::fixheight(Node* node)
{
	unsigned char hl = height(node->left);
	unsigned char hr = height(node->right);
	node->height = (hl > hr ? hl : hr) + 1;
}

AVLtree::Node* AVLtree::rotateright(Node* node)
{
	Node* left_node = node->left;
	node->left = left_node->right;
	left_node->right = node;
	fixheight(node);
	fixheight(left_node);
	return left_node;
}

AVLtree::Node* AVLtree::rotateleft(Node* node)
{
	Node* right_node = node->right;
	node->right = right_node->left;
	right_node->left = node;
	fixheight(node);
	fixheight(right_node);
	return right_node;
}

AVLtree::Node* AVLtree::balance(Node* node)
{
	fixheight(node);
	if (bfactor(node) == 2)
	{
		if (bfactor(node->right) < 0)
			node->right = rotateright(node->right);
		return rotateleft(node);
	}
	if (bfactor(node) == -2)
	{
		if (bfactor(node->left) > 0)
			node->left = rotateleft(node->left);
		return rotateright(node);
	}
	return node; // балансировка не нужна
}

AVLtree::Node* AVLtree::findmin(Node* node) // поиск узла с минимальным ключом в дереве node
{
	return node->left ? findmin(node->left) : node;
}

AVLtree::Node* AVLtree::removemin(Node* node) // удаление узла с минимальным ключом из дерева node
{
	if (node->left == nullptr)
		return node->right;
	node->left = removemin(node->left);
	return balance(node);
}

void AVLtree::deleteTree(Node* node)
{
	if (node->left)
		deleteTree(node->left);
	if (node->right)
		deleteTree(node->right);

	delete node;
}