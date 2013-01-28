#include "StdAfx.h"
#include "TestSystem.h"

CTestSytem::CTestSytem()
{
	n=0;
	bTesting=FALSE;
}

CTestSytem::~CTestSytem()
{
	n=0;
	comm->~CCommunication();
	delete comm;
}

void CTestSytem::SetCommunication(CCommunication *comm)
{
	this->comm=comm;
}

void CTestSytem::AddModule(CTestModule *module)
{
	module->comm = this->comm;
	modules[this->n]=module;
	n++;
}

void CTestSytem::RemoveModule(CTestModule *module)
{
	int i;
	for ( i = 0; i < n; i++ ){
		if ( modules[i] == module ){
			cout << "remove "<< i << endl;
			for( ; i < (n - 1); i++ ){
				modules[i] = modules[i+1];
			}
			break;
		}
	}
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
		for ( i = 0; i < n; i++ ){
			if(modules[i]->PerformTest()==FALSE){
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