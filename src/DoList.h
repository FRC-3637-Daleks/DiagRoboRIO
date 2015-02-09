/*
 * PollList.h
 *
 *  Created on: Feb 9, 2015
 *      Author: edward
 */

#ifndef SRC_DOLIST_H_
#define SRC_DOLIST_H_

#include <vector>
#include <memory>
#include "PushPullBase.h"

namespace DRR
{

using std::vector;
using std::shared_ptr;

class DoList: virtual public PushPullBase, protected vector<shared_ptr<PushPullBase>>
{
public:
	typedef vector<shared_ptr<PushPullBase>> LIST_TYPE;

private:
	int iteration;	/// Changes while it iterates through the list, -1 when it is not currently iterating through the list

public:
	DoList(): iteration(-1) {};
	DoList(const LIST_TYPE& other): vector<shared_ptr<PushPullBase>>(other), iteration(-1) {};
	DoList(const DoList& other): vector<shared_ptr<PushPullBase>>(other), iteration(other.iteration + (other.iteration == -1? 0:1)) {};
	virtual ~DoList() {};

public:
	const int GetIteration() const {return iteration;};

public:
	/// Iterates through every object in list and calls it's `Do`
	virtual const int DoAll();
	virtual const int Do() override final {return DoAll();};

	/// Allows access to const public members of vector
	const LIST_TYPE * const operator->() const {return this;};
	const LIST_TYPE &get() const {return *this;};
};

}



#endif /* SRC_DOLIST_H_ */
