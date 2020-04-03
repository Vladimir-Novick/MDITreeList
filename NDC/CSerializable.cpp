#include "StdAfx.h"
#include "CSerializable.h"
#include "Property.h"
#include <string>
#include <regex>

list<string> CSerializable::GetProperties() {
	list<string> ret;
	for (auto it = m_Values.begin(); it != m_Values.end(); ++it) {
		ret.push_back(it->first);
	}
	return ret;
}

void* CSerializable::GetProperty(const string& name) {
	auto it = m_Values.find(name);
	if (it != m_Values.end()) {
		return (it->second);
	}
	string err = "Invalid argument" + name;
	throw new exception(err.c_str());
}

string CSerializable::ToXml() {

	stringstream stringBuilder;
	stringBuilder << "<" << m_classNane << ">\n";
	for (auto it = m_Values.begin(); it != m_Values.end(); ++it) {
		stringBuilder << "<" << it->first << ">";
		stringBuilder << static_cast<StringProperty*>(it->second)->value;
		stringBuilder << "</" << it->first << ">\n";
	}
	stringBuilder << "</" << m_classNane << ">\n";
	return stringBuilder.str();
}

void CSerializable::Parse(const string& xml) {
	stringstream stringBuilder;
	stringBuilder << "<" << m_classNane << ">";
	stringBuilder << "(.*)";
	stringBuilder << "</" << m_classNane << ">";
	regex e(stringBuilder.str());
	stringBuilder.str("");
	smatch m,m1;
	if (regex_search(xml, m, e, regex_constants::match_any)) {
		auto group = m[1].str();
		regex em("<([a-z,A-z,0-9,_]+)[ ]*([^>]*)>([^<]+)</[^>]*>");
		while (regex_search(group, m1, em, regex_constants::match_any)) {
			string v = m1[1].str();
			auto it = m_Values.find(v);
			if (it != m_Values.end()) {
				static_cast<StringProperty*>(it->second)->value = m1[3].str();
			}
			group = m1.suffix().str();
		}
	}
}
