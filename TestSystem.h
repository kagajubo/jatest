#ifndef __TEST_SYSTEM__
#define __TEST_SYSTEM__

#include <iostream>
#include "list.h"
#include "TestModule.h"
//#include "comm.h"
#include "SerialComm.h"
#include "NetworkComm.h"

using namespace std;

class CTestSytem
{
public:
	CCommunication *comm;
	List<CTestModule *> modules;
	BOOL bTesting; // testing or not
	
public:
	CTestSytem();
	~CTestSytem();
	
	void SetCommunication(CCommunication *comm);

	BOOL DoTest();
	void StopTest();
	
private:
	void TestInit();
	BOOL TestAllModule();
	void DoReport(BOOL bSuccess);
	void SaveLog(BOOL bSuccess);
};

#endif