#include "stdafx.h"
#include "CAppParamsMngr.h"
#include <regex>

using namespace std;

CAppParamsMngr::CAppParamsMngr(CString fileParam, CAppParamsMngr::Operation type)
{
	currentOperationType = type;
	WCHAR    directory[512];
	GetCurrentDirectory(512, directory);
	StorageFileName = directory;
	StorageFileName  += "\\" + fileParam + ".ini";
}

CAppParamsMngr::~CAppParamsMngr()
{
	
}


CString CAppParamsMngr::GetAppParameter(CString paramName, CString group_name, CString defaultValue)
{

	WCHAR    prms[1000];
	GetPrivateProfileString(group_name, paramName, L"", prms, 999, StorageFileName);
	if (prms[0] == '\0')
		return defaultValue;

	return prms;
}

void CAppParamsMngr::SetAppParameter(CString Name, CString Section, CString Value)
{
	WritePrivateProfileString(Section, Name, Value, StorageFileName);
}


int CAppParamsMngr::GetAppParameterInt(CString Name, CString Section, int DefaultValue) {
	WCHAR prms[1000];
	GetPrivateProfileString(Section, Name, L"", prms, 999, StorageFileName);
	if (prms[0] == '\0')
		return DefaultValue;
	int ret;

	ret = _wtoi(prms);

	return ret;
}
void CAppParamsMngr::SetAppParameterInt(CString Name, CString Section, int Value) {
	CString strValue;
	strValue.Format(L"%d", Value);
	WritePrivateProfileString(Section, Name, strValue, StorageFileName);
}