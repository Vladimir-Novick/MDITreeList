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
	string paramsData;
	string filePathAndName;
	stringstream stringBuilder;
	map<string, string> m_Values;
public:
	enum Operation {
		READ,
		WRITE
	};
	CAppParamsMngr(string fileParam, Operation type);
	virtual ~CAppParamsMngr();

	CString GetAppParameter(string paramName, string group_name,
		CString defaultValue);

	void SetAppParameter(string paramName, string group_name,
		CString newValue);
private:
	CAppParamsMngr::Operation currentOperationType;

};

