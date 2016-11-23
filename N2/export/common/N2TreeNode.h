// -*- mode:c++; coding:utf-8; -*-
///
/// \file		N2TreeNode.h
///
///	\brief 		Узел дерева
/// \details	Абстрактный узел дерева для использования
/// \details	в классе N2Tree и т.п. 
///
/// \copyright  ЗАО НТЦ "Модуль"
/// \author 	Чихичин Д.А.
///
/// \date 		23.04.2014
/// \version 	0.1
///  
///  История изменений:
///   02.06.14 - Полностью изменен класс, параметризирован
///	  24.06.14 - переписан, добавлен класс N2TreeNodeCreator
///

#pragma once

#include "N2Base.h"
#include "ITreeNode.h"
//#include "N2LiveObjectsPolicy.h"
#include <vector>
//#include "N2Register.h"

//using namespace TotalControl;

template<class T>
class N2TreeNodeCreator;



template<class T >
class N2TreeNode  :  public ITreeNode
{
	//USID usid_;
	friend N2TreeNodeCreator<T>;
	T data;
	INDEX index;
	std::vector<N2TreeNode<T>*> childs;
	//static N2ProjectSpecialInfo deviceInfo_;

public:
	N2TreeNode ():
		index(0)
	{clear();}
	~N2TreeNode () {
		clear();
		//return N2Register::self()<N2TreeNode<T> >::release(this);
	}
	void clear() { childs.clear(); }

	N2TreeNode<T>* getFirstChild(void){
		if(childs.empty())
			return NULL;
		index = 0;
		return childs[index];
	}

	/// Получить дочерний узел с идентичными данными
	/// 
	N2TreeNode<T>* getChild(T* t){
		if(childs.empty())
			return NULL;
		for(size_t i=0; i<childs.size(); i++) {
			if(*(childs[i]->getData()) == *t) {
				index = i;
				return childs[i];
			}
		}
		return NULL;
	}

	N2TreeNode<T>* getNextChild(void) {
		if(childs.empty())
			return NULL;
		index ++;
		if(index >= childs.size())
			return NULL;
		return childs[index];
	}

	T* getData(void) {
		return &data;
	}
	//
	void setData(T* t){
		data = *t;
	}
	// abstract
	const ITreeNode* getTaskNode(USID str_USID) const
	{
		//return T.getTaskNode(str_USID);
		return NULL;
	}

	//const N2ProjectSpecialInfo* getInfo(void)
	//{
	//	return &N2TreeNode<T>::deviceInfo_;
	//}

};

//template <class T>
//N2ProjectSpecialInfo  N2TreeNode<T>::deviceInfo_;

template<class T>
class N2TreeNodeCreator
{
public:
	/// Создает узел в динамической памяти
	N2TreeNode<T>* createNode(void)
	{
		//return N2Register::->create<N2TreeNode<T> >::create(EMPTY_STR);
		return new N2TreeNode<T>();
	}

	/// Вставляет дочерний элемент
	/// \return указатель на вставленный элемент
	N2TreeNode<T>* setChild(N2TreeNode<T>* pNodeParent, T* data)
	{
		//if(!pNodeParent->childs.empty() && data)
		//{// проверить что у детей другие данные
		//	for(size_t i=0; i< pNodeParent->childs.size(); i++) {
		//		if(*(pNodeParent->childs[i]->getData()) == *data)
		//			return NULL;
		//	}
		//}

		N2TreeNode<T>* temp = createNode();
		if(data)
			temp->data = *data;
		pNodeParent->childs.push_back(temp);
		return *(pNodeParent->childs.rbegin());
	}
};


