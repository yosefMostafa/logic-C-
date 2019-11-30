#pragma once
#pragma once
#include "Action.h"
class empty : public Action
{
private:
	ApplicationManager* pManager; 
public:
	empty(ApplicationManager *pApp) { pManager = pApp; };
	void Draw() {};
};
