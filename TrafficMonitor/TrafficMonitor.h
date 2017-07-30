
// TrafficMonitor.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������
#include "Common.h"

// CTrafficMonitorApp: 
// �йش����ʵ�֣������ TrafficMonitor.cpp
//

class CTrafficMonitorApp : public CWinApp
{
public:
	wstring m_config_path;
	wstring m_history_traffic_path;
	wstring m_log_path;

	//�������ݶ���ΪApp���еĹ�����Ա���Ա��������Ի���������������ж��ܷ���
	unsigned int m_in_speed{};		//�����ٶ�
	unsigned int m_out_speed{};		//�ϴ��ٶ�
	int m_cpu_usage{};		//CPU������
	int m_memory_usage{};	//�ڴ�������
	int m_used_memory{};	//���������ڴ棨��λΪKB��
	int m_total_memory{};	//�����ڴ���������λΪKB��

	__int64 m_today_traffic{};	//������ʹ�õ�����

	bool m_hide_main_window;	//����������
	bool m_show_notify_icon{ true };	//��ʾ֪ͨ����ͼ��

	CTrafficMonitorApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CTrafficMonitorApp theApp;