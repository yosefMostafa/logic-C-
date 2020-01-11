#include "Pin.h"

Pin::Pin()
{
	m_Status = NCON;	//Default Status is not connected
}

void Pin::setStatus(STATUS r_Status)
{
	m_Status = r_Status;
}

int Pin::getStatus()
{
	return m_Status;
}