#include "stdafx.h"
#include "Plugin.h"

#ifdef __cplusplus

Plugin_::Plugin_()
{
	this->inner_plugin = this; // �ڲ���ָ��ָ�������Ա��߼������������ĳ�Ա��
	this->Name = LPCTSTR(EMPTY_STRING);
	this->DisplayName = LPCTSTR(EMPTY_STRING);
	*this->Version = DEFAULT_VERSION;
	*this->MinVersion = DEFAULT_VERSION;
	this->Description = LPCTSTR(EMPTY_STRING);
	*this->Guid = DEFAULT_GUID;
}

Plugin_::~Plugin_()
{
	if (this->inner_plugin != NULL)
	{
		this->inner_plugin = NULL; // ���ָ��������ڲ�ָ��ָ��ա�
	}
}
#endif