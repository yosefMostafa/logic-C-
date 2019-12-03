#include "Connection.h"

Connection::Connection(GraphicsInfo *r_GfxInfo, OutputPin *pSrcPin,InputPin *pDstPin):Component(r_GfxInfo)	
{
	*m_pGfxInfo = *r_GfxInfo;
	SrcPin = pSrcPin;
	DstPin = pDstPin;
}
Connection::Connection(GraphicsInfo* r_GfxInfo, bool trfa) :Component(r_GfxInfo) {
	trandfa = trfa;
}
void Connection::setSourcePin(OutputPin *pSrcPin)
{	SrcPin = pSrcPin;	}

OutputPin* Connection::getSourcePin()
{	return SrcPin;	}


void Connection::setDestPin(InputPin *pDstPin)
{	DstPin = pDstPin;	}

InputPin* Connection::getDestPin()
{	return DstPin;	}



void Connection::Operate()
{
	//Status of connection destination pin = status of connection source pin
	DstPin->setStatus((STATUS)SrcPin->getStatus());
}

void Connection::Draw(UI* pUI)
{

	pUI->DrawConnection(*m_pGfxInfo,trandfa);
}

int Connection::GetOutPinStatus()	//returns status of outputpin if LED, return -1
{
	return DstPin->getStatus();
}


int Connection::GetInputPinStatus(int n)	//returns status of Inputpin # n if SWITCH, return -1
{
	return SrcPin->getStatus();	//n is ignored as connection has only one input pin (src pin)	
}

void Connection::setInputPinStatus(int n, STATUS s)
{
	SrcPin->setStatus(s);
}
bool Connection::selected(int x, int y) {
	int z = m_pGfxInfo->PointsList[1].x;
	if ( (y<=(m_pGfxInfo->PointsList[0].y)+5 && y>= (m_pGfxInfo->PointsList[0].y)-5)&&((x> m_pGfxInfo->PointsList[0].x&&x< m_pGfxInfo->PointsList[1].x)||(x> m_pGfxInfo->PointsList[1].x&& x<m_pGfxInfo->PointsList[0].x))) {
		return true;
	}if ((x<=(m_pGfxInfo->PointsList[1].x)+5 && x>=( m_pGfxInfo->PointsList[1].x)-5)&&((y> m_pGfxInfo->PointsList[0].y&&y< m_pGfxInfo->PointsList[1].y)||(y> m_pGfxInfo->PointsList[1].y&&y< m_pGfxInfo->PointsList[0].y))) {
		return true;
	}else {
		false;
	}
	return false;
}
