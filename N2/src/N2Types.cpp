#include "N2Types.h"
#include "N2Register.h"

template <class T> N2AbstractSimple<T>::N2AbstractSimple(string vName, uint N, T defVal) : N2BaseVariable(vName)
{
    for (uint i=0;i<N;i++) value.push_back(defVal);
}

template <class T> N2AbstractSimple<T>::N2AbstractSimple(N2AbstractSimple &data) : N2BaseVariable(data.varName)
{
    for (uint i=0;i<data.value.size();i++) value.push_back(data.value.at(i));
    type = data.getType();
}

template <class T> void N2AbstractSimple<T>::setValue(uint index, T newValue)
{
    try {
        value.at(index) = newValue;
    } catch (const std::out_of_range &err) {
        cout << err.what() << endl;
    }
}

template <class T> T N2AbstractSimple<T>::getValue(uint index)
{
    try {
        return value.at(index);
    } catch (const std::out_of_range &err) {
        cout << err.what() << endl;
    }
}

template <class T> N2BaseVariable *N2AbstractSimple<T>::clone() {
    return N2Register::self()->getMemoryAllocator()->createCopyVar< N2AbstractSimple<T> >(*this);
}

template <class T> T N2AbstractSimple<T>::custom(N2BaseVariable *pVar)
{

}

template <class T> N2AbstractSimple<T>::~N2AbstractSimple() {
    cout << "N2AbstractSimple: " << varName << endl;
}

template class N2AbstractSimple<bool>;
template class N2AbstractSimple<int>;
template class N2AbstractSimple<long>;
template class N2AbstractSimple<float>;
template class N2AbstractSimple<string>;

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


template <class T> N2AbstractTable<T>::N2AbstractTable(string vName, uint N_Rows, uint N_Columns, T defVal) : N2BaseVariable(vName)
{
    for (uint i=0;i<N_Rows;i++) {
        vector<T> line;
        for (uint j=0;j<N_Columns;j++)
            line.push_back(defVal);
        value.push_back(line);
    }
}

template <class T> N2AbstractTable<T>::N2AbstractTable(N2AbstractTable &data) : N2BaseVariable(data.varName)
{
    for (uint i=0;i<data.value.size();i++) {
        vector<T> line;
        for (uint j=0;j<data.value.at(i).size();j++)
            line.push_back(data.getValue(i,j));
        value.push_back(line);
    }
    type = data.getType();
}

template <class T> void N2AbstractTable<T>::setValue(uint row, uint column, T newValue)
{
    try {
        value.at(row).at(column) = newValue;
    } catch (const std::out_of_range &err) {
        cout << err.what() << endl;
    }
}

template <class T> T N2AbstractTable<T>::getValue(uint row, uint column)
{
    try {
        return value.at(row).at(column);
    } catch (const std::out_of_range &err) {
        cout << err.what() << endl;
    }
}

template <class T> N2BaseVariable *N2AbstractTable<T>::clone() {
    return N2Register::self()->getMemoryAllocator()->createCopyVar< N2AbstractTable<T> >(*this);
}

template <class T> N2AbstractTable<T>::~N2AbstractTable() {
    cout << "N2AbstractTable: " << varName << endl;
}

template class N2AbstractTable<bool>;
template class N2AbstractTable<int>;
template class N2AbstractTable<long>;
template class N2AbstractTable<float>;
template class N2AbstractTable<string>;

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


void N2User::addCopyVar(N2BaseVariable *var) {
    vars.push_back(var->clone());
}

N2BaseVariable *N2User::getVar(string strHierarchy, TYPE_VAR t) {
    istringstream iss(strHierarchy);   vector<string> names;
    while (getline(iss, strHierarchy, '.'))    names.push_back(strHierarchy);

    if (names.size() == 0)  return 0;
    else if (names.size() == 1)  return searchVar(names[0], t);
    else {
        strHierarchy.clear();
        for (uint i=1;i<names.size();i++) {
            strHierarchy+=names[i];
            if (i!=names.size()-1) strHierarchy+='.';
        }
        N2BaseVariable* var = searchVar(names[0], VAR_VMUSER);
        if(var) return ((N2User*)var)->getVar(strHierarchy,t);
        else    return 0;
    }
}

N2User *N2User::clone() {
    N2User* clone = N2Register::self()->getMemoryAllocator()->createUserVar<N2User>(varName);
    for (uint i=0; i<vars.size();i++) {
        N2BaseVariable* var = vars.at(i);
        clone->addCopyVar(var->clone());
    }
    return clone;
}

N2User::~N2User() {
    cout << "N2UserType: " << varName << endl;
    for (uint i=0; i<vars.size(); i++)
        N2Register::self()->getMemoryAllocator()->releaseAnyVar<N2BaseVariable>(vars.at(i));
}

N2BaseVariable *N2User::searchVar(string vName, TYPE_VAR t) {
    N2BaseVariable* var;
    for (uint i=0; i<vars.size(); i++) {
        var = vars.at(i);
        if ((var->name() == vName) && (var->getType() == t)) return var;
    }
    return 0;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


N2BaseVariable *N2VariableCreator::createSimplex(TYPE_VAR type, string name, unsigned int cnt)
{
    switch (type) {
    case VAR_BOOL:   return N2Register::self()->getMemoryAllocator()->createSimpleVar<N2VariableBOOL>(name,cnt);
    case VAR_INT:    return N2Register::self()->getMemoryAllocator()->createSimpleVar<N2VariableINT>(name,cnt);
    case VAR_LONG:   return N2Register::self()->getMemoryAllocator()->createSimpleVar<N2VariableLONG>(name,cnt);
    case VAR_FLOAT:  return N2Register::self()->getMemoryAllocator()->createSimpleVar<N2VariableFLOAT>(name,cnt);
    case VAR_STRING: return N2Register::self()->getMemoryAllocator()->createSimpleVar<N2VariableSTR>(name,cnt);
    }
    return NULL;
}

N2BaseVariable *N2VariableCreator::createTable(TYPE_VAR type, string name, int rows, int columns)
{
    switch (type) {
    case VAR_BOOLTABLE:   return N2Register::self()->getMemoryAllocator()->createTableVar<N2VariableBoolTABLE>(name,rows,columns);
    case VAR_INTTABLE:    return N2Register::self()->getMemoryAllocator()->createTableVar<N2VariableIntTABLE>(name,rows,columns);
    case VAR_LONGTABLE:   return N2Register::self()->getMemoryAllocator()->createTableVar<N2VariableLongTABLE>(name,rows,columns);
    case VAR_FLOATTABLE:  return N2Register::self()->getMemoryAllocator()->createTableVar<N2VariableFloatTABLE>(name,rows,columns);
    case VAR_STRINGTABLE: return N2Register::self()->getMemoryAllocator()->createTableVar<N2VariableStringTABLE>(name,rows,columns);
    }
    return NULL;
}

N2BaseVariable *N2VariableCreator::createUser(string name)
{
    return N2Register::self()->getMemoryAllocator()->createUserVar<N2User>(name);
}

int N2VariableCreator::getIntFromSimplexVar(N2BaseVariable* pVar)
{
    int iRet = 0;
    N2VariableINT* tmp = (N2VariableINT*) createSimplex(VAR_INT);
    if (tmp)
        //iRet = tmp->custom(pVar);
    return iRet;
}
