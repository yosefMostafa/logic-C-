#pragma once
#include "action.h"
#include "..\Components\NOR.h"

class AddNORgate : public Action
{
private:
	//Parameters for rectangular area to be occupied by the gate
	int Cx, Cy;	//Center point of the gate
	int x1, y1, x2, y2;	//Two corners of the rectangluar area
	GraphicsInfo* pGInfo;
public:
	AddNORgate(ApplicationManager* pApp);
	virtual ~AddNORgate(void);

	//Execute action (code depends on action type)
	virtual void Execute(string s);

	virtual void Undo(GraphicsInfo* rGInfo);
	virtual void Redo(GraphicsInfo* rGInfo);
};