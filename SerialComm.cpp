#include "stdafx.h"
#include <string.h>
#include "SerialComm.h"


// serial communication
CSerialComm::CSerialComm()
{
	this->serialport=new cnComm();
}

CSerialComm::~CSerialComm()
{
	this->Close();
	delete this->serialport;
}

BOOL CSerialComm::Configure(ConfigArg_t conf)
{
	this->serialport->Open(conf.com,conf.baudrate);
	return TRUE;
}

BOOL CSerialComm::Open()
{
	this->serialport->Open();
	return TRUE;
}
BOOL CSerialComm::Close()
{
	this->serialport->Close();
	return TRUE;
}

BOOL CSerialComm::Read(char *buf, int size)
{
	return (this->serialport->Read(buf,size) == 0) ? FALSE : TRUE;
}

BOOL CSerialComm::Write(char *buf, int size)
{
	return (this->serialport->Write(buf,size) == 0) ? FALSE : TRUE;
}

BOOL CSerialComm::IsSystemBoot()
{
	return FALSE;
}

BOOL CSerialComm::Handshake()
{
	return FALSE;
}

/////////////////////////////////////////////////////////////////////////////////////
// every test modules
/////////////////////////////////////////////////////////////////////////////////////
CSerialGetInfo::PerformTest()
{
	char buf[1024];
	cout << "Get Info ...." << endl;
	strcpy(buf,"date 122001102012.10");
	comm->Write(buf,strlen(buf));
	comm->Read(buf,sizeof(buf));
	cout << "read data :" << endl << buf << endl;
	return TRUE;
}

CSerialSetTime::PerformTest()
{
	cout << "Set time ..." << endl;
	return TRUE;
}