#ifndef __COMM_H__
#define __COMM_H__

#include <iostream>

using namespace std;

#define COMM_TYPE_SERIAL	(1)
#define COMM_TYPE_NETWORK	(2)

typedef union{
	struct
	{
		int com;
		int baudrate;
		int timeout;
	};
	struct{
		unsigned char dev_ip[4];
		unsigned short port;
		int timeout;
	};
}ConfigArg_t;

class CCommunication 
{
protected:
	int type;
	CString dev_name;
	BOOL bTestMode;
	UINT32 timeout;
public:
	CCommunication()
	{
		bTestMode = false;
	}
	~CCommunication(){bTestMode = false;}

	virtual BOOL Init(ConfigArg_t conf){return false;}
	virtual void SetDevName(CString name) {dev_name=name;}
	virtual CString GetDevName() { return dev_name;}
	virtual void	SetTimeout(UINT32 to){timeout = to;}
	virtual UINT32  GetTimeout(){return timeout;}

	virtual BOOL isOpen(){return false;}
	virtual BOOL Open(){return false;}
	virtual BOOL Close(){return false;}
	virtual BOOL Read(char *buf, int size){return false;}
	virtual BOOL Write(char *buf, int size){return false;}
	
	//
	virtual BOOL IsSystemBoot(){return false;}
	virtual BOOL Handshake(){return false;}

	void SetTestMode(BOOL mode) { bTestMode = mode;}
	BOOL GetTestMode() { return bTestMode;}
};


#endif
