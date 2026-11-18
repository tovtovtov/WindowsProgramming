// header.h: 표준 시스템 포함 파일
// 또는 프로젝트 특정 포함 파일이 들어 있는 포함 파일입니다.
//

#pragma once

#include "targetver.h"
#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.
// Windows 헤더 파일
#include <windows.h>
// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

#include <string>
#include <memory>

#ifdef _UNICODE
typedef std::wstring tstring;
#else
typedef std::string tstring;
#endif

//
//template<typename ... Args>
//tstring string_format(const tstring& format, Args ... args)
//{
//	size_t size = snprintf(nullptr, 0, format.c_str(), args ...) + 1; // Extra space for '\0'
//	if (size <= 0) { throw std::runtime_error("Error during formatting."); }
//	std::unique_ptr<char[]> buf(new char[size]);
//
//#ifdef _UNICODE
//	snprintf(buf.get(), size, format.c_str(), args ...);
//#else
//	snprintf(buf.get(), size, format.c_str(), args ...);
//#endif
//
//	return std::string(buf.get(), buf.get() + size - 1); // We don't want the '\0' inside
//}