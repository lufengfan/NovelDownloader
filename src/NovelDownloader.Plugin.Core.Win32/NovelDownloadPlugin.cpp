#include "stdafx.h"
#include "NovelDownloadPlugin.h"

#ifdef __cplusplus

static bool TryGetBookTokenInternal(Plugin *hPlugin, LPCTSTR uri, NDTBook *bookToken)
{
	return false;
}

bool NovelDownloadPlugin_::TryGetBookToken(LPCTSTR uri, NDTBook* bookToken)
{
	return ((NovelDownloadPluginInterface_*)this->inner_plugin)->TryGetBookToken(this, uri, bookToken);
}

NovelDownloadPlugin_::NovelDownloadPlugin_()
{
	this->inner_plugin = this; // �ڲ���ָ��ָ�������Ա��߼������������ĳ�Ա��
	((NovelDownloadPluginInterface_*)this)->TryGetBookToken = &TryGetBookTokenInternal;
}

NovelDownloadPlugin_::~NovelDownloadPlugin_()
{
	if (this->inner_plugin != NULL)
	{
		this->inner_plugin = NULL; // ���ָ��������ڲ�ָ��ָ��ա�
	}
}
#endif