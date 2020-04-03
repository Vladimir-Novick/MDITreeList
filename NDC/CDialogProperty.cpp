#include "StdAfx.h"
#include "CDialogProperty.h"


CDialogProperty::CDialogProperty():CSerializable("DialogProperty") {
	ColorBackgrownd = new StringProperty(static_cast<CSerializable*>(this), "ColorBackgrownd");
}

string CDialogProperty::operator[] (const string& name) {
	auto dat = this->GetProperty(name);
	string ret = static_cast<StringProperty*>(dat)->value;
	return ret;
}

CDialogProperty::~CDialogProperty() {
	delete ColorBackgrownd;
}
