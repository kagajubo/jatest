/*
���ڻ�����⣨WIN32��	ver 0.2

������ �� BC++ 5; C++ BUILDER 4, 5, 6, X; VC++ 5, 6; VC.NET;  GCC;

ʹ��:

����
cnComm MyComm1(false, 0);//��1������Ϊ�Ƿ����������̣߳� ��2������Ϊ������0��/�첽��ʽ��Ĭ�ϣ�
cnComm MyComm2;//Ĭ�����������̣߳� �첽
cnComm MyComm3(true);//�����̣߳� ����

��
MyComm1.Open(1);//1-1024  2k֧��1024����
MyComm1.Open(1, 1200);
MyComm1.Open(1, 9600);
MyComm1.Open(1, "9600,8,n,1");//��ʹ�ñ�׼�������ַ���
MyComm1.SetBufferSize(1200, 4800)//���û�������С,�ɲ�������
MyComm1.SetState("9600,8,n,1")//�޸Ĳ����ʵ�


��д

MyComm1.Read(buf, 1000);
MyComm1.Write(buf, 200);


���ھ��
MyComm1.SetWnd(hWnd);

�߳̿������涼��ע���Ͳ�˵��

copyright(c) 2004.8 llbird wushaojian@21cn.com
*/

#ifndef	_CN_COMM_H_
#define _CN_COMM_H_

#pragma warning(disable: 4530)
#pragma warning(disable: 4786)
#pragma warning(disable: 4800)

#include <assert.h>
#include <stdio.h>
#include <windows.h>


//�����ܵ������͵����ڵ���Ϣ
#define ON_COM_RECEIVE WM_USER + 618	 //	 WPARAM �˿ں�

class cnComm	  
{
private:
	int port;
	DWORD baudrate;
	DWORD timeout;

public:
	cnComm(bool fAutoBeginThread = true, DWORD dwIOMode = FILE_FLAG_OVERLAPPED)
		: _dwIOMode(dwIOMode), _fAutoBeginThread(fAutoBeginThread)
	{
		Init();	
	}
	virtual ~cnComm()
	{
		Close();	
		UnInit();
	}
	inline void SetArg(int port,DWORD bd,DWORD timeout)
	{
		port = port;
		baudrate = bd;
		timeout = timeout;
	}
	inline bool Open()
	{
		return Open(port,baudrate);
	}	

	//�򿪴��� ȱʡ 9600, 8, n, 1
	inline bool Open(DWORD dwPort)
	{
		port=dwPort;
		baudrate=9600;
		return Open(dwPort, 9600);
	}
	//�򿪴��� ȱʡ baud_rate, 8, n, 1
	inline bool Open(DWORD dwPort, DWORD dwBaudRate)
	{
		port = dwPort;
		baudrate = dwBaudRate;

		if(dwPort < 1 || dwPort > 1024)
			return false;

		BindCommPort(dwPort);

		if(!OpenCommPort())
			return false;

		if(!SetupPort())
			return false;

		return SetState(dwBaudRate);
	}
	//�򿪴���, ʹ������"9600, 8, n, 1"�������ַ������ô���
	inline bool Open(DWORD dwPort, char *szSetStr)
	{
		if(dwPort < 1 || dwPort > 1024)
			return false;

		BindCommPort(dwPort);

		if(!OpenCommPort())
			return false;

		if(!SetupPort())
			return false;

		return SetState(szSetStr);
	}
	//�жϴ����ǻ��
	inline bool IsOpen()
	{
		return _hCommHandle != INVALID_HANDLE_VALUE;
	}
	//��ô��ھ��
	inline HANDLE GetHandle()
	{
		return _hCommHandle;
	}
	// set timeout
	inline void SetReadTimeout(int timeout /* second */)
	{
		this->timeout = timeout;
	}
	//���ô��ڲ����������ʣ�ֹͣλ���� ֧�������ַ��� "9600, 8, n, 1"
	bool SetState(char *szSetStr)	
	{
		if(IsOpen())
		{
			if(!::GetCommState(_hCommHandle, &_DCB))
				return false;
			if(!::BuildCommDCB(szSetStr, &_DCB))
				return false;
			return ::SetCommState(_hCommHandle, &_DCB) == TRUE;
		}
		return false;
	}
	//���ô��ڲ����������ʣ�ֹͣλ
	bool SetState(DWORD dwBaudRate, DWORD dwByteSize = 8, DWORD dwParity = NOPARITY, DWORD dwStopBits = ONESTOPBIT)
	{
		if(IsOpen())
		{
			if(!::GetCommState(_hCommHandle, &_DCB))
				return false;
			_DCB.BaudRate = dwBaudRate;
		    _DCB.ByteSize = dwByteSize;
		    _DCB.Parity   = dwParity;
			_DCB.StopBits = dwStopBits;
			return ::SetCommState(_hCommHandle, &_DCB) == TRUE;
		}
		return false;
	}
	//���ô��ڵ�I/O��������С
	bool SetBufferSize(DWORD dwInputSize, DWORD dwOutputSize)
	{
		if(IsOpen())
			return ::SetupComm(_hCommHandle, dwInputSize, dwOutputSize);
		return false;	
	}

	//��ȡ���� dwBufferLength - 1 ���ַ��� szBuffer ����ʵ�ʶ������ַ���
	DWORD Read(char *szBuffer, DWORD dwBufferLength)
	{
		DWORD dwWaitTime = timeout;
		if(!IsOpen())
			return 0;

		szBuffer[0] = '\0';

		COMSTAT  Stat;
		DWORD dwError;

		if(::ClearCommError(_hCommHandle, &dwError, &Stat) && dwError > 0)	//�������
		{
			::PurgeComm(_hCommHandle, PURGE_RXABORT | PURGE_RXCLEAR); /*������뻺����*/
			return 0;
		}

		if(!Stat.cbInQue)// ������������
			return 0;

		unsigned long uReadLength = 0;

		dwBufferLength = dwBufferLength - 1 > Stat.cbInQue ? Stat.cbInQue : dwBufferLength - 1;

		if(!::ReadFile(_hCommHandle, szBuffer, dwBufferLength, &uReadLength, &_ReadOverlapped)) //2000 �� ReadFile ʼ�շ��� True
		{
			if(::GetLastError() == ERROR_IO_PENDING) // �����첽I/O
			{
				WaitForSingleObject(_ReadOverlapped.hEvent, dwWaitTime);	//�ȴ�20ms
				if(!::GetOverlappedResult(_hCommHandle, &_ReadOverlapped, &uReadLength, false))
				{
					if(::GetLastError() != ERROR_IO_INCOMPLETE)//��������
							uReadLength = 0;
				}
			}
			else
				uReadLength = 0;
		}
			
		szBuffer[uReadLength] = '\0';

		TRACE("read %d byte %s,actural read:%d errno:%d\n",dwBufferLength,
			dwBufferLength == uReadLength ? "success" : "failed",uReadLength,
			::GetLastError());

		return uReadLength;
	}

	DWORD ReadLine(char *szBuffer, DWORD dwBufferLength)
	{
		DWORD dwWaitTime = timeout;
		if(!IsOpen())
			return 0;

		szBuffer[0] = '\0';

		COMSTAT  Stat;
		DWORD dwError;

		if(::ClearCommError(_hCommHandle, &dwError, &Stat) && dwError > 0)	//�������
		{
			::PurgeComm(_hCommHandle, PURGE_RXABORT | PURGE_RXCLEAR); /*������뻺����*/
			return 0;
		}

		if(!Stat.cbInQue)// ������������
			return 0;

		unsigned long uTotalRead = 0;
		unsigned long uReadLength = 0;

		//dwBufferLength = dwBufferLength - 1 > Stat.cbInQue ? Stat.cbInQue : dwBufferLength - 1;
			
		while(1){
			char ch;
			if(!::ReadFile(_hCommHandle, &ch, 1, &uReadLength, &_ReadOverlapped)) //2000 �� ReadFile ʼ�շ��� True
			{
				if(::GetLastError() == ERROR_IO_PENDING) // �����첽I/O
				{
					TRACE("ERROR_IO_PENDING \n");
					WaitForSingleObject(_ReadOverlapped.hEvent, dwWaitTime);	//�ȴ�20ms
					if(!::GetOverlappedResult(_hCommHandle, &_ReadOverlapped, &uReadLength, false))
					{
						if(::GetLastError() != ERROR_IO_INCOMPLETE){//��������
							TRACE("ERROR_IO_INCOMPLETE \n");
							uReadLength = 0;
						}
					}
				}
				else{					
					TRACE("not ERROR_IO_PENDING \n");
					uReadLength = 0;
				}
				break;
			}else{
				if(ch == 13 || uTotalRead >= dwBufferLength)
					break;
				szBuffer[uTotalRead++] = ch;
			}

		}
			
		szBuffer[uTotalRead] = '\0';

		TRACE("read %d byte errno:%d\n",uTotalRead,GetLastError());

		return uTotalRead;
	}

	//д���� szBuffer
	DWORD Write(char *szBuffer, DWORD dwBufferLength)
	{
		if(!IsOpen())
			return 0;
		
		DWORD dwError;

		if(::ClearCommError(_hCommHandle, &dwError, NULL) && dwError > 0)	//�������
			::PurgeComm(_hCommHandle, PURGE_TXABORT | PURGE_TXCLEAR);	

		unsigned long uWriteLength = 0;

		if(!::WriteFile(_hCommHandle, szBuffer, dwBufferLength, &uWriteLength, &_WriteOverlapped))
			if(::GetLastError() != ERROR_IO_PENDING)
				uWriteLength = 0;
		
		TRACE("send %d byte %s,actural sended:%d errno:%d\n",dwBufferLength,
			dwBufferLength == uWriteLength ? "success" : "failed",uWriteLength,
			::GetLastError());

		return uWriteLength;
	}
	//д���� szBuffer
	inline DWORD Write(char *szBuffer)
	{
		assert(szBuffer);

		return Write(szBuffer, strlen(szBuffer));
	}
	inline DWORD WriteLine(char *szBuffer)
	{
		int ret;
		char end=13;
		assert(szBuffer);
		if((ret = Write(szBuffer, strlen(szBuffer))) != strlen(szBuffer)){
		//	return ret;
		}
		if(Write(&end,1) != 1){
			return ret;
		}
		TRACE("send %d byte succss\n",ret+1);
		return ret+1;
	}
	//ǿ��ͬ��д
	inline DWORD WriteSync(char *szBuffer, DWORD dwBufferLength)
	{
		if(!IsOpen())
			return 0;
		
		DWORD dwError;

		if(::ClearCommError(_hCommHandle, &dwError, NULL) && dwError > 0)	//�������
			::PurgeComm(_hCommHandle, PURGE_TXABORT | PURGE_TXCLEAR);	

		unsigned long uWriteLength = 0;

		if(!::WriteFile(_hCommHandle, szBuffer, dwBufferLength, &uWriteLength, NULL))
			if(::GetLastError() != ERROR_IO_PENDING)
				uWriteLength = 0;

		return uWriteLength;
	}
	//д���� szBuffer ���������ʽ�ַ���
	DWORD Write(char *szBuffer, DWORD dwBufferLength, char * szFormat, ...)
	{
		if(!IsOpen())
			return 0;
		
		DWORD dwError;

		if(::ClearCommError(_hCommHandle, &dwError, NULL) && dwError > 0)	//�������
			::PurgeComm(_hCommHandle, PURGE_TXABORT | PURGE_TXCLEAR);	

		va_list va;
		va_start(va, szFormat);
		_vsnprintf(szBuffer, dwBufferLength, szFormat, va);
		va_end(va);

		unsigned long uWriteLength = 0;

		if(!::WriteFile(_hCommHandle, szBuffer, dwBufferLength, &uWriteLength, &_WriteOverlapped))
			if(::GetLastError() != ERROR_IO_PENDING)
				uWriteLength = 0;

		return uWriteLength;
	}
	//�رմ���
	inline virtual void Close()
	{
		if(IsOpen())		
		{
			EndThread();
			::CloseHandle(_hCommHandle);

			_hCommHandle = INVALID_HANDLE_VALUE;
		}
	}
	//�趨����֪ͨ, �����ַ���Сֵ
	inline void SetNotifyNum(int iNum)
	{
		_dwNotifyNum = iNum;
	}
	//����Ϣ�Ĵ��ھ��
	inline void SetWnd(HWND hWnd)
	{
		_hNotifyWnd = hWnd;
	}
	//�����߳̿��� �������߳�
	bool BeginThread() 
	{
		if(!IsThreadRunning()) 
		{
			_fRunFlag = true;
			_hThreadHandle = NULL;

			DWORD id;

			_hThreadHandle = ::CreateThread(NULL, 0, CommThreadProc, this, 0, &id); //����98 ��ʹ��&ID

			return (_hThreadHandle != NULL); //�����߳�
		}
		return false;
	}
	//�߳��Ƿ�����
	inline bool IsThreadRunning()
	{
		return _hThreadHandle != NULL;
	}
	//����߳̾��
	inline HANDLE GetThread()
	{
		return _hThreadHandle;
	}
	//��ͣ�����߳�
	inline bool SuspendThread()
	{
		return IsThreadRunning() ? ::SuspendThread(_hThreadHandle) != 0xFFFFFFFF : false;
	}
	//�ָ������߳�
	inline bool ResumeThread()
	{
		return IsThreadRunning() ? ::ResumeThread(_hThreadHandle) != 0xFFFFFFFF : false;
	}
	//��ֹ�߳�
	bool EndThread(DWORD dwWaitTime = 100)
	{
		if(IsThreadRunning()) 
		{
			_fRunFlag = false;
			::SetCommMask(_hCommHandle, 0);
			::SetEvent(_WaitOverlapped.hEvent);
			if(::WaitForSingleObject(_hThreadHandle, dwWaitTime) != WAIT_OBJECT_0)
				if(!::TerminateThread(_hThreadHandle, 0))
					return false;

			::CloseHandle(_hThreadHandle);
			::ResetEvent(_WaitOverlapped.hEvent);

			_hThreadHandle = NULL;

			return true;
		}
		return false;
	}
protected:

	volatile DWORD _dwPort;	 //���ں�
	volatile HANDLE _hCommHandle;//���ھ��
	char _szCommStr[20];

	DCB _DCB;			  //�����ʣ�ֹͣλ����
	COMMTIMEOUTS _CO;     //��ʱ�ṹ

	DWORD _dwIOMode; // 0 ͬ��  Ĭ�� FILE_FLAG_OVERLAPPED �ص�I/O �첽
	OVERLAPPED _ReadOverlapped, _WriteOverlapped; //	�ص�I/O

	//�߳���
	volatile HANDLE _hThreadHandle;	//�����߳�
	volatile HWND _hNotifyWnd; // ֪ͨ����
	volatile DWORD _dwNotifyNum;//���ܶ����ֽ�(>_dwNotifyNum)����֪ͨ��Ϣ
	volatile bool _fRunFlag; //�߳�����ѭ����־
	bool _fAutoBeginThread;//Open() �Զ� BeginThread();
	OVERLAPPED _WaitOverlapped; //WaitCommEvent use

	//�߳��յ���Ϣ�Զ�����, �細�ھ����Ч, �ͳ���Ϣ, �������ڱ��
	virtual void OnReceive()
	{
		if(_hNotifyWnd)
			::PostMessage(_hNotifyWnd, ON_COM_RECEIVE, WPARAM(_dwPort), LPARAM(0));
	}
	void Init()	//��ʼ��
	{
		memset(_szCommStr, 0, sizeof(_szCommStr));
		memset(&_DCB, 0, sizeof(_DCB));
		_DCB.DCBlength = sizeof(_DCB);
		_hCommHandle = INVALID_HANDLE_VALUE;

		memset(&_ReadOverlapped, 0, sizeof(_ReadOverlapped));
		memset(&_WriteOverlapped, 0, sizeof(_WriteOverlapped));

		_ReadOverlapped.hEvent = ::CreateEvent(NULL, true, false, NULL);
		assert(_ReadOverlapped.hEvent != INVALID_HANDLE_VALUE); 
		
		_WriteOverlapped.hEvent = ::CreateEvent(NULL, true, false, NULL);
		assert(_WriteOverlapped.hEvent != INVALID_HANDLE_VALUE);

		_dwNotifyNum = 0;
		_hNotifyWnd = NULL;
		_hThreadHandle = NULL;

		memset(&_WaitOverlapped, 0, sizeof(_WaitOverlapped));
		_WaitOverlapped.hEvent = ::CreateEvent(NULL, true, false, NULL);
		assert(_WaitOverlapped.hEvent != INVALID_HANDLE_VALUE);	
	}		
	void UnInit()
	{
		if(_ReadOverlapped.hEvent != INVALID_HANDLE_VALUE)
			CloseHandle(_ReadOverlapped.hEvent);

		if(_WriteOverlapped.hEvent != INVALID_HANDLE_VALUE)
			CloseHandle(_WriteOverlapped.hEvent);

		if(_WaitOverlapped.hEvent != INVALID_HANDLE_VALUE)
			CloseHandle(_WaitOverlapped.hEvent);
	}
	// com number to string 
	inline void BindCommPort(DWORD dwPort)
	{
		assert(dwPort >= 1 && dwPort <= 1024);

		char p[5];

		_dwPort = dwPort;
		strcpy(_szCommStr, "\\\\.\\COM");	
		ltoa(_dwPort, p, 10);
		strcat(_szCommStr, p);
	}
	//�򿪴���
	virtual bool OpenCommPort()
	{
		if(IsOpen())
			Close();

		_hCommHandle = ::CreateFile(
			_szCommStr,
			GENERIC_READ | GENERIC_WRITE,
			0,
			NULL,
			OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL | _dwIOMode,	
			NULL
			);

		if(_fAutoBeginThread)
		{
			if(IsOpen() && BeginThread())
				return true;
			else
			{
				Close(); //�����߳�ʧ��
				return false;
			}
		}
		return IsOpen();//��⴮���Ƿ�ɹ���
	}
	//���ô���
	virtual bool SetupPort()
	{
		if(!IsOpen())
			return false;

		//�����Ƽ�������
		if(!::SetupComm(_hCommHandle, 4096, 4096))
			return false;	

		//���ó�ʱʱ��
		if(!::GetCommTimeouts(_hCommHandle, &_CO))
			return false;
		_CO.ReadIntervalTimeout = 0xFFFFFFFF;
		_CO.ReadTotalTimeoutMultiplier = 0;
		_CO.ReadTotalTimeoutConstant = 0;
		_CO.WriteTotalTimeoutMultiplier = 0;
		_CO.WriteTotalTimeoutConstant = 2000;
		if(!::SetCommTimeouts(_hCommHandle, &_CO))
			return false;	

		//��մ��ڻ�����
		if(!::PurgeComm(_hCommHandle, PURGE_TXABORT | PURGE_RXABORT | PURGE_TXCLEAR | PURGE_RXCLEAR ))
			return false;	

		return true;
	}			
	
private:
	//�����߳�
	static DWORD WINAPI CommThreadProc(LPVOID lpPara)
	{
		cnComm *pComm = (cnComm *)lpPara;	
		

        if(!::SetCommMask(pComm->_hCommHandle, EV_RXCHAR | EV_ERR))
			return 1;

		COMSTAT Stat;
		DWORD dwError;

		for(DWORD dwLength, dwMask = 0; pComm->_fRunFlag && pComm->IsOpen(); dwMask = 0)
		{
			if(!::WaitCommEvent(pComm->_hCommHandle, &dwMask, &pComm->_WaitOverlapped))
			{
				if(::GetLastError() == ERROR_IO_PENDING)
				{
					::GetOverlappedResult(pComm->_hCommHandle, &pComm->_WaitOverlapped, &dwLength, TRUE);
				}
			}

			if(dwMask & EV_ERR) // == EV_ERR
				::ClearCommError(pComm->_hCommHandle, &dwError, &Stat);

			if(dwMask & EV_RXCHAR) // == EV_RXCHAR
			{
				::ClearCommError(pComm->_hCommHandle, &dwError, &Stat);
				if(Stat.cbInQue > pComm->_dwNotifyNum)
					pComm->OnReceive();
			}
        }
		return 0;
	}
};

#endif //_CN_COMM_H_