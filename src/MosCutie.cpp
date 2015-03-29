/*
 * MosCutie.cpp
 *
 *  Created on: Feb 20, 2015
 *      Author: edward
 */

#include <algorithm>

#include "TextLog.h"

#include "MosCutie.h"


namespace DRR
{
unique_ptr<MosCutie> MosCutie::instance(nullptr);

unordered_map<string, MosCutie::VerifiedValue> MosCutie::subscriptions;
vector<MosCutieListener *> MosCutie::listeners;

int MosCutie::initPeriod(-1);
const char * MosCutie::initHost(NULL);
bool MosCutie::init(false);

MosCutie& MosCutie::GetInstance()
{
	if(!instance)
	{
		mosqpp::lib_init();
		if(init)
			instance.reset(new MosCutie(initHost, initPeriod));
		else
			instance.reset(new MosCutie);
	}

	return *instance;
}

const int MosCutie::Publish(const string &topic, const string& value, const bool retain)
{
	return GetInstance().publish(NULL, ConvertTopic(topic).c_str(), value.size(), value.c_str(), 0, retain);
}

const int MosCutie::Subscribe(const string &topic)
{
	return GetInstance().subscribe(NULL, ConvertTopic(topic).c_str());
}

const bool MosCutie::Has(const string& topic)
{
	return subscriptions.count(topic) != 0;
}

const string MosCutie::Get(const string& topic, const bool sub)
{
	if(!Has(topic) && sub)
	{
		Subscribe(topic);
		return string("");
	}
	else
	{
		return subscriptions.at(ConvertTopic(topic));
	}
}

const bool MosCutie::AddVerifier(const string &topic, const Verifier &ver)
{
	subscriptions[topic].verify = ver;
	return true;
}

void MosCutie::Init(const int period, const char *host)
{
	init = true;
	initPeriod = period;
	initHost = host;
}

void MosCutie::AddListener(MosCutieListener * const listen)
{
	if(listen == NULL)
		return;
	listeners.push_back(listen);
	Subscribe(listen->GetPath()+'#');
}

void MosCutie::RemoveListener(MosCutieListener * const listen)
{
	listeners.erase(std::remove(listeners.begin(), listeners.end(), listen), listeners.end());
}

const string MosCutie::ConvertTopic(const string &top)
{
	return top;
}

const string MosCutie::StripTopic(const string &top)
{
	return top;
	/*
	static const string prefix("roborio/");
	if(top.size() > prefix.size())
	{
		if(top.substr(0, prefix.size()) == prefix)
			return top.substr(prefix.size());
	}
	return "";
	*/
}

MosCutie::MosCutie(const char * const host, const int timeout): mosquittopp()
{
	connect_async(host, 1180);
	loop_start();
}

void MosCutie::on_connect(int rc)
{
	if(rc)
		LogText(LEVEL_t::NOTICE)<<"MQTT Fail on connect";
	else
	{
		LogText(LEVEL_t::NOTICE)<<"MQTT Success on connect";
		for(auto i = subscriptions.begin(); i != subscriptions.end(); i++)
		{
			Publish(i->first, i->second.value);
		}
	}
}

void MosCutie::on_disconnect(int rc)
{
	if(rc)
		LogText(LEVEL_t::NOTICE)<<"MQTT Fail on disconnect";
	else
		LogText(LEVEL_t::NOTICE)<<"MQTT Success on disconnect";
}

void MosCutie::on_message(const mosquitto_message * message)
{
	if(message == NULL)
		return;
	if(message->topic == NULL || message->payload == NULL)
		return;
	string val = string((char *)message->payload, message->payloadlen);
	if(subscriptions[message->topic].verify.Verify(val))
		subscriptions[message->topic].value = val;
	else
	{
		Publish(message->topic, subscriptions[message->topic].value);
		return;
	}
	string top = StripTopic(message->topic);

	for(int i = 0; i < listeners.size(); i++)
	{
		if(listeners[i]->InPath(top))
			listeners[i]->Message(listeners[i]->StripTopic(top), val);
	}
}

void MosCutie::on_publish(int mid)
{
}

void MosCutie::on_subscribe(int mid, int qos_count, const int * granted_qos)
{

}

void MosCutie::on_unsubscribe(int mid)
{

}

}


