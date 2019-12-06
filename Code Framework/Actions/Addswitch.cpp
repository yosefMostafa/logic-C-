#include "Addswitch.h"
#include<iostream>
#include "..\ApplicationManager.h"

Addswitch::Addswitch(ApplicationManager* pApp) :Action(pApp)
{
}

Addswitch::~Addswitch(void)
{
}

void Addswitch::Execute()
{

	//Get a Pointer to the user Interfaces
	UI* pUI = pManager->GetUI();

	//Print Action Message
	pUI->PrintMsg("Switch: Click to add the gate");

	//Get Center point of the Gate
	pUI->GetPointClicked(Cx, Cy);

	//Clear Status Bar
	pUI->ClearStatusBar();
	//Calculate the rectangle Corners
	int gateWidth = pUI->getGateWidth();
	int gateHeight = pUI->getGateHeight();

	GraphicsInfo* pGInfo = new GraphicsInfo(2); //Gfx info to be used to construct the AND2 gate

	pGInfo->PointsList[0].x = Cx - gateWidth / 2;
	pGInfo->PointsList[0].y = Cy - gateHeight / 2;
	pGInfo->PointsList[1].x = Cx + gateWidth / 2;
	pGInfo->PointsList[1].y = Cy + gateHeight / 2;
	Switch* pA = new Switch(pGInfo, AND2_FANOUT, true, "SWITCH");
	pManager->AddComponent(pA);
}


void Addswitch::Undo()
{}

void Addswitch::Redo()
{}