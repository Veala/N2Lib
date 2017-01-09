// ModuleManager.cpp: определяет точку входа для консольного приложения.
//


#include "stdafx.h"
#include "../../../export/common/N2Module.h"
#include "../../../export/common/N2ModulesManager.h"
#include "../../../export/common/IControl.h"
#include "../../../export/common/N2ControlObject.h"
#include "../../Testing.h"

using namespace GloTest;

void printTable(const N2RoutingTable* tbl)
{
	
};



int _tmain(int argc, _TCHAR* argv[])
{
	N2Module* pMod = NULL;
	IControl* pControl = N2ControlObject::getControl();
	std_string er;
	TEST_CHK(pControl->loadProject(CT("lp.xprj"), er) != NULL);
	N2ModulesManager* pmm = pControl->getModulesManager();
	pmm->updateRoutingTable();
	N2RoutingTable* pTable = pmm->getRoutingTable();
	printTable(pTable);
	SIGN s1 = 0xFFFFFF;
	N2RouteLine* pInfo1 = pTable->getOnSign(s1);

	TEST_CHK((pMod = pmm->createModule(pInfo1)) != NULL);

	printResult();
	return 0;
}

