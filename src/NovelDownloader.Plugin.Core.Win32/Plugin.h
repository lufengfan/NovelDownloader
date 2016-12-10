#pragma once
//#undef __cplusplus
#ifndef _PLUGIN_H_
#define _PLUGIN_H_
#include "Plugin.Core.Win32.h"

static void CreateInstance_PluginInterface_(PluginInterface_ *p_pi);
struct PluginInterface_
{
	void *reserved_inner_plugin;

	LPCTSTR Name; // ��������ơ�
	LPCTSTR DisplayName; // �����ʾ�ڲ���������е����ơ�
	::Version *Version; // ����İ汾��
	::Version *MinVersion; // ���֧�ֵ���С�汾��
	LPCTSTR Description; // �����������
	GUID *Guid; // �����ȫ��Ψһ��ʶ����

#ifdef __cplusplus
	PluginInterface_()
	{
		size_t size = sizeof(PluginInterface_);
		PluginInterface_ *p_pi = NULL;
		::CreateInstance_PluginInterface_(p_pi);

		memcpy_s(this, size, p_pi, size);
	}
	~PluginInterface_() {}
#endif
};

static void CreateInstance_PluginInterface_(PluginInterface_ *p_pi)
{
	::PluginInterface_ pi = {};
	pi.reserved_inner_plugin = NULL;
	pi.Name = LPCTSTR(EMPTY_STRING);
	pi.DisplayName = LPCTSTR(EMPTY_STRING);
	*pi.Version = DEFAULT_VERSION;
	*pi.MinVersion = DEFAULT_VERSION;
	pi.Description = LPCTSTR(EMPTY_STRING);
	*pi.Guid = DEFAULT_GUID;

	p_pi = &pi;
}

struct Plugin_
{
#ifdef __cplusplus
protected:
	const void *inner_plugin;

public:
	LPCTSTR Name; // ��������ơ�
	LPCTSTR DisplayName; // �����ʾ�ڲ���������е����ơ�
	::Version *Version; // ����İ汾��
	::Version *MinVersion; // ���֧�ֵ���С�汾��
	LPCTSTR Description; // �����������
	GUID *Guid; // �����ȫ��Ψһ��ʶ����

	Plugin_();
	~Plugin_();
#endif
};

#ifdef __cplusplus
EXTERN_C
{
#endif
NOVELDOWNLOADERPLUGINCOREWIN32_API LPCTSTR Plugin_Name(HPLUGIN);
NOVELDOWNLOADERPLUGINCOREWIN32_API LPCTSTR Plugin_DisplayName(HPLUGIN);
NOVELDOWNLOADERPLUGINCOREWIN32_API Version Plugin_Version(HPLUGIN);
NOVELDOWNLOADERPLUGINCOREWIN32_API Version Plugin_MinVersion(HPLUGIN);
NOVELDOWNLOADERPLUGINCOREWIN32_API LPCTSTR Plugin_Description(HPLUGIN);
NOVELDOWNLOADERPLUGINCOREWIN32_API GUID Plugin_Guid(HPLUGIN);
#ifdef __cplusplus
}
#endif
#endif