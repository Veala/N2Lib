#include "src/include/N2Types.h"

template <class T> N2AbstractSimple<T>::N2AbstractSimple(string vName, uint N, T defVal) : N2AbstractType(vName)
{
    for (uint i=0;i<N;i++) value.push_back(defVal);
}

template <class T> N2AbstractSimple<T>::N2AbstractSimple(N2AbstractSimple &data) : N2AbstractType(data.varName)
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

template <class T> N2AbstractType *N2AbstractSimple<T>::clone() {
    return N2Register::self()->getMemoryAllocator()->createCopyVar< N2AbstractSimple<T> >(*this);
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


template <class T> N2AbstractTable<T>::N2AbstractTable(string vName, uint N_Rows, uint N_Columns, T defVal) : N2AbstractType(vName)
{
    for (uint i=0;i<N_Rows;i++) {
        vector<T> line;
        for (uint j=0;j<N_Columns;j++)
            line.push_back(defVal);
        value.push_back(line);
    }
}

template <class T> N2AbstractTable<T>::N2AbstractTable(N2AbstractTable &data) : N2AbstractType(data.varName)
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

template <class T> N2AbstractType *N2AbstractTable<T>::clone() {
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


void N2User::addCopyVar(N2AbstractType *var) {
    vars.push_back(var->clone());
}

N2AbstractType *N2User::getVar(string strHierarchy, N2AbstractType::types t) {
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
        N2AbstractType* var = searchVar(names[0], VMUSER);
        if(var) return ((N2User*)var)->getVar(strHierarchy,t);
        else    return 0;
    }
}

N2User *N2User::clone() {
    N2User* clone = N2Register::self()->getMemoryAllocator()->createUserVar<N2User>(varName);
    for (uint i=0; i<vars.size();i++) {
        N2AbstractType* var = vars.at(i);
        clone->addCopyVar(var->clone());
    }
    return clone;
}

N2User::~N2User() {
    cout << "N2UserType: " << varName << endl;
    for (uint i=0; i<vars.size(); i++)
        N2Register::self()->getMemoryAllocator()->releaseAnyVar<N2AbstractType>(vars.at(i));
}

N2AbstractType *N2User::searchVar(string vName, N2AbstractType::types t) {
    N2AbstractType* var;
    for (uint i=0; i<vars.size(); i++) {
        var = vars.at(i);
        if ((var->getName() == vName) && (var->getType() == t)) return var;
    }
    return 0;
}
