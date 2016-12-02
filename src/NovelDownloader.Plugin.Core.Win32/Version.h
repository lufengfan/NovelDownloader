#pragma once

#ifndef _VERSION_H_
#define _VERSION_H_

#include "exports.h"
#include <Windows.h>

typedef struct
{
	unsigned int Major; // ���汾��
	unsigned int Minor; // �ΰ汾��
	unsigned int Revision; // �׶ΰ汾��
	LPCTSTR Date; // ���ڰ汾��
	LPCTSTR Period; // ϣ����ĸ�汾��
} _Version;
typedef _Version *Version;

#ifdef __cplusplus
EXTERN_C
{
#endif
typedef HANDLE HVERSION; // �汾�Žṹ�ľ����

NOVELDOWNLOADERPLUGINCOREWIN32_API unsigned int Version_Major(HVERSION);
NOVELDOWNLOADERPLUGINCOREWIN32_API unsigned int Version_Minor(HVERSION);
NOVELDOWNLOADERPLUGINCOREWIN32_API unsigned int Version_Revision(HVERSION);

NOVELDOWNLOADERPLUGINCOREWIN32_API LPCTSTR Version_Date(HVERSION);
NOVELDOWNLOADERPLUGINCOREWIN32_API LPCTSTR Version_Period(HVERSION);
#ifdef __cplusplus
}
#endif

#endif