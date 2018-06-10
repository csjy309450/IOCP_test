// IOCPServer.cpp : �������̨Ӧ�ó������ڵ㡣
//
#include "stdafx.h"

#include <string>
#include <iostream>

#include "IOCPServer.h"

namespace nsp_std = std;

DWORD RecvFun_(PER_HANDLE_DATA *pHandleData, PER_IO_DATA *pIoData, DWORD dwBytes) {
	pIoData->data.append(pIoData->buf, dwBytes);
	while (1)
	{
		size_t begin_idx = pIoData->data.find_first_of('<'),
			end_idx = pIoData->data.find_first_of('>');
		if (begin_idx == nsp_std::string::npos)
		{
			pIoData->data.clear();
			return 0;
		}
		else {
			if (end_idx == nsp_std::string::npos) {
				pIoData->data.erase(0, begin_idx);
				return 0;
			}
			else {
				if (begin_idx < end_idx) {
					nsp_std::string t_sub(pIoData->data.substr(begin_idx, end_idx - begin_idx + 1));
					printf("�յ���%ld,%s\n", pIoData->socket,t_sub.c_str());
				}
				pIoData->data.erase(0, end_idx + 1);
				continue;
			}
		}
	}
	
	return 0;
}

int main(int argc, LPTSTR argv) {
	IOCPServer *abc = new IOCPServer;
	abc->SetRecvFun(RecvFun_);
	TRACE("Start()");
	if (abc->Start() == FALSE) // ��ȷ����TRUE�����󷵻�FALSE  
	{
		TRACE("Stop()");
		abc->Stop();
		TRACE("�����˳�");
		delete abc;
	}
	while (1);
	return 0;
}

