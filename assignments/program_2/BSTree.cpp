//A binary search tree where everything on left is 
//smaller than parent, everything on right is greater than parent

#include <iostream>
#include <fstream>
#include <string>
#include "BSTree.h"
#pragma once
using namespace std;

/**
* Class BSTree:
*
* Public Methods:
*    int count();

void insert(int x);

void deleteNode(int key);

void minValue();

int height(int key = -1);

int top();

void printLevelOrder();

void GraphVizOut(string filename);
*/

/**
* Function count:
*     counts the number of elements in the tree
*
* Params:
*     node* root
* Returns
*      int -number of items in tree
*/
int BSTree::count(node *root)
	{
		if (!root)
		{
			return 0;
		}
		else
		{
			return 1 + count(root->left) + count(root->right);
		}
	}

/**
* Function Insert:
*      Inserts an item into the tree
*
* Params:
*     node*& root, node*&temp
* Returns
*      void
*/
void BSTree::insert(node *&root, node *&temp)
	{
		if (!root)
		{
			root = temp;
		}
		else
		{
			if (temp->data < root->data)
			{
				insert(root->left, temp);
			}
			else
			{
				insert(root->right, temp);
			}
		}
	}

/**
* Function print_node:
*     prints out the tree and states if its left child or right child
*
* Params:
*     node* node, string label
* Returns
*      void
*/
void BSTree::print_node(node *n, string label)
	{
		if (label != "")
		{
			cout << "[" << label << "]";
		}
		cout << "[[" << n << "][" << n->data << "]]\n";
		if (n->left)
		{
			cout << "\t|-->[L][[" << n->left << "][" << n->left->data << "]]\n";
		}
		else
		{
			cout << "\t\\-->[L][null]\n";
		}
		if (n->right)
		{
			cout << "\t\\-->[R][[" << n->right << "][" << n->right->data << "]]\n";
		}
		else
		{
			cout << "\t\\-->[R][null]\n";
		}
	}

/**
* Function minVlueNode:
*      finds the predecessor or successor for when deleting a nod
*
* Params:
*     node* root
* Returns
*      node*
*/
node* BSTree::minValueNode(node *root)
	{
		node *current = root;

		if (root->right)
		{
			current = root->right;
			while (current->left != NULL)
			{
				current = current->left;
			}
		}
		else if (root->left)
		{
			current = root->left;
			while (current->right != NULL)
			{
				current = current->right;
			}
		}

		return current;
	}

/**
* Function deleteNode:
*     finds and deletes a key from the tree
*
* Params:
*     node*& root,int key
* Returns
*      node*
*/
node* BSTree::deleteNode(node *&root, int key)
	{
		if (!root)
		{
			return NULL;
		}
		if (key < root->data)
		{
			cout << "going left" << endl;
			root->left = deleteNode(root->left, key);
		}
		else if (key > root->data)
		{
			cout << "going right" << endl;
			root->right = deleteNode(root->right, key);
		}
		else
		{
			if (root->left == NULL)
			{
				node *temp = root->right;
				delete root;
				return temp;
			}
			else if (root->right == NULL)
			{
				node *temp = root->left;
				delete root;
				return temp;
			}

			// node with two children: Get the inorder successor (smallest
			// in the right subtree)
			node *temp = minValueNode(root);

			print_node(temp, "minvaluenode");

			// Copy the inorder successor's content to this node
			root->data = temp->data;

			// Delete the inorder successor
			root->right = deleteNode(root->right, temp->data);
		}
		return root;
	}

/**
* Function height:
*      calculates the height of the tree
*
* Params:
*     node* root
* Returns
*      int
*/
int BSTree::height(node *root)
	{
		if (!root)
		{
			return 0;
		}
		else
		{
			int left = height(root->left);
			int right = height(root->right);
			if (left > right)
			{
				return left + 1;
			}
			else
			{
				return right + 1;
			}
		}
	}

/**
* Function printGivenLevel:
*      print nodes at a given level
*
* Params:
*     node* root, int level
* Returns
*      void
*/
void BSTree::printGivenLevel(node *root, int level)
	{
		if (root == NULL)
			return;
		if (level == 1)
		{
			print_node(root);
		}
		else if (level > 1)
		{
			printGivenLevel(root->left, level - 1);
			printGivenLevel(root->right, level - 1);
		}
	}
	//************************************************************************
	// Method to help create GraphViz code so the expression tree can
	// be visualized. This method prints out all the unique node id's
	// by traversing the tree.
	// Recivies a node pointer to root and performs a simple recursive
	// tree traversal.
	//************************************************************************
void BSTree::GraphVizGetIds(node *nodePtr, ofstream &VizOut)
	{
		static int NullCount = 0;
		if (nodePtr)
		{
			GraphVizGetIds(nodePtr->left, VizOut);
			VizOut << "node" << nodePtr->data
				<< "[label=\"" << nodePtr->data << "\\n"
				//<<"Add:"<<nodePtr<<"\\n"
				//<<"Par:"<<nodePtr->parent<<"\\n"
				//<<"Rt:"<<nodePtr->right<<"\\n"
				//<<"Lt:"<<nodePtr->left<<"\\n"
				<< "\"]" << endl;
			if (!nodePtr->left)
			{
				NullCount++;
				VizOut << "nnode" << NullCount << "[label=\"X\",shape=point,width=.15]" << endl;
			}
			GraphVizGetIds(nodePtr->right, VizOut);
			if (!nodePtr->right)
			{
				NullCount++;
				VizOut << "nnode" << NullCount << "[label=\"X\",shape=point,width=.15]" << endl;
			}
		}
	}

	//************************************************************************
	// This method is partnered with the above method, but on this pass it
	// writes out the actual data from each node.
	// Don't worry about what this method and the above method do, just
	// use the output as your told:)
	//************************************************************************
void BSTree::GraphVizMakeConnections(node *nodePtr, ofstream &VizOut)
	{
		static int NullCount = 0;
		if (nodePtr)
		{
			GraphVizMakeConnections(nodePtr->left, VizOut);
			if (nodePtr->left)
				VizOut << "node" << nodePtr->data << "->"
				<< "node" << nodePtr->left->data << endl;
			else
			{
				NullCount++;
				VizOut << "node" << nodePtr->data << "->"
					<< "nnode" << NullCount << endl;
			}

			if (nodePtr->right)
				VizOut << "node" << nodePtr->data << "->"
				<< "node" << nodePtr->right->data << endl;
			else
			{
				NullCount++;
				VizOut << "node" << nodePtr->data << "->"
					<< "nnode" << NullCount << endl;
			}

			GraphVizMakeConnections(nodePtr->right, VizOut);
		}
	}


BSTree::BSTree()
	{
		root = NULL;
	}
BSTree::~BSTree()
	{
	}

/**
* Function count:
*      calls private count to get number of items in tree
*
* Params:
*     none
* Returns
*      int
*/
int BSTree::count()
	{
		return count(root);
	}

/**
* Function insert:
*     calls real insert to insert x into tree
*
* Params:
*    int x
* Returns
*      void
*/
void BSTree::insert(int x)
	{
		node *temp = new node(x);
		insert(root, temp);
	}

/**
* Function deletNode:
*      looks for key and calls real delete to delete key from tree
*
* Params:
*     int key
* Returns
*      void
*/
void BSTree::deleteNode(int key)
	{
		root = deleteNode(root, key);
	}

/**
* Function minValue:
*      call real minValue and gets predecessor or sucessor
*
* Params:
*     none
* Returns
*      void
*/
void BSTree::minValue()
	{
		print_node(minValueNode(root), "minVal");
	}

/**
* Function height:
*     calls real height to get height of the tree
*
* Params:
*     int key
* Returns
*      int
*/
int BSTree::height(int key)
	{
		if (key > 0)
		{
			//find node
		}
		else
		{
			return height(root);
		}
		return 0;
	}

/**
* Function top:
*     returns value of root node
*
* Params:
*     none
* Returns
*      int
*/
int BSTree::top()
	{
		if (root)
			return root->data;
		else
			return 0;
	}

/**
* Function printLevelOrder:
*      Function to line by line print level order traversal a tree
*
* Params:
*     none
* Returns
*      none
*/
void BSTree::printLevelOrder()
	{
		cout << "Begin Level Order===================\n";
		int h = height(root);
		int i;
		for (i = 1; i <= h; i++)
		{
			printGivenLevel(root, i);
			cout << "\n";
		}
		cout << "End Level Order===================\n";
	}

	//************************************************************************
	// Recieves a filename to place the GraphViz data into.
	// It then calls the above two graphviz methods to create a data file
	// that can be used to visualize your expression tree.
	//************************************************************************
void BSTree::GraphVizOut(string filename)
	{
		ofstream VizOut;
		VizOut.open(filename);
		VizOut << "Digraph G {\n";
		GraphVizGetIds(root, VizOut);
		GraphVizMakeConnections(root, VizOut);
		VizOut << "}\n";
		VizOut.close();
	}

