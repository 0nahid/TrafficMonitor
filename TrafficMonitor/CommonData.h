//���ļ�����ȫ�ֽṹ�塢ö�����͵Ķ���
#pragma once
#include "stdafx.h"

//����ĳһ�����ʷ����
struct HistoryTraffic
{
	int year;
	int month;
	int day;
	unsigned int kBytes;	//����ʹ�õ���������KBΪ��λ��

	//�Ƚ�����HistoryTraffic��������ڣ����a��ʱ�����b���򷵻�true
	static bool DateGreater(const HistoryTraffic& a, const HistoryTraffic& b)
	{
		if (a.year != b.year)
			return a.year > b.year;
		else if (a.month != b.month)
			return a.month > b.month;
		else if (a.day != b.day)
			return a.day > b.day;
		else
			return false;
	}

	//�ж�����HistoryTraffic����������Ƿ����
	static bool DateEqual(const HistoryTraffic& a, const HistoryTraffic& b)
	{
		return a.year == b.year && a.month == b.month && a.day == b.day;
	}
};

//���ٵ�λ
enum class SpeedUnit
{
	AUTO,		//�Զ�
	KBPS,		//KB/s
	MBPS		//MB/s
};

#define DEF_CH L'\"'		//д��Ͷ�ȡini�ļ��ַ���ʱ�����ַ���ǰ����ӵ��ַ�
#define NONE_STR L"@@@"		//����ָ��һ����Ч�ַ���
struct DispStrings		//��ʾ���ı�
{
	wstring up;
	wstring down;
	wstring cpu;
	wstring memory;
	void operator=(const DispStrings& disp_str)		//���ظ�ֵ�����
	{
		//�����ֵ���ַ����Ƕ������Ч�ַ������򲻸�ֵ
		if (disp_str.up != NONE_STR)
			up = disp_str.up;
		if (disp_str.down != NONE_STR)
			down = disp_str.down;
		if (disp_str.cpu != NONE_STR)
			cpu = disp_str.cpu;
		if (disp_str.memory != NONE_STR)
			memory = disp_str.memory;
	}
	bool IsInvalid() const
	{
		return (up == NONE_STR && down == NONE_STR && cpu == NONE_STR && memory == NONE_STR);
	}
};

//ѡ����������
#define MAIN_WND_COLOR_NUM 4		//��������ɫ����
struct MainWndSettingData
{
	//������
	COLORREF text_colors[MAIN_WND_COLOR_NUM]{};		//������ɫ���ֱ�Ϊ���ϴ����������ء�����CPU�������ڴ桱����ɫ��
	bool specify_each_item_color{ false };		//�Ƿ�ָ��ÿ����Ŀ����ɫ
	CString font_name;	//��������
	int font_size;		//�����С
	DispStrings disp_str;	//��ʾ���ı�
	bool speed_short_mode{ false };		//������ʾ���ģʽ������С�����λ������λ����ʾ��B����
	bool swap_up_down{ false };		//�����ϴ���������ʾ��λ��
	bool hide_main_wnd_when_fullscreen;		//�г���ȫ������ʱ����������
	SpeedUnit speed_unit;		//���ٵĵ�λ
	bool hide_unit;			//���ص�λ
	bool hide_percent;		//���ذٷֺ�
};

#define TASKBAR_COLOR_NUM 8		//������������ɫ����
struct TaskBarSettingData
{
	//����������
	COLORREF  back_color{ RGB(0, 0, 0) };	//������ɫ
	COLORREF text_colors[TASKBAR_COLOR_NUM]{};		//������ɫ������Ϊ���ϴ����������ء�����CPU�������ڴ桱�ı�ǩ��������ɫ��
	bool specify_each_item_color{ false };		//�Ƿ�ָ��ÿ����Ŀ����ɫ
	CString  font_name;	//��������
	int  font_size;		//�����С
	DispStrings disp_str;	//��ʾ���ı�
	bool swap_up_down{ false };		//�����ϴ���������ʾ��λ��
	bool speed_short_mode{ false };		//������ʾ���ģʽ������С�����λ������λ����ʾ��B����
	bool value_right_align{ false };	//��ֵ�Ƿ��Ҷ���
	bool tbar_wnd_on_left{ false };		//���Ϊtrue����������������ʾ������������ࣨ���Ϸ���
	SpeedUnit speed_unit;		//���ٵĵ�λ
	bool hide_unit;			//���ص�λ
	bool hide_percent;		//���ذٷֺ�
};

struct GeneralSettingData
{
	//��������
	bool check_update_when_start{ true };
	bool auto_run{ false };
	bool allow_skin_cover_font{ true };
	bool allow_skin_cover_text{ true };
};

enum class Alignment
{
	LEFT,
	RIGHT,
	CENTER
};

//�����ڲ�������
struct LayoutData
{
	int text_height;	//�ı�����ĸ߶�
	bool no_text;		//����ʾ��ֵǰ�ġ��ϴ����������ء����ı�
	int preview_width;		//Ԥ�����������
	int preview_height;		//Ԥ���������߶�

	//�󴰿�ģʽ����ѡ����ʾ������Ϣ��ʱ�Ĳ��֣�
	int width_l;	//���ڵĿ��
	int height_l;	//���ڵĸ߶�
	int up_x_l;		//���ϴ�����x����
	int up_y_l;		//���ϴ�����y����
	int up_width_l;		//���ϴ����Ŀ��
	Alignment up_align_l;	//���ϴ����Ķ��뷽ʽ
	bool show_up_l;			//�Ƿ���ʾ���ϴ���
	int down_x_l;			//�����ء���x����
	int down_y_l;			//�����ء���y����
	int down_width_l;		//�����ء��Ŀ��
	Alignment down_align_l;	//�����ء��Ķ��뷽ʽ
	bool show_down_l;		//�Ƿ���ʾ�����ء�
	int cpu_x_l;			//��CPU����x����
	int cpu_y_l;			//��CPU����y����
	int cpu_width_l;		//��CPU���Ŀ��
	Alignment cpu_align_l;	//��CPU���Ķ��뷽ʽ
	bool show_cpu_l;		//�Ƿ���ʾ��CPU��
	int memory_x_l;			//���ڴ桱��x����
	int memory_y_l;			//���ڴ桱��y����
	int memory_width_l;		//���ڴ桱�Ŀ��
	Alignment memory_align_l;	//���ڴ桱�Ķ��뷽ʽ
	bool show_memory_l;		//�Ƿ���ʾ���ڴ桱
	int preview_x_l;		//�ڡ�ѡ��Ƥ����������Ԥ��ͼ��x����
	int preview_y_l;		//�ڡ�ѡ��Ƥ����������Ԥ��ͼ��y����

	//С����ģʽ������ѡ����ʾ������Ϣ��ʱ�Ĳ��֣�
	int width_s;	//���ڵĿ��
	int height_s;	//���ڵĸ߶�
	int up_x_s;		//���ϴ�����x����
	int up_y_s;		//���ϴ�����y����
	int up_width_s;		//���ϴ����Ŀ��
	Alignment up_align_s;	//���ϴ����Ķ��뷽ʽ
	bool show_up_s;			//�Ƿ���ʾ���ϴ���
	int down_x_s;			//�����ء���x����
	int down_y_s;			//�����ء���y����
	int down_width_s;		//�����ء��Ŀ��
	Alignment down_align_s;	//�����ء��Ķ��뷽ʽ
	bool show_down_s;		//�Ƿ���ʾ�����ء�
	int cpu_x_s;			//��CPU����x����
	int cpu_y_s;			//��CPU����y����
	int cpu_width_s;		//��CPU���Ŀ��
	Alignment cpu_align_s;	//��CPU���Ķ��뷽ʽ
	bool show_cpu_s;		//�Ƿ���ʾ��CPU��
	int memory_x_s;			//���ڴ桱��x����
	int memory_y_s;			//���ڴ桱��y����
	int memory_width_s;		//���ڴ桱�Ŀ��
	Alignment memory_align_s;	//���ڴ桱�Ķ��뷽ʽ
	bool show_memory_s;		//�Ƿ���ʾ���ڴ桱
	int preview_x_s;	//�ڡ�ѡ��Ƥ����������Ԥ��ͼ��x����
	int preview_y_s;	//�ڡ�ѡ��Ƥ����������Ԥ��ͼ��y����
};


struct SkinData
{
	LayoutData layout;
	COLORREF text_colors[MAIN_WND_COLOR_NUM]{};		//������ɫ���ֱ�Ϊ���ϴ����������ء�����CPU�������ڴ桱����ɫ��
	bool specify_each_item_color;		//�Ƿ�ָ��ÿ����Ŀ����ɫ
	//wstring skin_author;
	DispStrings disp_str;
	wstring font_name;
	int font_size;
};

