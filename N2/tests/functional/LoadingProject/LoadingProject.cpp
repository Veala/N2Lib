// LoadingProject.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"

#include "../../../export/common/configuration.h"
#include "../../../export/common/N2Parser.h"
#include "../../../export/common/N2ParserXML.h"
#include "../../../export/common/N2TinyXMLParser.h"



void printTree(N2TreeNode<XMLF>* pNode)
{
	bool end = true;
	if(!pNode)
		return;
	printf("<%s ", pNode->getData()->nametag.c_str());
	for(int i=0; i<pNode->getData()->attr.size(); i++)
		printf(" %s=\"%s\"", pNode->getData()->attr[i].attribute.c_str(), pNode->getData()->attr[i].value.c_str());
	N2TreeNode<XMLF>* temp = pNode->getFirstChild();
	if(!temp && pNode->getData()->body == EMPTY_STR) {
		printf(" />\n");
		end = false;
	}
	else if(pNode->getData()->body != EMPTY_STR) {
		printf(" >\n");
		printf("%s\n", pNode->getData()->body.c_str());
		if(temp) {
			printf(" >\n");
			printTree(temp);
			printf("</%s >\n", pNode->getData()->nametag.c_str());
			temp = NULL;
			end = false;
		}
		else {
			printf("</%s >\n", pNode->getData()->nametag.c_str());
			temp = NULL;
			end = false;
		}
	}
	else 
		printf(" >\n");
	while(temp){
		printTree(temp);
		temp = pNode->getNextSibling();
	}
	if(end)
		printf("</%s >\n ", pNode->getData()->nametag.c_str());
};




int _tmain(int argc, _TCHAR* argv[])
{
	N2ParserXML<N2TinyXMLParser> parserXML;

	CFS* pCFS = parserXML.parse(CT("prjfile.xprj"), EMPTY_STR);

	printTree(pCFS);


	return 0;
}

