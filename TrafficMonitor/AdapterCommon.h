#pragma once
#include "Common.h"

//����һ������������Ϣ
struct NetWorkConection
{
	int index{};			//��������MIB_IFTABLE�е�����
	string description;		//��������
	unsigned int in_bytes;	//��ʼʱ�ѽ����ֽ���
	unsigned int out_bytes;	//��ʼʱ�ѷ����ֽ���
	wstring ip_address{ L"-.-.-.-" };	//IP��ַ
	wstring subnet_mask{ L"-.-.-.-" };	//��������
	wstring default_gateway{ L"-.-.-.-" };	//Ĭ������
};

class CAdapterCommon
{
public:
	CAdapterCommon();
	~CAdapterCommon();

	//��ȡ���������б��������������IP��ַ���������롢Ĭ��������Ϣ
	static void GetAdapterInfo(vector<NetWorkConection>& adapters);

	//��ȡ�����б���ÿ���������ӵ�MIB_IFTABLE�е���������ʼʱ�ѽ���/�����ֽ�������Ϣ
	static void GetIfTableInfo(vector<NetWorkConection>& adapters, MIB_IFTABLE* pIfTable);
private:
	//����һ���������������ж��Ƿ������������б�������������Ҳ����򷵻�-1
	static int FindConnectionInAdapterList(string connection, const vector<NetWorkConection>& adapters);
};

