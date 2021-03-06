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
#include <vector>

#include "mosquitto/mosquittopp.h"
#include "MosCutieListener.h"
#include "Verifier.h"
#include "Defaults.h"
#include "TextLogObject.h"

namespace DRR
{

using std::string;
using std::unique_ptr;
using std::unordered_map;
using std::vector;


/** Static mosquittopp wrapper which uses threaded mosquitto functions and maintains a map of get values
 */
class MosCutie: public mosqpp::mosquittopp, private TextLogObject<MosCutie>
{
public:
	friend MosCutieListener;

private:
	struct VerifiedValue
	{
		string value;
		Verifier verify;
		VerifiedValue() {};
		VerifiedValue(const string& val, const Verifier& ver): value(val), verify(ver) {};
		VerifiedValue(const string& val): value(val) {};
		VerifiedValue(const VerifiedValue& other): value(other.value), verify(other.verify) {};
		VerifiedValue(VerifiedValue &&other): value(other.value), verify(other.verify) {};
		operator string&() {return value;};
	};

private:
	static unique_ptr<MosCutie> instance;
	static MosCutie& GetInstance();

	static int initPeriod;
	static const char * initHost;
	static bool init;

public:
	static const int Publish(const string &topic, const string &value, const bool retain=false);	///< Publishes value to topic
	static const int Subscribe(const string &topic);	///< Subscribes to topic
	static const string Get(const string& topic, const bool sub=false);		///< If not subscribed and sub is true, subscribes to topic, and gets current value in topic
	static const bool Has(const string& topic);	///< Returns if it has subscribed or received a message for that value

private:
	static void AddListener(MosCutieListener * const listen);
	static void RemoveListener(MosCutieListener * const listen);
	static const string ConvertTopic(const string& top);
	static const string StripTopic(const string& top);

public:
	static const bool AddVerifier(const string& topic, const Verifier& ver);
	template<typename T>
	static const bool AddVerifier(const string& topic, const std::function<const bool(const T&)> &fn)
	{
		return AddVerifier(topic, Verifier(fn));
	}

public:
	static void Init(const int period, const char * host);
	static void InitHost(const char *host) {Init(initPeriod, host);};
	static void InitPeriod(const int period) {Init(period, initHost);};

private:
	static unordered_map<string, VerifiedValue> subscriptions;
	static vector<MosCutieListener *> listeners;

private:
	MosCutie(const char * const host=DEFAULT_MQTT_HOST, const int timeout=DEFAULT_MQTT_PERIOD);

public:
	virtual ~MosCutie() {};

private:
	void on_connect(int rc) override;
	void on_disconnect(int rc) override;
	void on_publish(int mid) override;
	void on_message(const struct mosquitto_message *message) override;
	void on_subscribe(int mid, int qos_count, const int *granted_qos) override;
	void on_unsubscribe(int mid) override;

};

}

#endif /* SRC_MOSCUTIE_H_ */
