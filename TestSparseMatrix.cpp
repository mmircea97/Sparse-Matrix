#include"TestSparseMatrix.h"
#include"SparseMatrix.h"
#include<assert.h>


void TestSMatrix::test_all()
{
	SMatrix sm;
	sm.init(sm, 6, 6);
	assert(sm.nrLines(sm)==6);
	assert(sm.nrColumns(sm) == 6);
	sm.init(sm, 7, 3);
	assert(sm.nrLines(sm) == 7);
	assert(sm.nrColumns(sm) == 3);
	sm.init(sm, 10, 10);
	assert(sm.nrLines(sm) == 10);
	assert(sm.nrColumns(sm) == 10);
	assert(sm.head == nullptr);
	assert(sm.element(sm, 3, 3) == 0);
	sm = sm.modify(sm, 3, 3, 27);
	assert(sm.element(sm, 3, 3) == 27);
	sm = sm.modify(sm, 3, 3, 0);
	assert(sm.element(sm, 3, 3) == 0);
	sm = sm.modify(sm, 3, 3, 20);
	assert(sm.element(sm, 3, 3) == 20);
	sm = sm.modify(sm, 4, 1, 99);
	assert(sm.element(sm, 4, 1) == 99);
	sm = sm.modify(sm, 3, 5, 80);
	assert(sm.element(sm, 3, 5) == 80);
	sm = sm.modify(sm, 3, 5, 0);
	assert(sm.element(sm, 3, 5) == 0);
	assert(sm.element(sm, 4, 1) == 99);
	sm = sm.modify(sm, 4, 4, 200);
	sm = sm.modify(sm, 5, 2, 38);
	sm = sm.modify(sm, 4, 3, 800);
	assert(sm.element(sm, 4, 4) == 200);
	assert(sm.element(sm, 5, 2) == 38);
	assert(sm.element(sm, 4, 3) == 800);
	sm = sm.modify(sm, 4, 4, 0);
	assert(sm.element(sm, 4, 4) == 0);
	assert(sm.element(sm, 5, 2) == 38);
	assert(sm.element(sm, 4, 3) == 800);
	sm = sm.modify(sm, 5, 3, 89);
	sm = sm.modify(sm, 5, 5, 88);
	assert(sm.element(sm, 5, 3) == 89);
	assert(sm.element(sm, 5, 5) == 88);
	sm.modify(sm, 5, 2, 0);
	assert(sm.element(sm, 5, 2) == 0);
	assert(sm.element(sm, 5, 3) == 89);
	assert(sm.element(sm, 5, 5) == 88);
}
