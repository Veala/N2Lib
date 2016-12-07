#include "N2Types.h"

void f(N2AbstractType* data) {
    switch (data->getType()) {
    case N2AbstractType::BOOL:
        cout << ((N2Bool*)data)->getValue(0) << endl;
        break;
    case N2AbstractType::INT:
        cout << ((N2Int*)data)->getValue(0) << endl;
        break;
    case N2AbstractType::LONG:
        cout << ((N2Long*)data)->getValue(0) << endl;
        break;
    case N2AbstractType::FLOAT:
        cout << ((N2Float*)data)->getValue(0) << endl;
        break;
    case  N2AbstractType::STRING:
        cout << ((N2String*)data)->getValue(0) << endl;
        break;
    case  N2AbstractType::BOOLTABLE:
        cout << ((N2BoolTable*)data)->getValue(0,1) << endl;
        break;
    case  N2AbstractType::INTTABLE:
        cout << ((N2IntTable*)data)->getValue(0,1) << endl;
        break;
    case  N2AbstractType::LONGTABLE:
        cout << ((N2LongTable*)data)->getValue(0,1) << endl;
        break;
    case  N2AbstractType::FLOATTABLE:
        cout << ((N2FloatTable*)data)->getValue(0,1) << endl;
        break;
    case  N2AbstractType::STRINGTABLE:
        cout << ((N2StringTable*)data)->getValue(0,1) << endl;
        break;
    case  N2AbstractType::VMUSER:
        cout << ((N2User*)data)->getName() << endl;
        break;
    }
}

int main()
{
    N2User *userVal = N2Register::self()->getMemoryAllocator()->createUserVar<N2User>("userVal");


    N2AbstractType *data1 = N2Register::self()->getMemoryAllocator()->createSimpleVar<N2Int>("data1",1);
    N2AbstractType *data2 = N2Register::self()->getMemoryAllocator()->createTableVar<N2IntTable>("data2",3,3);
    ((N2Int*)data1)->setValue(0, 17);
    ((N2IntTable*)data2)->setValue(0, 1, 18);
    userVal->addCopyVar(data1);
    userVal->addCopyVar(data2);
    N2Register::self()->getMemoryAllocator()->releaseAnyVar<N2AbstractType>(data1);
    N2Register::self()->getMemoryAllocator()->releaseAnyVar<N2AbstractType>(data2);

    N2AbstractType *value = userVal->getVar("data1", N2AbstractType::INT);
    if (value!=0) {
        f(value);
    }
    value = userVal->getVar("data2", N2AbstractType::INTTABLE);
    if (value!=0) {
        f(value);
    }
    N2AbstractType *data3 = N2Register::self()->getMemoryAllocator()->createSimpleVar<N2Int>("data3",1);
    N2AbstractType *data4 = N2Register::self()->getMemoryAllocator()->createTableVar<N2IntTable>("data4",4,4);
    ((N2Int*)data3)->setValue(0, 21);
    ((N2IntTable*)data4)->setValue(0, 1, 42);
    N2User *uv = N2Register::self()->getMemoryAllocator()->createUserVar<N2User>("uv");
    uv->addCopyVar(data3);
    uv->addCopyVar(data4);
    uv->addCopyVar(userVal);

    N2Register::self()->getMemoryAllocator()->releaseAnyVar<N2AbstractType>(data3);
    N2Register::self()->getMemoryAllocator()->releaseAnyVar<N2AbstractType>(data4);

    N2User *uVal = uv->clone();

    N2Register::self()->getMemoryAllocator()->releaseAnyVar<N2User>(uv);

    value = uVal->getVar("data3", N2AbstractType::INT);
    if (value!=0) {
        f(value);
    }
    value = uVal->getVar("data4", N2AbstractType::INTTABLE);
    if (value!=0) {
        f(value);
    }
    value = uVal->getVar("userVal.data1", N2AbstractType::INT);
    if (value!=0) {
        f(value);
    }
    value = uVal->getVar("userVal.data2", N2AbstractType::INTTABLE);
    if (value!=0) {
        f(value);
    }
    value = uVal->getVar("userVal", N2AbstractType::VMUSER);
    if (value!=0) {
        f(value);
    }

    N2Register::self()->getMemoryAllocator()->releaseAnyVar<N2AbstractType>(uVal);
    N2Register::self()->getMemoryAllocator()->releaseAnyVar<N2AbstractType>(userVal);

    return 0;
}

