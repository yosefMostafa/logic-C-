#pragma once
#include "action.h"
class addconc : public Action {
public:
private:
	//Parameters for rectangular area to be occupied by the gate
	int Cx, Cy,Cx1,Cy1;	//Center point of the gate
	int x1, y1, x2, y2;	//Two corners of the rectangluar area
public:
	addconc(ApplicationManager* pApp);
	void Execute();
	void Undo();
	void Redo() ;

};