#pragma once

// ���� ifdef ���Ǵ���ʹ�� DLL �������򵥵�
// ��ı�׼�������� DLL �е������ļ��������������϶���� NOVELDOWNLOADERPLUGINCOREWIN32EXPORTS
// ���ű���ġ���ʹ�ô� DLL ��
// �κ�������Ŀ�ϲ�Ӧ����˷��š�������Դ�ļ��а������ļ����κ�������Ŀ���Ὣ
// NOVELDOWNLOADERPLUGINCOREWIN32EXPORTS ������Ϊ�Ǵ� DLL ����ģ����� DLL ���ô˺궨���
// ������Ϊ�Ǳ������ġ�
#ifdef NOVELDOWNLOADERPLUGINCOREWIN32_EXPORTS
#define NOVELDOWNLOADERPLUGINCOREWIN32_API __declspec(dllexport)
#else
#define NOVELDOWNLOADERPLUGINCOREWIN32_API __declspec(dllimport)
#endif
