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
    N2VariableComplex *userVal = N2Register::self()->getMemoryAllocator()->create<N2VariableComplex>("userVal");    userVal->rename("userVal");


    N2BaseVariable *data1 = N2Register::self()->getMemoryAllocator()->create<N2VariableINT>("data1");
//    N2BaseVariable *data2 = N2Register::self()->getMemoryAllocator()->create<N2VariableIntTABLE>("data2",3,3);
    int data=17;
    ((N2VariableINT*)data1)->set(data, 0);
    cout << ((N2VariableINT*)data1)->getValue(0) << endl;
//    ((N2VariableIntTABLE*)data2)->setValue(0, 1, 18);
    userVal->addCopyVar(data1);
//    userVal->addCopyVar(data2);
    N2Register::self()->getMemoryAllocator()->release(data1);
//    N2Register::self()->getMemoryAllocator()->release<N2BaseVariable>(data2);

    N2BaseVariable *value = userVal->getVar("data1", VAR_INT);
    if (value!=0) {
        f(value);
    }
//    value = userVal->getVar("data2", VAR_INTTABLE);
//    if (value!=0) {
//        f(value);
//    }
    N2BaseVariable *data3 = N2Register::self()->getMemoryAllocator()->create<N2VariableINT>("data3");
//    N2BaseVariable *data4 = N2Register::self()->getMemoryAllocator()->create<N2VariableIntTABLE>("data4",4,4);
    data =21;
    ((N2VariableINT*)data3)->set(data, 0);
//    ((N2VariableIntTABLE*)data4)->setValue(0, 1, 42);
    N2VariableComplex *uv = N2Register::self()->getMemoryAllocator()->create<N2VariableComplex>("uv");  uv->rename("uv");
    uv->addCopyVar(data3);
//    uv->addCopyVar(data4);
    uv->addCopyVar(userVal);

    N2Register::self()->getMemoryAllocator()->release(data3);
//    N2Register::self()->getMemoryAllocator()->release(data4);

    N2VariableComplex *uVal = uv->clone();

    N2Register::self()->getMemoryAllocator()->release(uv);

    value = uVal->getVar("data3", VAR_INT);
    if (value!=0) {
        f(value);
    }
//    value = uVal->getVar("data4", VAR_IntTABLE);
//    if (value!=0) {
//        f(value);
//    }
    value = uVal->getVar("userVal.data1", VAR_INT);
    if (value!=0) {
        f(value);
    }
//    value = uVal->getVar("userVal.data2", VAR_INTTABLE);
//    if (value!=0) {
//        f(value);
//    }
    value = uVal->getVar("userVal", VAR_VMUSER);
    if (value!=0) {
        f(value);
    }

    N2Register::self()->getMemoryAllocator()->release(uVal);
    N2Register::self()->getMemoryAllocator()->release(userVal);

    return 0;
}

