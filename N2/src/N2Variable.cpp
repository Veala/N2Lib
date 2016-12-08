// -*- mode:c++; coding:utf-8; -*-
///
/// \file		N2VariableSimplex.c
///
///	\brief
/// \details
///
/// \copyright  ЗАО НТЦ "Модуль"
/// \author 	Чихичин Д.А.
///
/// \date 		21.03.2014
/// \version 	0.1
///
///  История изменений:
///
///

#include "../export/common/N2Variable.h"
#include "../export/common/N2Register.h"
#include <stdlib.h> // нужно только для atoi()
#include <cmath>
#include "N2PHelper.h"

using namespace std;


std_string
N2BaseVariable::name(void)
{
    return name_;
}

TYPE_VAR
N2BaseVariable::type(void)
{
    return type_;
}

KIND_TYPE
N2BaseVariable::kind(void)
{
    return kind_;
}

std_string
N2BaseVariable::rename(std_string newName)
{
    std_string retVal = name_;
    name_ = newName;
    return retVal;
}

bool
N2BaseVariable::add(N2BaseVariable* addVar)
{
    return false;
}

//bool
//N2BaseVariable::set(N2BaseVariable* )
//{
//	return false;
//}

const COUNT
N2BaseVariable::dimension(void)
{
    return 1;
}

N2_ERRORS_OPCODES
N2BaseVariable::operation(N2_OPERATING_CODE code, N2BaseVariable* op2, N2BaseVariable* res)
{
    return N2EC_EMPTY;
}


void*
N2BaseVariable::getVoid(INDEX index)
{
    return NULL;
}

///////////////////////////////////

template<class T>
N2VariableSimplex<T>::N2VariableSimplex(const N2VariableSimplex<T> & copy):
    N2BaseVariable(copy.type(), copy.kind()),
    value_(NULL),
    count_(0)
{
    create(copy.name(), copy.dimension);
    value_ = copy.getValue();
}

template<class T>
N2VariableSimplex<T>::N2VariableSimplex(const TYPE_VAR typeName, std_string name, COUNT numElements):
    N2BaseVariable(typeName, KT_SIMPLEX),
    value_(NULL),
    count_(numElements)
{
    create(name, numElements);
}

template<class T>
N2VariableSimplex<T>::~N2VariableSimplex()
{
    N2Register::self()->getMemoryAllocator()->releaseVar<T>(value_, count_);
}

template<typename T>
void
N2VariableSimplex<T>::create(std_string name, COUNT count)
{
    value_ = N2Register::self()->getMemoryAllocator()->createVar<T>(name, count);
    rename(name);
}

template<class T>
bool
N2VariableSimplex<T>::set(T& value, INDEX index)
{
    if(index >= count_ ||
        type() == VAR_COMPOSITE)
            return false;
    value_[index] = value;
    return true;
}

template<class T>
bool
N2VariableSimplex<T>::set(N2BaseVariable* pVar, INDEX index)
{
    if(index >= count_)
        return false;
    value_[index] = custom(pVar);
    return true;
}

template<class T>
T*
N2VariableSimplex<T>::get(INDEX index)
{
    if(index >= count_)
        return NULL;
    return &value_[index];
}

template<class T>
T
N2VariableSimplex<T>::getValue(INDEX index)
{
    if(index >= count_)
        return T();
    return value_[index];
}

template<class T>
const COUNT
N2VariableSimplex<T>::dimension(void)
{
    return count_;
}

template<class T>
T&
N2VariableSimplex<T>::operator [] (int index)
{
    return *get((INDEX)index);
}

template<class T>
bool
N2VariableSimplex<T>::compare(N2_COMPARE_CODES code, N2BaseVariable* pVar)
{
    bool retVal = false;
    switch(code)
        {
        case N2COMPARE_EQU: // EQU
            if ((*get()) == custom(pVar)) retVal = true;
            break;
        case N2COMPARE_GR: // GR
            if ((*get())> custom(pVar))	retVal = true;
            break;
        case N2COMPARE_LS: // LS
            if ((*get())< custom(pVar))	retVal = true;
            break;
        case N2COMPARE_GREQ: // GREQ
            if ((*get())>= custom(pVar)) retVal=true;
            break;
        case N2COMPARE_LSEQ: // LSEQ
            if ((*get())<= custom(pVar)) retVal=true;
            break;
        case N2COMPARE_NEQ: // NEQ
            if ((*get())!= custom(pVar)) retVal=true;
            break;
        }
    return retVal;
}

template<class T>
bool
N2VariableSimplex<T>::setVoid(void* pVal, INDEX index)
{
    if (index >= count_ || !pVal)
        return false;
    value_[index] = *((T*)pVal);

    return true;
}

template<class T>
void*
N2VariableSimplex<T>::getVoid(INDEX index)
{
    if(index >= count_)
        return false;
     return (void*) &value_[index];
}


//template<typename T>
// N2BaseVariable*
//N2VariableSimplex<T>::toType(TYPE_VAR type)
//{
//	N2BaseVariable* retVal = NULL;
//	retVal = custom(
//	return retVal;
//}

///////////////////////////////////
N2BaseVariable*
N2VariableINT::clone(void)
{
    SIZE_N2 size = dimension();
    N2BaseVariable* retVal = new N2VariableINT(name(), size);
    for(INDEX i=0; i<size; i++) {
        int t = this->getValue(i);
        ((N2VariableINT*)retVal)->set(t, i);
    }
    return retVal;
}

N2BaseVariable*
N2VariableLONG::clone(void)
{
    N2BaseVariable* retVal = new N2VariableLONG(name(), dimension());
    //((N2VariableLONG*)retVal)->set(*value_);
    for(INDEX i=0; i<dimension(); i++) {
        long t = this->getValue(i);
        ((N2VariableLONG*)retVal)->set(t, i);
    }

    return retVal;
}

N2BaseVariable*
N2VariableBOOL::clone(void)
{
    N2BaseVariable* retVal = new N2VariableBOOL(name(), dimension());
    //((N2VariableBOOL*)retVal)->set(*value_);
    for(INDEX i=0; i<dimension(); i++) {
        bool t = this->getValue(i);
        ((N2VariableBOOL*)retVal)->set(t, i);
    }
    return retVal;
}

N2BaseVariable*
N2VariableSTR::clone(void)
{
    N2BaseVariable* retVal = new N2VariableSTR(name(), dimension());
    //((N2VariableSTR*)retVal)->set(*value_);
    for(INDEX i=0; i<dimension(); i++) {
        std_string t = this->getValue(i);
        ((N2VariableSTR*)retVal)->set(t, i);
    }
    return retVal;
}

N2BaseVariable*
N2VariableFLOAT::clone(void)
{
    N2BaseVariable* retVal = new N2VariableFLOAT(name(), dimension());
    //((N2VariableFLOAT*)retVal)->set(*value_);
    for(INDEX i=0; i<dimension(); i++) {
        float t = this->getValue(i);
        ((N2VariableFLOAT*)retVal)->set(t, i);
    }
    return retVal;
}

N2BaseVariable*
N2VariableTO::clone(void)
{
    N2BaseVariable* retVal = new N2VariableTO(name(), dimension());
    //((N2VariableTO*)retVal)->set(*value_);
    for(INDEX i=0; i<dimension(); i++) {
        TERNAR t = this->getValue(i);
        ((N2VariableTO*)retVal)->set(t, i);
    }
    return retVal;
}

///////////////////////////////////

template <class T>
N2Table<T>::N2Table(int rows, int columns) :
    tbl_(NULL)
{
    rows_ = rows;
    columns_ = columns;
	
    tbl_ = N2Register::self()->getMemoryAllocator()->createVar<T>(CT("table_variable"), rows_ * columns_);
    /*if(rows*columns > 1)
        tbl_ = new T[rows * columns];
    else
        tbl_ = new T;*/
}

template <class T>
N2Table<T>::~N2Table()
{
    if (tbl_)
        N2Register::self()->getMemoryAllocator()->releaseVar<T>(tbl_, rows_ * columns_);  //  delete[] tbl_;
}

template <class T>
bool
N2Table<T>::set(INDEX row, INDEX column, T value)
{
    if(row >= rows_ ||
        column >= columns_ ||
        tbl_ == NULL)
            return false;
    tbl_[row*columns_ + column] = value;
    return true;
}

//template <>
//bool
//N2Table<bool>::set(INDEX row, INDEX column, bool value)
//{
//	if(row >= rows_ ||
//		column >= columns_ ||
//		tbl_ == NULL)
//			return false;
//	return tbl_[row*columns_ + column] = value;
//}

template <class T>
T
N2Table<T>::get(INDEX row, INDEX column)
{
    if(row >= rows_ ||
        column >= columns_ ||
        tbl_ == NULL)
            return T();
    return tbl_[row*columns_ + column];
}

template <>
bool
N2Table<bool>::get(INDEX row, INDEX column)
{
    if(row >= rows_ ||
        column >= columns_ ||
        tbl_ == NULL)
            return false;
    return tbl_[row*columns_ + column];
}

template <class T>
SIZE_N2
N2Table<T>::rows(void)
{
    return rows_;
}

template <class T>
SIZE_N2
N2Table<T>::columns(void)
{
    return columns_;
}

template <class T>
bool
N2Table<T>::fill(T value)
{
    for(size_t i=0; i<rows_; i++) {
        for(size_t j=0; j<columns_; j++) {
            if(!set(i, j, value))
                return false;
        }
    }
    return true;
}


///////////////////////////////////

bool N2VariableComplex::add(N2BaseVariable* pVar)
{
    if(!pVar)
        return false;
    if(findChild(pVar->name()))
        return false;
    vecSimples.push_back(pVar);
    return true;
}


bool N2VariableComplex::add(N2VariableComplex* pVar)
{
    if(!pVar)
        return false;
    if(findChild(pVar->name()))
        return false;
    vecComplex.push_back(pVar);
    return true;
}


N2BaseVariable*
N2VariableComplex::findChild(std_string pureName)
{
    vector<N2BaseVariable*>::iterator it;
    vector<N2VariableComplex*>::iterator itx;
    for(it=vecSimples.begin(); it<vecSimples.end(); it++) {
        if((*it)->name() == pureName) {
            return (*it);
        }
    }
    for(itx=vecComplex.begin(); itx<vecComplex.end(); it++) {
        if((*itx)->name() == pureName) {
            return (*itx);
        }
    }
    return NULL;
}


N2BaseVariable*
N2VariableComplex::getNamed(std_string name)
{
    N2BaseVariable* retVal = NULL;
	
    ////разделение сложного имени
    //std_string label; // = cutPartName(name);
    //N2BaseVariable* pVar = NULL; //this->members;
    //N2VariableComplex* pCpx = this;
    //INDEX index = 0;
    //std_string pureName;
    //pVar = pCpx;

    //label = cutPartName(name);
    //pureName = clearName(label);
    //index = parseIndex(label);

    return retVal;
}

//template<class T>
//N2Table::N2Table<T>(int rows, int columns):
//	rows_(rows),
//	columns_(columns)
//{
//
//}
//
//template<class T>
//N2Table::~N2Table()
//{
//	delete [] tbl_;
//}
//
//template<class T>
//bool N2Table::set(int row, int column, T value)
//{
//	if(row >= rows_ ||
//		column >= columns_)
//			return false;
//	return tbl_[row*columns_+column] = value;
//}
////
//template<class T>
//T N2Table::get(int row, int column)
//{
//	if(row >= rows_ ||
//		column >= columns_)
//			return T();
//	return tbl_[row*columns_+column];
//}

//N2BaseVariable*
//N2VariableComplex::add(N2BaseVariable& pVar, INDEX index)
//{
//	Combo* pCmb = N2VariableSimplex::get(index);
//	if(!pCmb)
//		return NULL;
//	return pCmb->add(pVar);
//}
//
//
//
//N2BaseVariable*
//N2VariableComplex::getNamed(std_string name, INDEX index)
//{
//	N2BaseVariable* retVal = NULL;
//	Combo* pCmb = N2VariableSimplex::get(index);
//	if(!pCmb)
//		return NULL;
//	retVal = pCmb->getMember(name);
//	return retVal;
//}
//
////////////////////////////////////////////////////////// Combo
//N2BaseVariable* Combo::find(std_string name)
//{
//	for(size_t i=0; i<members.size(); i++)
//		if(members[i]->name() == name)
//			return members[i];
//	return NULL;
//}
//
////// не работает !!!!!!!!!!!!!!
//N2BaseVariable* Combo::getMember(std_string name)
//{
//	// разделение сложного имени
//	std_string label; // = cutPartName(name);
//	N2BaseVariable* pVar = NULL; //this->members;
//
//	INDEX index = 0;
//	std_string pureName;
//	Combo* curCombo = this;
//
//	do{
//	label = cutPartName(name);
//	pureName = clearName(label);
//	index = parseIndex(label);
//	pVar = curCombo->find(pureName);
//	if(pVar) {
//		if(name != EMPTY_STR) {
//			if(pVar->type() != VAR_COMPOSITE)
//				return NULL;
//			curCombo = (Combo*) pVar;
//		}
//	}
//	} while(name != EMPTY_STR && pVar != NULL);
//
//
//	return pVar;
//}
//
//
////// не работает !!!!!!!!!!!!!!
//N2BaseVariable* Combo::add(N2BaseVariable& pVar)
//{
//	N2BaseVariable* retVal = NULL;
//
//	//retVal = N2Register::self()->getMemoryAllocator()->create<N2BaseVariable>();
//	//members.push_back(retVal);
//
//	return retVal;;
//}
//
//
///// Зачистка имени от квадратных скобок
//std_string
//Combo::clearName(std_string name)
//{
//	std_string tempS(name);
//	std_string::size_type pos = tempS.find(CT("["));
//	if(pos != std_string::npos)
//		tempS.assign(tempS.begin(), tempS.begin() + pos);
//
//	return tempS;
//}
//
//INDEX
//Combo::parseIndex(std_string name)
//{
//	std_string tempS(name);
//	INDEX ind = 0;
//	std_string::size_type pos = name.find(CT("["));
//	if(pos != std_string::npos) {
//		tempS = name.substr(pos + 1);
//		pos = tempS.find(CT("]"));
//		if(pos == std_string::npos)
//			return NULL;
//		tempS.assign(tempS.begin(), tempS.begin() + pos);
//		ind = std_atoi(tempS.c_str());
//	}
//	return ind;
//}
//
//// Вырезает начало имени (до точки)
//// Возврат - вырезанное начало
//// в name возвращается остаток справа (без точки)
//std_string
//Combo::cutPartName(std_string& name)
//{
//	std_string tempS(name);
//	std_string::size_type pos = name.find(CT("."));
//
//	if(pos == std_string::npos)
//		name = EMPTY_STR;
//	else {
//		tempS.assign(name.begin(), name.begin() + pos);
//		name = name.substr(pos + 1);
//	}
//
//	return tempS;
//}

////
////bool N2VariableComplex::add(N2BaseVariable* pVar)
////{
////	if(!pVar)
////		return false;
////	vecIns.push_back(pVar);
////	return true;
////}
////
////N2BaseVariable* N2VariableComplex::getNamed(std_string name)
////{
////	 разделение сложного имени
////	std_string label; // = cutPartName(name);
////	N2BaseVariable* pVar = NULL; //this->members;
////	N2VariableComplex* pCpx = this;
////	INDEX index = 0;
////	std_string pureName;
////	pVar = pCpx;
////
////	label = cutPartName(name);
////	pureName = clearName(label);
////	index = parseIndex(label);
////	vp = ((N2VariableComplex*)pVar)->get(index);
////	if(!vp)
////		return NULL;
////
////	while(name != EMPTY_STR) {
////		label = cutPartName(name);
////		pureName = clearName(label);
////		index = parseIndex(label);
////		if(pVar->type() == VAR_COMPOSITE) {
////			pVar = vp->findForName(pureName);
////			if(!pVar)
////				return NULL;
////			if(pVar->dimension() <= index)
////				return NULL;
////			if(pVar->type() == VAR_COMPOSITE)
////				vp =  ((N2VariableComplex*)pVar)->get(index);
////		}
////		else {
////			if(name == EMPTY_STR)
////				return pVar;
////			else
////				return NULL;
////	}
////
////
////	do {
////	}while(1);
////
////
////	label = cutPartName(name);
////	pureName = clearName(label);
////	index = parseIndex(label);
////
////	pVar = vp->findForName(pureName);
////	if(!pVar)
////		return NULL;
////	if(name == EMPTY_STR) {
////		if(pVar->type() != VAR_COMPOSITE)
////			return NULL;
////		else
////			return pVar;
////	}
////
////
////
////	do{
////	/*label = cutPartName(name);
////	pureName = clearName(label);
////	index = parseIndex(label);*/
////	pVar = pCpx->find(pureName);
////	if(pVar) {
////		if(name != EMPTY_STR) {
////			if(pVar->type() != VAR_COMPOSITE)
////				return NULL;
////		if(pVar->type() == VAR_COMPOSITE)
////			pCpx = (N2VariableComplex*)pVar;
////		else
////			break;
////		label = cutPartName(name);
////		pureName = clearName(label);
////		index = parseIndex(label);
////		pVar = pCpx->find(pureName);
////		}
////	}
////	} while(name != EMPTY_STR && pVar != NULL);
////
////	return pVar;
////}
////
////
////N2BaseVariable* N2VariableComplex::find(std_string name)
////{
////	 Первое значение в векторе собственный указатель (нулевой), не проверяется
////	for(size_t i=1; i<values.size(); i++) {
////		if(!values[i].ptr)
////			return NULL;
////		if(values[i].ptr->name() == name)
////			return values[i].ptr;
////	}
////	return NULL;
////}
////
////
//// Зачистка имени от квадратных скобок
////std_string
////N2VariableComplex::clearName(std_string name)
////{
////	std_string tempS(name);
////	std_string::size_type pos = tempS.find(CT("["));
////	if(pos != std_string::npos)
////		tempS.assign(tempS.begin(), tempS.begin() + pos);
////
////	return tempS;
////}
////
////INDEX
////N2VariableComplex::parseIndex(std_string name)
////{
////	std_string tempS(name);
////	INDEX ind = 0;
////	std_string::size_type pos = name.find(CT("["));
////	if(pos != std_string::npos) {
////		tempS = name.substr(pos + 1);
////		pos = tempS.find(CT("]"));
////		if(pos == std_string::npos)
////			return NULL;
////		tempS.assign(tempS.begin(), tempS.begin() + pos);
////		ind = std_atoi(tempS.c_str());
////	}
////	return ind;
////}
////
//// Вырезает начало имени (до точки)
//// Возврат - вырезанное начало
//// в name возвращается остаток справа (без точки)
////std_string
////N2VariableComplex::cutPartName(std_string& name)
////{
////	std_string tempS(name);
////	std_string::size_type pos = name.find(CT("."));
////
////	if(pos == std_string::npos)
////		name = EMPTY_STR;
////	else {
////		tempS.assign(name.begin(), name.begin() + pos);
////		name = name.substr(pos + 1);
////	}
////
////	return tempS;
////}



N2_ERRORS_OPCODES
N2VariableINT::operation(N2_OPERATING_CODE code, N2BaseVariable* op2, N2BaseVariable* res)
{
    if(res)
        if(res->type() != VAR_INT)
            return N2EC_BAD_OPERAND_TYPE;

    N2VariableINT* retVal = (res == NULL) ? this : (N2VariableINT*)res;
	
    switch(code) {
        case N2OC_DEC:
        case N2OC_INC:
        case N2OC_LOG_10:
        case N2OC_LOG:
        case N2OC_NOT: {
            //retVal = (N2VariableINT*)clone();
            int value = getValue();
            if(code == N2OC_DEC) {
                value--;
                retVal->set(value) ;
            }
            else if(code == N2OC_INC) {
                value ++;
                retVal->set(value) ;
            }
            else if(N2OC_LOG_10) {
                value =(int)log10(value);
                retVal->set(value);
            }
            else if(N2OC_LOG) {
                value = (int)log(value);
                retVal->set(value);
            }
            else if(N2OC_NOT) {
                value = ~value;
                retVal->set(value);
            }
                       }
            return N2EC_SUCCESS;
    }
	
    if(!op2)
        return N2EC_NULL_OPERAND;
    int i2 = custom(op2);
    int temp = *(this->get());
    switch(code) {
        case N2OC_INIT: temp = i2; break;
        case N2OC_PLUS: temp += i2; break;
        case N2OC_MINUS: temp -= i2; break;
        case N2OC_DIV: temp = temp / (i2); break;
        case N2OC_AND: temp &= i2; break;
        case N2OC_OR: temp |= i2; break;
        case N2OC_XOR: temp ^= i2; break;
        case N2OC_MULT: temp *= i2; break;
        case N2OC_SHIFT_LEFT: temp = temp << (i2); break;
        case N2OC_SHIFT_RIGTH: temp = temp >> (i2); break;
        case N2OC_MIN: temp = (temp > (i2) ) ? temp :  (i2); break;
        case N2OC_MAX: temp = (temp < (i2) ) ? temp :  (i2); break;
        case N2OC_MOD: temp = temp % (i2); break;
        case N2OC_NOT: temp = ~temp; break;
        default:
            return N2EC_INAPPLICABLE_CODE;
    }

    retVal->set(temp);
    return N2EC_SUCCESS;
}



int
N2VariableINT::custom(N2BaseVariable* pVar)
{
    int retVal = 0;

    if(!pVar)
        return retVal;

    switch(pVar->type()) {
        case VAR_INT: retVal = *(((N2VariableINT*)pVar)->get()); break;
        case VAR_FLOAT: retVal = (int)*(((N2VariableFLOAT*)pVar)->get()); break;
        case VAR_LONG: retVal = *(((N2VariableLONG*)pVar)->get()); break;
        case VAR_STRING: {
             std_string s = *(((N2VariableSTR*)pVar)->get());
             PHelper help;
             retVal = help.StoI(s);
            } break;
        case VAR_BOOL: retVal = (*(((N2VariableBOOL*)pVar)->get()))?1:0; break;
        case VAR_TERNAR: retVal = (int) (((N2VariableTO*)pVar)->get()); break;
    }

    return retVal;
}

//bool
//N2VariableINT::compare(N2_COMPARE_CODES code, N2BaseVariable* pVar)
//{
//	bool retVal = false;
//	switch(code)
//		{
//		case N2COMPARE_EQU: // EQU
//			if ((*get()) == custom(pVar)) retVal = true;
//			break;
//		case N2COMPARE_GR: // GR
//			if ((*get())> custom(pVar))	retVal = true;
//			break;
//		case N2COMPARE_LS: // LS
//			if ((*get())< custom(pVar))	retVal = true;
//			break;
//		case N2COMPARE_GREQ: // GREQ
//			if ((*get())>= custom(pVar)) retVal=true;
//			break;
//		case N2COMPARE_LSEQ: // LSEQ
//			if ((*get())<= custom(pVar)) retVal=true;
//			break;
//		case N2COMPARE_NEQ: // NEQ
//			if ((*get())!= custom(pVar)) retVal=true;
//			break;
//		}
//	return retVal;
//}

//N2BaseVariable*
//N2VariableINT::toType(TYPE_VAR type)
//{
//	N2BaseVariable* pVar = NULL;
//
//	switch(type) {
//		case VAR_INT: retVal = *(((N2VariableINT*)pVar)->get()); break;
//		case VAR_FLOAT: retVal = *(((N2VariableFLOAT*)pVar)->get()); break;
//		case VAR_LONG: retVal = *(((N2VariableLONG*)pVar)->get()); break;
//		case VAR_STRING: {
//			 std_string s = *(((N2VariableSTR*)pVar)->get());
//			 PHelper help;
//			 retVal = help.StoI(s);
//			} break;
//		case VAR_BOOL: retVal = (*(((N2VariableFLOAT*)pVar)->get()))?1:0; break;
//	}
//
//	return pVar;
//}

N2_ERRORS_OPCODES
N2VariableLONG::operation(N2_OPERATING_CODE code, N2BaseVariable* op2, N2BaseVariable* res)
{
    if(res)
        if(res->type() != VAR_LONG)
            return N2EC_BAD_OPERAND_TYPE;

    N2VariableLONG* retVal = (res == NULL) ? this : (N2VariableLONG*)res;

    switch(code) {
        case N2OC_DEC:
        case N2OC_INC:
        case N2OC_LOG_10:
        case N2OC_LOG:
        case N2OC_NOT: {
            retVal = (N2VariableLONG*)clone();
            if(code == N2OC_DEC)
                (*retVal->get()) -- ;
            else if(code == N2OC_INC)
                (*retVal->get()) ++ ;
            else if(N2OC_LOG_10)
                (log10l(*retVal->get()));
            else if(N2OC_LOG)
                (logl(*retVal->get()));
            else if(N2OC_NOT) {
                long x = ~(*retVal->get());
                (retVal->set(x));
            }
                       }
            return N2EC_SUCCESS;
    }
	
    if(!op2)
        return N2EC_NULL_OPERAND;
    long i2 = custom(op2);
    long temp = *(this->get());
    switch(code) {
        case N2OC_INIT: temp = i2; break;
        case N2OC_PLUS: temp += i2; break;
        case N2OC_MINUS: temp -= i2; break;
        case N2OC_DIV: temp = temp / (i2); break;
        case N2OC_AND: temp &= i2; break;
        case N2OC_OR: temp |= i2; break;
        case N2OC_XOR: temp ^= i2; break;
        case N2OC_MULT: temp *= i2; break;
        case N2OC_SHIFT_LEFT: temp = temp << (i2); break;
        case N2OC_SHIFT_RIGTH: temp = temp >> (i2); break;
        case N2OC_MIN: temp = (temp > (i2) ) ? temp :  (i2); break;
        case N2OC_MAX: temp = (temp < (i2) ) ? temp :  (i2); break;
        case N2OC_MOD: temp = temp % (i2); break;
        case N2OC_NOT: temp = ~temp; break;
        default:
            return N2EC_INAPPLICABLE_CODE;
    }

    retVal->set(temp);
    return N2EC_SUCCESS;
}

long
N2VariableLONG::custom(N2BaseVariable* pVar)
{
    long retVal = 0;

    switch(pVar->type()) {
        case VAR_INT: retVal = *(((N2VariableINT*)pVar)->get()); break;
        case VAR_FLOAT: retVal = (long) *(((N2VariableFLOAT*)pVar)->get()); break;
        case VAR_LONG: retVal = *(((N2VariableLONG*)pVar)->get()); break;
        case VAR_STRING: {
             std_string s = *(((N2VariableSTR*)pVar)->get());
             PHelper help;
             retVal = help.StoI(s);
            } break;
        case VAR_BOOL: retVal = (*(((N2VariableBOOL*)pVar)->get()))?1:0; break;
        case VAR_TERNAR: retVal = (long) (((N2VariableTO*)pVar)->get()); break;
    }

    return retVal;
}


N2_ERRORS_OPCODES
N2VariableBOOL::operation(N2_OPERATING_CODE code, N2BaseVariable* op2, N2BaseVariable* res)
{
    if(res)
        if(res->type() != VAR_BOOL)
            return N2EC_BAD_OPERAND_TYPE;

    N2VariableBOOL* retVal = (res == NULL) ? this : (N2VariableBOOL*)res;

    switch(code) {
        case N2OC_DEC:
        case N2OC_INC:
        case N2OC_LOG_10:
        case N2OC_LOG:
        case N2OC_NOT:
            if(code == N2OC_NOT) {
                bool x = !(*retVal->get());
                retVal->set(x);
            }
            return N2EC_SUCCESS;
            break;
    }
	
    if(!op2)
        return N2EC_NULL_OPERAND;
    bool i2 = custom(op2);
    bool temp = *(this->get());
    switch(code) {
        case N2OC_INIT: temp = i2; break;
        case N2OC_AND: temp = temp && i2; break;
        case N2OC_OR: temp = temp || i2; break;
        case N2OC_XOR: temp = (temp == i2) ? false : true; break;
        case N2OC_NOT: temp = !i2; break;
        default:
            return N2EC_INAPPLICABLE_CODE;
    }

    retVal->set(temp);
    return N2EC_SUCCESS;
}

bool
N2VariableBOOL::custom(N2BaseVariable* pVar)
{
    bool retVal = 0;

    if(!pVar)
        return false;

    switch(pVar->type()) {
        case VAR_INT: retVal = (*(((N2VariableINT*)pVar)->get()) > 0) ? true : false ;
            break;
        case VAR_FLOAT: retVal = (*(((N2VariableFLOAT*)pVar)->get()) > 0) ? true : false;
            break;
        case VAR_LONG: retVal = (*(((N2VariableLONG*)pVar)->get()) > 0 ) ? true : false;
            break;
        case VAR_STRING: {
             std_string s = *(((N2VariableSTR*)pVar)->get());
             PHelper help;
             help.AddFirst("TRUE", 1);
             help.Add("FALSE", 0);
             help.Add("YES", 1);
             help.Add("NO", 0);
             help.Add("+", 1);
             help.Add("-", 0);
             if(help.WhatIs(s) == AHE_TOKEN ||
                 help.WhatIs(s) == AHE_DIGIT)
                    retVal = !! help.GetValue();
             else
                retVal = false;
            } break;
        case VAR_BOOL: retVal = !!(*(((N2VariableBOOL*)pVar)->get())); break;
        case VAR_TERNAR: retVal = (((N2VariableTO*)pVar)->getValue() == TERNAR_YES)?true:false; break;
    }

    return retVal;
}

N2_ERRORS_OPCODES
N2VariableSTR::operation(N2_OPERATING_CODE code, N2BaseVariable* op2, N2BaseVariable* res)
{
    if(res)
        if(res->type() != VAR_STRING)
            return N2EC_BAD_OPERAND_TYPE;

    N2VariableSTR* retVal = (res == NULL) ? this : (N2VariableSTR*)res;

    if(!op2)
        return N2EC_NULL_OPERAND;
    std_string i2 = custom(op2);
    std_string temp = this->getValue();
    switch(code) {
        case N2OC_INIT: temp = i2; break;
        case N2OC_PLUS: temp += i2; break;
        case N2OC_MIN: temp = (temp.size() > i2.size() ) ? temp : i2; break;
        case N2OC_MAX: temp = (temp.size() < i2.size() ) ? temp : i2; break;
        default:
            return N2EC_INAPPLICABLE_CODE;
    }

    retVal->set(temp);
    return N2EC_SUCCESS;
}

std_string
N2VariableSTR::custom(N2BaseVariable* pVar)
{
    std_string retVal = EMPTY_STR;
    char buff[1024];
	
    if(!pVar)
        return retVal;

    switch(pVar->type()) {
        case VAR_INT:
            sprintf(buff, "%d", ((N2VariableINT*)pVar)->getValue());
            retVal = buff;
            break;
        case VAR_LONG:
            sprintf(buff, "%d", ((N2VariableLONG*)pVar)->getValue());
            retVal = buff;
            break;
        case VAR_FLOAT:
            sprintf(buff,"%f",  ((N2VariableFLOAT*)pVar)->getValue());
            retVal = buff;
            break;
        case VAR_STRING:
            retVal = ((N2VariableSTR*)pVar)->getValue();
            break;
        case VAR_BOOL:
            retVal = (((N2VariableBOOL*)pVar)->getValue()) ? CT("TRUE") : CT("FALSE");
            break;
        case VAR_TERNAR:
            switch (((N2VariableTO*)pVar)->getValue()) {
                case TERNAR_YES: retVal =  CT("YES"); break;
                case TERNAR_NO: retVal =  CT("NO"); break;
                default: retVal = CT("DISABLE");
            }
            break;
    }
	
    return retVal;
}

///// FLOAT
N2_ERRORS_OPCODES
N2VariableFLOAT::operation(N2_OPERATING_CODE code, N2BaseVariable* op2, N2BaseVariable* res)
{
    if(res)
        if(res->type() != VAR_FLOAT)
            return N2EC_BAD_OPERAND_TYPE;

    N2VariableFLOAT* retVal = (res == NULL) ? this : (N2VariableFLOAT*)res;
    float temp = *(this->get());

    switch(code) {
        case N2OC_DEC:
        case N2OC_INC:
            return N2EC_INAPPLICABLE_CODE;
        case N2OC_LOG_10:
        case N2OC_LOG: {
            if(N2OC_LOG_10)
                (temp = log10(*retVal->get()));
            else if(N2OC_LOG)
                (temp = log(*retVal->get()));
                       }
            retVal->set(temp);
            return N2EC_SUCCESS;
    }
	
    if(!op2)
        return N2EC_NULL_OPERAND;
    float i2 = custom(op2);
    switch(code) {
        case N2OC_INIT: temp = i2; break;
        case N2OC_PLUS: temp += i2; break;
        case N2OC_MINUS: temp -= i2; break;
        case N2OC_DIV: temp = temp / (i2); break;
        case N2OC_MULT: temp *= i2; break;
        case N2OC_MIN: temp = (temp > (i2) ) ? temp :  (i2); break;
        case N2OC_MAX: temp = (temp < (i2) ) ? temp :  (i2); break;
        default:
            return N2EC_INAPPLICABLE_CODE;
    }

    retVal->set(temp);
    return N2EC_SUCCESS;
}

float
N2VariableFLOAT::custom(N2BaseVariable* pVar)
{
    float retVal = 0;
    if(!pVar)
        return (0.0);

    switch(pVar->type()) {
        case VAR_INT: retVal = (float) *(((N2VariableINT*)pVar)->get()); break;
        case VAR_FLOAT: retVal = *(((N2VariableFLOAT*)pVar)->get()); break;
        case VAR_LONG: retVal = (float) *(((N2VariableLONG*)pVar)->get()); break;
        case VAR_STRING: {
             std_string s = *(((N2VariableSTR*)pVar)->get());
             PHelper help;
             help.WhatIs(s);
             retVal = help.GetValueFloat();
            } break;
        case VAR_BOOL: retVal = (float) ((*(((N2VariableBOOL*)pVar)->get()))? 1 : 0); break;
        case VAR_TERNAR: retVal = 0.0; break;
    }

    return retVal;
}


N2_ERRORS_OPCODES
N2VariableTO::operation(N2_OPERATING_CODE code, N2BaseVariable* op2, N2BaseVariable* res)
{
    if(res)
        if(res->type() != VAR_TERNAR)
            return N2EC_BAD_OPERAND_TYPE;

    N2VariableTO* retVal = (res == NULL) ? this : (N2VariableTO*)res;

    switch(code) {
        case N2OC_DEC:
        case N2OC_INC:
        case N2OC_LOG_10:
        case N2OC_LOG:
            return N2EC_INAPPLICABLE_CODE;
    }
	
    if(!op2)
        return N2EC_NULL_OPERAND;

    TERNAR i2 = custom(op2);
    TERNAR temp = *(this->get());
	
    switch(code) {
        case N2OC_INIT: temp = i2; break;
        default:
            return N2EC_INAPPLICABLE_CODE;
    }

    retVal->set(temp);
    return N2EC_SUCCESS;
}

TERNAR
N2VariableTO::custom(N2BaseVariable* pVar)
{
    TERNAR retVal(TERNAR_DISABLE);
    int temp = 0;

    switch(pVar->type()) {
        case VAR_INT:
            temp = *(((N2VariableINT*)pVar)->get());
            break;
        case VAR_FLOAT: //retVal = (*(((N2VariableFLOAT*)pVar)->get()) > 0) ? true : false;
            return retVal;
            break;
        case VAR_LONG:
            temp = (int)(*(((N2VariableLONG*)pVar)->get()) > 0 ) ;
            break;
        case VAR_STRING: {
             std_string s = *(((N2VariableSTR*)pVar)->get());
             PHelper help;
             help.AddFirst("TRUE", 1);
             help.Add("FALSE", 0);
             help.Add("YES", 1);
             help.Add("NO", 0);
             help.Add("DISABLE", 2);
             help.Add("DIS", 2);
             help.Add("1", 1);
             help.Add("0", 0);
             help.Add("-", 2);
             if(help.WhatIs(s) == AHE_TOKEN ||
                 help.WhatIs(s) == AHE_DIGIT) {
				
                temp = help.GetValue();
             }
             else
                return retVal;
            } break;
        case VAR_BOOL:
            retVal = (*(((N2VariableBOOL*)pVar)->get())) ? TERNAR_YES : TERNAR_NO;
            return retVal;
        case VAR_TERNAR:
            retVal = (*(((N2VariableTO*)pVar)->get()));
            return retVal;
    }

    switch((TERNAR) temp) {
        case TERNAR_YES: retVal = TERNAR_YES; break;
        case TERNAR_NO: retVal = TERNAR_NO; break;
        default: retVal = TERNAR_DISABLE;
    }

    return retVal;
}



//////////////

N2BaseVariable*
N2VariableCreator::createSimplex(TYPE_VAR type, string name, int cnt)
{

    N2BaseVariable* retVal = NULL;
    //N2VariableSimplex<T> tmp = new N2VariableSimplex<T> (name, cnt);
    switch(type) {
        case VAR_INT:
            {
                N2VariableINT* tmpVar = new N2VariableINT(name, cnt);
                if (tmpVar)
                    retVal = static_cast<N2BaseVariable*>(tmpVar);
            }
            break;
        case VAR_LONG:
            {
                N2VariableLONG* tmpVar = new N2VariableLONG(name, cnt);
                if (tmpVar)
                    retVal = static_cast<N2BaseVariable*>(tmpVar);
            }
            break;
        case VAR_STRING:
            {
                N2VariableSTR* tmpVar = new N2VariableSTR(name, cnt);
                if (tmpVar)
                    retVal = static_cast<N2BaseVariable*>(tmpVar);
            }
            break;
        case VAR_BOOL:
            {
                N2VariableBOOL* tmpVar = new N2VariableBOOL(name, cnt);
                if (tmpVar)
                    retVal = static_cast<N2BaseVariable*>(tmpVar);
            }
            break;
        case VAR_FLOAT:
            {
                N2VariableFLOAT* tmpVar = new N2VariableFLOAT(name, cnt);
                if (tmpVar)
                    retVal = static_cast<N2BaseVariable*>(tmpVar);
            }
            break;
        case VAR_TERNAR:
            {
                N2VariableTO* tmpVar = new N2VariableTO(name, cnt);
                if (tmpVar)
                    retVal = static_cast<N2BaseVariable*>(tmpVar);
            }
            break;
    }
    return retVal;
}


N2BaseVariable*
N2VariableCreator::createTable(TYPE_VAR el_type, string name, int rows, int columns)
{

    N2BaseVariable* retVal = NULL;
    //N2VariableSimplex<T> tmp = new N2VariableSimplex<T> (name, cnt);
    if (rows > 0 && columns > 0)
        switch(el_type) {
            case VAR_INT:
                retVal = (N2BaseVariable*) N2VariableIntTABLE(name, rows, columns).clone();
                break;
            case VAR_LONG:
                retVal = (N2BaseVariable*) N2VariableLongTABLE(name, rows, columns).clone();
                break;
            case VAR_STRING:
                retVal = (N2BaseVariable*) N2VariableStringTABLE(name, rows, columns).clone();
                break;
            case VAR_BOOL:
                retVal = (N2BaseVariable*) N2VariableBoolTABLE(name, rows, columns).clone();
                break;
            case VAR_FLOAT:
                retVal = (N2BaseVariable*) N2VariableFloatTABLE(name, rows, columns).clone();
                break;
            case VAR_TERNAR:
                retVal = (N2BaseVariable*) N2VariableTernarTABLE(name, rows, columns).clone();
                break;

        }
    return retVal;
}

int
N2VariableCreator::getIntFromSimplexVar(N2BaseVariable* pVar)
{
    int iRet = 0;
    N2VariableINT* tmp = (N2VariableINT*) createSimplex(VAR_INT);
    if (tmp)
        iRet = tmp->custom(pVar);
    return iRet;
}

template <class T>
N2BaseVariable*
N2VariableTABLE<T>::clone()
{
    N2BaseVariable* retVal = NULL;
    retVal = new N2VariableTABLE<T>(name(), tbl.rows(), tbl.columns(), typeElement_);
    INDEX raw = tbl.rows();
    INDEX col = tbl.columns();
    for(INDEX i=0; i<raw; i++)
        for(INDEX j=0; j<col; j++) {
            ((N2VariableTABLE<T> *) retVal)->tbl.set(i, j, tbl.get(i, j));
    }
    return retVal;
}
