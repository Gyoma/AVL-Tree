#pragma once

class AVLtree
{
public:

	class Node
	{
	public:

		Node(int _key = 0, int _height = 1, Node * _left = nullptr, Node * _right = nullptr);
		int key;
		friend class AVLtree;

	private:
		int height;
		Node* left, * right;
	};

	AVLtree();

	void push(int k);

	void pop(int k);

	Node* find(int key);

	void printTree(int mode = 0, Node * node = nullptr);

	~AVLtree();

private:

	Node* push(Node* node, int key);

	Node* pop(Node* node, int key);

	Node* find(Node* node, int key);

	unsigned char height(Node* node);

	int bfactor(Node* node);

	void fixheight(Node* node);

	Node* rotateright(Node* node);

	Node* rotateleft(Node* node);

	Node* balance(Node* node);

	Node* findmin(Node* node);

	Node* removemin(Node* node);

	void deleteTree(Node* node);

	Node* root;
};