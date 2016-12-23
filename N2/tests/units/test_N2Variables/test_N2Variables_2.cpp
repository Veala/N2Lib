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
    N2VariableTO* ternarVar1 = (N2VariableTO*)maker.createSimplex(VAR_TERNAR, "ternarVar1", 10);
    TERNAR tern [10] = {TERNAR_YES, TERNAR_NO, TERNAR_DISABLE, \
                        TERNAR_YES, TERNAR_NO, TERNAR_DISABLE, \
                        TERNAR_YES, TERNAR_NO, TERNAR_DISABLE, \
                        TERNAR_YES };
    for(int i=0; i<ternarVar1->dimension(); i++) TEST_CHK(ternarVar1->set(tern[i], i));
    for(int i=0; i<ternarVar1->dimension(); i++) TEST_CHK(*ternarVar1->get(i) == tern[i]);
    for(int i=0; i<ternarVar1->dimension(); i++) TEST_CHK(ternarVar1->getValue(i) == tern[i]);
    N2VariableIntTABLE* intTab1 = (N2VariableIntTABLE*)maker.createTable(VAR_INT, "intTab1", 10, 5);
    int x = 0;
    for(int i=0; i<10; i++)
        for(int j=0; j<5; j++)
            TEST_CHK(intTab1->tbl.set(i, j, x++));
    x=0;
    for(int i=0; i<10; i++)
        for(int j=0; j<5; j++)
            TEST_CHK(intTab1->tbl.get(i, j) == x++);


    //-------------------------------------------------------Проверка создания пользовательского типа
    //               Complex "uv"
    //                   / | \
    //                  /  |  \
    //                 /   |   \
    //          intVar1 intVar2 userVar
    //                          /  |  \
    //                         /   |   \
    //                        /    |    \
    //                 intVar1 ternarVar1 intTab1
    N2VariableComplex *userVar;
    TEST_CHK((userVar = (N2VariableComplex*)maker.createComplex("userVar")) != NULL);
    TEST_CHK(userVar->addCopyVar(intVar1));
    TEST_CHK(userVar->addCopyVar(ternarVar1));
    TEST_CHK(userVar->addCopyVar(intTab1));
    N2Register::self()->getMemoryAllocator()->releaseVar<N2BaseVariable>(intVar1, 1);
    N2Register::self()->getMemoryAllocator()->releaseVar<N2BaseVariable>(ternarVar1, 1);
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
    TEST_CHK((value = uVar->getVar("userVar.ternarVar1", VAR_TERNAR)) != NULL);
    ternarVar1 = (N2VariableTO*)value;
    TERNAR tern_2 [10] = {TERNAR_YES, TERNAR_YES, TERNAR_YES, \
                        TERNAR_NO, TERNAR_NO, TERNAR_NO, \
                        TERNAR_DISABLE, TERNAR_DISABLE, TERNAR_DISABLE, \
                        TERNAR_DISABLE };
    for(int i=0; i<ternarVar1->dimension(); i++) TEST_CHK(ternarVar1->set(tern_2[i], i));
    for(int i=0; i<ternarVar1->dimension(); i++) TEST_CHK(*ternarVar1->get(i) == tern_2[i]);
    for(int i=0; i<ternarVar1->dimension(); i++) TEST_CHK(ternarVar1->getValue(i) == tern_2[i]);
    TEST_CHK((value = uVar->getVar("userVar.intTab1", VAR_TABLE)) != NULL);
    intTab1 = (N2VariableIntTABLE*)value;
    x = 0;
    for(int i=0; i<10; i++)
        for(int j=0; j<5; j++)
            TEST_CHK(intTab1->tbl.get(i, j) == x++);
    N2Register::self()->getMemoryAllocator()->releaseVar<N2BaseVariable>(uVar, 1);


    //-------------------------------------------------------Проверка функционала обычных типов
    int iVal1=10; int iVal2=2;
    long lVal1=1000; long lVal2=200;
    float fVal1=100.5; float fVal2=20.5;
    string sVal1="An"; string sVal2="Bcr";
    bool bVal1=true; bool bVal2=false;

    intVar1 = (N2VariableINT*)maker.createSimplex(VAR_INT, "intVar1",3);
    intVar2 = (N2VariableINT*)maker.createSimplex(VAR_INT, "intVar2");
    N2VariableINT *intVar3 = (N2VariableINT*)maker.createSimplex(VAR_INT, "intVar3");
    for (int i=0;i<intVar1->dimension();i++)
        intVar1->set(iVal1,i);
    intVar2->set(iVal2);

    N2VariableLONG* longVar1 = (N2VariableLONG*)maker.createSimplex(VAR_LONG, "longVar1",3);
    N2VariableLONG* longVar2 = (N2VariableLONG*)maker.createSimplex(VAR_LONG, "longVar2");
    N2VariableLONG* longVar3 = (N2VariableLONG*)maker.createSimplex(VAR_LONG, "longVar3");
    longVar1->set(lVal1); longVar2->set(lVal2);

    N2VariableFLOAT* floatVar1 = (N2VariableFLOAT*)maker.createSimplex(VAR_FLOAT, "floatVar1",3);
    N2VariableFLOAT* floatVar2 = (N2VariableFLOAT*)maker.createSimplex(VAR_FLOAT, "floatVar2");
    N2VariableFLOAT* floatVar3 = (N2VariableFLOAT*)maker.createSimplex(VAR_FLOAT, "floatVar3");
    for (int i=0;i<floatVar1->dimension();i++)
        floatVar1->set(fVal1,i);
    floatVar2->set(fVal2);

    N2VariableSTR* strVar1 = (N2VariableSTR*)maker.createSimplex(VAR_STRING, "strVar1",3);
    N2VariableSTR* strVar2 = (N2VariableSTR*)maker.createSimplex(VAR_STRING, "strVar2");
    N2VariableSTR* strVar3 = (N2VariableSTR*)maker.createSimplex(VAR_STRING, "strVar3");
    for (int i=0;i<strVar1->dimension();i++)
        strVar1->set(sVal1);
    strVar2->set(sVal2);

    N2VariableBOOL* boolVar1 = (N2VariableBOOL*)maker.createSimplex(VAR_BOOL, "boolVar1",3);
    N2VariableBOOL* boolVar2 = (N2VariableBOOL*)maker.createSimplex(VAR_BOOL, "boolVar2");
    N2VariableBOOL* boolVar3 = (N2VariableBOOL*)maker.createSimplex(VAR_BOOL, "boolVar3");
    for (int i=0;i<boolVar1->dimension();i++)
        boolVar1->set(bVal1);
    boolVar2->set(bVal2);

    ternarVar1 = (N2VariableTO*)maker.createSimplex(VAR_TERNAR, "ternarVar1", 10);
    for(int i=0; i<ternarVar1->dimension(); i++) TEST_CHK(ternarVar1->set(tern[i], i));
    for(int i=0; i<ternarVar1->dimension(); i++) TEST_CHK(*ternarVar1->get(i) == tern[i]);
    for(int i=0; i<ternarVar1->dimension(); i++) TEST_CHK(ternarVar1->getValue(i) == tern[i]);
    N2VariableTO* ternarVar2 = (N2VariableTO*)maker.createSimplex(VAR_TERNAR, "ternarVar2", 10);
    for(int i=0; i<ternarVar2->dimension(); i++) TEST_CHK(ternarVar2->set(tern_2[i], i));
    for(int i=0; i<ternarVar2->dimension(); i++) TEST_CHK(*ternarVar2->get(i) == tern_2[i]);
    for(int i=0; i<ternarVar2->dimension(); i++) TEST_CHK(ternarVar2->getValue(i) == tern_2[i]);
    N2VariableTO* ternarVar3 = (N2VariableTO*)maker.createSimplex(VAR_TERNAR, "ternarVar3", 10);

    //-------------------clone
    N2VariableINT *ic= (N2VariableINT*)intVar1->clone();
    TEST_CHK(intVar1->dimension() == ic->dimension());
    for (int i=0;i<ic->dimension();i++)
        TEST_CHK(intVar1->getValue(i) == ic->getValue(i));
    TEST_CHK(intVar1->name() == ic->name());
    N2VariableLONG *lc= (N2VariableLONG*)longVar1->clone();
    TEST_CHK(longVar1->dimension() == lc->dimension());
    for (int i=0;i<lc->dimension();i++)
        TEST_CHK(longVar1->getValue(i) == lc->getValue(i));
    TEST_CHK(longVar1->name() == lc->name());
    N2VariableFLOAT *fc= (N2VariableFLOAT*)floatVar1->clone();
    TEST_CHK(floatVar1->dimension() == fc->dimension());
    for (int i=0;i<fc->dimension();i++)
        TEST_CHK(floatVar1->getValue(i) == fc->getValue(i));
    TEST_CHK(floatVar1->name() == fc->name());
    N2VariableSTR *sc= (N2VariableSTR*)strVar1->clone();
    TEST_CHK(strVar1->dimension() == sc->dimension());
    for (int i=0;i<sc->dimension();i++)
        TEST_CHK(strVar1->getValue(i) == sc->getValue(i));
    TEST_CHK(strVar1->name() == sc->name());
    N2VariableBOOL *bc= (N2VariableBOOL*)boolVar1->clone();
    TEST_CHK(boolVar1->dimension() == bc->dimension());
    for (int i=0;i<bc->dimension();i++)
        TEST_CHK(boolVar1->getValue(i) == bc->getValue(i));
    TEST_CHK(boolVar1->name() == bc->name());
    N2VariableTO *tc= (N2VariableTO*)ternarVar1->clone();
    TEST_CHK(ternarVar1->dimension() == tc->dimension());
    for (int i=0;i<tc->dimension();i++)
        TEST_CHK(ternarVar1->getValue(i) == tc->getValue(i));
    TEST_CHK(ternarVar1->name() == tc->name());
    N2Register::self()->getMemoryAllocator()->releaseVar<N2BaseVariable>(ic, 1);
    N2Register::self()->getMemoryAllocator()->releaseVar<N2BaseVariable>(lc, 1);
    N2Register::self()->getMemoryAllocator()->releaseVar<N2BaseVariable>(fc, 1);
    N2Register::self()->getMemoryAllocator()->releaseVar<N2BaseVariable>(sc, 1);
    N2Register::self()->getMemoryAllocator()->releaseVar<N2BaseVariable>(bc, 1);
    N2Register::self()->getMemoryAllocator()->releaseVar<N2BaseVariable>(tc, 1);

    //-------------------custom
    //int to type
    int idata = intVar1->custom(longVar1);
    TEST_CHK(idata == longVar1->getValue());
    idata = intVar1->custom(floatVar1);
    TEST_CHK(idata == (int)floatVar1->getValue());
    idata = intVar1->custom(boolVar1);
    TEST_CHK(idata == boolVar1->getValue() ? 1:0);
    idata = intVar1->custom(strVar1);
    int idata2 = intVar1->custom(strVar1);
    TEST_CHK(idata == idata2);
    idata = intVar1->custom(ternarVar1);
    TEST_CHK(idata == (int)ternarVar1->get());
    //float to type
    float fdata = floatVar1->custom(longVar1);
    TEST_CHK(fdata == longVar1->getValue());
    fdata = floatVar1->custom(intVar1);
    TEST_CHK(fdata == intVar1->getValue());
    fdata = floatVar1->custom(boolVar1);
    TEST_CHK(fdata == boolVar1->getValue() ? 1:0);
    fdata = floatVar1->custom(strVar1);
    float fdata2 = floatVar1->custom(strVar1);
    TEST_CHK(fdata == fdata2);
    fdata = floatVar1->custom(ternarVar1);
    TEST_CHK(fdata == 0.0);
    //long to type
    long ldata = longVar1->custom(floatVar1);
    TEST_CHK(ldata == (long)floatVar1->getValue());
    ldata = longVar1->custom(intVar1);
    TEST_CHK(ldata == intVar1->getValue());
    ldata = longVar1->custom(boolVar1);
    TEST_CHK(ldata == boolVar1->getValue() ? 1:0);
    ldata = longVar1->custom(strVar1);
    long ldata2 = longVar1->custom(strVar1);
    TEST_CHK(ldata == ldata2);
    ldata = longVar1->custom(ternarVar1);
    TEST_CHK(ldata == (long)ternarVar1->get());
    //string to type ?????
    string sdata = strVar1->custom(floatVar1);
    string sdata2 = strVar1->custom(floatVar1);
    TEST_CHK(sdata == sdata2);
    sdata = strVar1->custom(intVar1);
    sdata2 = strVar1->custom(intVar1);
    TEST_CHK(sdata == sdata2);
    sdata = strVar1->custom(boolVar1);
    sdata2 = strVar1->custom(boolVar1);
    TEST_CHK(sdata == sdata2);
    sdata = strVar1->custom(longVar1);
    sdata2 = strVar1->custom(longVar1);
    TEST_CHK(sdata == sdata2);
    sdata = strVar1->custom(ternarVar1);
    sdata2 = strVar1->custom(ternarVar1);
    TEST_CHK(sdata == sdata2);
    //bool to type ?????
    bool bdata = boolVar1->custom(floatVar1);
    bool bdata2 = boolVar1->custom(floatVar1);
    TEST_CHK(bdata == bdata2);
    bdata = boolVar1->custom(intVar1);
    bdata2 = boolVar1->custom(intVar1);
    TEST_CHK(bdata == bdata2);
    bdata = boolVar1->custom(strVar1);
    bdata2 = boolVar1->custom(strVar1);
    TEST_CHK(bdata == bdata2);
    bdata = boolVar1->custom(longVar1);
    bdata2 = boolVar1->custom(longVar1);
    TEST_CHK(bdata == bdata2);
    bdata = boolVar1->custom(ternarVar1);
    bdata2 = boolVar1->custom(ternarVar1);
    TEST_CHK(bdata == bdata2);
    //ternar to type ?????
    TERNAR tdata = ternarVar1->custom(floatVar1);
    TERNAR tdata2 = ternarVar1->custom(floatVar1);
    TEST_CHK(tdata == tdata2);
    tdata = ternarVar1->custom(intVar1);
    tdata2 = ternarVar1->custom(intVar1);
    TEST_CHK(tdata == tdata2);
    tdata = ternarVar1->custom(strVar1);
    tdata2 = ternarVar1->custom(strVar1);
    TEST_CHK(tdata == tdata2);
    tdata = ternarVar1->custom(longVar1);
    tdata2 = ternarVar1->custom(longVar1);
    TEST_CHK(tdata == tdata2);
    tdata = ternarVar1->custom(boolVar1);
    tdata2 = ternarVar1->custom(boolVar1);
    TEST_CHK(tdata == tdata2);

    //-------------------operator []
    for (int i=0;i<intVar1->dimension();i++)        TEST_CHK((*intVar1)[i] == intVar1->getValue(i));
    for (int i=0;i<longVar1->dimension();i++)       TEST_CHK((*longVar1)[i] == longVar1->getValue(i));
    for (int i=0;i<floatVar1->dimension();i++)      TEST_CHK((*floatVar1)[i] == floatVar1->getValue(i));
    for (int i=0;i<strVar1->dimension();i++)        TEST_CHK((*strVar1)[i] == strVar1->getValue(i));
    for (int i=0;i<boolVar1->dimension();i++)       TEST_CHK((*boolVar1)[i] == boolVar1->getValue(i));
    for (int i=0;i<ternarVar1->dimension();i++)     TEST_CHK((*ternarVar1)[i] == ternarVar1->getValue(i));

    //-------------------compare
    TEST_CHK(!intVar1->compare(N2COMPARE_EQU, intVar2));
    TEST_CHK(!longVar1->compare(N2COMPARE_EQU, longVar2));
    TEST_CHK(!floatVar1->compare(N2COMPARE_EQU, floatVar2));
    TEST_CHK(!boolVar1->compare(N2COMPARE_EQU, boolVar2));
    TEST_CHK(!strVar1->compare(N2COMPARE_EQU, strVar2));
    TEST_CHK(ternarVar1->compare(N2COMPARE_EQU, ternarVar2));
    TEST_CHK(intVar1->compare(N2COMPARE_GR, intVar2));
    TEST_CHK(longVar1->compare(N2COMPARE_GR, longVar2));
    TEST_CHK(floatVar1->compare(N2COMPARE_GR, floatVar2));
    TEST_CHK(boolVar1->compare(N2COMPARE_GR, boolVar2));
    TEST_CHK(!strVar1->compare(N2COMPARE_GR, strVar2));
    TEST_CHK(!ternarVar1->compare(N2COMPARE_GR, ternarVar2));
    TEST_CHK(!intVar1->compare(N2COMPARE_LS, intVar2));
    TEST_CHK(!longVar1->compare(N2COMPARE_LS, longVar2));
    TEST_CHK(!floatVar1->compare(N2COMPARE_LS, floatVar2));
    TEST_CHK(!boolVar1->compare(N2COMPARE_LS, boolVar2));
    TEST_CHK(strVar1->compare(N2COMPARE_LS, strVar2));
    TEST_CHK(!ternarVar1->compare(N2COMPARE_LS, ternarVar2));
    TEST_CHK(intVar1->compare(N2COMPARE_GREQ, intVar2));
    TEST_CHK(longVar1->compare(N2COMPARE_GREQ, longVar2));
    TEST_CHK(floatVar1->compare(N2COMPARE_GREQ, floatVar2));
    TEST_CHK(boolVar1->compare(N2COMPARE_GREQ, boolVar2));
    TEST_CHK(!strVar1->compare(N2COMPARE_GREQ, strVar2));
    TEST_CHK(ternarVar1->compare(N2COMPARE_GREQ, ternarVar2));
    TEST_CHK(!intVar1->compare(N2COMPARE_LSEQ, intVar2));
    TEST_CHK(!longVar1->compare(N2COMPARE_LSEQ, longVar2));
    TEST_CHK(!floatVar1->compare(N2COMPARE_LSEQ, floatVar2));
    TEST_CHK(!boolVar1->compare(N2COMPARE_LSEQ, boolVar2));
    TEST_CHK(strVar1->compare(N2COMPARE_LSEQ, strVar2));
    TEST_CHK(ternarVar1->compare(N2COMPARE_LSEQ, ternarVar2));
    TEST_CHK(intVar1->compare(N2COMPARE_NEQ, intVar2));
    TEST_CHK(longVar1->compare(N2COMPARE_NEQ, longVar2));
    TEST_CHK(floatVar1->compare(N2COMPARE_NEQ, floatVar2));
    TEST_CHK(boolVar1->compare(N2COMPARE_NEQ, boolVar2));
    TEST_CHK(strVar1->compare(N2COMPARE_NEQ, strVar2));
    TEST_CHK(!ternarVar1->compare(N2COMPARE_NEQ, ternarVar2));


    //-------------------------------------------------------Проверка функционала табличных типов
    intTab1 = (N2VariableIntTABLE*)maker.createTable(VAR_INT, "intTab1", 10, 5);
    int ix = 0;
    for(int i=0; i<10; i++)
        for(int j=0; j<5; j++)
            TEST_CHK(intTab1->tbl.set(i, j, ix++));
    N2VariableLongTABLE* longTab1 = (N2VariableLongTABLE*)maker.createTable(VAR_LONG, "longTab1", 10, 5);
    long lx = 0;
    for(int i=0; i<10; i++)
        for(int j=0; j<5; j++)
            TEST_CHK(longTab1->tbl.set(i, j, lx++));
    N2VariableFloatTABLE* floatTab1 = (N2VariableFloatTABLE*)maker.createTable(VAR_FLOAT, "floatTab1", 10, 5);
    float fx = 0.1;
    for(int i=0; i<10; i++)
        for(int j=0; j<5; j++)
            TEST_CHK(floatTab1->tbl.set(i, j, fx++));
    N2VariableStringTABLE* strTab1 = (N2VariableStringTABLE*)maker.createTable(VAR_STRING, "strTab1", 10, 5);
    string sx = "DataX";
    for(int i=0; i<10; i++)
        for(int j=0; j<5; j++)
            TEST_CHK(strTab1->tbl.set(i, j, sx));
    N2VariableBoolTABLE* boolTab1 = (N2VariableBoolTABLE*)maker.createTable(VAR_BOOL, "boolTab1", 10, 5);
    bool bx = true;
    for(int i=0; i<10; i++)
        for(int j=0; j<5; j++) {
            bx=!bx;
            TEST_CHK(boolTab1->tbl.set(i, j, bx));
        }
    N2VariableTernarTABLE* ternarTab1 = (N2VariableTernarTABLE*)maker.createTable(VAR_TERNAR, "ternarTab1", 10, 5);
    for(int i=0; i<10; i++)
        for(int j=0; j<5; j++)
            TEST_CHK(ternarTab1->tbl.set(i, j, tern[0]));

    //-------------------clone
    N2VariableIntTABLE* itc = (N2VariableIntTABLE*)intTab1->clone();
    TEST_CHK(intTab1->name() == itc->name());
    for(int i=0; i<10; i++)
        for(int j=0; j<5; j++)
            TEST_CHK(intTab1->tbl.get(i, j) == itc->tbl.get(i,j));
    N2VariableLongTABLE* ltc = (N2VariableLongTABLE*)longTab1->clone();
    TEST_CHK(longTab1->name() == ltc->name());
    for(int i=0; i<10; i++)
        for(int j=0; j<5; j++)
            TEST_CHK(longTab1->tbl.get(i, j) == ltc->tbl.get(i,j));
    N2VariableFloatTABLE* ftc = (N2VariableFloatTABLE*)floatTab1->clone();
    TEST_CHK(floatTab1->name() == ftc->name());
    for(int i=0; i<10; i++)
        for(int j=0; j<5; j++)
            TEST_CHK(floatTab1->tbl.get(i, j) == ftc->tbl.get(i,j));
    N2VariableBoolTABLE* btc = (N2VariableBoolTABLE*)boolTab1->clone();
    TEST_CHK(boolTab1->name() == btc->name());
    for(int i=0; i<10; i++)
        for(int j=0; j<5; j++)
            TEST_CHK(boolTab1->tbl.get(i, j) == btc->tbl.get(i,j));
    N2VariableStringTABLE* stc = (N2VariableStringTABLE*)strTab1->clone();
    TEST_CHK(strTab1->name() == stc->name());
    for(int i=0; i<10; i++)
        for(int j=0; j<5; j++)
            TEST_CHK(strTab1->tbl.get(i, j) == stc->tbl.get(i,j));
    N2VariableTernarTABLE* ttc = (N2VariableTernarTABLE*)ternarTab1->clone();
    TEST_CHK(ternarTab1->name() == ttc->name());
    for(int i=0; i<10; i++)
        for(int j=0; j<5; j++)
            TEST_CHK(ternarTab1->tbl.get(i, j) == ttc->tbl.get(i,j));
    N2Register::self()->getMemoryAllocator()->releaseVar<N2BaseVariable>(itc, 1);
    N2Register::self()->getMemoryAllocator()->releaseVar<N2BaseVariable>(ltc, 1);
    N2Register::self()->getMemoryAllocator()->releaseVar<N2BaseVariable>(ftc, 1);
    N2Register::self()->getMemoryAllocator()->releaseVar<N2BaseVariable>(stc, 1);
    N2Register::self()->getMemoryAllocator()->releaseVar<N2BaseVariable>(btc, 1);
    N2Register::self()->getMemoryAllocator()->releaseVar<N2BaseVariable>(ttc, 1);

    //-------------------fill
    TEST_CHK(intTab1->fill(intVar2));
    for(int i=0; i<10; i++)
        for(int j=0; j<5; j++)
            TEST_CHK(intTab1->tbl.get(i, j) == intVar2->getValue());
    TEST_CHK(longTab1->fill(longVar2));
    for(int i=0; i<10; i++)
        for(int j=0; j<5; j++)
            TEST_CHK(longTab1->tbl.get(i, j) == longVar2->getValue());
    TEST_CHK(floatTab1->fill(floatVar2));
    for(int i=0; i<10; i++)
        for(int j=0; j<5; j++)
            TEST_CHK(floatTab1->tbl.get(i, j) == floatVar2->getValue());
    TEST_CHK(strTab1->fill(strVar2));
    for(int i=0; i<10; i++)
        for(int j=0; j<5; j++)
            TEST_CHK(strTab1->tbl.get(i, j) == strVar2->getValue());
    TEST_CHK(boolTab1->fill(boolVar2));
    for(int i=0; i<10; i++)
        for(int j=0; j<5; j++)
            TEST_CHK(boolTab1->tbl.get(i, j) == boolVar2->getValue());
    TEST_CHK(ternarTab1->fill(ternarVar2));
    for(int i=0; i<10; i++)
        for(int j=0; j<5; j++)
            TEST_CHK(ternarTab1->tbl.get(i, j) == ternarVar2->getValue());

    //-------------------Move Variable to Cell
    TEST_CHK(intTab1->moveVariableToCell(0,0,intVar1));
    TEST_CHK(intTab1->tbl.get(0,0) == intVar1->getValue());
    TEST_CHK(longTab1->moveVariableToCell(0,0,longVar1));
    TEST_CHK(longTab1->tbl.get(0,0) == longVar1->getValue());
    TEST_CHK(floatTab1->moveVariableToCell(0,0,floatVar1));
    TEST_CHK(floatTab1->tbl.get(0,0) == floatVar1->getValue());
    TEST_CHK(boolTab1->moveVariableToCell(0,0,boolVar1));
    TEST_CHK(boolTab1->tbl.get(0,0) == boolVar1->getValue());
    TEST_CHK(strTab1->moveVariableToCell(0,0,strVar1));
    TEST_CHK(strTab1->tbl.get(0,0) == strVar1->getValue());
    TEST_CHK(ternarTab1->moveVariableToCell(0,0,ternarVar1));
    TEST_CHK(ternarTab1->tbl.get(0,0) == ternarVar1->getValue());

    //-------------------Move Cell to Variable
    TEST_CHK(intTab1->moveCellToVariable(0,0,intVar3));
    TEST_CHK(intTab1->tbl.get(0,0) == intVar3->getValue());
    TEST_CHK(longTab1->moveCellToVariable(0,0,longVar3));
    TEST_CHK(longTab1->tbl.get(0,0) == longVar3->getValue());
    TEST_CHK(floatTab1->moveCellToVariable(0,0,floatVar3));
    TEST_CHK(floatTab1->tbl.get(0,0) == floatVar3->getValue());
    TEST_CHK(boolTab1->moveCellToVariable(0,0,boolVar3));
    TEST_CHK(boolTab1->tbl.get(0,0) == boolVar3->getValue());
    TEST_CHK(strTab1->moveCellToVariable(0,0,strVar3));
    TEST_CHK(strTab1->tbl.get(0,0) == strVar3->getValue());
    TEST_CHK(ternarTab1->moveCellToVariable(0,0,ternarVar3));
    TEST_CHK(ternarTab1->tbl.get(0,0) == ternarVar3->getValue());

    N2Register::self()->getMemoryAllocator()->releaseVar<N2BaseVariable>(intTab1, 1);
    N2Register::self()->getMemoryAllocator()->releaseVar<N2BaseVariable>(longTab1, 1);
    N2Register::self()->getMemoryAllocator()->releaseVar<N2BaseVariable>(floatTab1, 1);
    N2Register::self()->getMemoryAllocator()->releaseVar<N2BaseVariable>(strTab1, 1);
    N2Register::self()->getMemoryAllocator()->releaseVar<N2BaseVariable>(boolTab1, 1);
    N2Register::self()->getMemoryAllocator()->releaseVar<N2BaseVariable>(ternarTab1, 1);


    //-------------------------------------------------------Проверка операторов обычных типов

    //-------------------BAD OPERAND TYPE
    intVar1->set(iVal1); intVar2->set(iVal2);
    longVar1->set(lVal1); longVar2->set(lVal2);
    floatVar1->set(fVal1); floatVar2->set(fVal2);
    strVar1->set(sVal1); strVar2->set(sVal2);
    boolVar1->set(bVal1); boolVar2->set(bVal2);
    for(int i=0; i<ternarVar1->dimension(); i++) ternarVar1->set(tern[i], i);
    for(int i=0; i<ternarVar2->dimension(); i++) ternarVar2->set(tern_2[i], i);
    TEST_CHK(intVar1->operation(N2OC_DEC,NULL,floatVar3) == N2EC_BAD_OPERAND_TYPE);
    TEST_CHK(floatVar1->operation(N2OC_INC,NULL,longVar3) == N2EC_BAD_OPERAND_TYPE);
    TEST_CHK(longVar1->operation(N2OC_DEC,NULL,boolVar3) == N2EC_BAD_OPERAND_TYPE);
    TEST_CHK(strVar1->operation(N2OC_INC,NULL,ternarVar3) == N2EC_BAD_OPERAND_TYPE);
    TEST_CHK(boolVar1->operation(N2OC_DEC,NULL,intVar3) == N2EC_BAD_OPERAND_TYPE);
    TEST_CHK(ternarVar1->operation(N2OC_INC,NULL,strVar3) == N2EC_BAD_OPERAND_TYPE);

    //-------------------NULL OPERAND
    TEST_CHK(intVar1->operation(N2OC_PLUS,NULL,intVar3) == N2EC_NULL_OPERAND);
    TEST_CHK(floatVar1->operation(N2OC_PLUS,NULL,floatVar3) == N2EC_NULL_OPERAND);
    TEST_CHK(longVar1->operation(N2OC_PLUS,NULL,longVar3) == N2EC_NULL_OPERAND);
    TEST_CHK(strVar1->operation(N2OC_PLUS,NULL,strVar3) == N2EC_NULL_OPERAND);
    TEST_CHK(boolVar1->operation(N2OC_PLUS,NULL,boolVar3) == N2EC_NULL_OPERAND);
    TEST_CHK(ternarVar1->operation(N2OC_PLUS,NULL,ternarVar3) == N2EC_NULL_OPERAND);

    //-------------------DECREMENT
    TEST_CHK(intVar1->operation(N2OC_DEC,NULL,intVar3) == N2EC_SUCCESS);
    TEST_CHK(intVar1->getValue() != intVar3->getValue());
    TEST_CHK(intVar1->operation(N2OC_DEC,NULL,NULL) == N2EC_SUCCESS);
    TEST_CHK(intVar1->getValue() == intVar3->getValue());
    TEST_CHK(floatVar1->operation(N2OC_DEC,NULL,floatVar3) == N2EC_INAPPLICABLE_CODE);
//    TEST_CHK(floatVar1->getValue() != floatVar3->getValue());
//    TEST_CHK(floatVar1->operation(N2OC_DEC,NULL,NULL) == N2EC_SUCCESS);
//    TEST_CHK(floatVar1->getValue() == floatVar3->getValue());
    TEST_CHK(longVar1->operation(N2OC_DEC,NULL,longVar3) == N2EC_SUCCESS);
    TEST_CHK(longVar1->getValue() != longVar3->getValue());
    TEST_CHK(longVar1->operation(N2OC_DEC,NULL,NULL) == N2EC_SUCCESS);
    TEST_CHK(longVar1->getValue() == longVar3->getValue());
    TEST_CHK(strVar1->operation(N2OC_DEC,strVar2,strVar3) == N2EC_INAPPLICABLE_CODE);
    TEST_CHK(boolVar1->operation(N2OC_DEC,NULL,boolVar3) == N2EC_INAPPLICABLE_CODE);
//    TEST_CHK(boolVar1->getValue() != boolVar3->getValue());
//    TEST_CHK(boolVar1->operation(N2OC_DEC,NULL,NULL) == N2EC_SUCCESS);
//    TEST_CHK(boolVar1->getValue() != boolVar3->getValue());
    TEST_CHK(ternarVar1->operation(N2OC_DEC,NULL,NULL) == N2EC_INAPPLICABLE_CODE);

    //-------------------INCREMENT
    TEST_CHK(intVar1->operation(N2OC_INC,NULL,intVar3) == N2EC_SUCCESS);
    TEST_CHK(intVar1->getValue() != intVar3->getValue());
    TEST_CHK(intVar1->operation(N2OC_INC,NULL,NULL) == N2EC_SUCCESS);
    TEST_CHK(intVar1->getValue() == intVar3->getValue());
    TEST_CHK(floatVar1->operation(N2OC_INC,NULL,floatVar3) == N2EC_INAPPLICABLE_CODE);
//    TEST_CHK(floatVar1->getValue() != floatVar3->getValue());
//    TEST_CHK(floatVar1->operation(N2OC_INC,NULL,NULL) == N2EC_SUCCESS);
//    TEST_CHK(floatVar1->getValue() == floatVar3->getValue());
    TEST_CHK(longVar1->operation(N2OC_INC,NULL,longVar3) == N2EC_SUCCESS);
    TEST_CHK(longVar1->getValue() != longVar3->getValue());
    TEST_CHK(longVar1->operation(N2OC_INC,NULL,NULL) == N2EC_SUCCESS);
    TEST_CHK(longVar1->getValue() == longVar3->getValue());
    TEST_CHK(strVar1->operation(N2OC_INC,strVar2,strVar3) == N2EC_INAPPLICABLE_CODE);
    TEST_CHK(boolVar1->operation(N2OC_INC,NULL,boolVar3) == N2EC_INAPPLICABLE_CODE);
//    TEST_CHK(boolVar1->getValue() != boolVar3->getValue());
//    TEST_CHK(boolVar1->operation(N2OC_INC,NULL,NULL) == N2EC_SUCCESS);
//    TEST_CHK(boolVar1->getValue() != boolVar3->getValue());
    TEST_CHK(ternarVar1->operation(N2OC_INC,NULL,NULL) == N2EC_INAPPLICABLE_CODE);

    //-------------------LOG10
    intVar1->set(iVal1); intVar2->set(iVal2);
    longVar1->set(lVal1); longVar2->set(lVal2);
    floatVar1->set(fVal1); floatVar2->set(fVal2);
    strVar1->set(sVal1); strVar2->set(sVal2);
    boolVar1->set(bVal1); boolVar2->set(bVal2);
    for(int i=0; i<ternarVar1->dimension(); i++) ternarVar1->set(tern[i], i);
    for(int i=0; i<ternarVar2->dimension(); i++) ternarVar2->set(tern_2[i], i);
    TEST_CHK(intVar1->operation(N2OC_LOG_10,NULL,intVar3) == N2EC_SUCCESS);
    TEST_CHK(intVar1->getValue() != intVar3->getValue());
    TEST_CHK(intVar1->operation(N2OC_LOG_10,NULL,NULL) == N2EC_SUCCESS);
    TEST_CHK(intVar1->getValue() == intVar3->getValue());
    TEST_CHK(floatVar1->operation(N2OC_LOG_10,NULL,floatVar3) == N2EC_SUCCESS);
    TEST_CHK(floatVar1->getValue() != floatVar3->getValue());
    TEST_CHK(floatVar1->operation(N2OC_LOG_10,NULL,NULL) == N2EC_SUCCESS);
    TEST_CHK(floatVar1->getValue() == floatVar3->getValue());
    TEST_CHK(longVar1->operation(N2OC_LOG_10,NULL,longVar3) == N2EC_SUCCESS);
    TEST_CHK(longVar1->getValue() != longVar3->getValue());
    TEST_CHK(longVar1->operation(N2OC_LOG_10,NULL,NULL) == N2EC_SUCCESS);
    TEST_CHK(longVar1->getValue() == longVar3->getValue());
    TEST_CHK(strVar1->operation(N2OC_LOG_10,strVar2,strVar3) == N2EC_INAPPLICABLE_CODE);
    TEST_CHK(boolVar1->operation(N2OC_LOG_10,NULL,boolVar3) == N2EC_INAPPLICABLE_CODE);
//    TEST_CHK(boolVar1->getValue() != boolVar3->getValue());
//    TEST_CHK(boolVar1->operation(N2OC_LOG_10,NULL,NULL) == N2EC_SUCCESS);
//    TEST_CHK(boolVar1->getValue() != boolVar3->getValue());
    TEST_CHK(ternarVar1->operation(N2OC_LOG_10,NULL,NULL) == N2EC_INAPPLICABLE_CODE);

    //-------------------LOG
    intVar1->set(iVal1); intVar2->set(iVal2);
    longVar1->set(lVal1); longVar2->set(lVal2);
    floatVar1->set(fVal1); floatVar2->set(fVal2);
    strVar1->set(sVal1); strVar2->set(sVal2);
    boolVar1->set(bVal1); boolVar2->set(bVal2);
    for(int i=0; i<ternarVar1->dimension(); i++) ternarVar1->set(tern[i], i);
    for(int i=0; i<ternarVar2->dimension(); i++) ternarVar2->set(tern_2[i], i);
    TEST_CHK(intVar1->operation(N2OC_LOG,NULL,intVar3) == N2EC_SUCCESS);
    TEST_CHK(intVar1->getValue() != intVar3->getValue());
    TEST_CHK(intVar1->operation(N2OC_LOG,NULL,NULL) == N2EC_SUCCESS);
    TEST_CHK(intVar1->getValue() == intVar3->getValue());
    TEST_CHK(floatVar1->operation(N2OC_LOG,NULL,floatVar3) == N2EC_SUCCESS);
    TEST_CHK(floatVar1->getValue() != floatVar3->getValue());
    TEST_CHK(floatVar1->operation(N2OC_LOG,NULL,NULL) == N2EC_SUCCESS);
    TEST_CHK(floatVar1->getValue() == floatVar3->getValue());
    TEST_CHK(longVar1->operation(N2OC_LOG,NULL,longVar3) == N2EC_SUCCESS);
    TEST_CHK(longVar1->getValue() != longVar3->getValue());
    TEST_CHK(longVar1->operation(N2OC_LOG,NULL,NULL) == N2EC_SUCCESS);
    TEST_CHK(longVar1->getValue() == longVar3->getValue());
    TEST_CHK(strVar1->operation(N2OC_LOG,strVar2,strVar3) == N2EC_INAPPLICABLE_CODE);
    TEST_CHK(boolVar1->operation(N2OC_LOG,NULL,boolVar3) == N2EC_INAPPLICABLE_CODE);
//    TEST_CHK(boolVar1->getValue() != boolVar3->getValue());
//    TEST_CHK(boolVar1->operation(N2OC_LOG,NULL,NULL) == N2EC_SUCCESS);
//    TEST_CHK(boolVar1->getValue() != boolVar3->getValue());
    TEST_CHK(ternarVar1->operation(N2OC_LOG,NULL,NULL) == N2EC_INAPPLICABLE_CODE);

    //-------------------NOT
    TEST_CHK(intVar1->operation(N2OC_NOT,NULL,intVar3) == N2EC_SUCCESS);
    TEST_CHK(intVar1->getValue() != intVar3->getValue());
    TEST_CHK(intVar1->operation(N2OC_NOT,NULL,NULL) == N2EC_SUCCESS);
    TEST_CHK(intVar1->getValue() == intVar3->getValue());
    TEST_CHK(floatVar1->operation(N2OC_NOT,floatVar2,floatVar3) == N2EC_INAPPLICABLE_CODE);
//    TEST_CHK(floatVar1->getValue() != floatVar3->getValue());
//    TEST_CHK(floatVar1->operation(N2OC_NOT,NULL,NULL) == N2EC_SUCCESS);
//    TEST_CHK(floatVar1->getValue() == floatVar3->getValue());
    TEST_CHK(longVar1->operation(N2OC_NOT,NULL,longVar3) == N2EC_SUCCESS);
    TEST_CHK(longVar1->getValue() != longVar3->getValue());
    TEST_CHK(longVar1->operation(N2OC_NOT,NULL,NULL) == N2EC_SUCCESS);
    TEST_CHK(longVar1->getValue() == longVar3->getValue());
    TEST_CHK(strVar1->operation(N2OC_NOT,strVar2,strVar3) == N2EC_INAPPLICABLE_CODE);
    TEST_CHK(boolVar1->operation(N2OC_NOT,NULL,boolVar3) == N2EC_SUCCESS);
//    TEST_CHK(boolVar1->getValue() != boolVar3->getValue());
//    TEST_CHK(boolVar1->operation(N2OC_LOG,NULL,NULL) == N2EC_SUCCESS);
//    TEST_CHK(boolVar1->getValue() != boolVar3->getValue());
    TEST_CHK(ternarVar1->operation(N2OC_NOT,ternarVar2,NULL) == N2EC_INAPPLICABLE_CODE);

    //-------------------INIT
    TEST_CHK(intVar1->operation(N2OC_INIT,intVar2,intVar3) == N2EC_SUCCESS);
    TEST_CHK(intVar2->getValue() == intVar3->getValue());
    TEST_CHK(floatVar1->operation(N2OC_INIT,floatVar2,floatVar3) == N2EC_SUCCESS);
    TEST_CHK(floatVar2->getValue() == floatVar3->getValue());
//    TEST_CHK(floatVar1->operation(N2OC_INIT,NULL,NULL) == N2EC_SUCCESS);
//    TEST_CHK(floatVar1->getValue() == floatVar3->getValue());
    TEST_CHK(longVar1->operation(N2OC_INIT,longVar2,longVar3) == N2EC_SUCCESS);
    TEST_CHK(longVar2->getValue() == longVar3->getValue());
    TEST_CHK(strVar1->operation(N2OC_INIT,strVar2,strVar3) == N2EC_SUCCESS);
    TEST_CHK(strVar2->getValue() == strVar3->getValue());
    TEST_CHK(boolVar1->operation(N2OC_INIT,boolVar2,boolVar3) == N2EC_SUCCESS);
    TEST_CHK(boolVar2->getValue() == boolVar3->getValue());
    TEST_CHK(ternarVar1->operation(N2OC_INIT,ternarVar2,ternarVar3) == N2EC_SUCCESS);
    TEST_CHK(ternarVar2->getValue() == ternarVar3->getValue());

    //-------------------PLUS, MINUS: (Var2==Var3) ===> (Var1==Var3)
    TEST_CHK(intVar1->operation(N2OC_PLUS,intVar2,intVar3) == N2EC_SUCCESS);
    TEST_CHK(intVar3->operation(N2OC_MINUS,intVar2,NULL) == N2EC_SUCCESS);
    TEST_CHK(intVar1->getValue() == intVar3->getValue());
    floatVar1->set(fVal1);
    TEST_CHK(floatVar1->operation(N2OC_PLUS,floatVar2,floatVar3) == N2EC_SUCCESS);
    TEST_CHK(floatVar3->operation(N2OC_MINUS,floatVar2,NULL) == N2EC_SUCCESS);
    TEST_CHK(floatVar1->getValue() == floatVar3->getValue());
    TEST_CHK(longVar1->operation(N2OC_PLUS,longVar2,longVar3) == N2EC_SUCCESS);
    TEST_CHK(longVar3->operation(N2OC_MINUS,longVar2,NULL) == N2EC_SUCCESS);
    TEST_CHK(longVar1->getValue() == longVar3->getValue());
    TEST_CHK(strVar1->operation(N2OC_PLUS,strVar2,strVar3) == N2EC_SUCCESS);
    TEST_CHK(strVar1->operation(N2OC_MINUS,strVar2,strVar3) == N2EC_INAPPLICABLE_CODE);
    TEST_CHK(strVar2->getValue() != strVar3->getValue());
    TEST_CHK(boolVar1->operation(N2OC_PLUS,boolVar2,boolVar3) == N2EC_INAPPLICABLE_CODE);
    TEST_CHK(boolVar1->operation(N2OC_MINUS,boolVar2,boolVar3) == N2EC_INAPPLICABLE_CODE);
    TEST_CHK(ternarVar1->operation(N2OC_PLUS,ternarVar2,ternarVar3) == N2EC_INAPPLICABLE_CODE);
    TEST_CHK(ternarVar1->operation(N2OC_MINUS,ternarVar2,ternarVar3) == N2EC_INAPPLICABLE_CODE);

    //-------------------DIV, MULT: (Var1==Var3) ===> (Var1==Var3)
    TEST_CHK(intVar1->operation(N2OC_MULT,intVar2,intVar3) == N2EC_SUCCESS);
    TEST_CHK(intVar3->operation(N2OC_DIV,intVar2,NULL) == N2EC_SUCCESS);
    TEST_CHK(intVar1->getValue() == intVar3->getValue());
    TEST_CHK(floatVar1->operation(N2OC_MULT,floatVar2,floatVar3) == N2EC_SUCCESS);
    TEST_CHK(floatVar3->operation(N2OC_DIV,floatVar2,NULL) == N2EC_SUCCESS);
    TEST_CHK(floatVar1->getValue() == floatVar3->getValue());
    TEST_CHK(longVar1->operation(N2OC_MULT,longVar2,longVar3) == N2EC_SUCCESS);
    TEST_CHK(longVar3->operation(N2OC_DIV,longVar2,NULL) == N2EC_SUCCESS);
    TEST_CHK(longVar1->getValue() == longVar3->getValue());
    TEST_CHK(strVar1->operation(N2OC_MULT,strVar2,strVar3) == N2EC_INAPPLICABLE_CODE);
    TEST_CHK(strVar1->operation(N2OC_DIV,strVar2,strVar3) == N2EC_INAPPLICABLE_CODE);
    TEST_CHK(boolVar1->operation(N2OC_MULT,boolVar2,boolVar3) == N2EC_INAPPLICABLE_CODE);
    TEST_CHK(boolVar1->operation(N2OC_DIV,boolVar2,boolVar3) == N2EC_INAPPLICABLE_CODE);
    TEST_CHK(ternarVar1->operation(N2OC_MULT,ternarVar2,ternarVar3) == N2EC_INAPPLICABLE_CODE);
    TEST_CHK(ternarVar1->operation(N2OC_DIV,ternarVar2,ternarVar3) == N2EC_INAPPLICABLE_CODE);

    //-------------------DIV on 0
    int iZero=0;    float fZero=0;    long lZero=0;
    intVar3->set(iZero);    floatVar3->set(fZero);    longVar3->set(lZero);
    TEST_CHK(intVar1->operation(N2OC_DIV,intVar3,intVar2) == N2EC_NULL_OPERAND);
    TEST_CHK(floatVar1->operation(N2OC_DIV,floatVar3,floatVar2) == N2EC_NULL_OPERAND);
    TEST_CHK(longVar1->operation(N2OC_DIV,longVar3,longVar2) == N2EC_NULL_OPERAND);

    //-------------------AND
    int i1,i2,i3; float f1,f2,f3; long l1,l2,l3; bool b1,b2,b3; string s1,s2,s3;
    i1=intVar1->getValue(); i2=intVar2->getValue(); i3=i1&i2;
    f1=floatVar1->getValue(); f2=floatVar2->getValue();
    l1=longVar1->getValue(); l2=longVar2->getValue(); l3=l1&l2;
    b1=boolVar1->getValue(); b2=boolVar2->getValue(); b3=b1&&b2;
    TEST_CHK(intVar1->operation(N2OC_AND,intVar2,intVar3) == N2EC_SUCCESS);
    TEST_CHK(intVar1->operation(N2OC_AND,intVar2,NULL) == N2EC_SUCCESS);
    TEST_CHK(intVar3->getValue() == i3);
    TEST_CHK(intVar1->getValue() == i3);
    TEST_CHK(floatVar1->operation(N2OC_AND,floatVar2,floatVar3) == N2EC_INAPPLICABLE_CODE);
    TEST_CHK(floatVar1->operation(N2OC_AND,floatVar2,NULL) == N2EC_INAPPLICABLE_CODE);
    TEST_CHK(longVar1->operation(N2OC_AND,longVar2,longVar3) == N2EC_SUCCESS);
    TEST_CHK(longVar1->operation(N2OC_AND,longVar2,NULL) == N2EC_SUCCESS);
    TEST_CHK(longVar3->getValue() == l3);
    TEST_CHK(longVar1->getValue() == l3);
    TEST_CHK(strVar1->operation(N2OC_AND,longVar2,NULL) == N2EC_INAPPLICABLE_CODE);
    TEST_CHK(boolVar1->operation(N2OC_AND,boolVar2,boolVar3) == N2EC_SUCCESS);
    TEST_CHK(boolVar1->operation(N2OC_AND,boolVar2,NULL) == N2EC_SUCCESS);
    TEST_CHK(boolVar3->getValue() == b3);
    TEST_CHK(boolVar1->getValue() == b3);
    TEST_CHK(ternarVar1->operation(N2OC_AND,ternarVar2,ternarVar3) == N2EC_INAPPLICABLE_CODE);

    //-------------------OR
    intVar1->set(iVal1); intVar2->set(iVal2);
    longVar1->set(lVal1); longVar2->set(lVal2);
    floatVar1->set(fVal1); floatVar2->set(fVal2);
    strVar1->set(sVal1); strVar2->set(sVal2);
    boolVar1->set(bVal1); boolVar2->set(bVal2);
    i1=intVar1->getValue(); i2=intVar2->getValue(); i3=i1|i2;
    f1=floatVar1->getValue(); f2=floatVar2->getValue();
    l1=longVar1->getValue(); l2=longVar2->getValue(); l3=l1|l2;
    b1=boolVar1->getValue(); b2=boolVar2->getValue(); b3=b1||b2;
    TEST_CHK(intVar1->operation(N2OC_OR,intVar2,intVar3) == N2EC_SUCCESS);
    TEST_CHK(intVar1->operation(N2OC_OR,intVar2,NULL) == N2EC_SUCCESS);
    TEST_CHK(intVar3->getValue() == i3);
    TEST_CHK(intVar1->getValue() == i3);
    TEST_CHK(floatVar1->operation(N2OC_OR,floatVar2,floatVar3) == N2EC_INAPPLICABLE_CODE);
    TEST_CHK(floatVar1->operation(N2OC_OR,floatVar2,NULL) == N2EC_INAPPLICABLE_CODE);
    TEST_CHK(longVar1->operation(N2OC_OR,longVar2,longVar3) == N2EC_SUCCESS);
    TEST_CHK(longVar1->operation(N2OC_OR,longVar2,NULL) == N2EC_SUCCESS);
    TEST_CHK(longVar3->getValue() == l3);
    TEST_CHK(longVar1->getValue() == l3);
    TEST_CHK(strVar1->operation(N2OC_OR,longVar2,NULL) == N2EC_INAPPLICABLE_CODE);
    TEST_CHK(boolVar1->operation(N2OC_OR,boolVar2,boolVar3) == N2EC_SUCCESS);
    TEST_CHK(boolVar1->operation(N2OC_OR,boolVar2,NULL) == N2EC_SUCCESS);
    TEST_CHK(boolVar3->getValue() == b3);
    TEST_CHK(boolVar1->getValue() == b3);
    TEST_CHK(ternarVar1->operation(N2OC_OR,ternarVar2,ternarVar3) == N2EC_INAPPLICABLE_CODE);

    //-------------------XOR
    intVar1->set(iVal1); intVar2->set(iVal2);
    longVar1->set(lVal1); longVar2->set(lVal2);
    floatVar1->set(fVal1); floatVar2->set(fVal2);
    strVar1->set(sVal1); strVar2->set(sVal2);
    boolVar1->set(bVal1); boolVar2->set(bVal2);
    i1=intVar1->getValue(); i2=intVar2->getValue(); i3=i1^i2;
    f1=floatVar1->getValue(); f2=floatVar2->getValue();
    l1=longVar1->getValue(); l2=longVar2->getValue(); l3=l1^l2;
    b1=boolVar1->getValue(); b2=boolVar2->getValue(); b3=(b1 == b2) ? false : true;
    TEST_CHK(intVar1->operation(N2OC_XOR,intVar2,intVar3) == N2EC_SUCCESS);
    TEST_CHK(intVar1->operation(N2OC_XOR,intVar2,NULL) == N2EC_SUCCESS);
    TEST_CHK(intVar3->getValue() == i3);
    TEST_CHK(intVar1->getValue() == i3);
    TEST_CHK(floatVar1->operation(N2OC_XOR,floatVar2,floatVar3) == N2EC_INAPPLICABLE_CODE);
    TEST_CHK(floatVar1->operation(N2OC_XOR,floatVar2,NULL) == N2EC_INAPPLICABLE_CODE);
    TEST_CHK(longVar1->operation(N2OC_XOR,longVar2,longVar3) == N2EC_SUCCESS);
    TEST_CHK(longVar1->operation(N2OC_XOR,longVar2,NULL) == N2EC_SUCCESS);
    TEST_CHK(longVar3->getValue() == l3);
    TEST_CHK(longVar1->getValue() == l3);
    TEST_CHK(strVar1->operation(N2OC_XOR,longVar2,NULL) == N2EC_INAPPLICABLE_CODE);
    TEST_CHK(boolVar1->operation(N2OC_XOR,boolVar2,boolVar3) == N2EC_SUCCESS);
    TEST_CHK(boolVar1->operation(N2OC_XOR,boolVar2,NULL) == N2EC_SUCCESS);
    TEST_CHK(boolVar3->getValue() == b3);
    TEST_CHK(boolVar1->getValue() == b3);
    TEST_CHK(ternarVar1->operation(N2OC_XOR,ternarVar2,ternarVar3) == N2EC_INAPPLICABLE_CODE);

    //-------------------SHIFT LEFT
    intVar1->set(iVal1); intVar2->set(iVal2);
    longVar1->set(lVal1); longVar2->set(lVal2);
    floatVar1->set(fVal1); floatVar2->set(fVal2);
    strVar1->set(sVal1); strVar2->set(sVal2);
    boolVar1->set(bVal1); boolVar2->set(bVal2);
    i1=intVar1->getValue(); i2=intVar2->getValue(); i3=i1<<i2;
    f1=floatVar1->getValue(); f2=floatVar2->getValue();
    l1=longVar1->getValue(); l2=longVar2->getValue(); l3=l1<<l2;
    b1=boolVar1->getValue(); b2=boolVar2->getValue();
    TEST_CHK(intVar1->operation(N2OC_SHIFT_LEFT,intVar2,intVar3) == N2EC_SUCCESS);
    TEST_CHK(intVar1->operation(N2OC_SHIFT_LEFT,intVar2,NULL) == N2EC_SUCCESS);
    TEST_CHK(intVar3->getValue() == i3);
    TEST_CHK(intVar1->getValue() == i3);
    TEST_CHK(floatVar1->operation(N2OC_SHIFT_LEFT,floatVar2,floatVar3) == N2EC_INAPPLICABLE_CODE);
    TEST_CHK(floatVar1->operation(N2OC_SHIFT_LEFT,floatVar2,NULL) == N2EC_INAPPLICABLE_CODE);
    TEST_CHK(longVar1->operation(N2OC_SHIFT_LEFT,longVar2,longVar3) == N2EC_SUCCESS);
    TEST_CHK(longVar1->operation(N2OC_SHIFT_LEFT,longVar2,NULL) == N2EC_SUCCESS);
    TEST_CHK(longVar3->getValue() == l3);
    TEST_CHK(longVar1->getValue() == l3);
    TEST_CHK(strVar1->operation(N2OC_SHIFT_LEFT,longVar2,NULL) == N2EC_INAPPLICABLE_CODE);
    TEST_CHK(boolVar1->operation(N2OC_SHIFT_LEFT,boolVar2,boolVar3) == N2EC_INAPPLICABLE_CODE);
    TEST_CHK(ternarVar1->operation(N2OC_SHIFT_LEFT,ternarVar2,ternarVar3) == N2EC_INAPPLICABLE_CODE);

    //-------------------SHIFT RIGHT
    intVar1->set(iVal1); intVar2->set(iVal2);
    longVar1->set(lVal1); longVar2->set(lVal2);
    floatVar1->set(fVal1); floatVar2->set(fVal2);
    strVar1->set(sVal1); strVar2->set(sVal2);
    boolVar1->set(bVal1); boolVar2->set(bVal2);
    i1=intVar1->getValue(); i2=intVar2->getValue(); i3=i1>>i2;
    f1=floatVar1->getValue(); f2=floatVar2->getValue();
    l1=longVar1->getValue(); l2=longVar2->getValue(); l3=l1>>l2;
    b1=boolVar1->getValue(); b2=boolVar2->getValue();
    TEST_CHK(intVar1->operation(N2OC_SHIFT_RIGTH,intVar2,intVar3) == N2EC_SUCCESS);
    TEST_CHK(intVar1->operation(N2OC_SHIFT_RIGTH,intVar2,NULL) == N2EC_SUCCESS);
    TEST_CHK(intVar3->getValue() == i3);
    TEST_CHK(intVar1->getValue() == i3);
    TEST_CHK(floatVar1->operation(N2OC_SHIFT_RIGTH,floatVar2,floatVar3) == N2EC_INAPPLICABLE_CODE);
    TEST_CHK(floatVar1->operation(N2OC_SHIFT_RIGTH,floatVar2,NULL) == N2EC_INAPPLICABLE_CODE);
    TEST_CHK(longVar1->operation(N2OC_SHIFT_RIGTH,longVar2,longVar3) == N2EC_SUCCESS);
    TEST_CHK(longVar1->operation(N2OC_SHIFT_RIGTH,longVar2,NULL) == N2EC_SUCCESS);
    TEST_CHK(longVar3->getValue() == l3);
    TEST_CHK(longVar1->getValue() == l3);
    TEST_CHK(strVar1->operation(N2OC_SHIFT_RIGTH,longVar2,NULL) == N2EC_INAPPLICABLE_CODE);
    TEST_CHK(boolVar1->operation(N2OC_SHIFT_RIGTH,boolVar2,boolVar3) == N2EC_INAPPLICABLE_CODE);
    TEST_CHK(ternarVar1->operation(N2OC_SHIFT_RIGTH,ternarVar2,ternarVar3) == N2EC_INAPPLICABLE_CODE);

    //-------------------MAX
    intVar1->set(iVal1); intVar2->set(iVal2);
    longVar1->set(lVal1); longVar2->set(lVal2);
    floatVar1->set(fVal1); floatVar2->set(fVal2);
    strVar1->set(sVal1); strVar2->set(sVal2);
    boolVar1->set(bVal1); boolVar2->set(bVal2);
    i1=intVar1->getValue(); i2=intVar2->getValue(); i3=(i1>i2) ? i1:i2;
    f1=floatVar1->getValue(); f2=floatVar2->getValue(); f3=(f1>f2) ? f1:f2;
    l1=longVar1->getValue(); l2=longVar2->getValue(); l3=(l1>l2) ? l1:l2;
    b1=boolVar1->getValue(); b2=boolVar2->getValue();
    s1=strVar1->getValue(); s2=strVar2->getValue(); s3=(s1.size()>s2.size()) ? s1:s2;
    TEST_CHK(intVar1->operation(N2OC_MAX,intVar2,intVar3) == N2EC_SUCCESS);
    TEST_CHK(intVar1->operation(N2OC_MAX,intVar2,NULL) == N2EC_SUCCESS);
    TEST_CHK(intVar3->getValue() == i3);
    TEST_CHK(intVar1->getValue() == i3);
    TEST_CHK(floatVar1->operation(N2OC_MAX,floatVar2,floatVar3) == N2EC_SUCCESS);
    TEST_CHK(floatVar1->operation(N2OC_MAX,floatVar2,NULL) == N2EC_SUCCESS);
    TEST_CHK(floatVar3->getValue() == f3);
    TEST_CHK(floatVar1->getValue() == f3);
    TEST_CHK(longVar1->operation(N2OC_MAX,longVar2,longVar3) == N2EC_SUCCESS);
    TEST_CHK(longVar1->operation(N2OC_MAX,longVar2,NULL) == N2EC_SUCCESS);
    TEST_CHK(longVar3->getValue() == l3);
    TEST_CHK(longVar1->getValue() == l3);
    TEST_CHK(strVar1->operation(N2OC_MAX,strVar2,strVar3) == N2EC_SUCCESS);
    TEST_CHK(strVar1->operation(N2OC_MAX,strVar2,NULL) == N2EC_SUCCESS);
    TEST_CHK(strVar3->getValue() == s3);
    TEST_CHK(strVar1->getValue() == s3);
    TEST_CHK(boolVar1->operation(N2OC_MAX,boolVar2,boolVar3) == N2EC_INAPPLICABLE_CODE);
    TEST_CHK(ternarVar1->operation(N2OC_MAX,ternarVar2,ternarVar3) == N2EC_INAPPLICABLE_CODE);

    //-------------------MIN
    intVar1->set(iVal1); intVar2->set(iVal2);
    longVar1->set(lVal1); longVar2->set(lVal2);
    floatVar1->set(fVal1); floatVar2->set(fVal2);
    strVar1->set(sVal1); strVar2->set(sVal2);
    boolVar1->set(bVal1); boolVar2->set(bVal2);
    i1=intVar1->getValue(); i2=intVar2->getValue(); i3=(i1<i2) ? i1:i2;
    f1=floatVar1->getValue(); f2=floatVar2->getValue(); f3=(f1<f2) ? f1:f2;
    l1=longVar1->getValue(); l2=longVar2->getValue(); l3=(l1<l2) ? l1:l2;
    b1=boolVar1->getValue(); b2=boolVar2->getValue();
    s1=strVar1->getValue(); s2=strVar2->getValue(); s3=(s1.size()<s2.size()) ? s1:s2;
    TEST_CHK(intVar1->operation(N2OC_MIN,intVar2,intVar3) == N2EC_SUCCESS);
    TEST_CHK(intVar1->operation(N2OC_MIN,intVar2,NULL) == N2EC_SUCCESS);
    TEST_CHK(intVar3->getValue() == i3);
    TEST_CHK(intVar1->getValue() == i3);
    TEST_CHK(floatVar1->operation(N2OC_MIN,floatVar2,floatVar3) == N2EC_SUCCESS);
    TEST_CHK(floatVar1->operation(N2OC_MIN,floatVar2,NULL) == N2EC_SUCCESS);
    TEST_CHK(floatVar3->getValue() == f3);
    TEST_CHK(floatVar1->getValue() == f3);
    TEST_CHK(longVar1->operation(N2OC_MIN,longVar2,longVar3) == N2EC_SUCCESS);
    TEST_CHK(longVar1->operation(N2OC_MIN,longVar2,NULL) == N2EC_SUCCESS);
    TEST_CHK(longVar3->getValue() == l3);
    TEST_CHK(longVar1->getValue() == l3);
    TEST_CHK(strVar1->operation(N2OC_MIN,strVar2,strVar3) == N2EC_SUCCESS);
    TEST_CHK(strVar1->operation(N2OC_MIN,strVar2,NULL) == N2EC_SUCCESS);
    TEST_CHK(strVar3->getValue() == s3);
    TEST_CHK(strVar1->getValue() == s3);
    TEST_CHK(boolVar1->operation(N2OC_MIN,boolVar2,boolVar3) == N2EC_INAPPLICABLE_CODE);
    TEST_CHK(ternarVar1->operation(N2OC_MIN,ternarVar2,ternarVar3) == N2EC_INAPPLICABLE_CODE);

    //-------------------MOD
    intVar1->set(iVal1); intVar2->set(iVal2);
    longVar1->set(lVal1); longVar2->set(lVal2);
    floatVar1->set(fVal1); floatVar2->set(fVal2);
    strVar1->set(sVal1); strVar2->set(sVal2);
    boolVar1->set(bVal1); boolVar2->set(bVal2);
    i1=intVar1->getValue(); i2=intVar2->getValue(); i3=i1%i2;
    f1=floatVar1->getValue(); f2=floatVar2->getValue();
    l1=longVar1->getValue(); l2=longVar2->getValue(); l3=l1%l2;
    b1=boolVar1->getValue(); b2=boolVar2->getValue();
    s1=strVar1->getValue(); s2=strVar2->getValue();
    TEST_CHK(intVar1->operation(N2OC_MOD,intVar2,intVar3) == N2EC_SUCCESS);
    TEST_CHK(intVar1->operation(N2OC_MOD,intVar2,NULL) == N2EC_SUCCESS);
    TEST_CHK(intVar3->getValue() == i3);
    TEST_CHK(intVar1->getValue() == i3);
    TEST_CHK(floatVar1->operation(N2OC_MOD,floatVar2,floatVar3) == N2EC_INAPPLICABLE_CODE);
    TEST_CHK(floatVar1->operation(N2OC_MOD,floatVar2,NULL) == N2EC_INAPPLICABLE_CODE);
    TEST_CHK(longVar1->operation(N2OC_MOD,longVar2,longVar3) == N2EC_SUCCESS);
    TEST_CHK(longVar1->operation(N2OC_MOD,longVar2,NULL) == N2EC_SUCCESS);
    TEST_CHK(longVar3->getValue() == l3);
    TEST_CHK(longVar1->getValue() == l3);
    TEST_CHK(strVar1->operation(N2OC_MOD,strVar2,strVar3) == N2EC_INAPPLICABLE_CODE);
    TEST_CHK(strVar1->operation(N2OC_MOD,strVar2,NULL) == N2EC_INAPPLICABLE_CODE);
    TEST_CHK(boolVar1->operation(N2OC_MOD,boolVar2,boolVar3) == N2EC_INAPPLICABLE_CODE);
    TEST_CHK(ternarVar1->operation(N2OC_MOD,ternarVar2,ternarVar3) == N2EC_INAPPLICABLE_CODE);

    N2Register::self()->getMemoryAllocator()->releaseVar<N2BaseVariable>(intVar1, 1);
    N2Register::self()->getMemoryAllocator()->releaseVar<N2BaseVariable>(intVar2, 1);
    N2Register::self()->getMemoryAllocator()->releaseVar<N2BaseVariable>(intVar3, 1);
    N2Register::self()->getMemoryAllocator()->releaseVar<N2BaseVariable>(longVar1, 1);
    N2Register::self()->getMemoryAllocator()->releaseVar<N2BaseVariable>(longVar2, 1);
    N2Register::self()->getMemoryAllocator()->releaseVar<N2BaseVariable>(longVar3, 1);
    N2Register::self()->getMemoryAllocator()->releaseVar<N2BaseVariable>(floatVar1, 1);
    N2Register::self()->getMemoryAllocator()->releaseVar<N2BaseVariable>(floatVar2, 1);
    N2Register::self()->getMemoryAllocator()->releaseVar<N2BaseVariable>(floatVar3, 1);
    N2Register::self()->getMemoryAllocator()->releaseVar<N2BaseVariable>(boolVar1, 1);
    N2Register::self()->getMemoryAllocator()->releaseVar<N2BaseVariable>(boolVar2, 1);
    N2Register::self()->getMemoryAllocator()->releaseVar<N2BaseVariable>(boolVar3, 1);
    N2Register::self()->getMemoryAllocator()->releaseVar<N2BaseVariable>(strVar1, 1);
    N2Register::self()->getMemoryAllocator()->releaseVar<N2BaseVariable>(strVar2, 1);
    N2Register::self()->getMemoryAllocator()->releaseVar<N2BaseVariable>(strVar3, 1);
    N2Register::self()->getMemoryAllocator()->releaseVar<N2BaseVariable>(ternarVar1, 1);
    N2Register::self()->getMemoryAllocator()->releaseVar<N2BaseVariable>(ternarVar2, 1);
    N2Register::self()->getMemoryAllocator()->releaseVar<N2BaseVariable>(ternarVar3, 1);

    GloTest::printResult();
    return GloTest::errors();
}
