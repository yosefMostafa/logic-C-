#pragma once
#include "action.h"
#include "..\Components\Component.h"
class selectd : public Action {
public:
private:
	//Parameters for rectangular area to be occupied by the gate
	int Cx, Cy;//Center point of the gate
public:
	selectd(ApplicationManager* pApp);
	void Execute() ;
	void Undo() {};
	void Redo() {};

};
