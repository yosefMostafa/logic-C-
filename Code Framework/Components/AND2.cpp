#include "AND2.h"




AND2::AND2(GraphicsInfo *r_pGfxInfo, int r_FanOut,bool tf,string s):Gate(r_pGfxInfo,2, r_FanOut)
{
	trandfa = tf; label = s;
}


void AND2::Operate()
{
	//caclulate the output status as the ANDing of the two input pins

	//Add you code here
}


// Function Draw
// Draws 2-input AND gate
void AND2::Draw(UI* pUI)
{
		//Call output class and pass gate drawing info to it.
		pUI->DrawAND2(*m_pGfxInfo,trandfa,label);
	
}

//returns status of outputpin
int AND2::GetOutPinStatus()	
{
	return m_OutputPin.getStatus();
}


//returns status of Inputpin #n
int AND2::GetInputPinStatus(int n)	
{
	return m_InputPins[n-1].getStatus();	//n starts from 1 but array index starts from 0.
}

//Set status of an input pin ot HIGH or LOW
void AND2::setInputPinStatus(int n, STATUS s)
{
	m_InputPins[n-1].setStatus(s);
}
void AND2::save(ofstream &data) {
	
	data << AND << "  " <<label<<"  "<< m_pGfxInfo->PointsList[0].x << "  " << m_pGfxInfo->PointsList[0].y <<"  "<< m_pGfxInfo->PointsList[1].x << "  " << m_pGfxInfo->PointsList[1].y << endl;
}