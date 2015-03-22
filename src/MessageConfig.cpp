/*
 * MessageConfig.cpp
 *
 *  Created on: Mar 22, 2015
 *      Author: 3637-DS-1
 */

#include "MessageConfig.h"

namespace DRR
{

MessageConfig::MessageConfig(const string &file): MosCutieListener(file), ConfigFile(file)
{
	Publish(SaveCommandTopic(), "0");
	Publish(RevertCommandTopic(), "0");
	LogText()<<"Created MessageConfig for "<<file;
}

void MessageConfig::SetValue(const string &key, const string &value)
{
	LogText()<<"["<<GetFilename()<<"] Setting "<<key<<" to "<<value;
	Publish(key, value);
}

const int MessageConfig::Message(const string &topic, const string &value)
{
	LogText()<<"["<<GetFilename()<<"] Received message \""<<topic<<"\"=\""<<value<<"\"";
	int ret = 0;
	if(topic == SaveCommandTopic())
	{
		if(value == "0")
			return 0;
		if(value == "1")
		{
			ret = Save();	// If the value is 1, it uses the original file
			if(ret < 0)
				LogText(LEVEL_t::ALERT)<<"["<<GetFilename()<<"] Saving to "<<GetFilename()<<" failed";
			else
				LogText()<<"["<<GetFilename()<<"] Saved to "<<GetFilename();
		}
		else
		{
			ret = Save(value);	// Otherwise it assumes the value is the filename it wants it saved to
			if(ret < 0)
				LogText(LEVEL_t::ALERT)<<"["<<GetFilename()<<"] Saving to "<<value<<" failed";
			else
				LogText()<<"["<<GetFilename()<<"] Saved to "<<value;
		}


		Publish(SaveCommandTopic(), "0");
	}
	else if(topic == RevertCommandTopic())
	{
		if(value == "0")
			return 0;
		if(value == "1")
		{
			ret = Reload();	// If the value is 1, it uses the original file
			if(ret < 0)
				LogText(LEVEL_t::ALERT)<<"["<<GetFilename()<<"] Reverting from "<<GetFilename()<<" failed";
			else
				LogText()<<"["<<GetFilename()<<"] Reverted from "<<GetFilename();
		}
		else
		{
			ret = Reload(value);	// Otherwise it assumes the value is the filename it wants it to load from
			if(ret < 0)
				LogText(LEVEL_t::ALERT)<<"["<<GetFilename()<<"] Reverting from "<<value <<" failed";
			else
				LogText()<<"["<<GetFilename()<<"] Reverted from "<<value;
		}

		Publish(RevertCommandTopic(), "0");
	}
	else
	{
		ConfigFile::SetValue(topic, value);
		LogText()<<"["<<GetFilename()<<"] Setting \""<<topic<<"\" to \""<<value<<"\"";
	}

	return ret;
}




}


