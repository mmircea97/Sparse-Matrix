#pragma once

struct Triple
{
	int lin, col, val;
};

struct SMatrixNode {
	SMatrixNode* left;
	SMatrixNode* right;
	Triple tr;
};


class SMatrix {
private:
	int nrLine, nrColumn;
	int valueAtPosition(SMatrixNode* node, int i, int j);
public:
	SMatrixNode* head;
	void init(SMatrix &mat, int nrL, int nrC);
	int nrLines(SMatrix mat);
	int nrColumns(SMatrix mat);
	int element(SMatrix mat, int nrL, int nrC);
	SMatrix modify(SMatrix mat, int lin, int col, int v);

};

