#include <iostream>
#include "comm.h"

using namespace std;

class CTestModule
{
public:
	CCommunication *comm;
	string name;

public:
	CTestModule(void);
	CTestModule(string name);
	~CTestModule(void);

	virtual BOOL PerformTest() = 0;
};


