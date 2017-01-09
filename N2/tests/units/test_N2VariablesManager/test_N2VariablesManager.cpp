// test_N2VariablesManager.cpp: определяет точку входа для консольного приложения.
//

//#include "stdafx.h"
#include "../../Testing.h"
#include "N2VariablesManager.h"


int _tmain(int argc, _TCHAR* argv[])
{
	using namespace GloTest;
	TEST_INIT("N2VariablesManager.h");

	N2VariablesManager test_class;
	N2BaseVariable* class_ptr;
	
	//N2_VMT type = VMT_CACHE;

	TEST_CHK(!test_class.declare(class_ptr/*, type*/));

	std_string name = "string name";

	TEST_CHK(!test_class.release(name/*, type*/));

	TEST_CHK(test_class.getVar(name) == NULL);
	//TEST_CHK(test_class.getGlobal(name) == NULL);


	GloTest::printResult();
	return GloTest::errors();
}