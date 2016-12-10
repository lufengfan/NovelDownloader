#pragma once

#ifndef _NOVEL_DOWNLOAD_PLUGIN_H_
#define _NOVEL_DOWNLOAD_PLUGIN_H_
#include "Plugin.h"
#include "NDTBook.h"

struct NovelDownloadPluginInterface_;
struct NovelDownloadPlugin_;

static void CreateInstance_NovelDownloadPluginInterface_(NovelDownloadPluginInterface_*);
struct NovelDownloadPluginInterface_
{
	void *reserved_inner_plugin;

	LPCTSTR Name; // ��������ơ�
	LPCTSTR DisplayName; // �����ʾ�ڲ���������е����ơ�
	::Version *Version; // ����İ汾��
	::Version *MinVersion; // ���֧�ֵ���С�汾��
	LPCTSTR Description; // �����������
	GUID *Guid; // �����ȫ��Ψһ��ʶ����

	bool(*TryGetBookToken)(Plugin*, LPCTSTR, NDTBook*); // ���Ի�ȡλ��ָ��λ�õ�С˵��ǩ��

#ifdef __cplusplus
	NovelDownloadPluginInterface_()
	{
		size_t size = sizeof(NovelDownloadPluginInterface_);
		NovelDownloadPluginInterface_ *p_ndpi = NULL;
		::CreateInstance_NovelDownloadPluginInterface_(p_ndpi);

		memcpy_s(this, size, p_ndpi, size);
	}
	~NovelDownloadPluginInterface_() {}
#endif
};

static void CreateInstance_NovelDownloadPluginInterface_(NovelDownloadPluginInterface_ *p_ndpi)
{
	NovelDownloadPluginInterface_ ndpi = {};
	ndpi.reserved_inner_plugin = NULL;
	ndpi.Name = LPCTSTR(EMPTY_STRING);
	ndpi.DisplayName = LPCTSTR(EMPTY_STRING);
	*ndpi.Version = DEFAULT_VERSION;
	*ndpi.MinVersion = DEFAULT_VERSION;
	ndpi.Description = LPCTSTR(EMPTY_STRING);
	*ndpi.Guid = DEFAULT_GUID;
	ndpi.TryGetBookToken = NULL;

	p_ndpi = &ndpi;
}

struct NovelDownloadPlugin_
#ifdef __cplusplus
	: public Plugin_
#endif
{
	void *reserved_TryGetBookToken;

	bool TryGetBookToken(LPCTSTR, NDTBook*);  // ���Ի�ȡλ��ָ��λ�õ�С˵��ǩ��

	NovelDownloadPlugin_();
	~NovelDownloadPlugin_();
};

#ifdef __cplusplus
EXTERN_C
{
#endif
NOVELDOWNLOADERPLUGINCOREWIN32_API bool Plugin_TryGetBookToken(LPCTSTR, HNDTBook);
#ifdef __cplusplus
}
#endif
#endif