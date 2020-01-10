#include "AddNORgate.h"
#include<iostream>
#include "..\ApplicationManager.h"

AddNORgate::AddNORgate(ApplicationManager* pApp) :Action(pApp)
{
}

AddNORgate::~AddNORgate(void)
{
}

void AddNORgate::Execute(string s)
{

	//Get a Pointer to the user Interfaces
	UI* pUI = pManager->GetUI();

	//Print Action Message
	pUI->PrintMsg("2-Input NOR Gate: Click to add the gate");

	//Get Center point of the Gate
	pUI->GetPointClicked(Cx, Cy);

	//Clear Status Bar
	pUI->ClearStatusBar();
	//Calculate the rectangle Corners
	int gateWidth = pUI->getGateWidth();
	int gateHeight = pUI->getGateHeight();

	pGInfo = new GraphicsInfo(2); //Gfx info to be used to construct the AND2 gate

	pGInfo->PointsList[0].x = Cx - gateWidth / 2;
	pGInfo->PointsList[0].y = Cy - gateHeight / 2;
	pGInfo->PointsList[1].x = Cx + gateWidth / 2;
	pGInfo->PointsList[1].y = Cy + gateHeight / 2;
	if (pGInfo->PointsList[0].y > (pUI->getToolBarHeight()) + 15 &&
		pGInfo->PointsList[1].y < (pUI->getheight()) - (pUI->getStatusBarHeight()) &&
		pGInfo->PointsList[0].y < (pUI->getheight()) - (pUI->getStatusBarHeight()) &&
		pGInfo->PointsList[1].y >(pUI->getToolBarHeight()) + 15 &&
		pGInfo->PointsList[0].x < (pUI->getwidth()) - 100 && pGInfo->PointsList[1].x < (pUI->getwidth()) - 100) {
		NOR* pA = new NOR(pGInfo, AND2_FANOUT, true, s);
		pManager->AddComponent(pA);
	}
	else {
		pUI->PrintMsg("Invalid place.Try again.");
	}
}


void AddNORgate::Undo(GraphicsInfo* rGInfo)
{
	rGInfo->PointsList[0].x = pGInfo->PointsList[0].x;
	rGInfo->PointsList[1].x = pGInfo->PointsList[1].x;
	rGInfo->PointsList[1].y = pGInfo->PointsList[1].y;
	rGInfo->PointsList[0].y = pGInfo->PointsList[0].y;
}

void AddNORgate::Redo(GraphicsInfo* pGInfo)
{
	UI* pUI = pManager->GetUI();
	if (pGInfo->PointsList[0].y > (pUI->getToolBarHeight()) + 15 &&
		pGInfo->PointsList[1].y < (pUI->getheight()) - (pUI->getStatusBarHeight()) &&
		pGInfo->PointsList[0].y < (pUI->getheight()) - (pUI->getStatusBarHeight()) &&
		pGInfo->PointsList[1].y >(pUI->getToolBarHeight()) + 15 &&
		pGInfo->PointsList[0].x < (pUI->getwidth()) - 100 &&
		pGInfo->PointsList[1].x < (pUI->getwidth()) - 100) {
		NOR* pA = new NOR(pGInfo, AND2_FANOUT, true, "NOR");
		pManager->AddComponent(pA);
	}
}