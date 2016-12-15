//// test_N2VariablesManager.cpp: определяет точку входа для консольного приложения.
////

#include "../../Testing.h"
#include "N2Variable.h"
#include "N2Register.h"

/**/
void f(N2BaseVariable* data) {
    cout << data->type() << endl;
    switch (data->type()) {
    case VAR_BOOL:
        cout << ((N2VariableBOOL*)data)->getValue(0) << endl;
        break;
    case VAR_INT:
        cout << ((N2VariableINT*)data)->getValue(0) << endl;
        break;
    case VAR_LONG:
        cout << ((N2VariableLONG*)data)->getValue(0) << endl;
        break;
    case VAR_FLOAT:
        cout << ((N2VariableFLOAT*)data)->getValue(0) << endl;
        break;
    case  VAR_STRING:
        cout << ((N2VariableSTR*)data)->getValue(0) << endl;
        break;
//    case  VAR_BOOLTABLE:
//        cout << ((N2VariableBoolTABLE*)data)->getValue(0,1) << endl;
//        break;
//    case  VAR_IntTABLE:
//        cout << ((N2VariableIntTABLE*)data)->getValue(0,1) << endl;
//        break;
//    case  VAR_LONGTABLE:
//        cout << ((N2VariableLongTABLE*)data)->getValue(0,1) << endl;
//        break;
//    case  VAR_FLOATTABLE:
//        cout << ((N2VariableFloatTABLE*)data)->getValue(0,1) << endl;
//        break;
//    case  VAR_STRINGTABLE:
//        cout << ((N2VariableStringTABLE*)data)->getValue(0,1) << endl;
//        break;
    case  VAR_VMUSER:
        cout << ((N2VariableComplex*)data)->name() << endl;
        break;
    }
}
/**/

//int main(int argc, _TCHAR* argv[])
//{
//	using namespace GloTest;
//	TEST_INIT("N2Variables");

//	N2Variablemaker maker;
//	N2BaseVariable* pBase;
//	N2BaseVariableTable* pTable = NULL;
//	N2VariableINT* pI;
	
//	//N2_VMT type = VMT_CACHE;


//	TEST_CHK((pBase = maker.createSimplex(VAR_INT, "intVar1", 10)) != NULL);
//	pI = (N2VariableINT*)pBase;
//	for(int i=0; i<10; i++)
//		TEST_CHK(pI->set(i, i));
//	for(int i=0; i<10; i++)
//		TEST_CHK(*pI->get(i) == i);
//	for(int i=0; i<10; i++) {
//		TEST_CHK(pI->getValue(i) == i);
//		//cout << pI->getValue(i) << ", " ;
//	}
//	//maker

//	TEST_CHK((pBase = maker.createSimplex(VAR_TERNAR, "iTern1", 10)) != NULL);
//	N2VariableTO* ternarVar = (N2VariableTO*)pBase;
//	TERNAR tern [10] = {TERNAR_YES, TERNAR_NO, TERNAR_DISABLE, \
//						TERNAR_YES, TERNAR_NO, TERNAR_DISABLE, \
//						TERNAR_YES, TERNAR_NO, TERNAR_DISABLE, \
//						TERNAR_YES };
//	for(int i=0; i<ternarVar->dimension(); i++)
//		TEST_CHK(ternarVar->set(tern[i], i));
//	for(int i=0; i<ternarVar->dimension(); i++)
//		TEST_CHK(*ternarVar->get(i) == tern[i]);
//	for(int i=0; i<ternarVar->dimension(); i++) {
//		TEST_CHK(ternarVar->getValue(i) == tern[i]);
//		//cout << ternarVar->getValue(i) << ", " ;
//	}

//	TEST_CHK((pTable = (N2BaseVariableTable*)maker.createTable(VAR_INT, "iTable", 10, 5)) != NULL);
//	N2VariableIntTABLE* intTab1 = (N2VariableIntTABLE*)pTable;
//	int x = 0;
//	for(int i=0; i<10; i++)
//		for(int j=0; j<5; j++)
//			TEST_CHK(intTab1->tbl.set(i, j, x++));
//	for(int i=0; i<10; i++)
//		for(int j=0; j<5; j++) {
//			if(j == 0) cout << endl;
//			cout << intTab1->tbl.get(i, j) << " ; ";
//		}
//	cout << endl;

//	N2BaseVariableTable* pTemp = (N2BaseVariableTable*)pTable->clone();
//	intTab1 = (N2VariableIntTABLE*)pTemp;
//	for(int i=0; i<10; i++)
//		for(int j=0; j<5; j++) {
//			if(j == 0) cout << endl;
//			cout << intTab1->tbl.get(i, j) << " ; ";
//		}
//	cout << endl;

//	TEST_CHK(intTab1->tbl.fill(99));
//	for(int i=0; i<10; i++)
//		for(int j=0; j<5; j++) {
//			if(j == 0) cout << endl;
//			cout << intTab1->tbl.get(i, j) << " ; ";
//		}
//	cout << endl;



//	GloTest::printResult();
//	return GloTest::errors();
//}

int main()
{
    using namespace GloTest;
    TEST_INIT("N2VariableComplex");
    N2VariableCreator maker;


    //----------------------- creating data ----------------

    N2VariableINT* intVar1 = (N2VariableINT*)maker.createSimplex(VAR_INT, "intVar1");
    int iValue = 17;
    intVar1->set(iValue);
    N2VariableINT* intVar2 = (N2VariableINT*)maker.createSimplex(VAR_INT, "intVar2",3);
    for(int i=0; i<3; i++) intVar2->set(i, i);
    N2VariableTO* ternarVar = (N2VariableTO*)maker.createSimplex(VAR_TERNAR, "ternarVar", 10);
    TERNAR tern [10] = {TERNAR_YES, TERNAR_NO, TERNAR_DISABLE, \
                        TERNAR_YES, TERNAR_NO, TERNAR_DISABLE, \
                        TERNAR_YES, TERNAR_NO, TERNAR_DISABLE, \
                        TERNAR_YES };
    for(int i=0; i<ternarVar->dimension(); i++)   ternarVar->set(tern[i], i);
    N2VariableIntTABLE* intTab1 = (N2VariableIntTABLE*)maker.createTable(VAR_INT, "intTab1", 10, 5);
    int x = 0;
    for(int i=0; i<10; i++)
        for(int j=0; j<5; j++)
            intTab1->tbl.set(i, j, x++);

    //----------------------- creating data ----------------


    N2VariableComplex *userVar;
    TEST_CHK((userVar = (N2VariableComplex*)maker.createComplex("userVar")) != NULL);

    TEST_CHK(userVar->addCopyVar(intVar1));
    TEST_CHK(userVar->addCopyVar(ternarVar));
    TEST_CHK(userVar->addCopyVar(intTab1));
    N2Register::self()->getMemoryAllocator()->releaseVar<N2BaseVariable>(intVar1, 1);
    N2Register::self()->getMemoryAllocator()->releaseVar<N2BaseVariable>(ternarVar, 1);
    N2Register::self()->getMemoryAllocator()->releaseVar<N2BaseVariable>(intTab1, 1);

    N2BaseVariable *value;
    TEST_CHK((value = userVar->getVar("intVar1", VAR_INT)) != NULL);
    N2VariableComplex *uv;
    TEST_CHK((uv = (N2VariableComplex*)maker.createComplex("uv")) != NULL);

    TEST_CHK(uv->addCopyVar(value));
    TEST_CHK(uv->addCopyVar(intVar2));
    TEST_CHK(uv->addCopyVar(userVar));
    N2Register::self()->getMemoryAllocator()->releaseVar<N2BaseVariable>(value, 1);
    N2Register::self()->getMemoryAllocator()->releaseVar<N2BaseVariable>(intVar2, 1);
    N2Register::self()->getMemoryAllocator()->releaseVar<N2BaseVariable>(userVar, 1);

    N2VariableComplex *uVar;
    TEST_CHK((uVar = uv->clone()) != NULL);

    N2Register::self()->getMemoryAllocator()->releaseVar<N2BaseVariable>(uv, 1);

    TEST_CHK((value = uVar->getVar("intVar1", VAR_INT)) != NULL);
    TEST_CHK((value = uVar->getVar("intVar2", VAR_INT)) != NULL);
    TEST_CHK((value = uVar->getVar("userVar", VAR_VMUSER)) != NULL);
    TEST_CHK((value = uVar->getVar("userVar.intVar1", VAR_INT)) != NULL);
    //TEST_CHK((value = uVar->getVar("userVar.intVar2", VAR_INT)) != NULL);
    TEST_CHK((value = uVar->getVar("userVar.ternarVar", VAR_TERNAR)) != NULL);
    TEST_CHK((value = uVar->getVar("userVar.intTab1", VAR_TABLE)) != NULL);


    N2Register::self()->getMemoryAllocator()->releaseVar<N2BaseVariable>(uVar, 1);

    GloTest::printResult();
    return GloTest::errors();
}
