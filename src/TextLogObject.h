/*
 * TextLogObject.h
 *
 *  Created on: Mar 27, 2015
 *      Author: Edward
 */

#ifndef SRC_TEXTLOGOBJECT_H_
#define SRC_TEXTLOGOBJECT_H_

#include "LogObjectBase.h"
#include "TextLog.h"

namespace DRR
{

template<class SERVICE>
class TextLogObject: public LogObjectBase<SERVICE>
{
protected:
	TextLogObject(): LogObjectBase<SERVICE>(nullptr) {};
	TextLogObject(const string& instName): LogObjectBase<SERVICE>(instName) {};

public:
	TextLogObject(SERVICE * const obj): LogObjectBase<SERVICE>(obj) {};
	TextLogObject(SERVICE * const obj, const string& instName): LogObjectBase<SERVICE>(obj, instName) {};
	TextLogObject(TextLogObject &&other): LogObjectBase<SERVICE>(std::move(other)) {};

public:
	virtual ~TextLogObject() {};

public:
	const int LogText(const string& message, const LEVEL_t &level=LEVEL_t::INFO)
	{
		return TextLog::Log(this->GetName(), this->GetInstanceName(), message, level);
	}

	StreamHandle LogText(const LEVEL_t &level=LEVEL_t::INFO)
	{
		return TextLog::Log(this->GetName(), this->GetInstanceName(), level);
	}

};

}



#endif /* SRC_TEXTLOGOBJECT_H_ */
