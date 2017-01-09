// test_N2XMLF.cpp: определяет точку входа для консольного приложения.
//

//#include "stdafx.h"
#include "../../Testing.h"
#include "N2XMLF.h"


int _tmain(int argc, _TCHAR* argv[])
{
	using namespace GloTest;
	TEST_INIT("N2XMLF testing");

	XMLF _xmlf;
	ATTR _attr;
	
	_attr.attribute = "attribute";
	_attr.value = "value";
	std_string a = "std_string a",
		v = EMPTY_STR;

	TEST_CHK(_xmlf.find(a, v));
	
	_attr.attribute = "a";
	a = "a";
	
	TEST_CHK(_xmlf.getValue(a) == _attr.value);
	
	a= "b";
	
	TEST_CHK(_xmlf.getValue(a) == EMPTY_STR);


	GloTest::printResult();
	return GloTest::errors();
}

