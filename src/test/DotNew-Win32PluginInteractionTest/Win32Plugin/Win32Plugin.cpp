// Win32Plugin.cpp : ���� DLL Ӧ�ó���ĵ���������
//

#include "stdafx.h"
#include "Win32Plugin.h"

#include <iostream>
using namespace std;

using namespace SamLu::Plugin;

WIN32PLUGIN_API HPLUGIN LoadPlugin(GUID guid)
{
	char szGuid[128] = { 0 };

	_snprintf(szGuid, sizeof(szGuid)
		, "{%08X-%04X-%04x-%02X%02X-%02X%02X%02X%02X%02X%02X}"
		, guid.Data1
		, guid.Data2
		, guid.Data3
		, guid.Data4[0], guid.Data4[1]
		, guid.Data4[2], guid.Data4[3], guid.Data4[4], guid.Data4[5]
		, guid.Data4[6], guid.Data4[7]
	);

	cout << "In LoadPlugin.    guid: "<< szGuid << endl;

	return new MyPlugin();
}
WIN32PLUGIN_API void ReleasePlugin(HPLUGIN hPlugin)
{
	cout << "In ReleasePlugin.    hPlugin: " << hPlugin << endl;

	delete hPlugin;
}

WIN32PLUGIN_API HPLUGIN LoadPluginWithReleaseMethod(GUID guid, OUT void(**phRelease)(HPLUGIN))
{
	cout << "In LoadPluginWithReleaseMethod." << endl;

	*phRelease = &ReleasePlugin;

	return LoadPlugin(guid);
}

#ifdef WIN32PLUGIN_EXAMPLES
// ���ǵ���������һ��ʾ��
WIN32PLUGIN_API int nWin32Plugin=0;

// ���ǵ���������һ��ʾ����
WIN32PLUGIN_API int fnWin32Plugin(void)
{
    return 42;
}

// �����ѵ�����Ĺ��캯����
// �й��ඨ�����Ϣ������� Win32Plugin.h
CWin32Plugin::CWin32Plugin()
{
    return;
}
#endif
