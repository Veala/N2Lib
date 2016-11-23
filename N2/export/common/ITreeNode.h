// -*- mode:c++; coding:utf-8; -*-
///
/// \file		ITreeNode.h
///
///	\brief 		Интерфейс узла дерева
/// \details	
///
/// \copyright  ЗАО НТЦ "Модуль"
/// \author 	Чихичин Д.А.
///
/// \date 		21.03.2014
/// \version 	0.1
///  
///  �История изменений:
///  
///

#pragma once

#include "isolator.h"
#include "N2ProjectSpecInfo.h"


//struct N2ProjectSpecialInfo;

/// Базовый элемент узла дерева
struct ITreeNode {
	
	/// Получить узел по его уникальному строковому идентификатору
	/// \param str_USID - уникальный строковый идентификатор узла
	/// \return Возвращает найденный узел или NULL
	virtual const ITreeNode* getTaskNode(USID str_USID) const = 0;	

	/// Получить обобщенную информацию о загруженном проекте и т.п.	
	/// \return специальную информацию о загруженном проекте
	//virtual const N2ProjectSpecialInfo* getInfo(void) = 0;

};

