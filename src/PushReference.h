/*
 * PushReference.h
 *
 *  Created on: Feb 9, 2015
 *      Author: edward
 */

#ifndef SRC_PUSHREFERENCE_H_
#define SRC_PUSHREFERENCE_H_

#include <functional>
#include <mutex>
#include <memory>

#include "DatumValue.h"
#include "PollValue.h"
#include "PushValue.h"

namespace DRR
{
using std::shared_ptr;
using std::weak_ptr;

template<typename T>
class PushReference: public PushValue<T>
{
public:
	typedef typename PushValue<T>::FUNC_t FUNC_t;

public:
	static const shared_ptr<PushReference<T> > Create(const T* val, const FUNC_t& fn)
	{
		return std::shared_ptr<PushReference<T> >(new PushReference<T>(val, fn));
	}

	static const shared_ptr<PushReference<T> > Create(const T* val, const DatumValue<T> datum)
	{
		return std::shared_ptr<PushReference<T> >(new PushReference<T>(val, datum));
	}

	static const shared_ptr<PushReference<T> > Create(const weak_ptr<PollValue<T>> obj, const FUNC_t fn)
	{
		return std::shared_ptr<PushReference<T> >(new PushReference(obj, fn));
	}

	static const shared_ptr<PushReference<T> > Create(const weak_ptr<PollValue<T>> obj, const DatumValue<T> datum)
	{
		return std::shared_ptr<PushReference<T> >(new PushReference(obj, datum));
	}

private:
	const T *ref;	///< Pointer to data which is to be pushed
	weak_ptr<PollValue<T> > refObj;	///< Weak pointer to the referring object

protected:
	PushReference(const T *val, const FUNC_t fn): PushValue<T>(fn), ref(val), refObj() {};
	PushReference(const T *val, const DatumValue<T> datum): PushReference(val, datum.GetPushFunctor()) {};
	PushReference(const weak_ptr<PollValue<T> > obj, const FUNC_t fn): PushValue<T>(fn), ref(&obj.lock()->getPrevious()), refObj(obj) {};
	PushReference(const weak_ptr<PollValue<T>> obj, const DatumValue<T> datum): PushReference(obj, datum.GetPushFunctor()) {};
	PushReference(const PushReference& other)=delete;

public:
	virtual ~PushReference() {};

public:
	virtual const int Push() override
	{
		if( ref == NULL)	// Invalid states
			return -1;

		return PushValue<T>::Push();
	}

	virtual const T GetValue() override
	{
		return *ref;
	}

};


}



#endif /* SRC_PUSHREFERENCE_H_ */
