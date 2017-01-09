// test_N2ModulesManager.cpp: определяет точку входа для консольного приложения.
//
//#include "stdafx.h"
#include "../../Testing.h"
#include "N2ModulesManager.h"
#include "N2Base.h"


int _tmain(int argc, _TCHAR* argv[])
{
	using namespace GloTest;
	TEST_INIT("test_N2ModulesManager");

	N2ModulesManager test_N2_MM;


	//TEST_CHK(!(MODE_UNDEFINE == NULL));
	
	GloTest::printResult();
	return GloTest::errors();
}

