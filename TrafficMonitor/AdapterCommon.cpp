#include "stdafx.h"
#include "AdapterCommon.h"


CAdapterCommon::CAdapterCommon()
{
}


CAdapterCommon::~CAdapterCommon()
{
}

void CAdapterCommon::GetAdapterInfo(vector<NetWorkConection>& adapters)
{
	adapters.clear();
	PIP_ADAPTER_INFO pIpAdapterInfo = new IP_ADAPTER_INFO();		//PIP_ADAPTER_INFO�ṹ��ָ��洢����������Ϣ
	unsigned long stSize = sizeof(IP_ADAPTER_INFO);		//�õ��ṹ���С,����GetAdaptersInfo����
	int nRel = GetAdaptersInfo(pIpAdapterInfo, &stSize);	//����GetAdaptersInfo����,���pIpAdapterInfoָ�����;����stSize��������һ��������Ҳ��һ�������

	if (ERROR_BUFFER_OVERFLOW == nRel)
	{
		//����������ص���ERROR_BUFFER_OVERFLOW
		//��˵��GetAdaptersInfo�������ݵ��ڴ�ռ䲻��,ͬʱ�䴫��stSize,��ʾ��Ҫ�Ŀռ��С
		//��Ҳ��˵��ΪʲôstSize����һ��������Ҳ��һ�������
		delete pIpAdapterInfo;	//�ͷ�ԭ�����ڴ�ռ�
		pIpAdapterInfo = (PIP_ADAPTER_INFO)new BYTE[stSize];	//���������ڴ�ռ������洢����������Ϣ
		nRel = GetAdaptersInfo(pIpAdapterInfo, &stSize);		//�ٴε���GetAdaptersInfo����,���pIpAdapterInfoָ�����
	}

	PIP_ADAPTER_INFO pIpAdapterInfoHead = pIpAdapterInfo;	//����pIpAdapterInfo�����е�һ��Ԫ�صĵ�ַ
	if (ERROR_SUCCESS == nRel)
	{
		while (pIpAdapterInfo)
		{
			NetWorkConection connection;
			connection.description = pIpAdapterInfo->Description;
			connection.ip_address = CCommon::StrToUnicode(pIpAdapterInfo->IpAddressList.IpAddress.String);
			connection.subnet_mask = CCommon::StrToUnicode(pIpAdapterInfo->IpAddressList.IpMask.String);
			connection.default_gateway = CCommon::StrToUnicode(pIpAdapterInfo->GatewayList.IpAddress.String);

			adapters.push_back(connection);
			pIpAdapterInfo = pIpAdapterInfo->Next;
		}
	}
	//�ͷ��ڴ�ռ�
	if (pIpAdapterInfoHead)
	{
		delete pIpAdapterInfoHead;
	}
	if (adapters.empty())
		adapters.push_back(NetWorkConection());
}

void CAdapterCommon::GetIfTableInfo(vector<NetWorkConection>& adapters, MIB_IFTABLE* pIfTable)
{
	for (unsigned int i{}; i < pIfTable->dwNumEntries; i++)
	{
		string descr = (const char*)pIfTable->table[i].bDescr;
		int index = FindConnectionInAdapterList(descr, adapters);
		if (index != -1)
		{
			adapters[index].index = i;
			adapters[index].in_bytes = pIfTable->table[i].dwInOctets;
			adapters[index].out_bytes = pIfTable->table[i].dwOutOctets;
		}
	}
}

int CAdapterCommon::FindConnectionInAdapterList(string connection, const vector<NetWorkConection>& adapters)
{
	for (size_t i{}; i<adapters.size(); i++)
	{
		if (adapters[i].description == connection)
			return i;
	}
	return -1;
}
