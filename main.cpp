#include<iostream>
#include "SparseMatrix.h"
#include"TestSparseMatrix.h"
using namespace std;

void Inorder(SMatrixNode* node, SMatrix mat)
{
	if (node == nullptr)
		return;
	Inorder(node->left, mat);
	if(node == mat.head)
		cout << node->tr.lin << " " << node->tr.col << " " << node->tr.val << " -h" << endl;
	else
		cout << node->tr.lin << " " << node->tr.col << " " << node->tr.val << endl;
	Inorder(node->right, mat);
}

void constructMatrix1(SMatrix& mat)
{
	Triple t;
	//Adding the head
	t.lin = 2;
	t.col = 4;
	t.val = 60;
	mat = mat.modify(mat, t.lin, t.col, t.val);

	
	//Adding values
	t.lin = 2;
	t.col = 3;
	t.val = 42;
	mat = mat.modify(mat, t.lin, t.col, t.val);

	t.lin = 2;
	t.col = 1;
	t.val = 12;
	mat = mat.modify(mat, t.lin, t.col, t.val);
	
	t.lin = 4;
	t.col = 5;
	t.val = 868;
	mat = mat.modify(mat, t.lin, t.col, t.val);

	t.lin = 4;
	t.col = 3;
	t.val = 27;
	mat = mat.modify(mat, t.lin, t.col, t.val);

	t.lin = 5;
	t.col = 1;
	t.val = 8;
	mat = mat.modify(mat, t.lin, t.col, t.val);

	t.lin = 5;
	t.col = 4;
	t.val = 10;
	mat = mat.modify(mat, t.lin, t.col, t.val);

	t.lin = 4;
	t.col = 2;
	t.val = 50;
	mat = mat.modify(mat, t.lin, t.col, t.val);

	t.lin = 4;
	t.col = 4;
	t.val = 66;
	mat = mat.modify(mat, t.lin, t.col, t.val);

	t.lin = 4;
	t.col = 8;
	t.val = 70;
	mat = mat.modify(mat, t.lin, t.col, t.val);
	
}

void constructMatrix2(SMatrix& mat)
{
	Triple t;
	//Adding the head
	t.lin = 2;
	t.col = 1;
	t.val = 12;
	mat = mat.modify(mat, t.lin, t.col, t.val);


	//Adding values
	t.lin = 1;
	t.col = 6;
	t.val = 67;
	mat = mat.modify(mat, t.lin, t.col, t.val);

	t.lin = 1;
	t.col = 1;
	t.val = 140;
	mat = mat.modify(mat, t.lin, t.col, t.val);

	t.lin = 4;
	t.col = 5;
	t.val = 132;
	mat = mat.modify(mat, t.lin, t.col, t.val);

	t.lin = 4;
	t.col = 7;
	t.val = 299;
	mat = mat.modify(mat, t.lin, t.col, t.val);

	t.lin = 5;
	t.col = 1;
	t.val = 2;
	mat = mat.modify(mat, t.lin, t.col, t.val);

	t.lin = 5;
	t.col = 3;
	t.val = 11;
	mat = mat.modify(mat, t.lin, t.col, t.val);

	t.lin = 4;
	t.col = 2;
	t.val = 5;
	mat = mat.modify(mat, t.lin, t.col, t.val);

	t.lin = 4;
	t.col = 7;
	t.val = 23;
	mat = mat.modify(mat, t.lin, t.col, t.val);

	t.lin = 4;
	t.col = 8;
	t.val = 7;
	mat = mat.modify(mat, t.lin, t.col, t.val);

}

void addMatrices(SMatrix m1, SMatrix m2, SMatrix& m3)
{
	//Matrices must have the same number of lines and columns
	int i, j;
	for(i=1; i<=m1.nrLines(m1); i++)
		for(j=1; j<=m1.nrColumns(m1); j++)
			if (m1.element(m1, i, j) != 0)
			{
				if (m2.element(m2, i, j) != 0)
					m3 = m3.modify(m3, i, j, m1.element(m1, i, j) + m2.element(m2, i, j));
				else if (m2.element(m2, i, j) == 0)
					m3 = m3.modify(m3, i, j, m1.element(m1, i, j));
			}
			else if (m1.element(m1, i, j) == 0)
			{
				if (m2.element(m2, i, j) != 0)
					m3 = m3.modify(m3, i, j, m2.element(m2, i, j));
			}
}

void subtractMatrices(SMatrix m1, SMatrix m2, SMatrix& m3)
{
	//Matrices must have the same number of lines and columns
	int i, j;
	for (i = 1; i <= m1.nrLines(m1); i++)
		for (j = 1; j <= m1.nrColumns(m1); j++)
			if (m1.element(m1, i, j) != 0)
			{
				if (m2.element(m2, i, j) != 0)
					m3 = m3.modify(m3, i, j, m1.element(m1, i, j) - m2.element(m2, i, j));
				else if (m2.element(m2, i, j) == 0)
					m3 = m3.modify(m3, i, j, m1.element(m1, i, j));
			}
			else if (m1.element(m1, i, j) == 0)
			{
				if (m2.element(m2, i, j) != 0)
					m3 = m3.modify(m3, i, j, -m2.element(m2, i, j));
			}
}

int main()
{
	SMatrix mat1;
	SMatrix mat2;
	SMatrix mat3;
	SMatrix mat4;

	TestSMatrix t;
	
	t.test_all();

	mat1.init(mat1, 8, 8);
	mat2.init(mat2, 8, 8);
	mat3.init(mat3, 8, 8);
	mat4.init(mat4, 8, 8);

	constructMatrix1(mat1);
	constructMatrix2(mat2);

	bool notExit = true;
	int op;
	while (notExit)
	{
		cout << "1. Print the first matrix\n2. Print the second matrix\n3. Add the two matrices\n4. Subtract the two matrices\n0. Exit\n";
		cout << "Select one of the above options: ";
		cin >> op;
		if (op == 1)
		{
			cout << "The first matrix is: " << endl;
			Inorder(mat1.head, mat1);
		}
		else if (op == 2)
		{
			cout << "The second matrix is: " << endl;
			Inorder(mat2.head, mat2);
		}
		else if (op == 3)
		{
			addMatrices(mat1, mat2, mat3);
			cout << "The addition matrix is: " << endl;
			Inorder(mat3.head, mat3);
		}
		else if (op == 4)
		{
			subtractMatrices(mat1, mat2, mat4);
			cout << "The subtraction matrix is: " << endl;
			Inorder(mat4.head, mat4);
		}
		else if (op == 0)
		{
			notExit = false;
		}
	}
	return 0;
}