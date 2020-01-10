#ifndef APPLICATION_MANAGER_H
#define APPLICATION_MANAGER_H

#include "Defs.h"
#include "UI\UI.h"
#include "Actions\Action.h"
#include "Components\Component.h"

//Main class that manages everything in the application.
class ApplicationManager
{

	enum { MaxCompCount = 200 };	//Max no of Components	

private:
		//List of all Components (Array of pointers)

	UI* pUI; //pointer to the UI

	
	int CompCount;		//Actual number of Components
	int comtype;
	Component* CompList[MaxCompCount];
	GraphicsInfo* rGInfo[MaxCompCount];
	ActionType RActtype[MaxCompCount];
	string label,cLabel;
public:	
	ApplicationManager(); //constructor
	//Reads the required action from the user and returns the corresponding action type
	ActionType GetUserAction();
	
	
	//Creates an action and executes it
	void ExecuteAction(ActionType);
	void delete1(int func);
	void save();
	void load();
	void selectd();
	void edit();
	void uselect();
	void copy();
	void cut();
	void move();
	void paste();
	void undo();
	void redo();	
	void UpdateInterface();	//Redraws all the drawing window

	//Gets a pointer to UI Object
	UI* GetUI();

	//Adds a new component to the list of components
	void AddComponent(Component* pComp);

	//destructor
	~ApplicationManager();
};

#endif