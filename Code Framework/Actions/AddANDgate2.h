#ifndef _ADD_AND_GATE_H
#define _ADD_AND_GATE_H

#include "action.h"
#include "..\Components\AND2.h"

class AddANDgate2 :	public Action
{
private:
	//Parameters for rectangular area to be occupied by the gate
	int Cx, Cy;	//Center point of the gate
	int x1, y1, x2, y2;	//Two corners of the rectangluar area
public:
	AddANDgate2(ApplicationManager *pApp);
	virtual ~AddANDgate2(void);
	GraphicsInfo* pGInfo;
	//Execute action (code depends on action type)
	virtual void Execute(string s);

	virtual void Undo(GraphicsInfo* rGInfo);
	virtual void Redo(GraphicsInfo* rGInfo);
};

#endif