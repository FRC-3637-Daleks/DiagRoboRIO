/*
 * TextLogMQTT.h
 *
 *  Created on: Mar 8, 2015
 *      Author: edward
 */

#ifndef SRC_TEXTLOGMQTT_H_
#define SRC_TEXTLOGMQTT_H_

#include "TextLog.h"
#include "MosCutie.h"

namespace DRR
{

class TextLogMQTT: public TextLog
{
public:
	static const shared_ptr<TextLogMQTT> Create(const string &top)
	{
		return shared_ptr<TextLogMQTT>(new TextLogMQTT(top));
	}

private:
	const string topic;

protected:
	TextLogMQTT(const string &top): topic(top) {};

protected:
	virtual const int LogInternal(const string& message) {return MosCutie::Publish(topic, message, false);};
};



}



#endif /* SRC_TEXTLOGMQTT_H_ */
