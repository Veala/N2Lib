// test_N2VariablesManager.cpp: определяет точку входа для консольного приложения.
//

//#include "stdafx.h"
#include "../../Testing.h"
#include "N2Variable.h"
#include <iostream>

using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	using namespace GloTest;
	TEST_INIT("N2Variables");

	N2VariableCreator maker;
	N2BaseVariable* pBase;
	N2BaseVariableTable* pTable = NULL;
	N2VariableINT* pI;
	
	//N2_VMT type = VMT_CACHE;


	TEST_CHK((pBase = maker.createSimplex(VAR_INT, "iVar1", 10)) != NULL);
	pI = (N2VariableINT*)pBase;
	for(int i=0; i<10; i++)
		TEST_CHK(pI->set(i, i));
	for(int i=0; i<10; i++)
		TEST_CHK(*pI->get(i) == i);
	for(int i=0; i<10; i++) {
		TEST_CHK(pI->getValue(i) == i);
		//cout << pI->getValue(i) << ", " ;
	}
	//maker

	TEST_CHK((pBase = maker.createSimplex(VAR_TERNAR, "iTern1", 10)) != NULL);
	N2VariableTO* pTO = (N2VariableTO*)pBase;
	TERNAR tern [10] = {TERNAR_YES, TERNAR_NO, TERNAR_DISABLE, \
						TERNAR_YES, TERNAR_NO, TERNAR_DISABLE, \
						TERNAR_YES, TERNAR_NO, TERNAR_DISABLE, \
						TERNAR_YES };
	for(int i=0; i<pTO->dimension(); i++)
		TEST_CHK(pTO->set(tern[i], i));
	for(int i=0; i<pTO->dimension(); i++)
		TEST_CHK(*pTO->get(i) == tern[i]);
	for(int i=0; i<pTO->dimension(); i++) {
		TEST_CHK(pTO->getValue(i) == tern[i]);
		//cout << pTO->getValue(i) << ", " ;
	}

	TEST_CHK((pTable = (N2BaseVariableTable*)maker.createTable(VAR_INT, "iTable", 10, 5)) != NULL);
	N2VariableIntTABLE* pTI = (N2VariableIntTABLE*)pTable;
	int x = 0;
	for(int i=0; i<10; i++)
		for(int j=0; j<5; j++)
			TEST_CHK(pTI->tbl.set(i, j, x++));
	for(int i=0; i<10; i++)
		for(int j=0; j<5; j++) {
			if(j == 0) cout << endl;
			cout << pTI->tbl.get(i, j) << " ; ";
		}
	cout << endl;

	N2BaseVariableTable* pTemp = (N2BaseVariableTable*)pTable->clone();
	pTI = (N2VariableIntTABLE*)pTemp;
	for(int i=0; i<10; i++)
		for(int j=0; j<5; j++) {
			if(j == 0) cout << endl;
			cout << pTI->tbl.get(i, j) << " ; ";
		}
	cout << endl;

	TEST_CHK(pTI->tbl.fill(99));
	for(int i=0; i<10; i++)
		for(int j=0; j<5; j++) {
			if(j == 0) cout << endl;
			cout << pTI->tbl.get(i, j) << " ; ";
		}
	cout << endl;



	GloTest::printResult();
	return GloTest::errors();
}