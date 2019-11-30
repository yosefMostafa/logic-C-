#include "delete.h"
#include<iostream>
#include "..\ApplicationManager.h"
#include "empty.h"

delete1::delete1(ApplicationManager* pApp) :Action(pApp)
{
}

delete1::~delete1(void)
{
}

void delete1::Execute()
{

	//Get a Pointer to the user Interfaces
	UI* pUI = pManager->GetUI();

	//Print Action Message
	pUI->PrintMsg("2-Input AND Gate: Click to add the gate");

	//Get Center point of the Gate
	pUI->GetPointClicked(Cx, Cy);

	//Clear Status Bar
	pUI->ClearStatusBar();
	for (int i = 0; i < pManager->CompCount; i++) {
		if (pManager->CompList[i]->selected(Cx, Cy)) {
			pUI->PrintMsg("deleted");//yosef added
			//pManager->CompList[i]=new empty(this);
		}
		else {
			pUI->PrintMsg("an empty place");
		}
	}
}


void delete1::Undo()
{}

void delete1::Redo()
{}