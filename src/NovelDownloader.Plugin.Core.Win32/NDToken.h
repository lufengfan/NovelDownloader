#pragma once
//#undef __cplusplus
#ifndef _NDTOKEN_H_
#define _NDTOKEN_H_

#include "exports.h"
#include "macros.h"
#include <Windows.h>
#include <list>

struct NDTokenInterface_;
struct NDToken_;

#ifdef __cplusplus
typedef struct NDToken_ NDToken;
#else
typedef struct NDTokenInterface_ *NDToken;
#endif

typedef struct
{
	LPCTSTR Message; // ��������Ϣ��
	DWORD Code; // �����Ĵ����롣
	void *Data; // �������������ݡ�
} _Args;
typedef _Args Args;

typedef void(*EventHandler)(void*, void*);

struct NDTokenInterface_
{
	void *reserved_inner_token;

	NDToken *Parent; // ��־�ĸ���־����
	NDToken *Children; // ��־���ӱ�־���󼯺ϡ�
	LPCTSTR Type; // ��־�����͡�
	LPCTSTR Title; // ��־�ı��⡣
	LPCTSTR Description; // ��־��������
	LPCTSTR Uri; // ��־��ȫ��ͳһ��ʶ����
	EventHandler *CreepStarted; // ����������ʱ���õĺ����б�
	EventHandler *CreepFetched; // �����沶׽������ʱ���õĺ����б�
	EventHandler *CreepFinished; // ��������ֹʱ���õĺ����б�
	EventHandler *CreepErrored; // �����������ڲ�����ʱ���õĺ����б�

	bool(*CanStartCreep)(NDToken*); // ����Ƿ�����������档
	void(*StartCreep)(NDToken*); // �������档
	void(*StartCreepInternal)(NDToken*); // �ڲ����õ���������ķ�����

	bool(*CanCreep)(NDToken*, void*); // ��������Ƿ����������һ����־��
	void*(*Creep)(NDToken*, void*); // ��������һ����־���С�����ȡ�ɼ��������ݡ�
	bool(*CreepInternal)(NDToken*); // �ڲ����õ��������еķ�����

	void(*OnCreepStarted)(NDToken*, void*, void*); // ����CreepStarted�ĵ��÷�����
	void(*OnCreepFetched)(NDToken*, void*, void*); // ����CreepFetched�ĵ��÷�����
	void(*OnCreepFinished)(NDToken*, void*, void*); // ����CreepFinished�ĵ��÷�����
	void(*OnCreepErrored)(NDToken*, void*, void*); // ����CreepErrored�ĵ��÷�����
};

struct NDToken_
{
#ifdef __cplusplus
protected:
	const void *inner_token;

public:
	NDToken *Parent; // ��־�ĸ���־����
	NDToken *Children; // ��־���ӱ�־���󼯺ϡ�
	LPCTSTR Type; // ��־�����͡�
	LPCTSTR Title; // ��־�ı��⡣
	LPCTSTR Description; // ��־��������
	LPCTSTR Uri; // ��־��ȫ��ͳһ��ʶ����
	EventHandler *CreepStarted; // ����������ʱ���õĺ����б�
	EventHandler *CreepFetched; // �����沶׽������ʱ���õĺ����б�
	EventHandler *CreepFinished; // ��������ֹʱ���õĺ����б�
	EventHandler *CreepErrored; // �����������ڲ�����ʱ���õĺ����б�

	void *reserved_CanStopCreep;
	void *reserved_StartCreep;
	void *reserved_StartCreepInternal;
	
	void *reserved_CanCreep;
	void *reserved_Creep;
	void *reserved_CreepInternal;
	
	void *reserved_OnCreepStarted;
	void *reserved_OnCreepFetched;
	void *reserved_OnCreepFinished;
	void *reserved_OnCreepErrored;

	bool CanStartCreep(); // ����Ƿ�����������档
	void StartCreep(); // �������档
	void StartCreepInternal(); // �ڲ����õ���������ķ�����

	bool CanCreep(void*); // ��������Ƿ����������һ����־��
	template<typename TData> bool CanCreep(TData*); // ��������Ƿ����������һ����־��
	void* Creep(void*); // ��������һ����־���С�����ȡ�ɼ��������ݡ�
	template<typename TData, typename TFetch> TFetch* Creep(TData*); // ��������һ����־���С�����ȡ�ɼ��������ݡ�
	bool CreepInternal(); // �ڲ����õ��������еķ�����

	void OnCreepStarted(void*, void*); // ����CreepStarted�ĵ��÷�����
	void OnCreepFetched(void*, void*); // ����CreepFetched�ĵ��÷�����
	template<typename TData> void OnCreepFetched(void*, TData*); // ����CreepFetched�ĵ��÷�����
	void OnCreepFinished(void*, void*); // ����CreepFinished�ĵ��÷�����
	void OnCreepErrored(void*, void*); // ����CreepErrored�ĵ��÷�����
	template<typename TArgs> void OnCreepErrored(void*, TArgs*); // ����CreepErrored�ĵ��÷�����
#endif
};

static int INTERNAL_NDToken_Children_count = 0;
static int INTERNAL_NDToken_Children_capacity = 0;
// ���־���ӱ�־���󼯺������һ����־��
static void INTERNAL_Token_Children_add(NDTokenInterface_ *DestinateToken, NDToken *Token)
{
	if (DestinateToken == NULL || Token == NULL) return;

	if (SYNTAX_FILTER_ACCESS(Token)->Parent != NULL && POINTER_ADDRESS_EQUALS(SYNTAX_FILTER_ACCESS(Token)->Parent, DestinateToken))
	{
		Args args = { LPCTSTR("��־�Ѿ��и�Ԫ�أ��޷����ǡ�"), 0, NULL };
		throw args;
	}
	
	*SYNTAX_FILTER_ACCESS(Token)->Parent = *(NDToken*)DestinateToken; // ������ӵı�־�ĸ�Ԫ�ء�
	
	if (INTERNAL_NDToken_Children_count >= INTERNAL_NDToken_Children_capacity)
	{
		size_t size = sizeof(NDToken);
		MALLOC(NDToken, children, size * (INTERNAL_NDToken_Children_count + 10))
		if (DestinateToken->Children != NULL)
		{
			memcpy_s(children, size * INTERNAL_NDToken_Children_count, DestinateToken->Children, size * INTERNAL_NDToken_Children_count);
			FREE(NDToken, DestinateToken->Children)
		}
		DestinateToken->Children = children;
		FREE(NDToken, children);
		INTERNAL_NDToken_Children_capacity = INTERNAL_NDToken_Children_count + 10;
	}
	DestinateToken->Children[INTERNAL_NDToken_Children_count] = *Token;
	INTERNAL_NDToken_Children_count++;
}

// �ӱ�־���ӱ�־���󼯺����Ƴ�һ����־��
static void INTERNAL_Token_Children_remove(NDTokenInterface_ *DestinateToken, NDToken *Token)
{
	if (DestinateToken == NULL || Token == NULL) return;

	for (int i = 0; i < INTERNAL_NDToken_Children_count; i++)
	{
		if (POINTER_ADDRESS_EQUALS(&(DestinateToken->Children[i]), Token))
		{
			size_t size = sizeof(NDToken) * (INTERNAL_NDToken_Children_count - i - 1);
			MALLOC(NDToken, temp, size)
			memcpy_s(&temp[0], size, &(DestinateToken->Children[i + 1]), size);
			memcpy_s(&(DestinateToken->Children[i]), size, &temp[0], size);
			FREE(NDToken, temp);
			INTERNAL_NDToken_Children_count--;
		}
	}
}

static int INTERNAL_Token_Children_indexof(NDTokenInterface_ *DestinateToken, NDToken *Token)
{
	if (DestinateToken == NULL || Token == NULL) return -1;

	for (int i = 0; i < INTERNAL_NDToken_Children_count; i++)
	{
		if (POINTER_ADDRESS_EQUALS(&(DestinateToken->Children[i]), Token))
			return i;
	}

	return -1;
}

static bool INTERNAL_Token_Children_contains(NDTokenInterface_ *DestinateToken, NDToken *Token)
{
	return INTERNAL_Token_Children_indexof(DestinateToken, Token) != -1;
}



#define EVENT_HANDLER_COLLECTION(struct_name, event_name, destinate_type, destinate_param, handler_type, handler_param)\
COLLECTION_FIELDS(struct_name, event_name)\
/* �����б������һ�������� */\
COLLECTION_ADD(struct_name, event_name, destinate_type, destinate_param, handler_type, handler_param, attach)\
/* �Ӻ����б����Ƴ�һ�������� */\
COLLECTION_REMOVE(struct_name, event_name, destinate_type, destinate_param, handler_type, handler_param, remove)

EVENT_HANDLER_COLLECTION(NDTokenInterface_, CreepStarted, NDTokenInterface_, token, EventHandler, handler)
EVENT_HANDLER_COLLECTION(NDTokenInterface_, CreepFetched, NDTokenInterface_, token, EventHandler, handler)
EVENT_HANDLER_COLLECTION(NDTokenInterface_, CreepFinished, NDTokenInterface_, token, EventHandler, handler)
EVENT_HANDLER_COLLECTION(NDTokenInterface_, CreepErrored, NDTokenInterface_, token, EventHandler, handler)

#define EVENT_INVOKE_FUNC(struct_name, event_name, destinate_type, destinate_param)\
static void INTERNAL_##struct_name##_On##event_name##(destinate_type *destinate_param, void *sender, void *args)\
{\
	if (destinate_param == NULL) return;\
\
	for (int i = 0; i < INTERNAL_##struct_name##_##event_name##_count; i++)\
	{\
		destinate_param->##event_name##[i](sender, args);\
	}\
}

EVENT_INVOKE_FUNC(NDTokenInterface_, CreepStarted, NDTokenInterface_, token)
EVENT_INVOKE_FUNC(NDTokenInterface_, CreepFetched, NDTokenInterface_, token)
EVENT_INVOKE_FUNC(NDTokenInterface_, CreepFinished, NDTokenInterface_, token)
EVENT_INVOKE_FUNC(NDTokenInterface_, CreepErrored, NDTokenInterface_, token)

static void i()
{
#ifndef __cplusplus
	NDToken token = {};
	NDToken *p_token = &token;
	(*p_token)->Uri = LPCTSTR("");
	INTERNAL_NDTokenInterface__CreepErrored_attach((NDTokenInterface_*)&token, (EventHandler)NULL);
#endif
}


#ifdef __cplusplus
EXTERN_C
{
#endif
typedef HANDLE HNDTOKEN;

NOVELDOWNLOADERPLUGINCOREWIN32_API HNDTOKEN NDToken_Parent(HNDTOKEN);
NOVELDOWNLOADERPLUGINCOREWIN32_API HNDTOKEN *NDToken_Children(HNDTOKEN);
NOVELDOWNLOADERPLUGINCOREWIN32_API LPCTSTR NDToken_Type(HNDTOKEN);
NOVELDOWNLOADERPLUGINCOREWIN32_API LPCTSTR NDToken_Title(HNDTOKEN);
NOVELDOWNLOADERPLUGINCOREWIN32_API LPCTSTR NDToken_Description(HNDTOKEN);
NOVELDOWNLOADERPLUGINCOREWIN32_API LPCTSTR NDToken_Uri(HNDTOKEN);
NOVELDOWNLOADERPLUGINCOREWIN32_API EventHandler *NDToken_CreepStarted(HNDTOKEN);
NOVELDOWNLOADERPLUGINCOREWIN32_API EventHandler *NDToken_CreepFetched(HNDTOKEN);
NOVELDOWNLOADERPLUGINCOREWIN32_API EventHandler *NDToken_CreepFinished(HNDTOKEN);
NOVELDOWNLOADERPLUGINCOREWIN32_API EventHandler *NDToken_CreepErrored(HNDTOKEN);

NOVELDOWNLOADERPLUGINCOREWIN32_API bool NDToken_CanStartCreep(HNDTOKEN);
NOVELDOWNLOADERPLUGINCOREWIN32_API void NDToken_StartCreep(HNDTOKEN);
//NOVELDOWNLOADERPLUGINCOREWIN32_API void NDToken_StartCreepInternal(HNDTOKEN);
NOVELDOWNLOADERPLUGINCOREWIN32_API bool NDToken_CanCreep(HNDTOKEN, void*);
NOVELDOWNLOADERPLUGINCOREWIN32_API void NDToken_Creep(HNDTOKEN, void*);
//NOVELDOWNLOADERPLUGINCOREWIN32_API bool NDToken_CreepInternal(HNDTOKEN);
NOVELDOWNLOADERPLUGINCOREWIN32_API void NDToken_OnCreepStarted(HNDTOKEN, void*, void*);
NOVELDOWNLOADERPLUGINCOREWIN32_API void NDToken_OnCreepFetched(HNDTOKEN, void*, void*);
NOVELDOWNLOADERPLUGINCOREWIN32_API void NDToken_OnCreepFinished(HNDTOKEN, void*, void*);
NOVELDOWNLOADERPLUGINCOREWIN32_API void NDToken_OnCreepErrored(HNDTOKEN, void*, void*);
#ifdef __cplusplus
}
#endif

#endif