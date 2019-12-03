#pragma once
#include "action.h"
class addconc : public Action {
public:
	addconc(ApplicationManager* pApp);
	void Execute();
	void Undo();
	void Redo() ;

};