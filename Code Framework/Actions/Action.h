#ifndef _ACTION_H
#define _ACTION_H
#include<string>
using namespace std;
class ApplicationManager; //forward class declaration
struct GraphicsInfo;
class srting;
//Base class for all possible actions (abstract class)
class Action
{
protected:
	ApplicationManager *pManager; //Actions needs AppMngr to do their job
public:
	Action(ApplicationManager *pApp) { pManager = pApp; }//constructor

	//Execute action (code depends on action type)
	virtual void Execute(string s)=0;

	//To undo this action (code depends on action type)
	virtual  void Undo(GraphicsInfo* rGInfo)=0;

	//To redo this action (code depends on action type)
	virtual  void Redo(GraphicsInfo* rGInfo)=0;

};

#endif