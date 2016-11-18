// -*- mode:c++; coding:utf-8; -*-
///
/// \file		N2TinyXMLParser.cpp
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

//#include "../export/common/N2RealParser.h"
#include "../export/common/N2TinyXMLParser.h"
#include "../export/common/N2Register.h"

#include "../utils/tinyxml/tinystr.h"
#include "../utils/tinyxml/tinyxml.h"



CFS* 
N2TinyXMLParser::parse(	std_string	filename, 
						std_string&	errorDescription, 
						std_string	firstMark)
{
	CFS* retVal;
	TiXmlDocument doc;
	bool loadOkay = doc.LoadFile(filename.c_str());
	if (!loadOkay) {
		N2ProjectSpecialInfo* pInfo = N2Register::self()->getDeviceInfo();
		std_string pm = pInfo->pathsTasks.empty() ? EMPTY_STR : pInfo->pathsTasks.getFirstPath();
		std_string fullError;
		errorDescription = EMPTY_STR;
		// поиск по всем путям
		/*COUNT indx = 0;*/
		while(pm != EMPTY_STR) {
			std_string pathName = pm + SLASH_STR + filename;
			loadOkay = doc.LoadFile(pathName.c_str());
			if(loadOkay)
				break;
			else {
				fullError += CT("Попытка обработать файл: ") + pathName + \
					CT("\n  завершена с ошибкой: ") + errorDescription + ENDL_STR;
			}
			/*indx ++;*/
			pm = pInfo->pathsTasks.getNextPath(); 
			//(pInfo->pathsTasks.size() > indx) ? pInfo->pathsTasks[indx] : EMPTY_STR;
		}

		if(!loadOkay) {
			errorDescription = fullError;
			return NULL;
		}
	}
	//	
	CFSC creator;
	retVal = creator.createNode();
	TiXmlNode* root = 0;
	root = doc.FirstChild();
	// нижеприведенный фрагмент нужен для удаления XML заголовков типа: 
	// <?xml version="1.0" encoding="Windows-1251"?> и т.п.
	while(root && !root->ToElement()) {
		root = root->NextSibling();
	}

	// поиск по метке, если она не пустая
	if(firstMark != EMPTY_STR) {
	   // здесь описать поиск
	}

	// собственно запись корневого (или метки) узла
	writeNode(root, retVal);

	return retVal;
}



void
N2TinyXMLParser::writeNode(void* vnode, CFS* curNode)
{
	CFSC creator;
	CFS* ptcfs;
	XMLF xmlf;

	TiXmlNode* node = (TiXmlNode*) vnode;

	// заполнение узла
	TiXmlElement* pElm = node->ToElement();
	if(pElm) {
		if(pElm->NoChildren())
			xmlf.tag = N2_XMLFTAG_SINGLE;
		else
			xmlf.tag = N2_XMLFTAG_BEGIN;
		TiXmlAttribute* attr = pElm->FirstAttribute();		
		xmlf.nametag = node->Value(); // <- если это так
		ATTR xa;
		while(attr != NULL) {
			xa.attribute = attr->Name();
			xa.value = attr->Value();
			xmlf.attr.push_back(xa);
			attr = attr->Next();
		}
		CCHAR_N2* pch = node->ToElement()->GetText();
		xmlf.body = pch ? pch : EMPTY_STR;
		curNode->setData(&xmlf);
	// конец заполнения узла
	}
	
	// записать все дочерние узлы
	TiXmlNode* temp = node->FirstChild();
	if( temp == NULL ||
		temp->Type() == TiXmlNode::TEXT)
			return;
	while(temp) {	
		xmlf.reset();
		ptcfs = creator.setChild(curNode, &xmlf);
		writeNode(temp, ptcfs);
		temp = temp->NextSibling();
	}

}

//CFS* 
//N2TinyXMLParser::getCFS(void)
//{
//	return pCFS;
//}
