#include "src/include/N2Types.h"

template <class T> N2AbstractSimple<T>::N2AbstractSimple(string vName, T defVal, uint N) : N2AbstractType(vName)
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

template class N2AbstractSimple<bool>;
template class N2AbstractSimple<int>;
template class N2AbstractSimple<long>;
template class N2AbstractSimple<float>;
template class N2AbstractSimple<string>;

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

template <class T> N2AbstractTable<T>::N2AbstractTable(string vName, T defVal, uint N_Rows, uint N_Columns) : N2AbstractType(vName)
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

template class N2AbstractTable<bool>;
template class N2AbstractTable<int>;
template class N2AbstractTable<long>;
template class N2AbstractTable<float>;
template class N2AbstractTable<string>;

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
