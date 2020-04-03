#pragma once
#include "StdAfx.h"
#include <string>
#include<map>
#include <list>
#include <sstream>
#include "Property.h"
#include "CSerializableBase.h"


using namespace std;


class CSerializable : public CSerializableBase
{
private:
	string m_classNane;
public:
	CSerializable(const string& className):CSerializableBase() {
		m_classNane = className;
	}

public:

	list<string> GetProperties();

	void* GetProperty(const string& name);


	string ToXml();
	void Parse(const string& xml);

};

