#include "AddNANDgate.h"
#include<iostream>
#include "..\ApplicationManager.h"
#include"selectd.h"

AddNANDgate2::AddNANDgate2(ApplicationManager* pApp) :Action(pApp)
{
}

AddNANDgate2::~AddNANDgate2(void)
{
}

void AddNANDgate2::Execute()
{

	//Get a Pointer to the user Interfaces
	UI* pUI = pManager->GetUI();

	//Print Action Message
	pUI->PrintMsg("2-Input NAND Gate: Click to add the gate");

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
	NAND2* pA = new NAND2(pGInfo, AND2_FANOUT, true);
	pManager->AddComponent(pA);
}


void AddNANDgate2::Undo()
{}

void AddNANDgate2::Redo()
{}