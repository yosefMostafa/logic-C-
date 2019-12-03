#include<iostream>
#include"selectd.h"
#include "..\ApplicationManager.h"
using namespace std;
selectd::selectd(ApplicationManager* pApp):Action(pApp){
}
void selectd::Execute() {
	//Get a Pointer to the user Interfaces
	UI* pUI = pManager->GetUI();


	for (int i = 0; i <pManager->CompCount; i++) {
		if (pManager->CompList[i]->selected(pUI->getlastclickx(), pUI->getlastclicky())) {
			pManager->CompList[i]->trandfa= false;
		}
		else {
			pManager->CompList[i]->trandfa = true;
		}
	}
}
	