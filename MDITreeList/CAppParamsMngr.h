#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include<map>


using namespace std;
class CAppParamsMngr
{
private:
	CString filePathAndName;
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
private:
	CAppParamsMngr::Operation currentOperationType;

};

