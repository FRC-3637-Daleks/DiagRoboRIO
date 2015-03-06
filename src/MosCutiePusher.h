/*
 * MosCutiePusher.h
 *
 *  Created on: Feb 27, 2015
 *      Author: Edward
 */

#ifndef SRC_MOSCUTIEPUSHER_H_
#define SRC_MOSCUTIEPUSHER_H_

#include "DashboardPusher.h"

namespace DRR
{

using std::weak_ptr;

class MosCutiePusher: public DashboardPusher
{
public:
	static const shared_ptr<MosCutiePusher> Create(const MILLISECONDS p)
	{
		return shared_ptr<MosCutiePusher>(new MosCutiePusher(p));
	}

protected:
	MosCutiePusher(const MILLISECONDS p): DashboardPusher(p) {};
	MosCutiePusher(MosCutiePusher&& other): DashboardPusher(std::move(other)) {};

public:
	virtual ~MosCutiePusher() {};

private:
	virtual void DoPublish(const Frame::KEY_t& key, const string& value, const int data)
	{
		MosCutie::Publish(key, value, data > 0? true:false);
	}

};

}



#endif /* SRC_MOSCUTIEPUSHER_H_ */
