#include "AddXORgate.h"
#include<iostream>
#include "..\ApplicationManager.h"
#include "..\Components\XOR.h"
AddXORgate::AddXORgate(ApplicationManager* pApp) :Action(pApp)
{
}

AddXORgate::~AddXORgate(void)
{
}

void AddXORgate::Execute()
{

	//Get a Pointer to the user Interfaces
	UI* pUI = pManager->GetUI();

	//Print Action Message
	pUI->PrintMsg("2-Input XOR Gate: Click to add the gate");

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
	XOR* pA = new XOR(pGInfo, AND2_FANOUT, true);
	pManager->AddComponent(pA);
}


void AddXORgate::Undo()
{}

void AddXORgate::Redo()
{}