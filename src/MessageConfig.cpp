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
	LogText()<<"Created MessageConfig for "<<file;
	Publish(SaveCommandTopic(), "0", true);
	Publish(RevertCommandTopic(), "0", true);
	Publish(SetCommandTopic(), "0", true);
	Reload();
	LogText()<<"Constructor Complete";
}

void MessageConfig::SetValue(const string &key, const string &value)
{
	LogText()<<"Publishing \""<<key<<"\" = \""<<value<<"\"";
	setValue(key, value);
	Publish(key, value, true);
}

void MessageConfig::RemoveValue(const string &key)
{
	if(!HasValue(key))
	{
		LogText()<<"Cannot remove \""<<key<<"\" because it does not exist";
	}
	else
	{
		LogText()<<"Removing \""<<key<<"\" from global table";
		removeValue(key);
		Publish(key, "", true);
	}
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
	else if(topic == SetCommandTopic())
	{
		if(value == "0")
			return 0;

		LogText()<<"Received request: "<<value;

		auto split = value.find(' ');
		if(split != value.npos)
		{
			string setTopic(value, 0, split);
			string setValue(value, split+1);

			if(!HasValue(setTopic))
				LogText(LEVEL_t::NOTICE)<<"Adding \""<<setTopic<<"\"";
			LogText()<<"Setting \""<<setTopic<<"\" to \""<<setValue<<"\"";
			SetValue(setTopic, setValue);
		}
		else if(split == value.npos)
		{
			string removeTopic(value);
			LogText()<<"Removing \""<<removeTopic<<"\"";
			RemoveValue(removeTopic);
		}

		Publish(SetCommandTopic(), "0", true);
	}
	else if(value != GetValue(topic))
	{
		LogText(LEVEL_t::ALERT)<<"Please use the \""<<SetCommandTopic()<<"\" topic to change values: ";
		LogText(LEVEL_t::ALERT)<<"To do so set the topic \""<<(GetPath()+SetCommandTopic())<<"\" to \""<<topic<<" "<<value<<"\"";
		Publish(topic, GetValue(topic), true);
	}

	return ret;
}

}
