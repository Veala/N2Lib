// -*- mode:c++; coding:utf-8; -*-
///
/// \file		N2AllOperatingState.cpp
///
///	\brief 		
/// \details	
///
/// \copyright  ЗАО НТЦ "Модуль"
/// \author 	Чихичин Д.А.
///
/// \date 		02.04.2014
/// \version 	0.1
///  
///  История изменений:
///  
///


#include "include/N2AllOperatingState.h"
#include "N2Register.h"

// run
STATE_TASK N2OperatingStateManual::run(void)
{
	stateTask = RST_UNDEFINED;

	if(!pProc_)
		return stateTask = RST_ERR_CRITICAL;
	if(!pProc_->Initial(pMM_, pOrder_))
		return stateTask = RST_ERR_CONDITION;
	stateTask = RST_READY;
	//pMM_->updateDevices();

	return stateTask;
}

STATE_TASK N2OperatingStateAuto::run(void)
{
	return RST_UNDEFINED;
}

STATE_TASK N2OperatingStateDebug::run(void)
{
	stateTask = RST_UNDEFINED;

	if(!pProc_)
		return stateTask = RST_ERR_CRITICAL;
	if(!pProc_->Initial(pMM_, pOrder_))
		return stateTask = RST_ERR_CONDITION;
	stateTask = RST_READY;
	pMM_->updateDevices();

	return stateTask;
}

STATE_TASK N2OperatingStateIdle::run(void)
{
	return RST_UNDEFINED;
}

// stop

STATE_TASK N2OperatingStateManual::stop(void)
{
	if(pProc_)
		pProc_->ResetProcessor();
	if(pOrder_)
		pOrder_->Reset();
	return RST_UNDEFINED;
}

STATE_TASK N2OperatingStateAuto::stop(void)
{
	return RST_UNDEFINED;
}

STATE_TASK N2OperatingStateDebug::stop(void)
{
	return RST_UNDEFINED;
}

STATE_TASK N2OperatingStateIdle::stop(void)
{
	return RST_UNDEFINED;
}

// getTaskState

STATE_TASK N2OperatingStateManual::getTaskState(void) const
{
	return stateTask;
}

STATE_TASK N2OperatingStateAuto::getTaskState(void) const
{
	return RST_UNDEFINED;
}

STATE_TASK N2OperatingStateDebug::getTaskState(void) const
{
	return RST_UNDEFINED;
}

STATE_TASK N2OperatingStateIdle::getTaskState(void) const
{
	return RST_UNDEFINED;
}

// clock

 bool N2OperatingStateManual::clock(void)
 {
	 if(stateTask != RST_READY)
		 return true;
	 if(pProc_) 
		return pProc_->tick();

	 return false;
 }
 
 bool N2OperatingStateAuto::clock(void)
 {
	return false;
 }
 
 bool N2OperatingStateDebug::clock(void)
 {
	 if(stateTask != RST_READY)
		 return true;
	 if(pProc_) 
		return pProc_->tick();

	 return false;
 }
 
 bool N2OperatingStateIdle::clock(void)
 {
	return false;
 }
 
 // pause
 
 STATE_TASK N2OperatingStateManual::pause(void)
 {
	return RST_UNDEFINED;
 }
 
 STATE_TASK N2OperatingStateAuto::pause(void)
 {
	return RST_UNDEFINED;
 }
 
 STATE_TASK N2OperatingStateDebug::pause(void)
 {
	return RST_UNDEFINED;
 }
 
 STATE_TASK N2OperatingStateIdle::pause(void)
 {
	return RST_UNDEFINED;
 }
 
 