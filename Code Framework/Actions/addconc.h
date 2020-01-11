#pragma once
#include "action.h"
class addconc : public Action {
private:
	GraphicsInfo* pGInfo;
	OutputPin *source;
	InputPin* Destination;
	Component* PC,*PC1;
	int c, pin1, pin0;
public:
	addconc(ApplicationManager* pApp);
	void checkcon();
	void Execute(string s);
	void Undo(GraphicsInfo* rGInfo);
	void Redo(GraphicsInfo* rGInfo) ;

};