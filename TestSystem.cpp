#include "StdAfx.h"
#include "TestSystem.h"

//
CTestSytem::CTestSytem()
{
	TRACE("new CTestSystem");
	bTesting=FALSE;
}

CTestSytem::~CTestSytem()
{
	comm->~CCommunication();
	delete comm;
	TRACE("new CTestSystem");
}

void CTestSytem::SetCommunication(CCommunication *comm)
{
	this->comm=comm;
}

void CTestSytem::TestInit()
{

}

void CTestSytem::DoReport(BOOL bSuccess)
{
	cout << "Test result: " << bSuccess << endl;
}

BOOL CTestSytem::DoTest()
{
	int i;
	while(bTesting){
		// check if system boot or not
		if(comm->IsSystemBoot()==FALSE){
			cout << "system boot test failed, please check it!" << endl;
			DoReport(FALSE);
			continue;
		}
		// system boot, do handshake...
		if(comm->Handshake()==FALSE){
			cout << "system boot test failed, please check it!" << endl;
			DoReport(FALSE);
			continue;
		}
		// handshake success, do test modules...
		for ( i = 0; i < modules.length(); i++ ){
			CTestModule *module=modules.at(i);
			if(module->PerformTest()==FALSE){
				cout << "module " << i << " test failed, please check it!" << endl;
				DoReport(FALSE);
				break;
			} else {
				cout << "module " << i << " test success!" << endl;
			}
		}
	}

	return TRUE;
}

void CTestSytem::StopTest()
{
	bTesting=FALSE;
}

void CTestSytem::SaveLog(BOOL bSuccess)
{
	cout << "save log for " << bSuccess << endl;
}