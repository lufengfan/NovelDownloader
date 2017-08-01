#include "exports.h"

typedef HANDLE HPLUGIN;

namespace SamLu
{
	namespace Plugin
	{
		class MyPlugin {};
	};
}

static void rp(HPLUGIN hPlugin);

WIN32PLUGIN_API HPLUGIN LoadPlugin(GUID);
WIN32PLUGIN_API void ReleasePlugin(HPLUGIN);

WIN32PLUGIN_API HPLUGIN LoadPluginWithReleaseMethod(GUID, OUT void(**)(HPLUGIN));

WIN32PLUGIN_API BOOL Plugin_Name(HPLUGIN, LPTSTR);

#ifdef WIN32PLUGIN_EXAMPLES
// �����Ǵ� Win32Plugin.dll ������
class WIN32PLUGIN_API CWin32Plugin {
public:
	CWin32Plugin(void);
	// TODO:  �ڴ�������ķ�����
};

extern WIN32PLUGIN_API int nWin32Plugin;

WIN32PLUGIN_API int fnWin32Plugin(void);
#endif // WIN32PLUGIN_EXAMPLES
