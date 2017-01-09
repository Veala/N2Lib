//
// source_code.cpp: 
//

//#include "stdafx.h"

#include "../../Testing.h"
#include "N2Commands.h"
//#include "../../../export/common/N2Register.h"
#include "N2Misc.h"

#define VALUE 0x321EDCBA

using namespace N2_Defines;

int _tmain(int argc, _TCHAR* argv[])
{	
	using namespace GloTest;
	TEST_INIT("Signature");

	//Signature testSign(VALUE);
	//TEST_CHK(testSign.value() == VALUE);
	//TEST_CHK(testSign.type() == TYPE_SIGN(VALUE));
	//TEST_CHK(testSign.subType() == SUBTYPE_SIGN(VALUE));
	//TEST_CHK(testSign.numberDevice() == 0xED); //NUMDEV_SIGN(VALUE));
	//TEST_CHK(testSign.command() == COMMAND_SIGN(VALUE));
	//TEST_CHK(testSign.classDevice() == (VALUE & N2_MASK_CLASS));
	//TEST_CHK(!testSign.isBroadcast());
	//Signature testSignBroad(0x321FFCBA);

	//TEST_CHK(testSignBroad.isBroadcast());
	//TEST_CHK(testSign.maskNumDevice() == (VALUE & (~N2_MASK_NUMDEV)));
	//TEST_CHK(testSign.maskCommand() == (VALUE & (~N2_MASK_COMMAND)));


	GloTest::printResult();
	return GloTest::errors();
}

