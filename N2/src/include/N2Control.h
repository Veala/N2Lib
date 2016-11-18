// -*- mode:c++; coding:utf-8; -*-
///
/// \file		N2Control.h
///
///	\brief 		Интерфейс управления пользователя
/// \details	Внешний по отношению к библиотеке интерфейс для ее управления
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

#pragma once

#include "../../export/common/N2TreeNode.h"
#include "../../export/common/N2Dissection.h"
#include "N2OperatingState.h"
#include "N2AllOperatingState.h"
#include "../../export/common/N2Parser.h"
#include "../../export/common/N2BaseSerialize.h"
//#include "../common/N2ModulesManager.h"


/// Класс управления библиотекой N2.
/// Для начала работы с библиотекой необходимо получить экземпляр данного класса как
/// указатель на интерфейс IControl :
///	IControl* pIControl = N2ControlObject::getControl();
class N2Control: public IControl
{	

	/// Указатель на текущий экземляр главного операционного модуля библиотеки
	N2OperatingState* pCurrentState_;
	/// Указатель на текущий "сериализатор"
	N2BaseSerialize* pSerial_;
	/// Менеджер модулей (устройств)
	N2ModulesManager* pModulesManager_;
	/// Текущий парсер задачи
	N2Parser* pParser_;
	/// Разборщики задач
	N2DissTotal* pDiss_;
	/// Очередь команд задачи
	N2Order* pOrder_;
	///

public:
	N2Control();
	~N2Control();

	/// Загрузить проект
	/// \param filename - имя файла проекта
	/// \param error - строковое описание ошибки
	/// \return Указатель ITreeNode* при успешной загрузке, в противном случае NULL
	//ITreeNode*
	bool
	loadProject(std_string filename,
				std_string& error);

	/// Получить управитель (менеджер) подключаемых модулей
	/// \return Менеджер модулей
	N2ModulesManager* getModulesManager(void);

	virtual bool 
		setProjectSerializer(N2BaseSerialize* pSerial);

	virtual bool
		setTaskParser(N2Parser* pParser);

	/// Сохранить проект
	virtual bool saveProject(std_string filename);
	
	/// Загрузить задачу
	virtual RETURN_ON_LOAD_TASK loadTask(std_string filename);

	/// Запуск загруженной задачи
	virtual STATE_TASK run(void);

	/// Аварийный останов загруженной задачи
	virtual STATE_TASK stop(void);

	/// Получить состояние выполняемой задачи
	virtual STATE_TASK getTaskState(void) const;

	/// Поставить исполнение задачи на паузу
	virtual STATE_TASK pause(void);

	/// "Тактирование" процессора
	virtual bool clock(void);

	/// Переключение режима
	virtual OPERATING_MODE switchMode(OPERATING_MODE mode);

	/// Создать сериализатор (класс обеспечивающий сохранение и загрузку однотипных данных)
	virtual N2BaseSerialize* 
		createUserSerializer(N2ProjectNode& rNode, N2DefaultXMLParserT& rParser);

	/// Добавить преобразователь команд заданий
	/// \param pDiss - д.б. создан в динамической памяти, удаляется автоматически
	virtual bool 
		addByteCoder(N2Dissection* pDiss);

	virtual N2Order* getOrder(void);
	
	virtual N2Processor* getProcessor(void);

	/// Получение глобальной переменной 
	virtual const N2BaseVariable*
		getGlobalVariable(std_string nameVar);

	/// Установка параметра/добавление глобальной переменной
	virtual bool
		setGlobalVariable(N2BaseVariable* var);

	/// Удаление глобальной переменной
	virtual bool
		delGlobalVariable(std_string nameVar);

	/// Впрыскивание команды вне очереди исполнения
	virtual bool
		commandInjection(DataPack* tc);
	//Environment* GetEnvironment(void);

	//bool SetEnvironment(Environment* pEnv);

	/////
	virtual bool
		reloadLastOrder(void);

};
