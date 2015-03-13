/*
 * mosquitto.h
 *
 *  Created on: Feb 1, 2015
 *      Author: Edward
 */

#ifndef SRC_MOSCUTIE_H_
#define SRC_MOSCUTIE_H_


#include <string>
#include <memory>
#include <unordered_map>

#include "mosquitto/mosquittopp.h"
#include "Defaults.h"

namespace DRR
{

using std::string;
using std::unique_ptr;
using std::unordered_map;


/** Static mosquittopp wrapper which uses threaded mosquitto functions and maintains a map of get values
 */
class MosCutie: public mosqpp::mosquittopp
{
private:
	static unique_ptr<MosCutie> instance;
	static MosCutie& GetInstance();

	static int initPeriod;
	static const char * initHost;
	static bool init;

public:
	static const int Publish(const string &topic, const string &value, const bool retain=false);	///< Publishes value to roborio/topic
	static const int Subscribe(const string &topic);	///< Subscribes to topic
	static const string Get(const string& topic, const bool sub=false);		///< If not subscribed and sub is true, subscribes to topic, and gets current value in topic
	static const bool Has(const string& topic);	///< Returns if it has subscribed or received a message for that value

public:
	static void Init(const int period, const char * host);
	static void InitHost(const char *host) {Init(initPeriod, host);};
	static void InitPeriod(const int period) {Init(period, initHost);};

private:
	static unordered_map<string, string> subscriptions;

private:
	MosCutie(const char * const host=DEFAULT_MQTT_HOST, const int timeout=DEFAULT_MQTT_PERIOD);

public:
	virtual ~MosCutie() {};

public:
	void on_connect(int rc) override;
	void on_disconnect(int rc) override;
	void on_publish(int mid) override;
	void on_message(const struct mosquitto_message *message) override;
	void on_subscribe(int mid, int qos_count, const int *granted_qos) override;
	void on_unsubscribe(int mid) override;

};

}

#endif /* SRC_MOSCUTIE_H_ */
