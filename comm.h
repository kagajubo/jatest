#ifndef __COMM_H__
#define __COMM_H__

#include <iostream>

using namespace std;

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
	BOOL bTestMode;
public:
	CCommunication();
	~CCommunication();

	virtual BOOL Configure(ConfigArg_t conf) = 0;

	virtual BOOL Open() =0;
	virtual BOOL Close() =0;
	virtual BOOL Read(char *buf, int size) =0;
	virtual BOOL Write(char *buf, int size) =0;

	virtual BOOL IsSystemBoot() =0;
	virtual BOOL Handshake() =0;

	void SetTestMode(BOOL mode);
	BOOL GetTestMode();
};


#endif
