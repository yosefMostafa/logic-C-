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
	pUI->PrintMsg("Click to delete the gate");

	//Get Center point of the Gate
	pUI->GetPointClicked(Cx, Cy);

	//Clear Status Bar
	pUI->ClearStatusBar();
	for (int i = 0; i < pManager->CompCount; i++) {
		if (pManager->CompList[i]->selected(Cx, Cy)) {
			delete pManager->CompList[i];//yosef added
			pManager->CompList[i] = pManager->CompList[pManager->CompCount - 1];
			pManager->CompCount = pManager->CompCount - 1;
			pUI->PrintMsg("deleted");
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