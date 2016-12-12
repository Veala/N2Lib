//#include "N2Types.h"
#include "N2Variable.h"
#include "N2Register.h"

void f(N2BaseVariable* data) {
//    switch (data->getType()) {
//    case N2BaseVariable::BOOL:
//        cout << ((N2Bool*)data)->getValue(0) << endl;
//        break;
//    case N2BaseVariable::INT:
//        cout << ((N2Int*)data)->getValue(0) << endl;
//        break;
//    case N2BaseVariable::LONG:
//        cout << ((N2Long*)data)->getValue(0) << endl;
//        break;
//    case N2BaseVariable::FLOAT:
//        cout << ((N2Float*)data)->getValue(0) << endl;
//        break;
//    case  N2BaseVariable::STRING:
//        cout << ((N2String*)data)->getValue(0) << endl;
//        break;
//    case  N2BaseVariable::BOOLTABLE:
//        cout << ((N2BoolTable*)data)->getValue(0,1) << endl;
//        break;
//    case  N2BaseVariable::INTTABLE:
//        cout << ((N2IntTable*)data)->getValue(0,1) << endl;
//        break;
//    case  N2BaseVariable::LONGTABLE:
//        cout << ((N2LongTable*)data)->getValue(0,1) << endl;
//        break;
//    case  N2BaseVariable::FLOATTABLE:
//        cout << ((N2FloatTable*)data)->getValue(0,1) << endl;
//        break;
//    case  N2BaseVariable::STRINGTABLE:
//        cout << ((N2StringTable*)data)->getValue(0,1) << endl;
//        break;
//    case  N2BaseVariable::VMUSER:
//        cout << ((N2User*)data)->getName() << endl;
//        break;
//    }
}

int main()
{
//    N2User *userVal = N2Register::self()->getMemoryAllocator()->createUserVar<N2User>("userVal");


//    N2BaseVariable *data1 = N2Register::self()->getMemoryAllocator()->createSimpleVar<N2Int>("data1",1);
//    N2BaseVariable *data2 = N2Register::self()->getMemoryAllocator()->createTableVar<N2IntTable>("data2",3,3);
//    ((N2Int*)data1)->setValue(0, 17);
//    ((N2IntTable*)data2)->setValue(0, 1, 18);
//    userVal->addCopyVar(data1);
//    userVal->addCopyVar(data2);
//    N2Register::self()->getMemoryAllocator()->releaseAnyVar<N2BaseVariable>(data1);
//    N2Register::self()->getMemoryAllocator()->releaseAnyVar<N2BaseVariable>(data2);

//    N2BaseVariable *value = userVal->getVar("data1", N2BaseVariable::INT);
//    if (value!=0) {
//        f(value);
//    }
//    value = userVal->getVar("data2", N2BaseVariable::INTTABLE);
//    if (value!=0) {
//        f(value);
//    }
//    N2BaseVariable *data3 = N2Register::self()->getMemoryAllocator()->createSimpleVar<N2Int>("data3",1);
//    N2BaseVariable *data4 = N2Register::self()->getMemoryAllocator()->createTableVar<N2IntTable>("data4",4,4);
//    ((N2Int*)data3)->setValue(0, 21);
//    ((N2IntTable*)data4)->setValue(0, 1, 42);
//    N2User *uv = N2Register::self()->getMemoryAllocator()->createUserVar<N2User>("uv");
//    uv->addCopyVar(data3);
//    uv->addCopyVar(data4);
//    uv->addCopyVar(userVal);

//    N2Register::self()->getMemoryAllocator()->releaseAnyVar<N2BaseVariable>(data3);
//    N2Register::self()->getMemoryAllocator()->releaseAnyVar<N2BaseVariable>(data4);

//    N2User *uVal = uv->clone();

//    N2Register::self()->getMemoryAllocator()->releaseAnyVar<N2User>(uv);

//    value = uVal->getVar("data3", N2BaseVariable::INT);
//    if (value!=0) {
//        f(value);
//    }
//    value = uVal->getVar("data4", N2BaseVariable::INTTABLE);
//    if (value!=0) {
//        f(value);
//    }
//    value = uVal->getVar("userVal.data1", N2BaseVariable::INT);
//    if (value!=0) {
//        f(value);
//    }
//    value = uVal->getVar("userVal.data2", N2BaseVariable::INTTABLE);
//    if (value!=0) {
//        f(value);
//    }
//    value = uVal->getVar("userVal", N2BaseVariable::VMUSER);
//    if (value!=0) {
//        f(value);
//    }

//    N2Register::self()->getMemoryAllocator()->releaseAnyVar<N2BaseVariable>(uVal);
//    N2Register::self()->getMemoryAllocator()->releaseAnyVar<N2BaseVariable>(userVal);

    return 0;
}

