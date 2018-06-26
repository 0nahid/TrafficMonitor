#pragma once
#include "CommonData.h"

class CIniHelper
{
public:
	CIniHelper();
	~CIniHelper();

	void SetPath(const wstring& path);

	void WriteString(const wchar_t* AppName, const wchar_t* KeyName, wstring str);
	wstring GetString(const wchar_t* AppName, const wchar_t* KeyName, const wchar_t* default_str);
	void WriteInt(const wchar_t * AppName, const wchar_t * KeyName, int value);
	int GetInt(const wchar_t * AppName, const wchar_t * KeyName, int default_value);
	void WriteBool(const wchar_t * AppName, const wchar_t * KeyName, bool value);
	bool GetBool(const wchar_t * AppName, const wchar_t * KeyName, bool default_value);
	void WriteIntArray(const wchar_t * AppName, const wchar_t * KeyName, const int* values, int size);		//д��һ��int���飬Ԫ�ظ���Ϊsize
	bool GetIntArray(const wchar_t * AppName, const wchar_t * KeyName, int* values, int size, int default_value = 0);		//��ȡһ��int���飬���浽values��Ԫ�ظ���Ϊsize
	void WriteBoolArray(const wchar_t * AppName, const wchar_t * KeyName, const bool* values, int size);
	void GetBoolArray(const wchar_t * AppName, const wchar_t * KeyName, bool* values, int size, bool default_value = false);

	void SaveFontData(const wchar_t * AppName, const FontInfo& font);
	void LoadFontData(const wchar_t * AppName, FontInfo& font, const FontInfo& default_font);

	bool CheckSaveFailed() const { return m_save_failed; }

protected:
	wstring m_path;
	bool m_save_failed{ false };		//�Ƿ񱣴�ʧ��
};

