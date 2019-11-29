#include "D:\zewail\Y2 Fall\C++\CIE202 - Project Fall 2019 - student\Code Framework\Components\OR2.h"
#include "OR2.h"


OR2::OR2(GraphicsInfo* r_pGfxInfo, int r_FanOut,bool tf) :Gate(r_pGfxInfo, 2, r_FanOut)
{
	trandfa = tf;
}


void OR2::Operate()
{
	//caclulate the output status as the ANDing of the two input pins

	//Add you code here
}


// Function Draw
// Draws 2-input AND gate
void OR2::Draw(UI* pUI)
{
	if (trandfa) {
		//Call output class and pass gate drawing info to it.
		pUI->DrawOR2(*m_pGfxInfo, true);
	}
	else {
		pUI->DrawOR2(*m_pGfxInfo, false);
	}
}

//returns status of outputpin
int OR2::GetOutPinStatus()
{
	return m_OutputPin.getStatus();
}


//returns status of Inputpin #n
int OR2::GetInputPinStatus(int n)
{
	return m_InputPins[n - 1].getStatus();	//n starts from 1 but array index starts from 0.
}

//Set status of an input pin ot HIGH or LOW
void OR2::setInputPinStatus(int n, STATUS s)
{
	m_InputPins[n - 1].setStatus(s);
}