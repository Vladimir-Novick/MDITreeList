#pragma once

#include "StdAfx.h"
#include <string>
#include "CSerializableBase.h"

using namespace std;

#define StringProperty Property<string>

    /// <summary>
    ///   Property definition 
    /// </summary>
    template <typename T>
    class Property 
    {
    private:
        string name_; 
      
    public:
        Property(void *baseClass, const string& name) {
          ((CSerializableBase*)(baseClass))->m_Values[name] = this;
            name_ = name;
        }
         T value;
        std::string name() const { return name_; }

        StringProperty& operator=(const T& value_) {
            value = value_;
            return *this;
        }

        T& operator=(const Property<T>& value_) {
            return *this;
        }
    };




