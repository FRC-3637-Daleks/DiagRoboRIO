/*
 * LogObjectBase.h
 *
 *  Created on: Mar 26, 2015
 *      Author: Edward
 */

#ifndef SRC_LOGOBJECTBASE_H_
#define SRC_LOGOBJECTBASE_H_

#include <string>

#include "DatumValue.h"


namespace DRR
{

using std::string;

/** Base class for LogObject hierarchy.
 * Manages each class's
 */
template<class SERVICE>
class LogObjectBase
{
private:
	static const string name;
	static int N;

public:
	static const int GetTotal()
	{
		return N;
	}

	static const string& GetName()
	{
		return name;
	}

private:
	SERVICE *self;
	string instance;

protected:
	LogObjectBase(): LogObjectBase(nullptr) {}; // nullptr Signifies that child class derives the object
	LogObjectBase(const string& instName): LogObjectBase(nullptr, instName) {};

public:
	LogObjectBase(SERVICE * const obj): LogObjectBase(obj, DatumValue<int>(N).toString()) {};
	LogObjectBase(SERVICE * const obj, const string& instName): self(obj), instance(instName) {N++;};

public:
	virtual ~LogObjectBase() {N--;};

public:
	SERVICE * const GetSelf()
	{
		if(self == nullptr)
			self = dynamic_cast<SERVICE*>(this);
		return self;
	}

	const string GetInstanceName() const
	{
		return instance;
	}
};

template<class SERVICE> const string LogObjectBase<SERVICE>::name(NameOf<SERVICE>());
template<class SERVICE> int LogObjectBase<SERVICE>::N = 0;

}



#endif /* SRC_LOGOBJECTBASE_H_ */
