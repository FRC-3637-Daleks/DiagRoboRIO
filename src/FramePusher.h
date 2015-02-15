/*
 * FramePusher.h
 *
 *  Created on: Feb 15, 2015
 *      Author: Edward
 */

#ifndef SRC_FRAMEPUSHER_H_
#define SRC_FRAMEPUSHER_H_

#include "ThreadList.h"
#include "Frame.h"

namespace DRR
{

class FramePusher: public Pusher, public ThreadList
{
private:
	Frame currentFrame;

protected:
	FramePusher(const MILLISECONDS p): ThreadList(p) {};
	FramePusher(FramePusher&& other): ThreadList(std::move(other)), currentFrame(other.currentFrame) {};

public:
	virtual ~FramePusher();

public:
	const int Add(const Frame::KEY_t &key, const Frame::DATA_t& d);

public:
	const Frame GetCurrentFrame() const {return currentFrame;};

public:
	virtual const int Do() override;

protected:
	Frame& CurrentFrame() {return currentFrame;};
};



}



#endif /* SRC_FRAMEPUSHER_H_ */
