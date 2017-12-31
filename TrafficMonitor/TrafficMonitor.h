
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
	wstring m_skin_path;

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

	//ѡ����������
	//������
	COLORREF m_text_color{};		//������ɫ
	CString m_font_name;	//��������
	int m_font_size;		//�����С
	wstring m_up_string;		//Ĭ��Ϊ���ϴ�: ��
	wstring m_down_string;		//Ĭ��Ϊ������: ��
	wstring m_cpu_string;		//Ĭ��Ϊ��CPU: ��
	wstring m_memory_string;		//Ĭ��Ϊ���ڴ�: ��
	bool m_swap_up_down{ false };		//�����ϴ���������ʾ��λ��
	bool m_hide_main_wnd_when_fullscreen;		//�г���ȫ������ʱ����������

	//����������
	COLORREF m_tbar_back_color{ RGB(0,0,0) };	//������ɫ
	COLORREF m_tbar_text_color{ RGB(255,255,255) };	//������ɫ
	CString m_tbar_font_name;	//��������
	int m_tbar_font_size;		//�����С
	wstring m_tbar_up_string;		//Ĭ��Ϊ����:��
	wstring m_tbar_down_string;		//Ĭ��Ϊ����:��
	wstring m_tbar_cpu_string;		//Ĭ��Ϊ��CPU:��
	wstring m_tbar_memory_string;		//Ĭ��Ϊ���ڴ�:��
	bool m_tbar_swap_up_down{ false };		//�����ϴ���������ʾ��λ��

	bool m_tbar_show_cpu_memory;	//������������ʾCPU���ڴ�������

	CTrafficMonitorApp();

	//bool WhenStart() const { return CCommon::WhenStart(m_no_multistart_warning_time); }
	void LoadConfig();
	void SaveConfig();

private:
	//int m_no_multistart_warning_time{};		//���������ڿ�����೤ʱ���ڲ��������Ѿ���һ�������������С��ľ�����ʾ
	bool m_no_multistart_warning{};			//���Ϊfalse������Զ�����ᵯ�����Ѿ���һ�������������С��ľ�����ʾ

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CTrafficMonitorApp theApp;