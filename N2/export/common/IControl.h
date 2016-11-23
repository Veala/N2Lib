// -*- mode:c++; coding:utf-8; -*-
///
/// \file		IControl.h
///
///	\brief 		Интерфейс управления библиотекой N2.
/// \details	
///
/// \copyright  ЗАО НТЦ "Модуль"
/// \author 	Чихичин Д.А.
///
/// \date 		21.03.2014
/// \version 	0.1
///  
//  История изменений :
//  
//

#pragma once


#include "N2Defines.h"
#include "N2ProjectNode.h"
#include "N2Parser.h"
#include "ITreeNode.h"
#include "N2BaseSerialize.h"
#include "ILauncher.h"
#include "N2ModulesManager.h"
#include "configuration.h"
#include "N2Dissection.h"
//#include "N2Order.h"
//#include "..\..\src\include\N2Processor.h"


class IControl : public ILauncher
{

public:

	/// Загрузить проект
	/// \param filename - имя файла проекта
	/// \param error - строковое описание ошибки
	/// \return Указатель ITreeNode* при успешной загрузке, в противном случае NULL
	//virtual ITreeNode*
	virtual bool
		loadProject(std_string filename,
					std_string& error) = 0;

	/// Получить управитель (менеджер) подключаемых модулей
	/// \return Менеджер модулей
	virtual N2ModulesManager* 
		getModulesManager(void) = 0;

	/// Сохранить проект
	/// \param filename - имя файла сохраняемого проекта
	/// \return При успешном сохранении - true, в противном случае - false
	virtual bool 
		saveProject(std_string filename) = 0;

	/// Загрузить задачу
	/// \param filename - имя файла задачи (задания)
	virtual RETURN_ON_LOAD_TASK 
		loadTask(std_string filename) = 0;

	/// Установить "сериализатор" (программный модуль отвечающий за сохранение и загрузку однотипной информации) проекта
	/// \param pSerial - указатель на созданный пользователем класс наследуемый от N2BaseSerialize, по умолчанию 
	/// создается N2Serializer<N2Standart2014ProjectNode, N2DefaultXMLParserT>. 
	/// \return При успешной установке - true, в противном случае - false
	virtual bool 
		setProjectSerializer(N2BaseSerialize* pSerial) = 0;

	/// Установить разборщик (парсер) для файла задачи
	/// \param pParser - указатель на созданный пользователем класс парсера.
	/// По умолчанию установлен - N2DefaultXMLParserT.
	/// \return При успешной установке - true, в противном случае - false
	virtual bool
		setTaskParser(N2Parser* pParser) = 0;

	/// Переключить текущий режим работы ядра. При переключении происходит остановка и сброс текущей задачи.
	/// По умолчанию ядро установлено в ручной режим .
	/// \param mode - режим, в который необходимо переключить ядро, имеются следующие варианты :
	///* MODE_IDLE - режим холостого хода, тестовый режим,
	///* MODE_MANUAL - "ручной" режим, "задающим генератором" здесь является приложение пользователя,
	///* MODE_AUTO - автоматический режим, здесь ядро тактируется самостоятельно и происходит распараллеливание нитей обработки команд и управления,
	///* MODE_DEBUG - отладочный режим, эквивалентен ручному, но с возможностью получения отладочной информации ядра на любом его шаге.
	/// \return Возвращается предыдущий установленный режим
	virtual OPERATING_MODE 
		switchMode(OPERATING_MODE mode) = 0;

	///
	virtual N2BaseSerialize* 
		createUserSerializer(N2ProjectNode& rNode, N2DefaultXMLParserT& rParser) = 0;

	/// Установить "внешний" байт-кодер задачи. Зависит от синтаксиса задачи.
	virtual bool 
		addByteCoder(N2Dissection* pDiss) = 0;
	
	/// Получение глобальной переменной 
	virtual const N2BaseVariable*
		getGlobalVariable(std_string nameVar) = 0;

	/// Установка параметра/добавление глобальной переменной
	virtual bool
		setGlobalVariable(N2BaseVariable* var) = 0;

	/// Удаление глобальной переменной
	virtual bool
		delGlobalVariable(std_string nameVar) = 0;

	/// Впрыскивание команды вне очереди исполнения
	virtual bool
		commandInjection(DataPack* tc) = 0;

	//virtual N2Order* getOrder(void) = 0;
	
	//virtual N2Processor* getProcessor(void) = 0;
	//Environment* GetEnvironment(void);

	//bool SetEnvironment(Environment* pEnv);

	virtual bool
		reloadLastOrder(void) = 0;

};
