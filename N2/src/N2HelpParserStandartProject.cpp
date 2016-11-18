// -*- mode:c++; coding:utf-8; -*-
///
/// \file		N2HelpParserStandartProject.cpp
///
///	\brief 		
/// \details	
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

#include "include/N2HelpParserStandart2014Project.h"
#include "../common/N2Register.h"
#include "N2Phelper.h"

std_string 
N2HelpParserStandart2014Project::getProjectFiles(std_string fileToParse, N2Parser* pParser, std_string& fileVoile)
{
	std_string retVal = EMPTY_STR;
	std_string errStr;
	CFS* temp =  pParser->parse(fileToParse, errStr, CT("ХTS"));
	CFS* beg;
	XMLF* curX = temp->getData();
	try{
	if(curX->nametag != "XTS")
		throw CT("Не найден тег XTS");
	// поиск файла константных данных
	if(!curX->find(CT("type"), CT("PRJ")))
		throw CT("Не найден атрибут type=\"PRJ\" ");
	//
	beg = temp;
	curX->reset();
	curX->nametag = CT("FILES");
	temp = temp->getChild(curX);
	if(!temp)
		throw CT("Не найден тег FILES");
	XMLF x(CT("TREE_FILE_CONST"));
	temp = temp->getChild(&x);
	if(!temp)
		throw CT("Не найден тег TREE_FILE_CONST");
	curX = temp->getData();
	if(!curX->find(CT("file")))
		throw CT("Не найден атрибут file ");
	retVal = curX->getValue(CT("file"));
	// поиск файла вуали
	curX->reset();
	curX->nametag = CT("FILES");
	temp = beg->getChild(curX);
	if(!temp)
		throw CT("Не найден тег FILES");
	x.reset();
	x.nametag = CT("VOILE_FILE");
	temp = temp->getChild(&x);
	if(!temp)
		throw CT("Не найден тег VOILE_FILE");
	x = *temp->getData();
	if(!x.find(CT("file")))
		throw CT("Не найден атрибут file ");
	fileVoile = x.getValue(CT("file"));
	//
	//pParser->reset();
	}
	catch(CHAR_N2* ){
		// запись в логер ошибок 
		// выброс обобщенного исключения
	}
	catch(...){		
		// предохранитель
		// если сработал - запись в логер ошибок 
	}

	return retVal;
}


//std_string 
//prjVoile(std_string filename, N2Parser* pParser)
//{
//	std_string retVal = EMPTY_STR;
//	
//	return retVal;
//}

//N2Environment *
//N2HelpParserStandart2014Project::getEnvironment(CFS* pcfs)
//{
//	return NULL;
//}

ITreeNode* 
N2HelpParserStandart2014Project::getTree(void)
{
	return (ITreeNode*)pTreeNode;
}

bool
N2HelpParserStandart2014Project::exists(std_string filename)
{
	bool retVal = false;
	FILE* pFile = std_fopen(filename.c_str(), CT("r"));
	if(pFile) {
		fclose(pFile);
		retVal = true;
	}
	return retVal;
}


bool
N2HelpParserStandart2014Project::yes_no(std_string val)
{
	if(	val == CT("YES") ||
		val == CT("yes") ||
		val == CT("Y") ||
		val == CT("y") ||
		val == CT("TRUE") ||
		val == CT("true") )
			
		return true;
	else
		return false;
}


int 
N2HelpParserStandart2014Project::strToInt(std_string val)
{
	return atoi(val.c_str());
}

bool
N2HelpParserStandart2014Project::fullParseConst(std_string filename, 
												N2Parser* pParser, 
												bool loadEnvironment)
{
	N2TreeNodeCreator<N2Standart2014ProjectNode> crt;
	N2TreeNode<N2Standart2014ProjectNode>* pNode;
	N2Standart2014ProjectNode dataNode;
	CFS* cfs, *tmp, *curBlk, *chptr;
	pTreeNode = pNode = crt.createNode();
	//pNode->setData(&dataNode);
	std_string errDesc;
	cfs = pParser->parse(filename, errDesc);
	if(cfs == NULL)
		return false;
	// Проверяем тип файла
	XMLF* curX = cfs->getData();
	if(curX->nametag != "XTS")
		throw CT("Не найден тег XTS");
	if(!curX->find(CT("type"), CT("CONST")))
		throw CT("Не найден атрибут type=\"CONST\" ");
	// Разбираем блок INFO
	curX->reset();
	curX->nametag = CT("INFO");
	tmp = cfs->getChild(curX);
	if(!tmp)
		throw CT("Не найден тег INFO");
	curBlk = tmp;

	XMLF x(CT("MODULES"));
	tmp = curBlk->getChild(&x);
	if(!tmp)
		throw CT("MODULES");

	chptr = tmp;
	tmp = chptr->getFirstChild();
	N2ProjectSpecialInfo* pdi = N2Register::self()->getDeviceInfo();
	pdi->modules.clear();
	// зписываем все относительные пути
	while(tmp){
		if(tmp->getData()->nametag != CT("MODULE"))
			break;
		N2ModulesSpecification ms;
		ms.signature = strToInt(tmp->getData()->getValue("sign"));
		ms.obligative = yes_no(tmp->getData()->getValue("obligative"));
		ms.libName = tmp->getData()->getValue("lib_name");
		pdi->modules.push_back(ms);
		tmp = chptr->getNextChild();
	};

	// Разбираем блок ENVIRONMENT
	if(loadEnvironment) {
		curX->reset();
		curX->nametag = CT("ENVIRONMENT");
		tmp = cfs->getChild(curX);
		if(!tmp)
			throw CT("Не найден тег ENVIRONMENT");
		if(! rollUpEnvr(tmp))
			return false;
	}
	// Разбираем блок TREE
	curX->reset();
	curX->nametag = CT("TREE");
	tmp = cfs->getChild(curX);
	if(!tmp)
		throw CT("Не найден тег TREE");
	curBlk = tmp;
	curX->reset();
	curX->nametag = CT("N");
	tmp = tmp->getChild(curX);

	rollUpTree(tmp, pTreeNode);

	return true;
}


void
N2HelpParserStandart2014Project::rollUpTree(CFS* pCFS, N2TreeNode<N2Standart2014ProjectNode>* pNode)
{
	N2TreeNodeCreator<N2Standart2014ProjectNode> creator;
	CFS* temp = pCFS;
	N2Standart2014ProjectNode dataNode;

	if(temp->getData()->nametag != CT("N"))
		return;
	dataNode.name = temp->getData()->getValue(CT("name"));
	dataNode.scriptName = temp->getData()->getValue(CT("script"));
	dataNode.description = temp->getData()->getValue(CT("description"));
	dataNode.execute = yes_no(temp->getData()->getValue(CT("exec")));
	dataNode.enable = yes_no(temp->getData()->getValue(CT("enable")));
	pNode->setData(&dataNode);

	temp = pCFS->getFirstChild();
	while(temp) {
		rollUpTree(temp, creator.createNode());
		temp = pCFS->getNextChild();
	}

}

bool
N2HelpParserStandart2014Project::fullParseVoile(std_string filename, 
												N2Parser* pParser, 
												bool loadEnvironment)
{
	return false;
}

bool
N2HelpParserStandart2014Project::createFileVoile(std_string filename)
{
	return false;
}

bool
N2HelpParserStandart2014Project::rollUpEnvr(CFS* pCFS)
{
	//CFS* tmp;
	bool retVal = false;
	//std_string name;
	//TYPE_VAR type(VAR_UNDEFINED);
	//COUNT count = 0;
	//std_string value;
	//PHelper helper;
	//N2BaseVariable* tv;
	//TYPE_VAR el_type(VAR_UNDEFINED);
	//COUNT raw, col;
	//
	//tmp = pCFS->getFirstChild();
	//while(tmp) {
	//	// 1
	//	if(tmp->getData()->nametag == CT("UV")) {
	//		type = getTypeFromString(tmp->getData()->getValue("type"));
	//		name = tmp->getData()->getValue("name");
	//		count = helper.StoI(tmp->getData()->getValue("count"));
	//		value = tmp->getData()->getValue("value");
	//		if(count == 0) count = 1;
	//		switch(type) {
	//			case VAR_INT:
	//				tv = N2VariableINT(name, count).clone();
	//				break;
	//			case VAR_LONG:
	//				tv = N2VariableLONG(name, count).clone();
	//				break;
	//			case VAR_BOOL:
	//				tv = N2VariableBOOL(name, count).clone();
	//				break;
	//			case VAR_STRING:
	//				tv = N2VariableSTR(name, count).clone();
	//				break;
	//			case VAR_FLOAT:
	//				tv = N2VariableFLOAT(name, count).clone();
	//				break;
	//			case VAR_TERNAR:
	//				tv = N2VariableTO(name, count).clone();
	//				break;
	//				default: return retVal;
	//		}
	//		if(value != EMPTY_STR) {
	//			N2VariableSTR vs;
	//			vs.set(value);
	//			tv->set(&vs);
	//		}
	//	}
	//	// 2
	//	if(tmp->getData()->nametag == CT("TABLE")) {
	//		el_type = getTypeFromString(tmp->getData()->getValue("el_type"));
	//		name = tmp->getData()->getValue("name");
	//		raw = helper.StoI(tmp->getData()->getValue("raw"));
	//		col = helper.StoI(tmp->getData()->getValue("col"));
	//		if(count == 0) count = 1;
	//		switch(type) {
	//			case VAR_INT:
	//				tv = N2VariableIntTABLE(name, raw, col).clone();
	//				break;
	//			case VAR_BOOL:
	//				tv = N2VariableBoolTABLE(name, raw, col).clone();
	//				break;
	//			case VAR_STRING:
	//				tv = N2VariableStringTABLE(name, raw, col).clone();
	//				break;
	//			case VAR_TERNAR:
	//				tv = N2VariableTernarTABLE(name, raw, col).clone();
	//				break;
	//				default: return retVal;
	//		}
	//	}
	//	// 3

	//	// добавляем в Environment
	//	N2Register::self()->getEnvironment()->add(tv);
	//	N2Register::self()->voidRelease(tv);
	//	//
	//	tmp = pCFS->getNextSibling();
	//}

	return retVal;
}

TYPE_VAR
N2HelpParserStandart2014Project::getTypeFromString(std_string str)
{
	TYPE_VAR retVal(VAR_UNDEFINED); 
	PHelper helper;
	helper.AddFirst("INT", VAR_INT);
	helper.Add("BOOL", VAR_INT);
	helper.Add("FLOAT", VAR_FLOAT);
	helper.Add("LONG", VAR_INT);
	helper.Add("STRING", VAR_STRING);
	helper.Add("TABLE", VAR_TABLE);
	helper.Add("TERN", VAR_TERNAR);
	helper.Add("TERNAR", VAR_TERNAR);
	AHE ahe = helper.WhatIs(str);
	if(ahe != AHE_TOKEN) {
		return retVal;	
	}
	retVal = (TYPE_VAR)helper.GetValue();
	return retVal;
}