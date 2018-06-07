#pragma once
class CWinVersionHelper
{
public:
	CWinVersionHelper();
	~CWinVersionHelper();

	bool IsWindows10FallCreatorOrLater() const;		//�жϵ�ǰWindows�汾�Ƿ�ΪWin10�＾�����߸��»���µİ汾
	bool IsWindows7() const;
	int GetMajorVersion() const { return m_major_version; }
	int GetMinorVersion() const { return m_minor_version; }
	int GetBuildNumber() const { return m_build_number; }
protected:
	int m_major_version{};
	int m_minor_version{};
	int m_build_number{};
};

