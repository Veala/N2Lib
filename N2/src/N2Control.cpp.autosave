
#include "../export/common/IControl.h"
#include "include/N2Control.h"
#include "../export/common/N2Base.h"
#include "../export/common/N2Register.h"
#include "../export/common/N2Serializer.h"
#include "../export/common/N2Standart2014ProjectNode.h"


N2Control::N2Control() :
pSerial_(NULL)
{
	pCurrentState_ = NULL;
	pSerial_ = new N2DefaultSerializerT; //N2Register::self()->getMemoryAllocator()->create<N2DefaultSerializerT>(CT("Project serializer"));
	pParser_ = N2Register::self()->getMemoryAllocator()->create<N2DefaultXMLParserT>(CT("Task parser"));
	pModulesManager_ = N2Register::self()->getMemoryAllocator()->create<N2ModulesManager>(CT("Modules Manager"));
	pDiss_ = N2Register::self()->getMemoryAllocator()->create<N2DissTotal>(CT("Dissection task"));
	pOrder_ = N2Register::self()->getMemoryAllocator()->create<N2Order>(CT("Order of task"));
	switchMode(MODE_IDLE);
}

N2Control::~N2Control()
{
	delete pSerial_;
	N2Register::self()->getMemoryAllocator()->release(pParser_);
	N2Register::self()->getMemoryAllocator()->release(pModulesManager_);
	N2Register::self()->getMemoryAllocator()->release(pDiss_);
	N2Register::self()->getMemoryAllocator()->release(pOrder_);
}


/// Загрузить проект
//ITreeNode*
bool
N2Control::loadProject(std_string filename,
						std_string& error)
{
	// загружаем проект
	bool retVal = pSerial_->loadProject(filename, error);
	// создаем список модулей
	pModulesManager_->updateModulesList();

	return retVal;
}


N2ModulesManager* 
N2Control::getModulesManager(void)
{
	return pModulesManager_;
}


bool 
N2Control::setProjectSerializer(N2BaseSerialize* pSerial)
 {
	if(!pSerial)
		return false;
	if(pSerial_)
		delete pSerial_;
	pSerial_ = pSerial;
	return true;
 }

bool
N2Control::setTaskParser(N2Parser* pParser)
{
	if(!pParser)
		return false;
	delete pParser_;
	pParser_ = pParser;
	return true;
}

bool 
N2Control::addByteCoder(N2Dissection* pDiss)
{
	if(!pDiss)
		return false;
	pDiss_->addDissector(pDiss);
	return true;
}

/// Сохранить проект
bool
N2Control::saveProject(std_string filename)
{
	bool b = pSerial_->saveProject(filename);
	return b;
}


RETURN_ON_LOAD_TASK 
N2Control::loadTask(std_string filename)
{
	std_string errDesc;
	CFS* pCFS = pParser_->parse(filename, errDesc);
	if(!pCFS)
		return ROLP_ERR_PARSE;
	VectorCommand* pVecComm = new VectorCommand;
	pDiss_->passParser(pParser_);
	if(!pDiss_->unpackWhole(pCFS, pVecComm))
		return ROLP_ERR_BYTECODER;

	if(pOrder_) {
		pOrder_->Reset();
		if(pOrder_->AddCommandsInOrder(pVecComm))
			return ROLP_OK;
	}
	
	return ROLP_ERR_INTERNAL;
}


// +-
OPERATING_MODE N2Control::switchMode(OPERATING_MODE mode)
{
	OPERATING_MODE old;

	if(!pCurrentState_) 
		old = MODE_IDLE;
	else
		old = pCurrentState_->mode();

	N2OperatingState* oldPointer = pCurrentState_;

	switch(mode){
		case MODE_UNDEFINE : ;break;
		case MODE_IDLE: 			
			pCurrentState_ =  N2Register::self()->getMemoryAllocator()->create<N2OperatingStateIdle>(CT("N2OperatingStateIdle")); 
			break;
		case MODE_MANUAL: 
			pCurrentState_ = N2Register::self()->getMemoryAllocator()->create<N2OperatingStateManual>(CT("N2OperatingStateManual")); 
			break;
		case MODE_AUTO: 
			pCurrentState_ = N2Register::self()->getMemoryAllocator()->create<N2OperatingStateAuto>(CT("N2OperatingStateAuto")); 
			break;
		case MODE_DEBUG: 
			pCurrentState_ = N2Register::self()->getMemoryAllocator()->create<N2OperatingStateDebug>(CT("N2OperatingStateDebug")); 
			break;
	}

	if(pCurrentState_) {
		if(oldPointer)
			N2Register::self()->getMemoryAllocator()->release(oldPointer);
		pCurrentState_->setModulesManager(pModulesManager_);
		pCurrentState_->setOrder(pOrder_);
	}

	return old;
}


N2BaseSerialize* 
N2Control::createUserSerializer(N2ProjectNode& rNode, N2DefaultXMLParserT& rParser)
{
	//return N2Register::self()->getMemoryAllocator()->create<N2Serializer<N2Standart2014ProjectNode, N2DefaultXMLParserT> >(CT("Project serializer"));
	return NULL;
}


// + Запуск загруженной задачи
//! Инициализация задачи
STATE_TASK  N2Control::run(void)
{
	if(!pCurrentState_)
		return RST_ERR_INTERNAL;
	return pCurrentState_->run();
}

// + Аварийный останов загруженной задачи
STATE_TASK  N2Control::stop(void)
{
	if(!pCurrentState_)
		return RST_ERR_INTERNAL;
	return pCurrentState_->stop();
}

// + Получить состояние выполняемой задачи
STATE_TASK  N2Control::getTaskState(void) const
{
	if(!pCurrentState_)
		return RST_ERR_INTERNAL;
	return pCurrentState_->getTaskState();
}

// + Пауза
STATE_TASK  N2Control::pause(void)
{
	if(!pCurrentState_)
		return RST_ERR_INTERNAL;
	return pCurrentState_->pause();
}

// + Clock
bool  N2Control::clock(void)
{
	if(!pCurrentState_)
		return false;
	return pCurrentState_->clock();
}

N2Order* 
N2Control::getOrder(void)
{
	if(pCurrentState_) {
		if(pCurrentState_->mode() == MODE_DEBUG)
			return pOrder_;
	}
	return NULL;
}
	
N2Processor* 
N2Control::getProcessor(void)
{
	if(pCurrentState_) {
		return static_cast<N2OperatingStateDebug*> (pCurrentState_)->getProcessor();
	}
	return NULL;
}



const N2BaseVariable*
N2Control::getGlobalVariable(std_string nameVar)
{
	//N2Processor* prc = getProcessor();
	//if(!prc)
	//	return NULL;
	//return prc->getManVar()->getGlobal(nameVar);

	return N2Register::self()->getEnvironment()->get(nameVar);
}


bool
N2Control::setGlobalVariable(N2BaseVariable* var)
{
	//N2Processor* prc = getProcessor();
	//if(!prc)
	//	return false;
	//return prc->getManVar()->declare(var, VMT_GLOBAL);	
	bool retVal = false;
	if(!var)
		return retVal;
    N2BaseVariable* temp = N2Register::self()->getEnvironment()->change(var->name());
	if(temp) {
        if(temp->operation(N2_Defines::N2OC_INIT, var))
			retVal = true;
	}
	else
		retVal = N2Register::self()->getEnvironment()->add(var);

	return retVal;
}


bool
N2Control::delGlobalVariable(std_string nameVar)
{
	//N2Processor* prc = getProcessor();
	//if(!prc)
	//	return false;
	//return prc->getManVar()->release(nameVar, VMT_GLOBAL);	

	return false;
}


bool
N2Control::commandInjection(DataPack* tc)
{
	N2Processor* prc = getProcessor();
	if(!prc)
		return false;	
	return prc->inject(tc);
}

bool
N2Control::reloadLastOrder(void)
{
	bool retVal = false;

	if(pOrder_) {
		
		if(pCurrentState_ )  {
			pOrder_->SetCIP(0);
			pCurrentState_->setOrder(pOrder_);
			pCurrentState_->run();
			retVal = true;
		}
	}
	
	return retVal;
}
