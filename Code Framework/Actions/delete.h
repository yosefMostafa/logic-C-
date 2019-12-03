#pragma once

#include "action.h"
#include "..\Components\AND2.h"
class delete1 : public Action
{
public:
	delete1(ApplicationManager* pApp);
	delete1() {};
	virtual ~delete1(void);

	//Execute action (code depends on action type)
	virtual void Execute();

	virtual void Undo() ;
	virtual void Redo() ;
};