#pragma once

#ifndef _PLUGIN_H_
#define _PLUGIN_H_
#include "Plugin.Core.Win32.h"

struct PluginInterface_
{
	void *reserved_inner_plugin;

	LPCTSTR Name; // ��������ơ�
	LPCTSTR DisplayName; // �����ʾ�ڲ���������е����ơ�
	::Version Version; // ����İ汾��
	::Version MinVersion; // ���֧�ֵ���С�汾��
	LPCTSTR Description; // �����������
};

struct Plugin_
{
#ifdef __cplusplus
protected:
	const void *inner_plugin;

public:
	LPCTSTR Name; // ��������ơ�
	LPCTSTR DisplayName; // �����ʾ�ڲ���������е����ơ�
	::Version Version; // ����İ汾��
	::Version MinVersion; // ���֧�ֵ���С�汾��
	LPCTSTR Description; // �����������

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
#ifdef __cplusplus
}
#endif
#endif