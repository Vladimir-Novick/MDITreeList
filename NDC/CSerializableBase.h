#pragma once
#include <string>
#include<map>

using namespace std;

class CSerializableBase {
public:
	map<string, void*> m_Values;
};
