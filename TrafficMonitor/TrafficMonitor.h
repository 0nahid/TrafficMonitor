
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

//ѡ����������
struct MainWndSettingData
{
	//������
	COLORREF text_color{};		//������ɫ
	CString font_name;	//��������
	int font_size;		//�����С
	wstring up_string;		//Ĭ��Ϊ���ϴ�: ��
	wstring down_string;		//Ĭ��Ϊ������: ��
	wstring cpu_string;		//Ĭ��Ϊ��CPU: ��
	wstring memory_string;		//Ĭ��Ϊ���ڴ�: ��
	bool swap_up_down{ false };		//�����ϴ���������ʾ��λ��
	bool hide_main_wnd_when_fullscreen;		//�г���ȫ������ʱ����������
};

struct TaskBarSettingData
{
	//����������
	COLORREF  back_color{ RGB(0,0,0) };	//������ɫ
	COLORREF  text_color{ RGB(255,255,255) };	//������ɫ
	CString  font_name;	//��������
	int  font_size;		//�����С
	wstring  up_string;		//Ĭ��Ϊ����:��
	wstring  down_string;		//Ĭ��Ϊ����:��
	wstring  cpu_string;		//Ĭ��Ϊ��CPU:��
	wstring  memory_string;		//Ĭ��Ϊ���ڴ�:��
	bool  swap_up_down{ false };		//�����ϴ���������ʾ��λ��
	bool tbar_wnd_on_left{ false };		//���Ϊtrue����������������ʾ������������ࣨ���Ϸ���
};

struct GeneralSettingData
{
	//��������
	bool check_update_when_start{ true };
	bool auto_run{ false };
};

class CTrafficMonitorApp : public CWinApp
{
public:
	wstring m_module_path;
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
	bool m_tbar_show_cpu_memory;	//������������ʾCPU���ڴ�������

	//ѡ����������
	MainWndSettingData m_main_wnd_data;
	TaskBarSettingData m_taskbar_data;
	GeneralSettingData m_general_data;

	bool m_is_windows10_fall_creator;

	CTrafficMonitorApp();

	//bool WhenStart() const { return CCommon::WhenStart(m_no_multistart_warning_time); }
	void LoadConfig();
	void SaveConfig();

	int DPI(int pixel);
	void GetDPI(CWnd* pWnd);

	static void CheckUpdate(bool message);		//�����£����messageΪtrue�����ڼ��ʱ������ʾ��Ϣ
	//����ʱ�������̺߳���
	static UINT CheckUpdateThreadFunc(LPVOID lpParam);

	void SetAutoRun(bool auto_run);
	bool GetAutoRun();

private:
	//int m_no_multistart_warning_time{};		//���������ڿ�����೤ʱ���ڲ��������Ѿ���һ�������������С��ľ�����ʾ
	bool m_no_multistart_warning{};			//���Ϊfalse������Զ�����ᵯ�����Ѿ���һ�������������С��ľ�����ʾ
	int m_dpi{ 96 };
	CWinThread* m_pUpdateThread;			//�����µ��߳�

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CTrafficMonitorApp theApp;