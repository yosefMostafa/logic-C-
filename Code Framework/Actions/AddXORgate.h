#pragma once
#include "action.h"
#include "..\Components\AND2.h"

class AddXORgate : public Action
{
private:
	//Parameters for rectangular area to be occupied by the gate
	int Cx, Cy;	//Center point of the gate
	int x1, y1, x2, y2;	//Two corners of the rectangluar area
public:
	AddXORgate(ApplicationManager* pApp);
	virtual ~AddXORgate(void);

	//Execute action (code depends on action type)
	virtual void Execute();

	virtual void Undo();
	virtual void Redo();
	void select();
};