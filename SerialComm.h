#ifndef __SERIAL_COMM_H__
#define __SERIAL_COMM_H__

#include "TestModule.h"
#include "comm.h"
#include "serialport.h"

// serial communication
class CSerialComm : public CCommunication
{
protected:
	cnComm *serialport;

public:
	CSerialComm();
	~CSerialComm();
	
	BOOL Configure(ConfigArg_t conf);
	
	BOOL Open();
	BOOL Close();
	BOOL Read(char *buf, int size);
	BOOL Write(char *buf, int size);
	
	BOOL IsSystemBoot();
	BOOL Handshake();
};

// every modules
class CSerialGetInfo : public CTestModule
{
public:
	BOOL PerformTest();
};

class CSerialSetTime : public CTestModule
{
public:
	BOOL PerformTest();
};
class CSerialTestMouse : public CTestModule
{
public:
	BOOL PerformTest();
};
class CSerialTestNetwork : public CTestModule
{
public:
	BOOL PerformTest();
};
class CSerialTestDisk : public CTestModule
{
public:
	BOOL PerformTest();
};
class CSerialTestUDisk : public CTestModule
{
public:
	BOOL PerformTest();
};
class CSerialTestPtz : public CTestModule
{
public:
	BOOL PerformTest();
};
class CSerialTestKeyboard : public CTestModule
{
public:
	BOOL PerformTest();
};
class CSerialTestIrKey : public CTestModule
{
public:
	BOOL PerformTest();
};
class CSerialTestRecord : public CTestModule
{
public:
	BOOL PerformTest();
};
class CSerialTestPlayback : public CTestModule
{
public:
	BOOL PerformTest();
};
class CSerialTestAudio : public CTestModule
{
public:
	BOOL PerformTest();
};

#endif
