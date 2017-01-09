// test_N2DllSharedAccess.cpp: определяет точку входа для консольного приложения.
//


#include "../../Testing.h"
#include "N2DllSharedAccess.h"
#include "N2Register.h"

using namespace std;


int _tmain(int argc, _TCHAR* argv[])
{
	using namespace GloTest;
	TEST_INIT("N2DllSharedAccess class testing");
	
	N2DllSharedAccess _test_class;
	std_string _path = "KERNE_L.dll";

	TEST_CHK(!_test_class.findLib(EMPTY_STR));
	TEST_CHK(!_test_class.attach(EMPTY_STR));
	TEST_CHK(_test_class.getProcedure(EMPTY_STR) == NULL);
	
	TEST_CHK(_test_class.findLib(_path));
	TEST_CHK(_test_class.attach(_path));
	TEST_CHK(_test_class.getProcedure(_path));
	
	GloTest::printResult();
	return GloTest::errors();
}

