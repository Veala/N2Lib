// test_N2Module.cpp: определяет точку входа для консольного приложения.
//

//#include "stdafx.h"
#include "../../Testing.h"
#include "N2Module.h"
#include "../../../src/N2Module.cpp"

int _tmain(int argc, _TCHAR* argv[])
{
	using namespace GloTest;
	TEST_INIT("N2Module testing");

	N2RouteLine test_struct;
	//N2RoutingTable test_struct_01;
	
	test_struct.signIn = 12345;
	test_struct.obligative = false;
	test_struct.fileExtLibrary = "";
	test_struct.name = "";
	test_struct.signOut = 321;
	test_struct.autoChange = FD_AUTO;

	SIGN x = 1234;

	//TEST_CHK(test_struct_01.getOnSign(x) == NULL);
	//TEST_CHK(!test_struct_01.getOnSign(test_struct.signIn) == NULL);

	//getchar();
	
	GloTest::printResult();
	return GloTest::errors();
}

