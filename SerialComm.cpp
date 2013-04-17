#include "stdafx.h"
#include <string.h>
#include "SerialComm.h"

// serial communication
CSerialComm::CSerialComm()
{
	TRACE("new CSerialComm \n");
	this->serialport=new cnComm();
	type=COMM_TYPE_SERIAL;
	dev_name="null";
}

CSerialComm::~CSerialComm()
{
	TRACE("delete CSerialComm \n");
	this->Close();
	delete this->serialport;
}

BOOL CSerialComm::Init(ConfigArg_t conf)
{
	this->serialport->SetArg(conf.com,conf.baudrate,conf.timeout);
	TRACE("serial port init: com:%d baudrate:%d timeout:%d \n",conf.com,conf.baudrate,conf.timeout);
	return TRUE;
}

void CSerialComm::SetDevName(CString name)
{
	CCommunication::SetDevName(name);
}

CString CSerialComm::GetDevName()
{
	return CCommunication::GetDevName();
}

BOOL CSerialComm::Open()
{
	this->serialport->Open();
	if(this->serialport->IsOpen()){
		TRACE("open port success\n");
		return TRUE;
	}else{
		TRACE("open port failed.\n");
		return FALSE;
	}
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