// -*- mode:c++; coding:utf-8; -*-
///
/// \file		N2XMLF.h
///
///	\brief 		Формат типа XML
/// \details	Формат для представления разобранного кода и т.п.
///
/// \copyright  ЗАО НТЦ "Модуль"
/// \author 	Чихичин Д.А.
///
/// \date 		29.04.2014
/// \version 	0.1
///  
///  История изменений:
///  
///

#pragma once

#include "isolator.h"
#include <vector>

enum TAG
{
	N2_XMLFTAG_BEGIN,
	N2_XMLFTAG_END,
	N2_XMLFTAG_SINGLE,
	N2_XMLFTAG_ERROR
};

struct ATTR
{
	ATTR(){}
	ATTR(std_string atr, std_string val):
		attribute(atr),
		value(val)
	{}
	std_string attribute;
	std_string value;
};

struct XMLF
{
	TAG tag;
	std::vector<ATTR> attr;
	std_string nametag;
	std_string body;
	//
	XMLF() : 
		nametag(""),
		body(""),
		tag(N2_XMLFTAG_ERROR)
	{}
	XMLF(std_string init):
		nametag(init),
		body(""),
		tag(N2_XMLFTAG_ERROR)
	{}
	//
	XMLF& operator = (XMLF& op){
		if(&op == this)
			return *this;
		tag = op.tag;
		nametag = op.nametag;
		body = op.body;
		attr.clear();
		for(size_t i=0; i<op.attr.size(); i++)
			attr.push_back(op.attr[i]);
		return *this;
	}
	//
	int operator == (XMLF& op){
		if(&op == this)
			return 1;
		return (nametag == op.nametag);
	}
	//
	bool find(std_string a, std_string v = EMPTY_STR){
		for(size_t i=0; i<attr.size(); i++) {
			if(attr[i].attribute == a) {
				if(v == EMPTY_STR)
					return true;
				else {
					if(attr[i].value == v)
						return true;
					else
						return false;
				}
			}
		}
		return false;
	}
	//
	std_string getValue(std_string a) {
		for(size_t i=0; i<attr.size(); i++) {
			if(attr[i].attribute == a) 
				return attr[i].value;
		}
		return EMPTY_STR;
	}
	//
	void reset(void)
	{
		attr.clear();
		nametag = EMPTY_STR;
		body = EMPTY_STR;
	}
};

#include "N2TreeNode.h"

typedef N2TreeNode<XMLF>  CFS; // CodeFormatStructure
typedef N2TreeNodeCreator<XMLF>  CFSC;