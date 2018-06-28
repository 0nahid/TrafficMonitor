
// TrafficMonitor.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "TrafficMonitor.h"
#include "TrafficMonitorDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTrafficMonitorApp

BEGIN_MESSAGE_MAP(CTrafficMonitorApp, CWinApp)
	//ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
	ON_COMMAND(ID_HELP, &CTrafficMonitorApp::OnHelp)
END_MESSAGE_MAP()


// CTrafficMonitorApp ����

CTrafficMonitorApp::CTrafficMonitorApp()
{
	// ֧����������������
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}

void CTrafficMonitorApp::LoadConfig()
{
	CIniHelper ini{ m_config_path };

	//��������
	m_general_data.check_update_when_start = ini.GetBool(_T("general"), _T("check_update_when_start"), true);
	m_general_data.allow_skin_cover_font = ini.GetBool(_T("general"), _T("allow_skin_cover_font"), true);
	m_general_data.allow_skin_cover_text = ini.GetBool(_T("general"), _T("allow_skin_cover_text"), true);
	m_general_data.language = static_cast<Language>(ini.GetInt(_T("general"), _T("language"), 0));

	//����������
	m_cfg_data.m_transparency = ini.GetInt(_T("config"), _T("transparency"), 80);
	m_cfg_data.m_always_on_top = ini.GetBool(_T("config"), _T("always_on_top"), true);
	m_cfg_data.m_lock_window_pos = ini.GetBool(_T("config"), _T("lock_window_pos"), false);
	m_cfg_data.m_show_notify_icon = ini.GetBool(_T("config"), _T("show_notify_icon"), true);
	m_cfg_data.m_show_more_info = ini.GetBool(_T("config"), _T("show_cpu_memory"), false);
	m_cfg_data.m_mouse_penetrate = ini.GetBool(_T("config"), _T("mouse_penetrate"), false);
	m_cfg_data.m_show_task_bar_wnd = ini.GetBool(_T("config"), _T("show_task_bar_wnd"), false);
	m_cfg_data.m_position_x = ini.GetInt(_T("config"), _T("position_x"), -1);
	m_cfg_data.m_position_y = ini.GetInt(_T("config"), _T("position_y"), -1);
	m_cfg_data.m_auto_select = ini.GetBool(_T("connection"), _T("auto_select"), true);
	m_cfg_data.m_select_all = ini.GetBool(_T("connection"), _T("select_all"), false);
	//m_main_wnd_data.text_color = ini.GetInt(_T("config"), _T("text_color"), 16384);
	ini.GetIntArray(_T("config"), _T("text_color"), (int*)m_main_wnd_data.text_colors, MAIN_WND_COLOR_NUM, 16384);
	m_main_wnd_data.specify_each_item_color = ini.GetBool(_T("config"), _T("specify_each_item_color"), false);
	m_cfg_data.m_hide_main_window = ini.GetBool(_T("config"), _T("hide_main_window"), false);
	m_cfg_data.m_connection_name = CCommon::UnicodeToStr(ini.GetString(L"connection", L"connection_name", L"").c_str());
	m_cfg_data.m_skin_name = ini.GetString(_T("config"), _T("skin_selected"), _T(""));
	if (m_cfg_data.m_skin_name.substr(0, 8) == L".\\skins\\")		//�����ȡ����Ƥ������ǰ����".\\skins\\"�������ɾ���������ں�ǰһ���汾���ּ����ԣ�
		m_cfg_data.m_skin_name = m_cfg_data.m_skin_name.substr(7);
	m_cfg_data.m_notify_icon_selected = ini.GetInt(_T("config"), _T("notify_icon_selected"), (m_win_version.IsWindows7() || m_win_version.IsWindows8Or8point1() ? 2 : 0));		//Win7/8/8.1Ĭ��ʹ����ɫ֪ͨ��ͼ�꣬��Ϊ����֪ͨ��ͼ����ɫͼ��ῴ���壬����ϵͳĬ��ʹ�ð�ɫͼ��
	m_main_wnd_data.swap_up_down = ini.GetBool(_T("config"), _T("swap_up_down"), false);
	m_main_wnd_data.hide_main_wnd_when_fullscreen = ini.GetBool(_T("config"), _T("hide_main_wnd_when_fullscreen"), true);

	FontInfo default_font{};
	default_font.name = CCommon::LoadText(IDS_DEFAULT_FONT);
	default_font.size = 10;
	ini.LoadFontData(_T("config"), m_main_wnd_data.font, default_font);
	//m_main_wnd_data.font.name = ini.GetString(_T("config"), _T("font_name"), CCommon::LoadText(IDS_MICROSOFT_YAHEI)).c_str();
	//m_main_wnd_data.font.size = ini.GetInt(_T("config"), _T("font_size"), 10);

	m_main_wnd_data.disp_str.up = ini.GetString(_T("config"), L"up_string", CCommon::LoadText(IDS_UPLOAD_DISP, _T(": $")));
	m_main_wnd_data.disp_str.down = ini.GetString(L"config", L"down_string", CCommon::LoadText(IDS_DOWNLOAD_DISP, _T(": $")));
	m_main_wnd_data.disp_str.cpu = ini.GetString(L"config", L"cpu_string", L"CPU: $");
	m_main_wnd_data.disp_str.memory = ini.GetString(L"config", L"memory_string", CCommon::LoadText(IDS_MEMORY_DISP, _T(": $")));

	m_main_wnd_data.speed_short_mode = ini.GetBool(_T("config"), _T("speed_short_mode"), false);
	m_main_wnd_data.separate_value_unit_with_space = ini.GetBool(_T("config"), _T("separate_value_unit_with_space"), true);
	m_main_wnd_data.speed_unit = static_cast<SpeedUnit>(ini.GetInt(_T("config"), _T("speed_unit"), 0));
	m_main_wnd_data.hide_unit = ini.GetBool(_T("config"), _T("hide_unit"), false);
	m_main_wnd_data.hide_percent = ini.GetBool(_T("config"), _T("hide_percent"), false);
	m_main_wnd_data.double_click_action = static_cast<DoubleClickAction>(ini.GetInt(_T("config"), _T("double_click_action"), 0));

	m_cfg_data.m_alow_out_of_border = ini.GetBool(_T("config"), _T("alow_out_of_border"), false);

	m_general_data.traffic_tip_enable = ini.GetBool(L"notify_tip", L"traffic_tip_enable", false);
	m_general_data.traffic_tip_value = ini.GetInt(L"notify_tip", L"traffic_tip_value", 200);
	m_general_data.traffic_tip_unit = ini.GetInt(L"notify_tip", L"traffic_tip_unit", 0);
	m_general_data.memory_usage_tip_enable = ini.GetBool(L"notify_tip", L"memory_usage_tip_enable", false);
	m_general_data.memory_tip_value = ini.GetInt(L"notify_tip", L"memory_tip_value", 80);


	//��������������
	m_taskbar_data.back_color = ini.GetInt(_T("task_bar"), _T("task_bar_back_color"), 0);
	//m_taskbar_data.text_color = GetPrivateProfileInt(_T("task_bar"), _T("task_bar_text_color"), 0x00ffffffU, m_config_path.c_str());
	ini.GetIntArray(_T("task_bar"), _T("task_bar_text_color"), (int*)m_taskbar_data.text_colors, TASKBAR_COLOR_NUM, 0x00ffffffU);
	m_taskbar_data.specify_each_item_color = ini.GetBool(L"task_bar", L"specify_each_item_color", false);
	m_cfg_data.m_tbar_show_cpu_memory = ini.GetBool(_T("task_bar"), _T("task_bar_show_cpu_memory"), false);
	m_taskbar_data.swap_up_down = ini.GetBool(_T("task_bar"), _T("task_bar_swap_up_down"), false);

	//m_taskbar_data.font.name = ini.GetString(_T("task_bar"), _T("tack_bar_font_name"), CCommon::LoadText(IDS_MICROSOFT_YAHEI)).c_str();
	//m_taskbar_data.font.size = ini.GetInt(_T("task_bar"), _T("tack_bar_font_size"), 9);
	default_font = FontInfo{};
	default_font.name = CCommon::LoadText(IDS_DEFAULT_FONT);
	default_font.size = 9;
	ini.LoadFontData(_T("task_bar"), m_taskbar_data.font, default_font);

	m_taskbar_data.disp_str.up = ini.GetString(L"task_bar", L"up_string", L"��: $");
	m_taskbar_data.disp_str.down = ini.GetString(L"task_bar", L"down_string", L"��: $");
	m_taskbar_data.disp_str.cpu = ini.GetString(L"task_bar", L"cpu_string", L"CPU: $");
	m_taskbar_data.disp_str.memory = ini.GetString(L"task_bar", L"memory_string", CCommon::LoadText(IDS_MEMORY_DISP, _T(": $")));

	m_taskbar_data.tbar_wnd_on_left = ini.GetBool(_T("task_bar"), _T("task_bar_wnd_on_left"), false);
	m_taskbar_data.speed_short_mode = ini.GetBool(_T("task_bar"), _T("task_bar_speed_short_mode"), false);
	m_taskbar_data.speed_unit = static_cast<SpeedUnit>(ini.GetInt(_T("task_bar"), _T("task_bar_speed_unit"), 0));
	m_taskbar_data.hide_unit = ini.GetBool(_T("task_bar"), _T("task_bar_hide_unit"), false);
	m_taskbar_data.hide_percent = ini.GetBool(_T("task_bar"), _T("task_bar_hide_percent"), false);
	m_taskbar_data.value_right_align = ini.GetBool(_T("task_bar"), _T("value_right_align"), false);
	m_taskbar_data.horizontal_arrange = ini.GetBool(_T("task_bar"), _T("horizontal_arrange"), false);
	m_taskbar_data.separate_value_unit_with_space = ini.GetBool(_T("task_bar"), _T("separate_value_unit_with_space"), true);
	m_taskbar_data.digits_number = ini.GetInt(_T("task_bar"), _T("digits_number"), 4);
	m_taskbar_data.double_click_action = static_cast<DoubleClickAction>(ini.GetInt(_T("task_bar"), _T("double_click_action"), 0));

	//��������
	m_cfg_data.m_show_internet_ip = ini.GetBool(L"connection_details", L"show_internet_ip", false);
	m_cfg_data.m_use_log_scale = ini.GetBool(_T("histroy_traffic"), _T("use_log_scale"), false);

	m_no_multistart_warning = ini.GetBool(_T("other"), _T("no_multistart_warning"), false);
	m_notify_interval = ini.GetInt(_T("other"), _T("notify_interval"), 60);
	m_exit_when_start_by_restart_manager = ini.GetBool(_T("other"), _T("exit_when_start_by_restart_manager"), true);
}

void CTrafficMonitorApp::SaveConfig()
{
	CIniHelper ini{ m_config_path };

	//��������
	ini.WriteBool(_T("general"), _T("check_update_when_start"), m_general_data.check_update_when_start);
	ini.WriteBool(_T("general"), _T("allow_skin_cover_font"), m_general_data.allow_skin_cover_font);
	ini.WriteBool(_T("general"), _T("allow_skin_cover_text"), m_general_data.allow_skin_cover_text);
	ini.WriteInt(_T("general"), _T("language"), static_cast<int>(m_general_data.language));

	//����������
	//����ǰ�Ȼ�ȡ���ڵ�λ��
	CRect rect;
	m_pMainWnd->GetWindowRect(rect);
	m_cfg_data.m_position_x = rect.left;
	m_cfg_data.m_position_y = rect.top;
	ini.WriteInt(L"config", L"transparency", m_cfg_data.m_transparency);
	ini.WriteBool(L"config", L"always_on_top", m_cfg_data.m_always_on_top);
	ini.WriteBool(L"config", L"lock_window_pos", m_cfg_data.m_lock_window_pos);
	ini.WriteBool(L"config", L"show_notify_icon", m_cfg_data.m_show_notify_icon);
	ini.WriteBool(L"config", L"show_cpu_memory", m_cfg_data.m_show_more_info);
	ini.WriteBool(L"config", L"mouse_penetrate", m_cfg_data.m_mouse_penetrate);
	ini.WriteBool(L"config", L"show_task_bar_wnd", m_cfg_data.m_show_task_bar_wnd);
	ini.WriteInt(L"config", L"position_x", m_cfg_data.m_position_x);
	ini.WriteInt(L"config", L"position_y", m_cfg_data.m_position_y);
	ini.WriteBool(L"connection", L"auto_select", m_cfg_data.m_auto_select);
	ini.WriteBool(L"connection", L"select_all", m_cfg_data.m_select_all);
	//ini.WriteInt(L"config", L"text_color", theApp.m_main_wnd_data.text_color);
	ini.WriteIntArray(L"config", L"text_color", (int*)m_main_wnd_data.text_colors, MAIN_WND_COLOR_NUM);
	ini.WriteBool(_T("config"), _T("specify_each_item_color"), m_main_wnd_data.specify_each_item_color);
	ini.WriteInt(L"config", L"hide_main_window", m_cfg_data.m_hide_main_window);
	//m_connection_name = m_connections[m_connection_selected].description;
	ini.WriteString(L"connection", L"connection_name", CCommon::StrToUnicode(m_cfg_data.m_connection_name.c_str()).c_str());
	ini.WriteString(_T("config"), _T("skin_selected"), m_cfg_data.m_skin_name.c_str());
	ini.WriteInt(L"config", L"notify_icon_selected", m_cfg_data.m_notify_icon_selected);

	//ini.WriteString(_T("config"), _T("font_name"), wstring(theApp.m_main_wnd_data.font.name));
	//ini.WriteInt(L"config", L"font_size", theApp.m_main_wnd_data.font.size);
	ini.SaveFontData(L"config", theApp.m_main_wnd_data.font);

	ini.WriteBool(L"config", L"swap_up_down", theApp.m_main_wnd_data.swap_up_down);
	ini.WriteBool(L"config", L"hide_main_wnd_when_fullscreen", theApp.m_main_wnd_data.hide_main_wnd_when_fullscreen);

	ini.WriteString(_T("config"), _T("up_string"), theApp.m_main_wnd_data.disp_str.up);
	ini.WriteString(_T("config"), _T("down_string"), theApp.m_main_wnd_data.disp_str.down);
	ini.WriteString(_T("config"), _T("cpu_string"), theApp.m_main_wnd_data.disp_str.cpu);
	ini.WriteString(_T("config"), _T("memory_string"), theApp.m_main_wnd_data.disp_str.memory);

	ini.WriteBool(L"config", L"speed_short_mode", theApp.m_main_wnd_data.speed_short_mode);
	ini.WriteBool(L"config", L"separate_value_unit_with_space", theApp.m_main_wnd_data.separate_value_unit_with_space);
	ini.WriteInt(L"config", L"speed_unit", static_cast<int>(theApp.m_main_wnd_data.speed_unit));
	ini.WriteBool(L"config", L"hide_unit", theApp.m_main_wnd_data.hide_unit);
	ini.WriteBool(L"config", L"hide_percent", theApp.m_main_wnd_data.hide_percent);
	ini.WriteInt(L"config", L"double_click_action", static_cast<int>(theApp.m_main_wnd_data.double_click_action));

	ini.WriteInt(L"config", L"alow_out_of_border", m_cfg_data.m_alow_out_of_border);

	ini.WriteBool(L"notify_tip", L"traffic_tip_enable", theApp.m_general_data.traffic_tip_enable);
	ini.WriteInt(L"notify_tip", L"traffic_tip_value", theApp.m_general_data.traffic_tip_value);
	ini.WriteInt(L"notify_tip", L"traffic_tip_unit", theApp.m_general_data.traffic_tip_unit);
	ini.WriteBool(L"notify_tip", L"memory_usage_tip_enable", theApp.m_general_data.memory_usage_tip_enable);
	ini.WriteInt(L"notify_tip", L"memory_tip_value", theApp.m_general_data.memory_tip_value);


	//��������������
	ini.WriteInt(L"task_bar", L"task_bar_back_color", m_taskbar_data.back_color);
	//ini.WriteInt(L"task_bar", L"task_bar_text_color", m_taskbar_data.text_color);
	ini.WriteIntArray(L"task_bar", L"task_bar_text_color", (int*)m_taskbar_data.text_colors, TASKBAR_COLOR_NUM);
	ini.WriteBool(L"task_bar", L"specify_each_item_color", m_taskbar_data.specify_each_item_color);
	ini.WriteBool(L"task_bar", L"task_bar_show_cpu_memory", m_cfg_data.m_tbar_show_cpu_memory);
	//ini.WriteString(_T("task_bar"), _T("tack_bar_font_name"), wstring(m_taskbar_data.font.name));
	//ini.WriteInt(L"task_bar", L"tack_bar_font_size", m_taskbar_data.font.size);
	ini.SaveFontData(L"task_bar", m_taskbar_data.font);
	ini.WriteBool(L"task_bar", L"task_bar_swap_up_down", m_taskbar_data.swap_up_down);

	ini.WriteString(_T("task_bar"), _T("up_string"), m_taskbar_data.disp_str.up);
	ini.WriteString(_T("task_bar"), _T("down_string"), m_taskbar_data.disp_str.down);
	ini.WriteString(_T("task_bar"), _T("cpu_string"), m_taskbar_data.disp_str.cpu);
	ini.WriteString(_T("task_bar"), _T("memory_string"), m_taskbar_data.disp_str.memory);

	ini.WriteBool(L"task_bar", L"task_bar_wnd_on_left", m_taskbar_data.tbar_wnd_on_left);
	ini.WriteBool(L"task_bar", L"task_bar_speed_short_mode", m_taskbar_data.speed_short_mode);
	ini.WriteInt(L"task_bar", L"task_bar_speed_unit", static_cast<int>(m_taskbar_data.speed_unit));
	ini.WriteBool(L"task_bar", L"task_bar_hide_unit", m_taskbar_data.hide_unit);
	ini.WriteBool(L"task_bar", L"task_bar_hide_percent", m_taskbar_data.hide_percent);
	ini.WriteBool(L"task_bar", L"value_right_align", m_taskbar_data.value_right_align);
	ini.WriteBool(L"task_bar", L"horizontal_arrange", m_taskbar_data.horizontal_arrange);
	ini.WriteBool(L"task_bar", L"separate_value_unit_with_space", m_taskbar_data.separate_value_unit_with_space);
	ini.WriteInt(L"task_bar", L"digits_number", m_taskbar_data.digits_number);
	ini.WriteInt(L"task_bar", L"double_click_action", static_cast<int>(m_taskbar_data.double_click_action));

	//��������
	ini.WriteBool(L"connection_details", L"show_internet_ip", m_cfg_data.m_show_internet_ip);
	ini.WriteBool(L"histroy_traffic", L"use_log_scale", m_cfg_data.m_use_log_scale);

	ini.WriteBool(_T("other"), _T("no_multistart_warning"), m_no_multistart_warning);
	ini.WriteBool(_T("other"), _T("exit_when_start_by_restart_manager"), m_exit_when_start_by_restart_manager);
	ini.WriteInt(_T("other"), _T("notify_interval"), m_notify_interval);

	//����Ƿ񱣴�ɹ�
	if (!ini.Save())
	{
		if (m_cannot_save_config_warning)
		{
			CString info;
			info.LoadString(IDS_CONNOT_SAVE_CONFIG_WARNING);
			info.Replace(_T("<%file_path%>"), theApp.m_config_path.c_str());
			AfxMessageBox(info, MB_ICONWARNING);
		}
		m_cannot_save_config_warning = false;
		return;
	}
}

int CTrafficMonitorApp::DPI(int pixel)
{
	return m_dpi * pixel / 96;
}

void CTrafficMonitorApp::DPI(CRect & rect)
{
	rect.left = DPI(rect.left);
	rect.right = DPI(rect.right);
	rect.top = DPI(rect.top);
	rect.bottom = DPI(rect.bottom);
}

void CTrafficMonitorApp::GetDPI(CWnd* pWnd)
{
	CWindowDC dc(pWnd);
	HDC hDC = dc.GetSafeHdc();
	m_dpi = GetDeviceCaps(hDC, LOGPIXELSY);
}

void CTrafficMonitorApp::CheckUpdate(bool message)
{
	CWaitCursor wait_cursor;
	wstring version_info;
	if (!CCommon::GetURL(L"https://raw.githubusercontent.com/zhongyang219/TrafficMonitor/master/version_utf8.info", version_info, true))		//��ȡ�汾��Ϣ
	{
		if(message)
			AfxMessageBox(CCommon::LoadText(IDS_CHECK_UPDATE_FAILD), MB_OK | MB_ICONWARNING);
		return;
	}

	size_t index, index1, index2, index3, index4, index5;
	index = version_info.find(L"<version>");
	index1 = version_info.find(L"</version>");
	index2 = version_info.find(L"<link>");
	index3 = version_info.find(L"</link>");
	index4 = version_info.find(L"<contents>");
	index5 = version_info.find(L"</contents>");
	wstring version;		//����汾
	wstring link;			//��������
	wstring contents;		//��������
	version = version_info.substr(index + 9, index1 - index - 9);
	link = version_info.substr(index2 + 6, index3 - index2 - 6);
	contents = version_info.substr(index4 + 10, index5 - index4 - 10);
	CString contents_str = contents.c_str();
	contents_str.Replace(L"\\n", L"\r\n");
	if (index == wstring::npos || index1 == wstring::npos || index2 == wstring::npos || index3 == wstring::npos || version.empty() || link.empty())
	{
		if (message)
			AfxMessageBox(CCommon::LoadText(IDS_CHECK_UPDATE_ERROR), MB_OK | MB_ICONWARNING);
		return;
	}
	if (version > VERSION)		//����������ϵİ汾���ڱ��ذ汾
	{
		CString info;
		if (contents.empty())
			info.Format(CCommon::LoadText(IDS_UPDATE_AVLIABLE), version.c_str());
		else
			info.Format(CCommon::LoadText(IDS_UPDATE_AVLIABLE2), version.c_str(), contents_str);
			
		if (AfxMessageBox(info, MB_YESNO | MB_ICONQUESTION) == IDYES)
		{
			ShellExecute(NULL, _T("open"), link.c_str(), NULL, NULL, SW_SHOW);		//ת����������
		}
	}
	else
	{
		if(message)
			AfxMessageBox(CCommon::LoadText(IDS_ALREADY_UPDATED), MB_OK | MB_ICONINFORMATION);
	}
}

UINT CTrafficMonitorApp::CheckUpdateThreadFunc(LPVOID lpParam)
{
	CCommon::SetThreadLanguage(theApp.m_general_data.language);		//�����߳�����
	CheckUpdate(false);		//������
	return 0;
}

void CTrafficMonitorApp::SetAutoRun(bool auto_run)
{
	CRegKey key;
	//��ע�����
	if (key.Open(HKEY_CURRENT_USER, _T("Software\\Microsoft\\Windows\\CurrentVersion\\Run")) != ERROR_SUCCESS)
	{
		AfxMessageBox(CCommon::LoadText(IDS_AUTORUN_FAILED_NO_KEY), MB_OK | MB_ICONWARNING);
		return;
	}
	if (auto_run)		//д��ע�����
	{
		if (key.SetStringValue(_T("TrafficMonitor"), m_module_path_reg.c_str()) != ERROR_SUCCESS)
		{
			AfxMessageBox(CCommon::LoadText(IDS_AUTORUN_FAILED_NO_ACCESS), MB_OK | MB_ICONWARNING);
			return;
		}
	}
	else		//ɾ��ע�����
	{
		//ɾ��ǰ�ȼ��ע������Ƿ���ڣ���������ڣ���ֱ�ӷ���
		wchar_t buff[256];
		ULONG size{ 256 };
		if (key.QueryStringValue(_T("TrafficMonitor"), buff, &size) != ERROR_SUCCESS)
			return;
		if (key.DeleteValue(_T("TrafficMonitor")) != ERROR_SUCCESS)
		{
			AfxMessageBox(CCommon::LoadText(IDS_AUTORUN_DELETE_FAILED), MB_OK | MB_ICONWARNING);
			return;
		}
	}
}

bool CTrafficMonitorApp::GetAutoRun()
{
	CRegKey key;
	if (key.Open(HKEY_CURRENT_USER, _T("Software\\Microsoft\\Windows\\CurrentVersion\\Run")) != ERROR_SUCCESS)
	{
		//��ע���Software\\Microsoft\\Windows\\CurrentVersion\\Run��ʧ�ܣ��򷵻�false
		return false;
	}
	wchar_t buff[256];
	ULONG size{ 256 };
	if (key.QueryStringValue(_T("TrafficMonitor"), buff, &size) == ERROR_SUCCESS)		//����ҵ��ˡ�TrafficMonitor����
	{
		return (m_module_path_reg == buff);	//�����TrafficMonitor����ֵ�ǵ�ǰ�����·�����ͷ���true�����򷵻�false
	}
	else
	{
		return false;		//û���ҵ���TrafficMonitor����������false
	}
}


// Ψһ��һ�� CTrafficMonitorApp ����

CTrafficMonitorApp theApp;


// CTrafficMonitorApp ��ʼ��

BOOL CTrafficMonitorApp::InitInstance()
{
	//���������ļ���·��
	wchar_t path[MAX_PATH];
	GetModuleFileNameW(NULL, path, MAX_PATH);
	m_module_path = path;
	if (m_module_path.find(L' ') != wstring::npos)
	{
		//���·�����пո����ڳ���·��ǰ�����˫����
		m_module_path_reg = L'\"';
		m_module_path_reg += m_module_path;
		m_module_path_reg += L'\"';
	}
	else
	{
		m_module_path_reg = m_module_path;
	}
	m_system_path = CCommon::GetSystemPath();
	m_temp_path = CCommon::GetTemplatePath();
	m_app_data_cfg_path = CCommon::GetAppDataConfigPath();
#ifdef _DEBUG
	m_config_path = L".\\config.ini";
	m_history_traffic_path = L".\\history_traffic.dat";
	m_log_path = L".\\error.log";
	m_skin_path = L".\\skins";
#else
	//AppData����ĳ��������ļ�·��
	m_config_path = m_app_data_cfg_path + L"config.ini";
	m_history_traffic_path = m_app_data_cfg_path + L"history_traffic.dat";
	m_log_path = m_app_data_cfg_path + L"error.log";
	//ԭ���ġ���������Ŀ¼�µ������ļ���·��
	wstring exe_path = CCommon::GetExePath();
	wstring config_path_old = exe_path + L"config.ini";
	wstring history_traffic_path_old = exe_path + L"history_traffic.dat";
	wstring log_path_old = exe_path + L"error.log";
	//�����������Ŀ¼�º��������ļ��������ƶ���AppData��Ӧ��Ŀ¼����
	CCommon::MoveAFile(config_path_old.c_str(), m_config_path.c_str());
	CCommon::MoveAFile(history_traffic_path_old.c_str(), m_history_traffic_path.c_str());
	CCommon::MoveAFile(log_path_old.c_str(), m_log_path.c_str());

	m_skin_path = exe_path + L"skins";
#endif

	bool is_windows10_fall_creator = m_win_version.IsWindows10FallCreatorOrLater();

	//��ini�ļ���������
	LoadConfig();

	//��ʼ����������
	CCommon::SetThreadLanguage(m_general_data.language);

#ifndef _DEBUG
	wstring cmd_line{ m_lpCmdLine };
	bool is_restart{ cmd_line.find(L"RestartByRestartManager") != wstring::npos };		//��������в����к����ַ�����RestartByRestartManager����˵�������Ǳ�Windows����������
	//bool when_start{ CCommon::WhenStart(m_no_multistart_warning_time) };
	if (m_exit_when_start_by_restart_manager && is_restart && is_windows10_fall_creator)		//��ǰWindows�汾���＾�����߸���ʱ���������������������ֱ���˳�����
	{
		//AfxMessageBox(_T("������Ϣ�������ѱ�Windows����������������������"));
		return FALSE;
	}

	//����Ƿ�����ʵ����������
	HANDLE hMutex = ::CreateMutex(NULL, TRUE, _T("TrafficMonitor-1419J3XLKL1w8OZc"));
	if (hMutex != NULL)
	{
		if (GetLastError() == ERROR_ALREADY_EXISTS)
		{
			//char buff[128];
			//string cmd_line_str{ CCommon::UnicodeToStr(cmd_line.c_str()) };
			//sprintf_s(buff, "when_start=%d, m_no_multistart_warning=%d, cmd_line=%s", when_start, m_no_multistart_warning, cmd_line_str.c_str());
			//CCommon::WriteLog(buff, _T(".\\start.log"));
			if (!m_no_multistart_warning)
			{
				AfxMessageBox(CCommon::LoadText(IDS_AN_INSTANCE_RUNNING));
			}
			return FALSE;
		}
	}
#endif

	//SaveConfig();

	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControlsEx()��  ���򣬽��޷��������ڡ�
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ��������Ϊ��������Ҫ��Ӧ�ó�����ʹ�õ�
	// �����ؼ��ࡣ
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	AfxEnableControlContainer();

	// ���� shell ���������Է��Ի������
	// �κ� shell ����ͼ�ؼ��� shell �б���ͼ�ؼ���
	CShellManager *pShellManager = new CShellManager;

	// ���Windows Native���Ӿ����������Ա��� MFC �ؼ�����������
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));

	//����ʱ������
	if (m_general_data.check_update_when_start)
	{
		m_pUpdateThread = AfxBeginThread(CheckUpdateThreadFunc, NULL);
	}

	CTrafficMonitorDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: �ڴ˷��ô����ʱ��
		//  ��ȷ�������رնԻ���Ĵ���
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: �ڴ˷��ô����ʱ��
		//  ��ȡ�������رնԻ���Ĵ���
	}
	else if (nResponse == -1)
	{
		TRACE(traceAppMsg, 0, "����: �Ի��򴴽�ʧ�ܣ�Ӧ�ó���������ֹ��\n");
		TRACE(traceAppMsg, 0, "����: ������ڶԻ�����ʹ�� MFC �ؼ������޷� #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS��\n");
	}

	// ɾ�����洴���� shell ��������
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

#ifndef _AFXDLL
	ControlBarCleanUp();
#endif

	// ���ڶԻ����ѹرգ����Խ����� FALSE �Ա��˳�Ӧ�ó���
	//  ����������Ӧ�ó������Ϣ�á�
	return FALSE;
}



void CTrafficMonitorApp::OnHelp()
{
	// TODO: �ڴ���������������
	CString language_code;
	language_code.LoadString(IDS_LANGUAGE_CODE);
	if (language_code == _T("2"))
		ShellExecute(NULL, _T("open"), _T("https://github.com/zhongyang219/TrafficMonitor/blob/master/Help.md"), NULL, NULL, SW_SHOW);	//�򿪳�����;
	else
		ShellExecute(NULL, _T("open"), _T("https://github.com/zhongyang219/TrafficMonitor/blob/master/Help_en-us.md"), NULL, NULL, SW_SHOW);
}
