//// test_N2VariablesManager.cpp: определяет точку входа для консольного приложения.
////

#include "../../Testing.h"
#include "N2Variable.h"
#include "N2Register.h"

/*
int main(int argc, _TCHAR* argv[])
{
    using namespace GloTest;
    TEST_INIT("N2Variables");

    N2Variablemaker maker;
    N2BaseVariable* pBase;
    N2BaseVariableTable* pTable = NULL;
    N2VariableINT* pI;
	
    //N2_VMT type = VMT_CACHE;


    TEST_CHK((pBase = maker.createSimplex(VAR_INT, "intVar1", 10)) != NULL);
    pI = (N2VariableINT*)pBase;
    for(int i=0; i<10; i++)
        TEST_CHK(pI->set(i, i));
    for(int i=0; i<10; i++)
        TEST_CHK(*pI->get(i) == i);
    for(int i=0; i<10; i++) {
        TEST_CHK(pI->getValue(i) == i);
        //cout << pI->getValue(i) << ", " ;
    }
    //maker

    TEST_CHK((pBase = maker.createSimplex(VAR_TERNAR, "iTern1", 10)) != NULL);
    N2VariableTO* ternarVar = (N2VariableTO*)pBase;
    TERNAR tern [10] = {TERNAR_YES, TERNAR_NO, TERNAR_DISABLE, \
                        TERNAR_YES, TERNAR_NO, TERNAR_DISABLE, \
                        TERNAR_YES, TERNAR_NO, TERNAR_DISABLE, \
                        TERNAR_YES };
    for(int i=0; i<ternarVar->dimension(); i++)
        TEST_CHK(ternarVar->set(tern[i], i));
    for(int i=0; i<ternarVar->dimension(); i++)
        TEST_CHK(*ternarVar->get(i) == tern[i]);
    for(int i=0; i<ternarVar->dimension(); i++) {
        TEST_CHK(ternarVar->getValue(i) == tern[i]);
        //cout << ternarVar->getValue(i) << ", " ;
    }

    TEST_CHK((pTable = (N2BaseVariableTable*)maker.createTable(VAR_INT, "iTable", 10, 5)) != NULL);
    N2VariableIntTABLE* intTab1 = (N2VariableIntTABLE*)pTable;
    int x = 0;
    for(int i=0; i<10; i++)
        for(int j=0; j<5; j++)
            TEST_CHK(intTab1->tbl.set(i, j, x++));
    for(int i=0; i<10; i++)
        for(int j=0; j<5; j++) {
            if(j == 0) cout << endl;
            cout << intTab1->tbl.get(i, j) << " ; ";
        }
    cout << endl;

    N2BaseVariableTable* pTemp = (N2BaseVariableTable*)pTable->clone();
    intTab1 = (N2VariableIntTABLE*)pTemp;
    for(int i=0; i<10; i++)
        for(int j=0; j<5; j++) {
            if(j == 0) cout << endl;
            cout << intTab1->tbl.get(i, j) << " ; ";
        }
    cout << endl;

    TEST_CHK(intTab1->tbl.fill(99));
    for(int i=0; i<10; i++)
        for(int j=0; j<5; j++) {
            if(j == 0) cout << endl;
            cout << intTab1->tbl.get(i, j) << " ; ";
        }
    cout << endl;



    GloTest::printResult();
    return GloTest::errors();
}
*/

int main()
{
    using namespace GloTest;
    TEST_INIT("N2VariableComplex");
    N2VariableCreator maker;


    //-------------------------------------------------------Проверка создания данных для польз. типа
    N2VariableINT* intVar1 = (N2VariableINT*)maker.createSimplex(VAR_INT, "intVar1");
    int iValue = 17;
    TEST_CHK(intVar1->set(iValue));
    TEST_CHK(*intVar1->get() == iValue);
    TEST_CHK(intVar1->getValue() == iValue);
    N2VariableINT* intVar2 = (N2VariableINT*)maker.createSimplex(VAR_INT, "intVar2",3);
    for(int i=0; i<3; i++) TEST_CHK(intVar2->set(i, i));
    for(int i=0; i<3; i++) TEST_CHK(*intVar2->get(i) == i);
    for(int i=0; i<3; i++) TEST_CHK(intVar2->getValue(i) == i);
    N2VariableTO* ternarVar = (N2VariableTO*)maker.createSimplex(VAR_TERNAR, "ternarVar", 10);
    TERNAR tern [10] = {TERNAR_YES, TERNAR_NO, TERNAR_DISABLE, \
                        TERNAR_YES, TERNAR_NO, TERNAR_DISABLE, \
                        TERNAR_YES, TERNAR_NO, TERNAR_DISABLE, \
                        TERNAR_YES };
    for(int i=0; i<ternarVar->dimension(); i++) TEST_CHK(ternarVar->set(tern[i], i));
    for(int i=0; i<ternarVar->dimension(); i++) TEST_CHK(*ternarVar->get(i) == tern[i]);
    for(int i=0; i<ternarVar->dimension(); i++) TEST_CHK(ternarVar->getValue(i) == tern[i]);
    N2VariableIntTABLE* intTab1 = (N2VariableIntTABLE*)maker.createTable(VAR_INT, "intTab1", 10, 5);
    int x = 0;
    for(int i=0; i<10; i++)
        for(int j=0; j<5; j++)
            TEST_CHK(intTab1->tbl.set(i, j, x++));
    x=0;
    for(int i=0; i<10; i++)
        for(int j=0; j<5; j++)
            TEST_CHK(intTab1->tbl.get(i, j) == x++);
    //-------------------------------------------------------Проверка создания данных для польз. типа


    //-------------------------------------------------------Проверка создания пользовательского типа
    //               Complex "uv"
    //                   / | \
    //                  /  |  \
    //                 /   |   \
    //          intVar1 intVar2 userVar
    //                          /  |  \
    //                         /   |   \
    //                        /    |    \
    //                 intVar1 ternarVar intTab1
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
    N2Register::self()->getMemoryAllocator()->releaseVar<N2BaseVariable>(intVar2, 1);
    N2Register::self()->getMemoryAllocator()->releaseVar<N2BaseVariable>(userVar, 1);
    N2VariableComplex *uVar;
    TEST_CHK((uVar = uv->clone()) != NULL);
    N2Register::self()->getMemoryAllocator()->releaseVar<N2BaseVariable>(uv, 1);
    //-------------------------------------------------------Проверка создания пользовательского типа


    //-------------------------------------------------------Проверка чтения и изменения данных польз. типа, удаление типа
    int offset = 37;
    TEST_CHK((value = uVar->getVar("intVar1", VAR_INT)) != NULL);
    TEST_CHK((value = uVar->getVar("intVar2", VAR_INT)) != NULL);
    for(int i=0; i<3; i++) TEST_CHK(*((N2VariableINT*)value)->get(i) == i);
    for(int i=0; i<3; i++) { int data = i+ offset; TEST_CHK(((N2VariableINT*)value)->set(data, i)); };
    for(int i=0; i<3; i++) TEST_CHK(((N2VariableINT*)value)->getValue(i) == i+offset);
    TEST_CHK((value = uVar->getVar("userVar", VAR_VMUSER)) != NULL);
    TEST_CHK(((N2VariableComplex*)value)->name() == "userVar");
    TEST_CHK((value = uVar->getVar("userVar.intVar1", VAR_INT)) != NULL);
    TEST_CHK(value->name() == "intVar1");
    TEST_CHK((value = uVar->getVar("userVar.intVar2", VAR_INT)) == NULL);
    TEST_CHK((value = uVar->getVar("userVar.ternarVar", VAR_TERNAR)) != NULL);
    ternarVar = (N2VariableTO*)value;
    TERNAR tern_2 [10] = {TERNAR_YES, TERNAR_YES, TERNAR_YES, \
                        TERNAR_NO, TERNAR_NO, TERNAR_NO, \
                        TERNAR_DISABLE, TERNAR_DISABLE, TERNAR_DISABLE, \
                        TERNAR_DISABLE };
    for(int i=0; i<ternarVar->dimension(); i++) TEST_CHK(ternarVar->set(tern_2[i], i));
    for(int i=0; i<ternarVar->dimension(); i++) TEST_CHK(*ternarVar->get(i) == tern_2[i]);
    for(int i=0; i<ternarVar->dimension(); i++) TEST_CHK(ternarVar->getValue(i) == tern_2[i]);
    TEST_CHK((value = uVar->getVar("userVar.intTab1", VAR_TABLE)) != NULL);
    intTab1 = (N2VariableIntTABLE*)value;
    x = 0;
    for(int i=0; i<10; i++)
        for(int j=0; j<5; j++)
            TEST_CHK(intTab1->tbl.get(i, j) == x++);
    N2Register::self()->getMemoryAllocator()->releaseVar<N2BaseVariable>(uVar, 1);
    //-------------------------------------------------------Проверка чтения и изменения данных польз. типа, удаление типа


    //-------------------------------------------------------Проверка операторов обычных типов
    int val1=10;
    N2VariableINT *var1 = (N2VariableINT*)maker.createSimplex(VAR_INT, "var1");
    TEST_CHK(var1->set(val1));
    int val2=2;
    N2VariableINT *var2 = (N2VariableINT*)maker.createSimplex(VAR_INT, "var2");
    TEST_CHK(var2->set(val2));




    GloTest::printResult();
    return GloTest::errors();
}
