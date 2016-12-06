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
//    N2User userVal("userVal");
//    N2AbstractType *data1 = new N2Int("data1", 7, 1);
//    N2AbstractType *data2 = new N2IntTable("data2", 8, 3, 3);
//    ((N2Int*)data1)->setValue(0, 17);
//    ((N2IntTable*)data2)->setValue(0, 1, 18);
//    userVal.addCopyVar(data1);
//    userVal.addCopyVar(data2);
//    N2AbstractType *value = userVal.getVar("data1", N2AbstractType::INT);
//    if (value!=0) {
//        f(value);
//    }
//    value = userVal.getVar("data2", N2AbstractType::INTTABLE);
//    if (value!=0) {
//        f(value);
//    }

//    N2AbstractType *data3 = new N2Int("data3", 21, 1);
//    N2AbstractType *data4 = new N2IntTable("data4", 42, 4, 4);
//    N2User *uv = new N2User("uv");
//    uv->addCopyVar(data3);
//    uv->addCopyVar(data4);
//    uv->addCopyVar(&userVal);

//    delete (N2Int*)data3; delete (N2IntTable*)data4;

//    N2User *uVal = uv->clone();

//    delete uv;

//    value = uVal->getVar("data3", N2AbstractType::INT);
//    if (value!=0) {
//        f(value);
//    }
//    value = uVal->getVar("data4", N2AbstractType::INTTABLE);
//    if (value!=0) {
//        f(value);
//    }
//    value = uVal->getVar("userVal.data1", N2AbstractType::INT);
//    if (value!=0) {
//        f(value);
//    }
//    value = uVal->getVar("userVal.data2", N2AbstractType::INTTABLE);
//    if (value!=0) {
//        f(value);
//    }
//    value = uVal->getVar("userVal", N2AbstractType::VMUSER);
//    if (value!=0) {
//        f(value);
//    }

//    delete uVal;

    return 0;
}

