#include <iostream>
#include "TestModule.h"
//#include "comm.h"

using namespace std;

#define MAX_MODULES		(100)

class CTestSytem
{
	CCommunication *comm;
	CTestModule *modules[MAX_MODULES];
	int n;// num of modules
	BOOL bTesting; // testing or not
	
public:
	CTestSytem();
	~CTestSytem();
	
	void SetCommunication(CCommunication *comm);
	void AddModule(CTestModule *module);
	void RemoveModule(CTestModule *module);

	BOOL DoTest();
	void StopTest();
	
private:
	void TestInit();
	BOOL TestAllModule();
	void DoReport(BOOL bSuccess);
	void SaveLog(BOOL bSuccess);
};