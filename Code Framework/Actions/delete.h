#pragma once

#include "action.h"
#include "..\Components\AND2.h"
class delete1 : public Action
{
private:
	//Parameters for rectangular area to be occupied by the gate
	int Cx, Cy;	//Center point of the gate
	int x1, y1, x2, y2;	//Two corners of the rectangluar area
public:
	delete1(ApplicationManager* pApp);
	delete1() {};
	virtual ~delete1(void);

	//Execute action (code depends on action type)
	virtual void Execute();

	virtual void Undo() ;
	virtual void Redo() ;
};