/*
 * TypeNameResolver.h
 *
 *  Created on: Feb 9, 2015
 *      Author: edward
 */

#ifndef SRC_TYPENAMERESOLVER_H_
#define SRC_TYPENAMERESOLVER_H_

#include <string>

namespace DRR
{

using std::string;

#ifndef DEMANGLER
#define DEMANGLER

/// Removes numbers before typenames, if any. FRC compilers found to mangle class names with numerals preceding source class name
inline const string demangleType(const string typeName)
{
	auto c = typeName.begin();
	for(; c != typeName.end() && !((*c <= 'Z' && *c >= 'A') || (*c <= 'z' && *c >= 'a') || *c == '_'); c++); // c++! :o
	return string(c, typeName.end());
}
#endif

/// The name of type T can be found at `NameOf<T>()`.
template<typename T>
inline const string NameOf()
{
	static string n(demangleType(typeid(T).name()));
	return n;
}

template<typename T>
inline const T DefaultValue()
{
	static T val(0.0);
	return val;
}

#define PRIMITIVE_NAME_MACRO(T) template<> inline const string NameOf<T>() {static string n(#T); return n;}
#define DEFAULT_VALUE_MACRO(T, def) template<> inline const T DefaultValue<T>() {static T val(def); return val;}

PRIMITIVE_NAME_MACRO(bool);
PRIMITIVE_NAME_MACRO(char);
PRIMITIVE_NAME_MACRO(short);
PRIMITIVE_NAME_MACRO(long);
PRIMITIVE_NAME_MACRO(long long);
PRIMITIVE_NAME_MACRO(unsigned char);
PRIMITIVE_NAME_MACRO(unsigned short);
PRIMITIVE_NAME_MACRO(unsigned long);
PRIMITIVE_NAME_MACRO(unsigned long long);
PRIMITIVE_NAME_MACRO(float);
PRIMITIVE_NAME_MACRO(double);

DEFAULT_VALUE_MACRO(std::string, " ");


}


#endif /* SRC_TYPENAMERESOLVER_H_ */
