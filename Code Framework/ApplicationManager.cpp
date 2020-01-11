#include "ApplicationManager.h"
#include "Actions\AddANDgate2.h"
#include "Actions\Addled.h"
#include "Actions\Addswitch.h"
#include "Actions\AddXORgate.h"
#include "Actions\AddNANDgate.h"
#include "Actions\AddXNORgate.h"
#include "Actions\AddNORgate.h"
#include "Actions\Addconc.h"
#include "Actions\AddORgate2.h"
#include "Actions\AddNOT.h"
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

	for (int i = 0; i < MaxCompCount; i++) {
		CompList[i] = NULL;
		rGInfo[i] = NULL;
		arrofswitches[i] = NULL;
		arrofleds[i] = NULL;
		arroflines[i] = NULL;
		RActtype[i]= DSN_TOOL;
	}
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
		case ADD_AND_GATE_2:
			pAct= new AddANDgate2(this);
			label = "AND";
			RActtype[CompCount] = ActType;
			break;
		case ADD_XOR_GATE_2:
			pAct = new AddXORgate(this);
			label = "XOR";
			RActtype[CompCount] = ActType;
			break;
		case ADD_OR_GATE_2:
			pAct = new AddORgate2(this);
			label = "OR";
			RActtype[CompCount] = ActType;
			break;
		case ADD_CONNECTION:
			pAct = new addconc(this);
			label = "Line";
			RActtype[CompCount] = ActType;
			break;
		case ADD_NAND_GATE_2:
			pAct = new AddNANDgate2(this);
			label = "NAND";
			RActtype[CompCount] = ActType;
			break;
		case ADD_NOR_GATE_2:
			pAct = new AddNORgate(this);
			label = "NOR";
			RActtype[CompCount] = ActType;
			break;
		case ADD_XNOR_GATE_2:
			pAct = new AddXNORgate(this);
			label = "XNOR";
			RActtype[CompCount] = ActType;
			break;
		case ADD_LED:
			pAct = new Addled(this);
			label = "Led";
			RActtype[CompCount] = ActType;
			break;
		case ADD_Switch:
			pAct=new Addswitch(this);
			label = "SWITCH";
			RActtype[CompCount] = ActType;
				break;
		case ADD_INV:
			pAct = new AddNOT(this);
			label = "NOT";
			RActtype[CompCount] = ActType;
			break;
		case PASTE:
			paste();
			break;
		case COPY:
			copy();
			break;
		case DEL:
			delete1(1);
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
		case CUT:
			cut();
			break;
		case EDIT_Label:
			edit();
			break;
		case USELECT:
			uselect();
			break;
		case MOVE:
			move();
			break;
		case UNDO:
			undo();
			break;
		case REDO:
			redo();
			break;
		case SIM_MODE:
			operate();
			break;
		case EXIT:
			break;
	}
	if(pAct)
	{
		pAct->Execute(label);
		rGInfo[CompCount-1] = new GraphicsInfo(2);
		pAct->Undo(rGInfo[CompCount-1]);
		delete pAct;
		pAct = NULL;
	}
}
////////////////////////////////////////////////////////////////////

void ApplicationManager::UpdateInterface()
{
	int width = pUI->getwidth(); int height = pUI->getheight();
	pUI->drawRectangle(0, 96, width- 100, height - 50);
	for (int i = 0; i < width - 100; i = i + 20) {
		pUI->drawline(i, 95, i, height - 50);
	}
	for (int i = 0; i < height - 150; i = i + 20) {
		pUI->drawline(0, i + 95, width - 95, i + 95);
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
	for (int i = 0; i < CompCount; i++) {
		delete CompList[i];
		delete rGInfo[i];
	}
	delete pUI;
}
///////////////////////////////////////////////////////////////////
void ApplicationManager::delete1(int func) {
	int Cx, Cy,c=0, n = 0;
	if (func == 0) {
		if (CompCount == 0) {

		}
		else {
			delete CompList[CompCount - 1];
			CompCount = CompCount - 1;
			UpdateInterface();
		}
	}
	else {
		for (int i = 0; i < CompCount; i++) {
			if (CompList[i]->gettrandfa() == false) {
				c = 1;
			}
		}
		if (c == 1) {
			int CompCount1 = CompCount;
			for (int i = 0; i < CompCount1; i++) {
				if (CompList[i]->gettrandfa() == false) {
					delete CompList[i];
					delete rGInfo[i];
					ActionType LActtype;
					RActtype[i] = DSN_TOOL;
					LActtype= RActtype[i];//yosef added
					CompList[i] = CompList[CompCount - 1];
					rGInfo[i] = rGInfo[CompCount-1];
					RActtype[i] = RActtype[CompCount - 1];
					RActtype[CompCount - 1]= LActtype;
					CompCount = CompCount - 1;
					pUI->PrintMsg("deleted");
					UpdateInterface();
				}
			}
		}
		else {
			pUI->PrintMsg("select component to delete .");
			pUI->GetPointClicked(Cx, Cy);
			pUI->ClearStatusBar();
			for (int i = 0; i < CompCount; i++) {
				if (CompList[i]->selected(Cx, Cy)) {
					delete CompList[i];
					delete rGInfo[i];
					ActionType LActtype;
					RActtype[i] = DSN_TOOL;
					LActtype = RActtype[i];//yosef added
					CompList[i] = CompList[CompCount - 1];
					rGInfo[i] = rGInfo[CompCount - 1];
					RActtype[i] = RActtype[CompCount - 1];
					RActtype[CompCount - 1] = LActtype;
					CompCount = CompCount - 1;
					UpdateInterface();
					n = 1;
				}
				else {
					if (n == 0) {
						pUI->PrintMsg("an empty place");
					}
				}
			}
		}
	}

	//Clear Status Bar
	/*if (c == 0) {
		pUI->PrintMsg("Click to delete the gate");
	}
	else {
		pUI->PrintMsg("Select to delete anothe Components or press any where");
		pUI->GetPointClicked(Cx, Cy);
	}*/
	
	/*for (int i = 0; i <CompCount; i++) {
			if (CompList[i]->selected(Cx, Cy)) {
				delete CompList[i];//yosef added
				CompList[i] = CompList[CompCount - 1];
				CompCount = CompCount - 1;
				pUI->PrintMsg("deleted");
			}
			else {
				pUI->PrintMsg("an empty place");
			}
	}*/
}
///////////////////////////////////////////////////////////////////
void ApplicationManager::selectd() {
	int j=0;
	for (int i = 0; i < CompCount; i++) {
		if (CompList[i]->selected(pUI->getlastclickx(), pUI->getlastclicky())) {
			j = 0;
			break;
		}
		else {
			j = 1;
		}
	}
	for (int i = 0; i < CompCount; i++) {
		if (CompList[i]->selected(pUI->getlastclickx(), pUI->getlastclicky())) {
			CompList[i]->settrandfa(false);
		}
		else if (j == 1) {
			CompList[i]->settrandfa(true);
		}
	}
}
///////////////////////////////////////////////////////////////////
void ApplicationManager::save() {
	string filename;
	pUI->ClearStatusBar();
	pUI->GetString(filename);
	ofstream datafile_1;
	datafile_1.open(filename);

	for (int i = 0; i < CompCount; i++) 
	 {
		CompList[i]->save(datafile_1);
	}
	pUI->PrintMsg("saved");
	datafile_1.close();
}
///////////////////////////////////////////////////////////////////
void ApplicationManager::load() {
	string filename;
	pUI->GetString(filename);
	ifstream datafile_1(filename);
	int gate;
	enum gate {
		AND,
		OR,
		NAND,
		XOR1,
		LINE,
		XNOR1,
		NOR1,
		LED,
		Switch1,
		NOT1,
		LEBGHT
	};
	int x, y, x1, y1;
	string label;
	Component* pA = NULL;
	while (datafile_1>>gate>>label>>x>>y>>x1>>y1) {
		GraphicsInfo* pGInfo = new GraphicsInfo(2); //Gfx info to be used to construct the Component
		pGInfo->PointsList[0].x = x;
		pGInfo->PointsList[0].y = y;
		pGInfo->PointsList[1].x = x1;
		pGInfo->PointsList[1].y = y1;
		switch(gate)
		{
			case AND:
				pA = new AND2(pGInfo, AND2_FANOUT, true,label);
				break;
			case OR:
				pA = new OR2(pGInfo, AND2_FANOUT, true, label);
				break;
			case NAND:
				pA = new NAND2(pGInfo, AND2_FANOUT, true, label);
				break;
			case XOR1:
				pA = new XOR(pGInfo, AND2_FANOUT, true, label);
				break;
			case LINE:
				pA = new Connection(pGInfo,true, label);
				break;
			case XNOR1:
				pA = new XNOR(pGInfo, AND2_FANOUT, true, label);
				break;
			case NOR1:
				pA = new NOR(pGInfo, AND2_FANOUT, true, label);
				break;
			case LED:
				pA = new Led(pGInfo, AND2_FANOUT, true, label);
				break;
			case Switch1:
				pA = new Switch(pGInfo, AND2_FANOUT, true, label);
				break;
			case NOT1:
				pA = new NOT(pGInfo, AND2_FANOUT, true, label);
				break;
		}
		if (pA) {
			AddComponent(pA);
			pA = NULL;
		}
	}
	delete pA;
	datafile_1.close();
}
///////////////////////////////////////////////////////////////////
void ApplicationManager::edit() {
	pUI->PrintMsg("Select Component to change the label");
	int x, y;
	pUI->GetPointClicked(x, y);
	for (int i = 0; i < CompCount; i++) {
		if (CompList[i]->selected(x,y))
		{
			pUI->ClearStatusBar();
				string s;
				pUI->GetString(s);
			CompList[i]->setlabel(s);
		}
	}
	pUI->ClearStatusBar();
}
///////////////////////////////////////////////////////////////////
void ApplicationManager::uselect() {
	for (int i = 0; i < CompCount; i++) {
		if (CompList[i]->gettrandfa() == false) {
			CompList[i]->settrandfa(true);
		}
	}
}
void ApplicationManager::copy() {
	for (int i = 0; i < CompCount; i++) {
		if (CompList[i]->gettrandfa() == false) {
			CompList[i]->getlabel(cLabel);
			if (cLabel == "Line") {
				pUI->PrintMsg("Line can't be Copied");
			}
			else {
				pUI->PrintMsg("Copied");
				comtype=CompList[i]->copy();
			}
		}
	}
}
void ApplicationManager::cut() {
	int x = 0;//needs improvments (conc)
	for (int i = 0; i < CompCount; i++) {
		if (CompList[i]->gettrandfa() == false) {
			CompList[i]->getlabel(cLabel);
			if (cLabel == "Line") {
				pUI->PrintMsg("Line can't be Cuted");
			}
			else {
				x++;
				if (x == 2) {
					break;
				}
				else {
					delete CompList[i];
					CompList[i] = CompList[CompCount - 1];
					CompCount = CompCount - 1;
					UpdateInterface();
					pUI->PrintMsg("Cuted");
					comtype = CompList[i]->copy();
				}
			}
		}
	}
}
void ApplicationManager::paste() {
	pUI->PrintMsg(" ");
	Action* pAct = NULL;
	if (comtype == AND) {
		pAct = new AddANDgate2(this);
		RActtype[CompCount] = ADD_AND_GATE_2;
	}
	else if (comtype == XOR1) {
		pAct = new AddXORgate(this);
		RActtype[CompCount] = ADD_XOR_GATE_2;
	}
	else if (comtype == OR) {
		pAct = new AddORgate2(this);
		RActtype[CompCount] = ADD_OR_GATE_2;
	}
	else if (comtype == NAND) {
		pAct = new AddNANDgate2(this);
		RActtype[CompCount] = ADD_NAND_GATE_2;
	}
	else if (comtype == NOR1) {
		pAct = new AddNORgate(this);
		RActtype[CompCount] = ADD_NOR_GATE_2;
	}
	else if (comtype == XNOR1) {
		pAct = new AddXNORgate(this);
		RActtype[CompCount] = ADD_XNOR_GATE_2;
	}
	else if (comtype == LED) {
		pAct = new Addled(this);
		RActtype[CompCount] = ADD_LED;
	}
	else if (comtype == Switch1){
		pAct = new Addswitch(this);
		RActtype[CompCount] = ADD_Switch;
    }else if (comtype == NOT1){
		pAct = new AddNOT(this);
		RActtype[CompCount] = ADD_INV;
	}
	if (pAct)
	{
		pAct->Execute(cLabel);
		rGInfo[CompCount-1] = new GraphicsInfo(2);
		pAct->Undo(rGInfo[CompCount-1]);
		delete pAct;
		pAct = NULL;
		pUI->PrintMsg("Pasted");
	}
}
void ApplicationManager::move() {
	int x, y;
	int x2 = 0, y2 = 0;
	string s;
	for (int i = 0; i < CompCount; i++) {
		while (CompList[i]->gettrandfa() == false) {
			pUI->getmousecor(x, y);
			int pics = 0;
			if ((x2 == x || y2 == y)) {
			}
			else if ((x2 > x + pics || x2 < x - pics) && (y2 > y + pics || y2 < y - pics)) {
				CompList[i]->getlabel(s);
				int x1, y1;
				if (s == "Line") {
					GraphicsInfo* pGInfo = new GraphicsInfo(2);
					GraphicsInfo* pGInfonew = new GraphicsInfo(2);//Gfx info to be used to construct
					CompList[i]->getGInfo(pGInfo);
						//pGInfonew->PointsList[0].x = x/2;
						//pGInfonew->PointsList[1].x = pGInfo->PointsList[1].x +(x - x2);
						//pGInfonew->PointsList[0].y = (10);
						//pGInfonew->PointsList[1].y = pGInfo->PointsList[1].y + (y- y2);
						CompList[i]->setGInfo(pGInfonew);
						UpdateInterface();
				
					/*/if (pGInfo->PointsList[0].y > (pUI->getToolBarHeight()) + 15 &&
						pGInfo->PointsList[1].y < (pUI->getheight()) - (pUI->getStatusBarHeight()) &&
						pGInfo->PointsList[0].y < (pUI->getheight()) - (pUI->getStatusBarHeight()) &&
						pGInfo->PointsList[1].y >(pUI->getToolBarHeight()) + 15 &&
						pGInfo->PointsList[0].x < (pUI->getwidth()) - 100 &&
						pGInfo->PointsList[1].x < (pUI->getwidth()) - 100) {
						UpdateInterface();
					}*/
					pUI->getmouseclick(x1, y1);
					if (x1 > 0) {
						break;
					}
					x2 = x; y = y2;
				}
				else {
					GraphicsInfo* pGInfo = new GraphicsInfo(2); //Gfx info to be used to construct
					pGInfo->PointsList[0].x = x - 25;
					pGInfo->PointsList[0].y = y - 25;
					pGInfo->PointsList[1].x = x + 25;
					pGInfo->PointsList[1].y = y + 25;
					CompList[i]->setGInfo(pGInfo);
					if (pGInfo->PointsList[0].y > (pUI->getToolBarHeight()) + 15 &&
						pGInfo->PointsList[1].y < (pUI->getheight()) - (pUI->getStatusBarHeight()) &&
						pGInfo->PointsList[0].y < (pUI->getheight()) - (pUI->getStatusBarHeight()) &&
						pGInfo->PointsList[1].y >(pUI->getToolBarHeight()) + 15 &&
						pGInfo->PointsList[0].x < (pUI->getwidth()) - 100 &&
						pGInfo->PointsList[1].x < (pUI->getwidth()) - 100){
						UpdateInterface();
				    }
					pUI->getmouseclick(x1, y1);
					if (x1 > 0) {
						break;
					}
					x2 = x; y = y2;
				}
			}
			else {

			}

		}
	}
}
void ApplicationManager::undo() {
	delete1(0);
}
void ApplicationManager::redo() {
	Action* pAct = NULL;
	switch (RActtype[CompCount])
	{
	case ADD_AND_GATE_2:
		pAct = new AddANDgate2(this);
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
	case ADD_LED:
		pAct = new Addled(this);
		break;
	case ADD_Switch:
		pAct = new Addswitch(this);
		break;
	case ADD_INV:
		pAct = new AddNOT(this);
		break;
	}
	if (pAct)
	{
		pAct->Redo(rGInfo[CompCount]);
		delete pAct;
		pAct = NULL;
	}
}
Component* ApplicationManager::CPoint(GraphicsInfo* rGInfo,int &pin) {
	for (int i = 0; i < CompCount; i++) {
		if (CompList[i]->selected(rGInfo->PointsList[0].x, rGInfo->PointsList[0].y))
		{
			pin = CompList[i]->checker(rGInfo);
			return CompList[i];
		}
	}
	return NULL;
}
void ApplicationManager::search() {
	nofswitches(arrofswitches,Snumber);
	noflines(arroflines, Linumber);
	nofleds(arrofleds, Lenumber);
	

	operate();
}
void ApplicationManager::nofswitches(int arr[], int& s) {
	int switchpin,c=0;
	for (int i = 0; i < CompCount; i++) {
		switchpin=CompList[i]->copy();
		if (switchpin==8) {
			arr[c] = i;
			c++;
			s = c;
		}
	}
}
void ApplicationManager::nofleds(int arr[], int& s){
	int ledpin, c = 0;
	for (int i = 0; i < CompCount; i++) {
		ledpin = CompList[i]->copy();
		if (ledpin == 7) {
			arr[c] = i;
			c++;
			s = c;
		}
	}
}
void ApplicationManager::noflines(int arr[], int& s){
	int concpin, c = 0;
	for (int i = 0; i < CompCount; i++) {
		concpin = CompList[i]->copy();
		if (concpin == 4) {
			arr[c] = i;
			c++;
			s = c;
		}
	}
}
void ApplicationManager::operate() {
	for (int j = 0; j< CompCount; j++) {
		for (int i = 0; i < CompCount; i++) {
			CompList[i]->Operate();
		}
	}
}

