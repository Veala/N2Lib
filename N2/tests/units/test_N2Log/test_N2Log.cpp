// test_N2Log.cpp: определяет точку входа для консольного приложения.
//

//#include "stdafx.h"
#include "../../Testing.h"
#include "N2Log.h"


int _tmain(int argc, _TCHAR* argv[])
{
	using namespace GloTest;
	TEST_INIT("N2Log testing");
	
	N2Logbook test_class;
	int error = 69;
	std::string module = "Module", 
		description = "Description",
		_description = "_Description";

	test_class.WriteError(module, error, description);
	TEST_CHK(test_class.GetLastError(_description) == error);

	
	GloTest::printResult();
	return GloTest::errors();
}



