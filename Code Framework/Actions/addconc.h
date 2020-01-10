#pragma once
#include "action.h"
class addconc : public Action {
private:
	GraphicsInfo* pGInfo;
public:
	addconc(ApplicationManager* pApp);
	void Execute(string s);
	void Undo(GraphicsInfo* rGInfo);
	void Redo(GraphicsInfo* rGInfo) ;

};