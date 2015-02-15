/*
 * DatumValue.h
 *
 *  Created on: Feb 9, 2015
 *      Author: edward
 */

#ifndef SRC_DATUMVALUE_H_
#define SRC_DATUMVALUE_H_

#include "PushValue.h"
#include <sstream>
#include "TypeNameResolver.h"
#include "Datum.h"

namespace DRR
{


template<typename T>
class DatumValue: public Datum
{
private:
	T value;
public:
	DatumValue(const T& init): value(init) {};
	DatumValue(const DatumValue& other): value(other.value) {};

public:
	void Set(const T& v) {value = v;};
	const T Get() const {return value;};
	const typename PushValue<T>::FUNC_t GetPushFunctor()
	{
		return std::bind(DatumValue<T>::Set, this, std::placeholders::_1);
	}

	virtual const string toString() const override
	{
		std::stringstream ss;
		ss<<value;
		return ss.str();
	}

	virtual const unsigned int fill(const void * *memPtr) const override
	{
		memPtr = &value;
		return sizeof(T);
	}

	virtual const string getType() const
	{
		return NameOf<T>::name;
	}

};


}



#endif /* SRC_DATUMVALUE_H_ */
