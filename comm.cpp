#include "StdAfx.h"
#include "comm.h"

CCommunication::CCommunication()
{
	this->bTestMode=FALSE;
};

CCommunication::~CCommunication()
{
	this->bTestMode=FALSE;
};

void CCommunication::SetTestMode(BOOL mode)
{
	this->bTestMode=mode;
}

BOOL CCommunication::GetTestMode()
{
	return this->bTestMode;
}