// TotalControl.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"

//#include <IControl.h>
#include <N2ControlObject.h>
#include <string>
#include <iostream>
#include "N2ParserXML.h"
#include "N2ProjectNode.h"
#include "configuration.h"
#include "N2Register.h"
#include "N2Serializer.h"
#include "N2ModulesManager.h"
#include "N2Module.h"
#include "user_node.h"


void PrintRoutingTable(const N2RoutingTable* table)
{
	
};


int _tmain(int argc, _TCHAR* argv[])
{
	using namespace std;

	////////////////////////////////////////////////////////////////
	// Скорей проработка интерфейса, чем тест
	// 1. IControl должен выполнять обязанности ILauncher'а

	// Получаем элемент управления библиотекой N2
	IControl* pControl = N2ControlObject::getControl();

	// установить сериализатор (загрузчик/сохранятель), такая же лабуда -
	// <N2Standart2014ProjectNode, N2DefaultXMLParserT> стоит и по умолчанию
	// Создание сериализатора должно скрываться за интерфейсом IControl
	// N2BaseSerialize* pSer = new N2Serializer<N2Standart2014ProjectNode, N2DefaultXMLParserT>();
	
	//pControl->setProjectSerializer(NULL);
	// Загрузить проект из файла
	std_string strError;
	bool loadOk = pControl->loadProject(CT("c:\\work\\design\\2014\\TRT-V\\Work\\NucisNucleo\\tests\\functional\\TotalControl\\prj.xprj"), strError);
	if(!loadOk){
		cout << "ERROR: " << strError.c_str() << endl;
		return 1;
	}
	// Работа с модулями
	N2ModulesManager* pMM = pControl->getModulesManager();
	pMM->updateRoutingTable();
	const N2RoutingTable* pRoute = pMM->getRoutingTable();
	PrintRoutingTable(pRoute);

	// Здесь в приложении обход загруженного дерева и перенос его параметров в интерфейс ГИП,
	// построение структур, получение переменных окружения для изменения и отображения.
	// Далее имитация этих действий :
	N2TreeNode<N2Standart2014ProjectNode>* droot = (N2TreeNode<N2Standart2014ProjectNode>*) root;
	std_string namePrj = droot->getData()->name;
	std_string script = droot->getData()->scriptName;
	N2PrjNode* pNode = droot->getFirstChild();	
	if(!pNode)
		return 1;
	script = pNode->getData()->scriptName;
	// получение environment
	N2Environment* pEnv = N2Register::self()->getEnvironment();
	if(!pEnv)
		return 1;

	// Устанавливаем режим работы ядра инициируемый тактированием из приложения
	// (Переключение режима ядра останавливает текущую задачу! сбрасывает данные!)
	pControl->switchMode(MODE_MANUAL);

	// Имитация получения указания пользователя выполнить задачу с данным USID (УСИ)
	USID str_GUID = CT("xxx1-111-111-111");
//const N2PrjNode* pCNode = static_cast<const N2PrjNode*> (root->getTaskNode(str_GUID));	
	// загрузка проекта
	// обяз. проверка возврата
	pControl->loadTask(pNode->getData()->scriptName);

	// Запуск загруженной задачи
	//pControl->run();
	// Имитация тактирования из приложения
	while(pControl->clock()){
		// здесь задержка
	}

	// Здесь извлечение результатов работы, если, к примеру, не происходило сохранение в файлы

	// Здесь что-то для деинициализации или перезагрузки проекта или т.п.


	return 0;
}

