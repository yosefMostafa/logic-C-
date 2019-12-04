#include "ApplicationManager.h"
#include "Actions\AddANDgate2.h"
#include "Actions\AddXORgate.h"
#include "Actions\AddNANDgate.h"
#include "Actions\AddXNORgate.h"
#include "Actions\AddNORgate.h"
#include "Actions\Addconc.h"
#include "Actions\AddORgate2.h"
#include "Actions\Action.h"
#include "Components\OR2.h"
#include "Components\XOR.h"
#include "Components\connection.h"
#include <iostream>
#include <fstream>
using namespace std;


ApplicationManager::ApplicationManager()
{
	CompCount = 0;

	for(int i=0; i<MaxCompCount; i++)
		CompList[i] = NULL;

	//Creates the UI Object & Initialize the UI
	pUI = new UI;
}
////////////////////////////////////////////////////////////////////
void ApplicationManager::AddComponent(Component* pComp)
{
	CompList[CompCount++] = pComp;		
}
////////////////////////////////////////////////////////////////////

ActionType ApplicationManager::GetUserAction()
{
	//Call input to get what action is reuired from the user
	return pUI->GetUserAction(); 	
}
////////////////////////////////////////////////////////////////////

void ApplicationManager::ExecuteAction(ActionType ActType)
{
	Action* pAct = NULL;
	switch (ActType)
	{
		UI *pUI;
		case ADD_AND_GATE_2:
			pAct= new AddANDgate2(this);
			break;
		case ADD_XOR_GATE_2:
			pAct = new AddXORgate(this);
			break;
		case ADD_OR_GATE_2:
			pAct = new AddORgate2(this);
			break;
		case ADD_CONNECTION:
			pAct = new addconc(this);
			break;
		case ADD_NAND_GATE_2:
			pAct = new AddNANDgate2(this);
			break;
		case ADD_NOR_GATE_2:
			pAct = new AddNORgate(this);
			break;
		case ADD_XNOR_GATE_2:
			pAct = new AddXNORgate(this);
			break;
		case DEL:
			delete1();
			break;
		case SELECT:
			selectd();
			break;
		case SAVE:
			save();
			break;
		case LOAD:
			load();
			break;
		case EXIT:
			break;
	}
	if(pAct)
	{
		pAct->Execute();
		delete pAct;
		pAct = NULL;
	}
}
////////////////////////////////////////////////////////////////////

void ApplicationManager::UpdateInterface()
{
	int width = 1280; int height = 720;
	pUI->drawRectangle(0, 96, width- 100, height - 50);
	for (int i = 0; i < width - 100; i = i + 20) {
		pUI->drawline(i, 95, i, height - 50);
	}
	for (int i = 0; i < height - 150; i = i + 20) {
		pUI->drawline(0, i + 95, width - 100, i + 95);
	}
		for(int i=0; i<CompCount; i++)
			CompList[i]->Draw(pUI);

}

////////////////////////////////////////////////////////////////////
UI* ApplicationManager::GetUI()
{
	return pUI;
}

////////////////////////////////////////////////////////////////////

ApplicationManager::~ApplicationManager()
{
	for(int i=0; i<CompCount; i++)
		delete CompList[i];
	delete pUI;
	
}
///////////////////////////////////////////////////////////////////
void ApplicationManager::delete1() {
	//Get a Pointer to the user Interfaces

	//Print Action Message
	pUI->PrintMsg("Click to delete the gate");
	int Cx, Cy;
	//Get Center point of the Gate
	pUI->GetPointClicked(Cx, Cy);

	//Clear Status Bar
	pUI->ClearStatusBar();
	for (int i = 0; i <CompCount; i++) {
		if (CompList[i]->selected(Cx, Cy)) {
			delete CompList[i];//yosef added
			CompList[i] = CompList[CompCount - 1];
			CompCount =CompCount - 1;
			pUI->PrintMsg("deleted");
		}
		else {
			pUI->PrintMsg("an empty place");
		}
	}
}
///////////////////////////////////////////////////////////////////
void ApplicationManager::selectd() {

	for (int i = 0; i <CompCount; i++) {
		if (CompList[i]->selected(pUI->getlastclickx(), pUI->getlastclicky())) {
			CompList[i]->trandfa = false;
		}
		else {
			CompList[i]->trandfa = true;
		}
	}
}
///////////////////////////////////////////////////////////////////
void ApplicationManager::save() {
	ofstream datafile_1;
	datafile_1.open("data.txt");

	for (int i = 0; i < CompCount; i++) 
	 {
		CompList[i]->save(datafile_1);
	}
	pUI->PrintMsg("saved");
	datafile_1.close();
}
///////////////////////////////////////////////////////////////////
void ApplicationManager::load() {
	//string filedir;
	//cout << "Enter file directory\n";
	ifstream datafile_1("data.txt");
	int gate;
	enum gate {
		AND,
		OR,
		NAND,
		XOR1,
		LINE,
		XNOR1,
		NOR1,
		LEBGHT
	};
	int x, y, x1, y1;
	while (datafile_1>>gate>>x>>y>>x1>>y1) {
		GraphicsInfo* pGInfo = new GraphicsInfo(2); //Gfx info to be used to construct the Component
		pGInfo->PointsList[0].x = x;
		pGInfo->PointsList[0].y = y;
		pGInfo->PointsList[1].x = x1;
		pGInfo->PointsList[1].y = y1;
		Component* pA = NULL;
		switch(gate)
		{
			case AND:
				pA = new AND2(pGInfo, AND2_FANOUT, true);
				break;
			case OR:
				pA = new OR2(pGInfo, OR2_FANOUT, true);
				break;
			case NAND:
				pA = new NAND2(pGInfo, AND2_FANOUT, true);
				break;
			case XOR1:
				pA = new XOR(pGInfo, AND2_FANOUT, true);
				break;
			case LINE:
				pA = new Connection(pGInfo,true);
				AddComponent(pA);
				break;
			case XNOR1:
				pA = new XNOR(pGInfo, AND2_FANOUT, true);
				break;
			case NOR1:
				pA = new NOR(pGInfo, AND2_FANOUT, true);
				break;
		}
		if (pA) {
			AddComponent(pA);
			pA = NULL;
		}
	}
}