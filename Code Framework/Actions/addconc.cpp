#include "D:\zewail\Y2 Fall\C++\CIE202 - Project Fall 2019 - student\logic-C-\Code Framework\ApplicationManager.h"
#include "addconc.h"
#include "..\Components\Connection.h"
#include "..\Components\Gate.h"
void addconc::Execute(string s) {
	//Get a Pointer to the user Interfaces
	UI* pUI = pManager->GetUI();

	//Print Action Message
	pUI->PrintMsg("2-Input draw line : Click to add Connecction");
	int Cx, Cy, Cx1, Cy1;	//ends of the line 
	//Get Center point of the Gate
	pUI->GetPointClicked(Cx, Cy);
	pUI->GetPointClicked(Cx1, Cy1);
	//Clear Status Bar
	pUI->ClearStatusBar();
	//Calculate the rectangle Corners
	//int gateWidth = pUI->getGateWidth();
	//int gateHeight = pUI->getGateHeight();
	

	pGInfo = new GraphicsInfo(2); //Gfx info to be used to construct the AND2 gate

	pGInfo->PointsList[0].x = Cx;
	pGInfo->PointsList[0].y = Cy;
	pGInfo->PointsList[1].x = Cx1;
	pGInfo->PointsList[1].y = Cy1;
	// TODO: Check thet the pointys belong to pins
	if (pGInfo->PointsList[0].y > (pUI->getToolBarHeight()) + 15 &&
		pGInfo->PointsList[1].y < (pUI->getheight()) - (pUI->getStatusBarHeight()) &&
		pGInfo->PointsList[0].y < (pUI->getheight()) - (pUI->getStatusBarHeight()) &&
		pGInfo->PointsList[1].y >(pUI->getToolBarHeight()) + 15 &&
		pGInfo->PointsList[0].x < (pUI->getwidth()) - 100 &&
		pGInfo->PointsList[1].x < (pUI->getwidth()) - 100) {
		Connection* pA = new Connection(pGInfo, true, s);
		pManager->AddComponent(pA);
	}
	else {
		pUI->PrintMsg("Invalid place.Try again.");
	}
}
void addconc::Undo(GraphicsInfo* rGInfo) {
	rGInfo->PointsList[0].x = pGInfo->PointsList[0].x;
	rGInfo->PointsList[1].x = pGInfo->PointsList[1].x;
	rGInfo->PointsList[1].y = pGInfo->PointsList[1].y;
	rGInfo->PointsList[0].y = pGInfo->PointsList[0].y;
}
void addconc::Redo(GraphicsInfo* pGInfo) {
	UI* pUI = pManager->GetUI();
	if (pGInfo->PointsList[0].y > (pUI->getToolBarHeight()) + 15 &&
		pGInfo->PointsList[1].y < (pUI->getheight()) - (pUI->getStatusBarHeight()) &&
		pGInfo->PointsList[0].y < (pUI->getheight()) - (pUI->getStatusBarHeight()) &&
		pGInfo->PointsList[1].y >(pUI->getToolBarHeight()) + 15 &&
		pGInfo->PointsList[0].x < (pUI->getwidth()) - 100 &&
		pGInfo->PointsList[1].x < (pUI->getwidth()) - 100) {
		Connection* pA = new Connection(pGInfo, true, "Line");
		pManager->AddComponent(pA);
	}
}
addconc::addconc(ApplicationManager* pApp) :Action(pApp)
{
}
