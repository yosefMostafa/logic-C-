#include "D:\zewail\Y2 Fall\C++\CIE202 - Project Fall 2019 - student\logic-C-\Code Framework\ApplicationManager.h"
#include "addconc.h"
#include "D:\zewail\Y2 Fall\C++\CIE202 - Project Fall 2019 - student\logic-C-\Code Framework\Components\Connection.h"
void addconc::Execute() {
	//Get a Pointer to the user Interfaces
	UI* pUI = pManager->GetUI();

	//Print Action Message
	pUI->PrintMsg("2-Input draw line : Click to add the gate");

	//Get Center point of the Gate
	pUI->GetPointClicked(Cx, Cy);
	pUI->GetPointClicked(Cx1, Cy1);
	//Clear Status Bar
	pUI->ClearStatusBar();
	//Calculate the rectangle Corners
	//int gateWidth = pUI->getGateWidth();
	//int gateHeight = pUI->getGateHeight();

	GraphicsInfo* pGInfo = new GraphicsInfo(2); //Gfx info to be used to construct the AND2 gate

	pGInfo->PointsList[0].x = Cx;
	pGInfo->PointsList[0].y = Cy;
	pGInfo->PointsList[1].x = Cx1;
	pGInfo->PointsList[1].y = Cy1;
	// TODO: Check thet the pointys belong to pins
	//pManager->CompList[0];
	Connection* pA = new Connection(pGInfo);
	pManager->AddComponent(pA);
	
}
void addconc::Undo() {}
void addconc::Redo() {}
addconc::addconc(ApplicationManager* pApp) :Action(pApp)
{
}
