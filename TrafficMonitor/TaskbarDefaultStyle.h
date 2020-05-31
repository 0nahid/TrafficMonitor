#pragma once
#include "CommonData.h"

#define TASKBAR_DEFAULT_STYLE_NUM 3
#define TASKBAR_DEFAULT_LIGHT_STYLE_INDEX (-1)

class CTaskbarDefaultStyle
{
public:
	struct TaskBarStyleData
	{
		COLORREF text_colors[TASKBAR_COLOR_NUM]{};
		COLORREF back_color{};
		COLORREF transparent_color{};
		COLORREF status_bar_color{};
		bool specify_each_item_color{};
	};

	CTaskbarDefaultStyle();
	~CTaskbarDefaultStyle();

	void LoadConfig();
	void SaveConfig() const;

	void ApplyDefaultStyle(int index, TaskBarSettingData& data);		//Ӧ��һ����ɫԤ��
	static void ApplyDefaultLightStyle(TaskBarSettingData& data);		//Ӧ��Ĭ�ϵ�ǳɫģʽԤ��
	void ModifyDefaultStyle(int index, TaskBarSettingData& data);     //����ǰ��ɫ���ñ��浽һ��Ԥ�跽��

	static bool IsTaskbarTransparent(const TaskBarSettingData& data);
	static void SetTaskabrTransparent(bool transparent, TaskBarSettingData& data);

private:
	TaskBarStyleData m_default_style[TASKBAR_DEFAULT_STYLE_NUM];    //Ԥ����ʽ

};

