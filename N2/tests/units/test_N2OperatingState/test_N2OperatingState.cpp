// test_N2OperatingState.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "../../Testing.h"
#include "N2OperatingState.h"
#include "c:\work\N2\export\common\N2Base.h"


int _tmain(int argc, _TCHAR* argv[])
{
	using namespace GloTest;
	TEST_INIT("test_N2OperatingState");
	
	using namespace N2_Defines;
	
	//check N2AllOperatingState.cpp file
	/*N2OperatingState test_N2_OS;

	TEST_CHK(N2OperatingState.mode() == OPERATING_MODE::MODE_UNDEFINE);*/
	
	GloTest::printResult();
	return GloTest::errors();
}


