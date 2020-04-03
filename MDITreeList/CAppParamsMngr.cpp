#include "stdafx.h"
#include "CAppParamsMngr.h"
#include <regex>

using namespace std;

CAppParamsMngr::CAppParamsMngr(string fileParam, CAppParamsMngr::Operation type)
{
	currentOperationType = type;
	filePathAndName = string(fileParam.c_str());
	filePathAndName = filePathAndName.append(".xml");
	if (type == CAppParamsMngr::Operation::READ) {
		struct stat buffer;
		bool isexit = (stat(filePathAndName.c_str(), &buffer) == 0);
		if (isexit) {
			string line;
			ifstream myfile(filePathAndName);
			if (myfile.is_open())
			{
				stringstream ss;
				while (getline(myfile, line))
				{
					ss << line << '\n';
				}
				myfile.close();
				paramsData = ss.str();

				smatch m, m1;
				auto group = paramsData;
				regex em("<([a-z,A-z,0-9,_]+)[ ]*([^>]*)>([^<]+)</[^>]*>");
				while (regex_search(group, m1, em, regex_constants::match_any)) {
					string v = m1[1].str();
					m_Values[v] = m1[3].str();
					group = m1.suffix().str();
				}
			}

		}

	}

}

CAppParamsMngr::~CAppParamsMngr()
{
	if (currentOperationType == Operation::WRITE) {
		ofstream myfile(filePathAndName);

		if (myfile.is_open())
		{
			for (auto it = m_Values.begin(); it != m_Values.end(); ++it) {
				myfile << "<" << it->first << ">";
				myfile << it->second;
				myfile << "</" << it->first << ">\n";
			}
			myfile.close();
		}
	}
}


CString CAppParamsMngr::GetAppParameter(string paramName, string group_name, CString defaultValue)
{
	CString retValue = defaultValue;
	auto it = m_Values.find(paramName);
	if (it != m_Values.end()) {
		return CString((it->second.c_str()));
	}
	return retValue;
}

void CAppParamsMngr::SetAppParameter(string paramName, string group_name, CString newValue)
{
	USES_CONVERSION;

	std::string s = W2A(newValue);

	auto it = m_Values.find(paramName);
	if (it != m_Values.end()) {
		it->second = s;
	}


	m_Values[paramName] = s;
}
