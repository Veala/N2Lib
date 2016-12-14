//#include "N2Types.h"
#include "N2Variable.h"
#include "N2Register.h"

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

int main()
{
    N2VariableCreator creator;
    N2VariableComplex *userVal = (N2VariableComplex*)creator.createComplex("userVal");


    N2BaseVariable *data1 = creator.createSimplex(VAR_INT,"data1");
    int data=17;
    ((N2VariableINT*)data1)->set(data, 0);
    cout << ((N2VariableINT*)data1)->getValue(0) << endl;
    userVal->addCopyVar(data1);
    N2Register::self()->getMemoryAllocator()->releaseVar<N2BaseVariable>(data1,1);

    N2BaseVariable *value = userVal->getVar("data1", VAR_INT);
    if (value!=0) {
        f(value);
    }
    N2BaseVariable *data3 = creator.createSimplex(VAR_INT,"data3");
    data =21;
    ((N2VariableINT*)data3)->set(data, 0);
    N2VariableComplex *uv = (N2VariableComplex*)creator.createComplex("uv");
    uv->addCopyVar(data3);
    uv->addCopyVar(userVal);

    N2Register::self()->getMemoryAllocator()->releaseVar<N2BaseVariable>(data3, 1);

    N2VariableComplex *uVal = uv->clone();

    N2Register::self()->getMemoryAllocator()->releaseVar<N2BaseVariable>(uv,1);

    value = uVal->getVar("data3", VAR_INT);
    if (value!=0) {
        f(value);
    }
    value = uVal->getVar("userVal.data1", VAR_INT);
    if (value!=0) {
        f(value);
    }
    value = uVal->getVar("userVal", VAR_VMUSER);
    if (value!=0) {
        f(value);
    }

    N2Register::self()->getMemoryAllocator()->releaseVar<N2BaseVariable>(uVal,1);
    N2Register::self()->getMemoryAllocator()->releaseVar<N2BaseVariable>(userVal,1);

    return 0;
}
