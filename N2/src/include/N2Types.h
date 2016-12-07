#ifndef N2AbstractType_H
#define N2AbstractType_H

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <stdexcept>
#include "N2LiveObjectsPolicy.h"
#include "N2Register.h"

using namespace std;

class N2AbstractType
{
public:
    typedef unsigned int uint;
    enum types {
        BOOL,     BOOLTABLE,
        INT,      INTTABLE,
        LONG,     LONGTABLE,
        FLOAT,    FLOATTABLE,
        STRING,   STRINGTABLE,
        VMUSER
    };
    void setName(string newName)    { varName = newName; }
    const string getName()          { return varName; }
    types getType()                 { return type; }
    virtual N2AbstractType* clone() = 0;
    virtual ~N2AbstractType() { cout << "N2AbstractType: " << varName << endl; }
protected:
    N2AbstractType(string vName)    { varName = vName; }
    string varName;
    types type;
private:

};

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

template <class T> class N2AbstractSimple : public N2AbstractType
{
    friend OLS_Heap;
public:
    void setValue(uint index, T newValue);
    T getValue(uint index);
    N2AbstractType* clone();
    ~N2AbstractSimple();
protected:
    N2AbstractSimple(string vName, uint N, T defVal);
    N2AbstractSimple(N2AbstractSimple &data);
    vector<T> value;
private:

};

class N2Bool : public N2AbstractSimple <bool>
{
    friend OLS_Heap;
protected:
    N2Bool(string vName, uint N=1, bool defVal=false) : N2AbstractSimple<bool>(vName, N, defVal) { type = BOOL; }
};
class N2Int : public N2AbstractSimple <int>
{
    friend OLS_Heap;
protected:
    N2Int(string vName, uint N=1, int defVal=0) : N2AbstractSimple<int>(vName, N, defVal) { type = INT; }
};
class N2Long : public N2AbstractSimple <long>
{
    friend OLS_Heap;
protected:
    N2Long(string vName, uint N=1, long defVal=0) : N2AbstractSimple<long>(vName, N, defVal) { type = LONG; }
};
class N2Float : public N2AbstractSimple <float>
{
    friend OLS_Heap;
protected:
    N2Float(string vName, uint N=1, float defVal=0) : N2AbstractSimple<float>(vName, N, defVal) { type = FLOAT; }
};
class N2String : public N2AbstractSimple <string>
{
    friend OLS_Heap;
protected:
    N2String(string vName, uint N=1, string defVal="defVal") : N2AbstractSimple<string>(vName, N, defVal) { type = STRING; }
};

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

template <class T> class N2AbstractTable : public N2AbstractType
{
    friend OLS_Heap;
public:
    void setValue(uint row, uint column, T newValue);
    T getValue(uint row, uint column);
    N2AbstractType* clone();
    ~N2AbstractTable();
protected:
    N2AbstractTable(string vName, uint numRows, uint numColumns, T defVal);
    N2AbstractTable(N2AbstractTable &data);
    vector< vector<T> > value;
private:

};

class N2BoolTable : public N2AbstractTable <bool>
{
    friend OLS_Heap;
protected:
    N2BoolTable(string vName, uint numRows=1, uint numColumns=1, bool defVal=false) : N2AbstractTable<bool>(vName, numRows, numColumns, defVal) { type = BOOLTABLE; }
};
class N2IntTable : public N2AbstractTable <int>
{
    friend OLS_Heap;
protected:
    N2IntTable(string vName, uint numRows=1, uint numColumns=1, int defVal=0) : N2AbstractTable<int>(vName, numRows, numColumns, defVal) { type = INTTABLE; }
};
class N2LongTable : public N2AbstractTable <long>
{
    friend OLS_Heap;
protected:
    N2LongTable(string vName, uint numRows=1, uint numColumns=1, long defVal=0) : N2AbstractTable<long>(vName, numRows, numColumns, defVal) { type = LONGTABLE; }
};
class N2FloatTable : public N2AbstractTable <float>
{
    friend OLS_Heap;
protected:
    N2FloatTable(string vName, uint numRows=1, uint numColumns=1, float defVal=0) : N2AbstractTable<float>(vName, numRows, numColumns, defVal) { type = FLOATTABLE; }
};
class N2StringTable : public N2AbstractTable <string>
{
    friend OLS_Heap;
protected:
    N2StringTable(string vName, uint numRows=1, uint numColumns=1, string defVal="defVal") : N2AbstractTable<string>(vName, numRows, numColumns, defVal) { type = STRINGTABLE; }
};

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class N2User : public N2AbstractType
{
    friend OLS_Heap;
public:
    void addCopyVar(N2AbstractType* var);
    N2AbstractType* getVar(string strHierarchy, types t);
    N2User* clone();
    ~N2User();
protected:
    N2User(string vName) : N2AbstractType(vName) { type = VMUSER; }
    vector<N2AbstractType*>   vars;
private:
    N2AbstractType* searchVar(string vName, types t);
};

#endif // N2AbstractType_H
