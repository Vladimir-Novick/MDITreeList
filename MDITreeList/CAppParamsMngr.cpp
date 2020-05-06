#include "stdafx.h"
#include "CAppParamsMngr.h"
#include <regex>

using namespace std;

CAppParamsMngr::CAppParamsMngr(CString fileParam, CAppParamsMngr::Operation type)
{
	currentOperationType = type;
	WCHAR    directory[512];
	GetCurrentDirectory(512, directory);
	filePathAndName = directory;
	filePathAndName  += "\\" + fileParam + ".ini";
}

CAppParamsMngr::~CAppParamsMngr()
{
	
}


CString CAppParamsMngr::GetAppParameter(CString paramName, CString group_name, CString defaultValue)
{

	WCHAR    prms[1000];
	GetPrivateProfileString(group_name, paramName, L"", prms, 999, filePathAndName);
	if (prms[0] == '\0')
		return defaultValue;

	return prms;
}

void CAppParamsMngr::SetAppParameter(CString Name, CString Section, CString Value)
{
	WritePrivateProfileString(Section, Name, Value, filePathAndName);
}
