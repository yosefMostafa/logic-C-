#pragma once
#include "action.h"
#include "..\Components\Component.h"
class selectd : public Action {
public:
	selectd(ApplicationManager* pApp);
	void Execute() ;
	void Undo() {};
	void Redo() {};

};
