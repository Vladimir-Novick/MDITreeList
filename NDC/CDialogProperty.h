#pragma once

#include "StdAfx.h"
#include "CSerializable.h"
#include "Property.h"

#include <string>

#include <windows.h>
#include <sstream>



using namespace std;




class CDialogProperty :public CSerializable
{

  public:
	  StringProperty *ColorBackgrownd;

	  CDialogProperty();

	  string operator[] (const string& name);

	  virtual ~CDialogProperty();

	

};

