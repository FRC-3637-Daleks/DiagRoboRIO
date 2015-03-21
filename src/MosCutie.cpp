/*
 * MosCutie.cpp
 *
 *  Created on: Feb 20, 2015
 *      Author: edward
 */

#include <iostream>
#include "MosCutie.h"

namespace DRR
{
unique_ptr<MosCutie> MosCutie::instance(nullptr);

unordered_map<string, string> MosCutie::subscriptions;

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
	return GetInstance().publish(NULL, (string("roborio/")+topic).c_str(), value.size(), value.c_str(), 0, retain);
}

const int MosCutie::Subscribe(const string &topic)
{
	return GetInstance().subscribe(NULL, topic.c_str());
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
		return subscriptions.at(topic);
	}
}

void MosCutie::Init(const int period, const char *host)
{
	init = true;
	initPeriod = period;
	initHost = host;
}

MosCutie::MosCutie(const char * const host, const int timeout): mosquittopp()
{
	connect_async(host, 1180);
	loop_start();
}

void MosCutie::on_connect(int rc)
{
	if(rc)
		std::cout<<"MQTT Connection Failed"<<std::endl;
	else
		std::cout<<"MQTT Connection Initiated"<<std::endl;
}

void MosCutie::on_disconnect(int rc)
{
	if(rc)
		std::cout<<"MQTT Fail on disconnect"<<std::endl;
	else
		std::cout<<"MQTT Safe disconnect"<<std::endl;
}

void MosCutie::on_message(const mosquitto_message * message)
{
	if(message == NULL)
		return;
	if(message->topic == NULL || message->payload == NULL)
		return;
	subscriptions[message->topic] = string((char *)message->payload, message->payloadlen);
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


