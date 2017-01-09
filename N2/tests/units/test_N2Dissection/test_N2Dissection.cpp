// test_N2Dissection.cpp: определяет точку входа для консольного приложения.
//

//#include "stdafx.h"
#include "../../Testing.h"
//#include "../../../export/common/N2Dissection.h"
//#include "../../../export/common/N2Commands.h"
//#include "../../../export/common/N2XMLF.h"
//#include "../../../export/common/N2Defines.h"
#include "N2Dissection.h"
#include "N2Commands.h"
#include "N2XMLF.h"
#include "N2Defines.h"

class ExtDiss : public N2Dissection
{
	public:
		virtual RESULT_DECODE
		decode(XMLF* px, DataPack& pack)
		{
			return SUCCESSFUL;
		}
		virtual bool 
		unpack(CFS* pCFS, VectorCommand* vecComm)
		{
			return true;
		}
};

class testN2Parser : N2Parser
{
	virtual CFS* parse(std_string filename, std_string firstMark = EMPTY_STR)
	{
		return NULL;
	};
	virtual void reset(void)
	{}
};


int _tmain(int argc, _TCHAR* argv[])
{
	using namespace GloTest;
	TEST_INIT("N2Dissection classes");

	N2DissInternal testInt;
	DataPack pck;
	vector<DataPack> testpack;

	TEST_CHK (testInt.decode(NULL, testpack) == N2Dissection::ERROR);

	XMLF testXMLF;
	
	testXMLF.nametag = CT("VAR");
	
	ATTR attr;
	
	attr.attribute = CT("type"); attr.value = CT("INT");
	testXMLF.attr.push_back(attr);
	attr.attribute = CT("var"); attr.value = CT("xxxx");
	testXMLF.attr.push_back(attr);
	TEST_CHK (testInt.decode(&testXMLF, testpack) == N2Dissection::SUCCESSFUL);

	N2DissTotal* _pN2DissTotal;

	_pN2DissTotal = new N2DissTotal;

	TEST_CHK(!_pN2DissTotal->addDissector(NULL));
	TEST_CHK(_pN2DissTotal->addDissector(_pN2DissTotal));
	
	/*N2DissTotal dt;

	TEST_CHK(dt.addDissector(new ExtDiss()));
	TEST_CHK(dt.addDissector(new ExtDiss()));
	TEST_CHK(dt.addDissector(new ExtDiss()));

	//TEST_CHK (testExt.decode(&testXMLF, testpack));

	//N2DissTotal 

	TEST_CHK(true);*/



	GloTest::printResult();
	return GloTest::errors();
}

