#pragma once
#include "action.h"
#include "..\Components\XNOR.h"

class AddXNORgate : public Action
{
private:
	//Parameters for rectangular area to be occupied by the gate
	int Cx, Cy;	//Center point of the gate
	int x1, y1, x2, y2;
	GraphicsInfo* pGInfo;	//Two corners of the rectangluar area
public:
	AddXNORgate(ApplicationManager* pApp);
	virtual ~AddXNORgate(void);

	//Execute action (code depends on action type)
	virtual void Execute(string s);

	virtual void Undo(GraphicsInfo* rGInfo);
	virtual void Redo(GraphicsInfo* rGInfo);
};