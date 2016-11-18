// -*- mode:c++; coding:utf-8; -*-
///
/// \file		N2Standart2014ProjectNode.h
///
///	\brief 		��������� ������������ ���� ������ �������
/// \details	������ ��������� ����������� ���� ������ ������������ ������������ �������
///
/// \copyright  ��� ��� "������"
/// \author 	������� �.�.
///
/// \date 		03.07.2014
/// \version 	0.1
///  
///  ������� ���������:
///  
///

#pragma once

#include "N2ProjectNode.h"
#include <vector>

using namespace std;

struct N2Standart2014SpecialInfo
{
	// ������ �������� 
	// ������ �����������
};



struct N2Standart2014ProjectNode : public N2ProjectNode
{
	static std_string mark;
	std_string name;
	std_string scriptName;
	std_string description;
	//
	//COLORING color;
	bool enable;
	bool execute;

	static N2Standart2014SpecialInfo info_;

public:
	N2Standart2014ProjectNode();
	virtual ~N2Standart2014ProjectNode();
	//
	virtual 
	bool interpretation(CFS *parsedTree);

	virtual
	std_string 	getMark(void) 
	{
		return mark;
	}


	///! ������ ������ � ������ �������� 
	virtual bool
		parseTree(std_string filename, std_string& errorDescription);


};

