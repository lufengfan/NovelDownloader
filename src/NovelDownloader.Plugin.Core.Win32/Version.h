#pragma once

#ifndef _VERSION_H_
#define _VERSION_H_

#include "exports.h"
#include <Windows.h>

struct _Version
{
	unsigned int Major; // ���汾��
	unsigned int Minor; // �ΰ汾��
	unsigned int Revision; // �׶ΰ汾��
	LPCTSTR Date; // ���ڰ汾��
	LPCTSTR Period; // ϣ����ĸ�汾��
};
typedef _Version VERSION;

#if defined __cplusplus & defined C_EXPORTS
EXTERN_C
{
#endif
typedef HANDLE HVERSION; // �汾�Žṹ�ľ����

NOVELDOWNLOADERPLUGINCOREWIN32_API unsigned int APIENTRY Version_Major(HVERSION);
NOVELDOWNLOADERPLUGINCOREWIN32_API unsigned int APIENTRY Version_Minor(HVERSION);
NOVELDOWNLOADERPLUGINCOREWIN32_API unsigned int APIENTRY Version_Revision(HVERSION);

NOVELDOWNLOADERPLUGINCOREWIN32_API LPCTSTR APIENTRY Version_Date(HVERSION);
NOVELDOWNLOADERPLUGINCOREWIN32_API LPCTSTR APIENTRY Version_Period(HVERSION);

#if defined __cplusplus & defined C_EXPORTS
}
#endif

#endif