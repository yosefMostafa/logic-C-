#pragma once
#include "action.h"
#include "..\Components\Switch.h"

class Addswitch : public Action
{
private:
	//Parameters for rectangular area to be occupied by the gate
	int Cx, Cy;	//Center point of the gate
	int x1, y1, x2, y2;	//Two corners of the rectangluar area
	GraphicsInfo* pGInfo;
public:
	Addswitch(ApplicationManager* pApp);
	virtual ~Addswitch(void);

	//Execute action (code depends on action type)
	virtual void Execute(string s);

	virtual void Undo(GraphicsInfo* rGInfo);
	virtual void Redo(GraphicsInfo* rGInfo);
};
