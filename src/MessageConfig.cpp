/*
 * MessageConfig.cpp
 *
 *  Created on: Mar 22, 2015
 *      Author: 3637-DS-1
 */

#include "MessageConfig.h"

namespace DRR
{

MessageConfig::MessageConfig(const string &file): LogObject<MessageConfig>(file), MosCutieListener(string("roborio/config/")+file), ConfigFile(file)
{
	Publish(SaveCommandTopic(), "0", true);
	Publish(RevertCommandTopic(), "0", true);
	LogText()<<"Created MessageConfig for "<<file;
	Reload();
}

void MessageConfig::SetValue(const string &key, const string &value)
{
	LogText()<<"Setting "<<key<<" to "<<value;
	ConfigFile::SetValue(key, value);
	Publish(key, value, true);
}

const int MessageConfig::Message(const string &topic, const string &value)
{
	LogText()<<"Received message \""<<topic<<"\"=\""<<value<<"\"";
	int ret = 0;
	if(topic == SaveCommandTopic())
	{
		if(value == "0")
			return 0;
		if(value == "1")
		{
			ret = Save();	// If the value is 1, it uses the original file
			if(ret < 0)
				LogText(LEVEL_t::ALERT)<<"Saving to "<<GetFilename()<<" failed";
			else
				LogText()<<"Saved to "<<GetFilename();
		}
		else
		{
			ret = Save(value);	// Otherwise it assumes the value is the filename it wants it saved to
			if(ret < 0)
				LogText(LEVEL_t::ALERT)<<"Saving to "<<value<<" failed";
			else
				LogText()<<"Saved to "<<value;
		}


		Publish(SaveCommandTopic(), "0", true);
	}
	else if(topic == RevertCommandTopic())
	{
		if(value == "0")
			return 0;

		if(value == "1")
		{
			ret = Reload();	// If the value is 1, it uses the original file
			if(ret < 0)
				LogText(LEVEL_t::ALERT)<<"Reverting from "<<GetFilename()<<" failed";
			else
				LogText()<<"Reverted from "<<GetFilename();
		}
		else
		{
			ret = Reload(value);	// Otherwise it assumes the value is the filename it wants it to load from
			if(ret < 0)
				LogText(LEVEL_t::ALERT)<<"Reverting from "<<value <<" failed";
			else
				LogText()<<"Reverted from "<<value;
		}

		Publish(RevertCommandTopic(), "0", true);
	}
	else if(GetValue(topic) != value)
	{
		ConfigFile::SetValue(topic, value);
		LogText()<<"Setting \""<<topic<<"\" to \""<<value<<"\"";
	}

	return ret;
}

}
