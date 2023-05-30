#include "SparseMatrix.h"
#include<utility>
#include<stdlib.h>



int SMatrix::valueAtPosition(SMatrixNode* node, int i, int j)
{
	if (node == nullptr)
		return 0;
	if (node->tr.lin == i && node->tr.col == j)
		return node->tr.val;
	if (node->tr.lin < i || (node->tr.lin == i && node->tr.col < j))
		return valueAtPosition(node->right, i, j);
	if (node->tr.lin > i || (node->tr.lin == i && node->tr.col > j))
		return valueAtPosition(node->left, i, j);
}


void SMatrix::init(SMatrix &mat, int nrL, int nrC)
{
	if (nrL < 1 || nrC < 1)
		throw "Invalid line or column number.";
	mat.nrLine = nrL;
	mat.nrColumn = nrC;
	mat.head = nullptr;
}


int SMatrix::nrLines(SMatrix mat)
{
	return mat.nrLine;
}


int SMatrix::nrColumns(SMatrix mat)
{
	return mat.nrColumn;
}


int SMatrix::element(SMatrix mat, int i, int j)
{
	if (i < 1 || i > mat.nrLines(mat) || j < 1 || j > mat.nrColumns(mat))
		throw "Invalid line or column number.";
	return valueAtPosition(mat.head, i, j);
}


std::pair<SMatrixNode*, SMatrixNode*> nodeAndParent(SMatrixNode* node, SMatrixNode* parent, int i, int j)
{
	//First value is the node of the value at (i, j), second one is the node of the parent
	if (node == nullptr)
		return std::make_pair(nullptr, parent);
	else if (node->tr.lin == i && node->tr.col == j)
		return std::make_pair(node, parent);
	else if (node->tr.lin < i || (node->tr.lin == i && node->tr.col < j))
		return nodeAndParent(node->right, node, i, j);
	else if (node->tr.lin > i || (node->tr.lin == i && node->tr.col > j))
		return nodeAndParent(node->left, node, i, j);
}

SMatrixNode* emptyNode()
{
	SMatrixNode* newNode = new SMatrixNode;
	newNode->left = nullptr;
	newNode->right = nullptr;
	return newNode;
}

SMatrix SMatrix::modify(SMatrix mat, int i, int j, int v)
{
	std::pair<SMatrixNode*, SMatrixNode*>nodesPair = nodeAndParent(mat.head, nullptr, i, j);
	SMatrixNode* aux;
	SMatrixNode* auxParent;
	if(i < 1 || i > mat.nrLines(mat) || j < 1 || j > mat.nrColumns(mat))
		throw "Invalid line or column number.";

	if (nodesPair.first == nullptr && nodesPair.second == nullptr && v != 0)
	{
		nodesPair.first = emptyNode();
		nodesPair.first->tr.lin = i;
		nodesPair.first->tr.col = j;
		nodesPair.first->tr.val = v;
		mat.head = nodesPair.first;
	}
	else if (element(mat, i, j) != 0 && v != 0)
	{
		nodesPair.first->tr.val = v;
	}
	else if (element(mat, i, j) == 0 && v != 0)
	{
		if (i < nodesPair.second->tr.lin || (i == nodesPair.second->tr.lin && j < nodesPair.second->tr.col))
		{
			nodesPair.second->left = emptyNode();
			nodesPair.second->left->tr.lin = i;
			nodesPair.second->left->tr.col = j;
			nodesPair.second->left->tr.val = v;
		}
		if (i > nodesPair.second->tr.lin || (i == nodesPair.second->tr.lin && j > nodesPair.second->tr.col))
		{
			nodesPair.second->right = emptyNode();
			nodesPair.second->right->tr.lin = i;
			nodesPair.second->right->tr.col = j;
			nodesPair.second->right->tr.val = v;
		}
	}
	else if (element(mat, i, j) != 0 && v == 0)
	{
		if (nodesPair.second != nullptr)
		{
			if (nodesPair.first->left != nullptr && nodesPair.first->right != nullptr)
			{
				aux = nodesPair.first->right;
				auxParent = nodesPair.first;
				while (aux->left != nullptr)
				{
					auxParent = aux;
					aux = aux->left;
				}
				if (auxParent == nodesPair.first)
				{
					aux->left = nodesPair.first->left;
					if (nodesPair.first->tr.lin < nodesPair.second->tr.lin || (nodesPair.first->tr.lin == nodesPair.second->tr.lin && nodesPair.first->tr.col < nodesPair.second->tr.col))
					{
						nodesPair.second->left = aux;
					}
					else if (nodesPair.first->tr.lin > nodesPair.second->tr.lin || (nodesPair.first->tr.lin == nodesPair.second->tr.lin && nodesPair.first->tr.col > nodesPair.second->tr.col))
					{
						nodesPair.second->right = aux;
					}
				}
				else {
					nodesPair.first->tr.lin = aux->tr.lin;
					nodesPair.first->tr.col = aux->tr.col;
					nodesPair.first->tr.val = aux->tr.val;
					auxParent->left = nullptr;
				}
			}
			else if (nodesPair.first->left != nullptr && nodesPair.first->right == nullptr)
			{
				if (nodesPair.first->tr.lin < nodesPair.second->tr.lin || (nodesPair.first->tr.lin == nodesPair.second->tr.lin && nodesPair.first->tr.col < nodesPair.second->tr.col))
				{
					nodesPair.second->left = nodesPair.first->left;
				}
				else if (nodesPair.first->tr.lin > nodesPair.second->tr.lin || (nodesPair.first->tr.lin == nodesPair.second->tr.lin && nodesPair.first->tr.col > nodesPair.second->tr.col))
				{
					nodesPair.second->right = nodesPair.first->left;
				}
			}
			else if (nodesPair.first->left == nullptr && nodesPair.first->right != nullptr)
			{
				if (nodesPair.first->tr.lin < nodesPair.second->tr.lin || (nodesPair.first->tr.lin == nodesPair.second->tr.lin && nodesPair.first->tr.col < nodesPair.second->tr.col))
				{
					nodesPair.second->left = nodesPair.first->right;
				}
				else if (nodesPair.first->tr.lin > nodesPair.second->tr.lin || (nodesPair.first->tr.lin == nodesPair.second->tr.lin && nodesPair.first->tr.col > nodesPair.second->tr.col))
				{
					nodesPair.second->right = nodesPair.first->right;
				}
			}
			else if (nodesPair.first->left == nullptr && nodesPair.first->right == nullptr)
			{
				if (nodesPair.first->tr.lin < nodesPair.second->tr.lin || (nodesPair.first->tr.lin == nodesPair.second->tr.lin && nodesPair.first->tr.col < nodesPair.second->tr.col))
					nodesPair.second->left = nullptr;
				else if (nodesPair.first->tr.lin > nodesPair.second->tr.lin || (nodesPair.first->tr.lin == nodesPair.second->tr.lin && nodesPair.first->tr.col > nodesPair.second->tr.col))
					nodesPair.second->right = nullptr;
			}
		}
		else if (nodesPair.second == nullptr)
		{
			if (nodesPair.first->left != nullptr && nodesPair.first->right != nullptr)
			{
				aux = nodesPair.first->right;
				auxParent = nodesPair.first;
				while (aux->left != nullptr)
				{
					auxParent = aux;
					aux = aux->left;
				}
				if (auxParent == nodesPair.first)
				{
					aux->left = nodesPair.first->left;
					mat.head = aux;
				}
				else {
					nodesPair.first->tr.lin = aux->tr.lin;
					nodesPair.first->tr.col = aux->tr.col;
					nodesPair.first->tr.val = aux->tr.val;
					auxParent->left = nullptr;
				}
			}
			else if (nodesPair.first->left != nullptr && nodesPair.first->right == nullptr)
			{
				mat.head = mat.head->left;
			}
			else if (nodesPair.first->left == nullptr && nodesPair.first->right != nullptr)
			{
				mat.head = mat.head->right;
			}
			else if (nodesPair.first->left == nullptr && nodesPair.first->right == nullptr)
			{
				mat.head = nullptr;
			}
		}
	}
	return mat;
}
