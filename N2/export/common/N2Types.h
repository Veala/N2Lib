//#ifndef N2AbstractType_H
//#define N2AbstractType_H

//#include <iostream>
//#include <sstream>
//#include <string>
//#include <vector>
//#include <stdexcept>
//#include "N2LiveObjectsPolicy.h"
//#include "N2Register.h"

//using namespace std;

//class N2AbstractType
//{
//public:
//    typedef unsigned int uint;
//    enum types {
//        BOOL,     BOOLTABLE,
//        INT,      INTTABLE,
//        LONG,     LONGTABLE,
//        FLOAT,    FLOATTABLE,
//        STRING,   STRINGTABLE,
//        VMUSER
//    };
//    void setName(string newName)    { varName = newName; }
//    const string getName()          { return varName; }
//    types getType()                 { return type; }
//    virtual N2AbstractType* clone() = 0;
//    virtual ~N2AbstractType() { cout << "N2AbstractType: " << varName << endl; }
//protected:
//    N2AbstractType(string vName)    { varName = vName; }
//    string varName;
//    types type;
//private:

//};

////----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

//template <class T> class N2AbstractSimple : public N2AbstractType
//{
//    friend OLS_Heap;
//public:
//    void setValue(uint index, T newValue);
//    T getValue(uint index);
//    N2AbstractType* clone();
//    ~N2AbstractSimple();
//protected:
//    N2AbstractSimple(string vName, uint N, T defVal);
//    N2AbstractSimple(N2AbstractSimple &data);
//    vector<T> value;
//private:

//};

//class N2Bool : public N2AbstractSimple <bool>
//{
//    friend OLS_Heap;
//protected:
//    N2Bool(string vName, uint N=1, bool defVal=false) : N2AbstractSimple<bool>(vName, N, defVal) { type = BOOL; }
//};
//class N2Int : public N2AbstractSimple <int>
//{
//    friend OLS_Heap;
//protected:
//    N2Int(string vName, uint N=1, int defVal=0) : N2AbstractSimple<int>(vName, N, defVal) { type = INT; }
//};
//class N2Long : public N2AbstractSimple <long>
//{
//    friend OLS_Heap;
//protected:
//    N2Long(string vName, uint N=1, long defVal=0) : N2AbstractSimple<long>(vName, N, defVal) { type = LONG; }
//};
//class N2Float : public N2AbstractSimple <float>
//{
//    friend OLS_Heap;
//protected:
//    N2Float(string vName, uint N=1, float defVal=0) : N2AbstractSimple<float>(vName, N, defVal) { type = FLOAT; }
//};
//class N2String : public N2AbstractSimple <string>
//{
//    friend OLS_Heap;
//protected:
//    N2String(string vName, uint N=1, string defVal="defVal") : N2AbstractSimple<string>(vName, N, defVal) { type = STRING; }
//};

////----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

//template <class T> class N2AbstractTable : public N2AbstractType
//{
//    friend OLS_Heap;
//public:
//    void setValue(uint row, uint column, T newValue);
//    T getValue(uint row, uint column);
//    N2AbstractType* clone();
//    ~N2AbstractTable();
//protected:
//    N2AbstractTable(string vName, uint numRows, uint numColumns, T defVal);
//    N2AbstractTable(N2AbstractTable &data);
//    vector< vector<T> > value;
//private:

//};

//class N2BoolTable : public N2AbstractTable <bool>
//{
//    friend OLS_Heap;
//protected:
//    N2BoolTable(string vName, uint numRows=1, uint numColumns=1, bool defVal=false) : N2AbstractTable<bool>(vName, numRows, numColumns, defVal) { type = BOOLTABLE; }
//};
//class N2IntTable : public N2AbstractTable <int>
//{
//    friend OLS_Heap;
//protected:
//    N2IntTable(string vName, uint numRows=1, uint numColumns=1, int defVal=0) : N2AbstractTable<int>(vName, numRows, numColumns, defVal) { type = INTTABLE; }
//};
//class N2LongTable : public N2AbstractTable <long>
//{
//    friend OLS_Heap;
//protected:
//    N2LongTable(string vName, uint numRows=1, uint numColumns=1, long defVal=0) : N2AbstractTable<long>(vName, numRows, numColumns, defVal) { type = LONGTABLE; }
//};
//class N2FloatTable : public N2AbstractTable <float>
//{
//    friend OLS_Heap;
//protected:
//    N2FloatTable(string vName, uint numRows=1, uint numColumns=1, float defVal=0) : N2AbstractTable<float>(vName, numRows, numColumns, defVal) { type = FLOATTABLE; }
//};
//class N2StringTable : public N2AbstractTable <string>
//{
//    friend OLS_Heap;
//protected:
//    N2StringTable(string vName, uint numRows=1, uint numColumns=1, string defVal="defVal") : N2AbstractTable<string>(vName, numRows, numColumns, defVal) { type = STRINGTABLE; }
//};

////----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

//class N2User : public N2AbstractType
//{
//    friend OLS_Heap;
//public:
//    void addCopyVar(N2AbstractType* var);
//    N2AbstractType* getVar(string strHierarchy, types t);
//    N2User* clone();
//    ~N2User();
//protected:
//    N2User(string vName) : N2AbstractType(vName) { type = VMUSER; }
//    vector<N2AbstractType*>   vars;
//private:
//    N2AbstractType* searchVar(string vName, types t);
//};

//class N2TypeCreator
//{
//public:
//    N2AbstractType* createSimple(N2AbstractType::types type, string name = "simpleVar", unsigned int cnt = 1);
//    N2AbstractType* createTable(N2AbstractType::types type, string name = "tableVar", int rows=1, int columns=1);
//    N2AbstractType* createUser(string name = "userVar");
//};

//#endif // N2AbstractType_H






#ifndef N2BaseVariable_H
#define N2BaseVariable_H

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <stdexcept>
#include "N2Defines.h"
#include "N2LiveObjectsPolicy.h"

using namespace std;
using namespace N2_Defines;

enum N2_ERRORS_OPCODES {
    N2EC_SUCCESS = 0,
    N2EC_INAPPLICABLE_CODE = 1, // неприменимый код
    N2EC_BAD_OPERAND_TYPE = 2,
    N2EC_NULL_OPERAND = 3,
    N2EC_EMPTY = 4 // ф-ция не выполнила действие
};

struct N2_ERRORS_OPCODES_DESCRIPTION {
    N2_ERRORS_OPCODES code;
    std_string description;
};

static N2_ERRORS_OPCODES_DESCRIPTION N2ERR_Definitions [] =
{
    {N2EC_SUCCESS, CT("без ошибок")},
    {N2EC_INAPPLICABLE_CODE, CT("неприменимый к операнду код")}
};

class N2BaseVariable
{
public:
    typedef unsigned int uint;
//    enum types {
//        BOOL,     BOOLTABLE,
//        INT,      INTTABLE,
//        LONG,     LONGTABLE,
//        FLOAT,    FLOATTABLE,
//        STRING,   STRINGTABLE,
//        VMUSER
//    };
    void setName(string newName)    { varName = newName; }
    const string name()             { return varName; }
    TYPE_VAR getType()                 { return type; }
    virtual N2BaseVariable* clone() = 0;
    virtual ~N2BaseVariable()       { cout << "N2BaseVariable: " << varName << endl; }


//    virtual std_string rename(std_string newName);
//    virtual bool add(N2BaseVariable* addVar);
//    virtual bool set(N2BaseVariable* , INDEX index = 0) = 0;
//    virtual const COUNT dimension(void);
//    virtual N2_ERRORS_OPCODES
//        operation(N2_OPERATING_CODE code, N2BaseVariable* op2 = NULL, N2BaseVariable* res = NULL);
//    virtual bool setVoid(void* pVal, INDEX index = 0) = 0;
//    virtual bool compare(N2_COMPARE_CODES code, N2BaseVariable* pVar) = 0;
//    KIND_TYPE kind(void);
//    virtual void* getVoid(INDEX index = 0) = 0;



protected:
    N2BaseVariable(string vName)    { varName = vName; }
    string varName;
    //types type;
    TYPE_VAR type;
private:

};


//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

template <class T> class N2AbstractSimple : public N2BaseVariable
{
    friend OLS_Heap;
public:
    void setValue(uint index, T newValue);
    T getValue(uint index);
    N2BaseVariable* clone();

//    virtual T* get(INDEX index = 0) = 0;
//    virtual T custom(N2BaseVariable* pVar) = 0;
//    virtual bool set(T& value, INDEX index = 0) = 0;
//    virtual T getValue(INDEX index = 0);

//    virtual bool add(N2BaseVariable* addVar);
//    virtual bool set(N2BaseVariable* , INDEX index = 0) = 0;
//    virtual const COUNT dimension(void);
//    virtual N2_ERRORS_OPCODES
//        operation(N2_OPERATING_CODE code, N2BaseVariable* op2 = NULL, N2BaseVariable* res = NULL);
//    virtual bool setVoid(void* pVal, INDEX index = 0) = 0;
//    virtual bool compare(N2_COMPARE_CODES code, N2BaseVariable* pVar) = 0;
//    //KIND_TYPE kind(void);
//    virtual void* getVoid(INDEX index = 0) = 0;

    ~N2AbstractSimple();
protected:
    N2AbstractSimple(string vName, uint N, T defVal);
    N2AbstractSimple(N2AbstractSimple &data);
    vector<T> value;
private:

};

class N2VariableBOOL : public N2AbstractSimple <bool>
{
    friend OLS_Heap;
protected:
    N2VariableBOOL(string vName, uint N=1, bool defVal=false) : N2AbstractSimple<bool>(vName, N, defVal) { type = VAR_BOOL; }
};
class N2VariableINT : public N2AbstractSimple <int>
{
    friend OLS_Heap;
protected:
    N2VariableINT(string vName, uint N=1, int defVal=0) : N2AbstractSimple<int>(vName, N, defVal) { type = VAR_INT; }
};
class N2VariableLONG : public N2AbstractSimple <long>
{
    friend OLS_Heap;
protected:
    N2VariableLONG(string vName, uint N=1, long defVal=0) : N2AbstractSimple<long>(vName, N, defVal) { type = VAR_LONG; }
};
class N2VariableFLOAT : public N2AbstractSimple <float>
{
    friend OLS_Heap;
protected:
    N2VariableFLOAT(string vName, uint N=1, float defVal=0) : N2AbstractSimple<float>(vName, N, defVal) { type = VAR_FLOAT; }
};
class N2VariableSTR : public N2AbstractSimple <string>
{
    friend OLS_Heap;
protected:
    N2VariableSTR(string vName, uint N=1, string defVal="defVal") : N2AbstractSimple<string>(vName, N, defVal) { type = VAR_STRING; }
};


//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

template <class T> class N2AbstractTable : public N2BaseVariable
{
    friend OLS_Heap;
public:
    void setValue(uint row, uint column, T newValue);
    T getValue(uint row, uint column);
    N2BaseVariable* clone();
    ~N2AbstractTable();
protected:
    N2AbstractTable(string vName, uint numRows, uint numColumns, T defVal);
    N2AbstractTable(N2AbstractTable &data);
    vector< vector<T> > value;
private:

};

class N2VariableBoolTABLE : public N2AbstractTable <bool>
{
    friend OLS_Heap;
protected:
    N2VariableBoolTABLE(string vName, uint numRows=1, uint numColumns=1, bool defVal=false) : N2AbstractTable<bool>(vName, numRows, numColumns, defVal) { type = VAR_BOOLTABLE; }
};
class N2VariableIntTABLE : public N2AbstractTable <int>
{
    friend OLS_Heap;
protected:
    N2VariableIntTABLE(string vName, uint numRows=1, uint numColumns=1, int defVal=0) : N2AbstractTable<int>(vName, numRows, numColumns, defVal) { type = VAR_INTTABLE; }
};
class N2VariableLongTABLE : public N2AbstractTable <long>
{
    friend OLS_Heap;
protected:
    N2VariableLongTABLE(string vName, uint numRows=1, uint numColumns=1, long defVal=0) : N2AbstractTable<long>(vName, numRows, numColumns, defVal) { type = VAR_LONGTABLE; }
};
class N2VariableFloatTABLE : public N2AbstractTable <float>
{
    friend OLS_Heap;
protected:
    N2VariableFloatTABLE(string vName, uint numRows=1, uint numColumns=1, float defVal=0) : N2AbstractTable<float>(vName, numRows, numColumns, defVal) { type = VAR_FLOATTABLE; }
};
class N2VariableStringTABLE : public N2AbstractTable <string>
{
    friend OLS_Heap;
protected:
    N2VariableStringTABLE(string vName, uint numRows=1, uint numColumns=1, string defVal="defVal") : N2AbstractTable<string>(vName, numRows, numColumns, defVal) { type = VAR_STRINGTABLE; }
};


//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class N2User : public N2BaseVariable
{
    friend OLS_Heap;
public:
    void addCopyVar(N2BaseVariable* var);
    N2BaseVariable* getVar(string strHierarchy, TYPE_VAR t);
    N2User* clone();
    ~N2User();
protected:
    N2User(string vName) : N2BaseVariable(vName) { type = VAR_VMUSER; }
    vector<N2BaseVariable*>   vars;
private:
    N2BaseVariable* searchVar(string vName, TYPE_VAR t);
};

class N2VariableCreator
{
public:
    N2BaseVariable* createSimplex(TYPE_VAR type, string name = "simpleVar", unsigned int cnt = 1);
    N2BaseVariable* createTable(TYPE_VAR type, string name = "tableVar", int rows=1, int columns=1);
    N2BaseVariable* createUser(string name = "userVar");
    int getIntFromSimplexVar(N2BaseVariable* pVar);
};

#endif // N2BaseVariable_H

