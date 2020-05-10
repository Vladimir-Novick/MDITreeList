#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include<map>


using namespace std;


#define DllExport   __declspec( dllexport )

class DllExport CAppParamsMngr
{
private:
	CString StorageFileName;
	stringstream stringBuilder;
	map<string, string> m_Values;
public:
	enum Operation {
		READ,
		WRITE
	};
	CAppParamsMngr(CString fileParam, Operation type);
	virtual ~CAppParamsMngr();

	CString GetAppParameter(CString paramName, CString group_name,
		CString defaultValue);

	void SetAppParameter(CString paramName, CString group_name,
		CString newValue);


	int GetAppParameterInt(CString Name, CString Section, int DefaultValue);
	void SetAppParameterInt(CString Name, CString Section, int Value);

private:
	CAppParamsMngr::Operation currentOperationType;

};

