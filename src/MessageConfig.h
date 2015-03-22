/*
 * MessageConfig.h
 *
 *  Created on: Mar 21, 2015
 *      Author: 3637-DS-1
 */

#ifndef SRC_MESSAGECONFIG_H_
#define SRC_MESSAGECONFIG_H_

#include "ConfigFile.h"
#include "MosCutieListener.h"
#include "LogObject.h"

namespace DRR
{

class MessageConfig: public MosCutieListener, public ConfigFile, private LogObject<MessageConfig>
{
public:
	static const string SaveCommandTopic() {static const string str("__save__"); return str;};
	static const string RevertCommandTopic() {static const string str("__revert__"); return str;};

public:
	MessageConfig(const string &file);
	MessageConfig(MessageConfig &&other): MosCutieListener(other), ConfigFile(std::move(other)) {};

public:
	virtual ~MessageConfig() {};

public:
	virtual void SetValue(const string &key, const string& value) override;
	virtual const int Message(const string &topic, const string& value) override;
};





}



#endif /* SRC_MESSAGECONFIG_H_ */
