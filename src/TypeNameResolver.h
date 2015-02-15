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
const string demangleType(const string typeName)
{
	auto c = typeName.begin();
	for(; c != typeName.end() && !((*c <= 'Z' && *c >= 'A') || (*c <= 'z' && *c >= 'a') || *c == '_'); c++); // c++! :o
	return string(c, typeName.end());
}
#endif

/// The name of type T can be found at `NameOf<T>::name`.
template<typename T>
struct NameOf
{
	static const string name() {static string n(demangleType(typeid(T).name())); return n;};
};

#define PRIMITIVE_NAME_MACRO(T) template<> struct NameOf<T> { static const string name() {static string n(#T); return n;}; };

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


}


#endif /* SRC_TYPENAMERESOLVER_H_ */
