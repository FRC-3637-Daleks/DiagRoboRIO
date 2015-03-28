/*
 * TypeNameResolver.cpp
 *
 *  Created on: Mar 28, 2015
 *      Author: 3637-DS-1
 */

#include <cxxabi.h>
#include <memory>
#include "TypeNameResolver.h"

namespace DRR
{


const string demangleType(const string typeName)
{
	int status = -4;
	std::unique_ptr<char, void(*)(void *)> res
	{
		abi::__cxa_demangle(typeName.c_str(), NULL, NULL, &status),
		std::free
	};

	return (status == 0)? res.get() : typeName;
}



}
