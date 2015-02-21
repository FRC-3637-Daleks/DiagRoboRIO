/*
 * LogPreferences.h
 *
 *  Created on: Jan 30, 2015
 *      Author: edward
 */

#ifndef SRC_LOGPREFERENCES_H_
#define SRC_LOGPREFERENCES_H_

#include "Defaults.h"

typedef unsigned int MILLISECONDS;

class LogPreferences
{
public:
	MILLISECONDS log_period;
	MILLISECONDS monitor_period;
	int mqtt_period;
	unsigned int n_buffer_frames;
	const char * mqtt_broker_host;
	const char * log_home_path;
	const char * text_log_filename;

public:
	LogPreferences(const char * tlf=DEFAULT_LOG_TEXT_OUT,
				   const unsigned int nbf=DEFAULT_LOG_BUF_LENGTH,
				   const char * lhp=DEFAULT_LOG_HOME_PATH,
				   const MILLISECONDS mp=DEFAULT_MONITOR_PERIOD,
				   const MILLISECONDS lp=DEFAULT_LOG_PERIOD,
				   const int mqttp=DEFAULT_MQTT_PERIOD,
				   const char * mbh=DEFAULT_MQTT_HOST):
					   log_period(lp), monitor_period(mp), mqtt_period(mqttp),
					   n_buffer_frames(nbf), mqtt_broker_host(mbh), log_home_path(lhp), text_log_filename(tlf) {};

	LogPreferences(const LogPreferences& other): log_period(other.log_period),
												 monitor_period(other.monitor_period),
												 mqtt_period(other.mqtt_period),
												 n_buffer_frames(other.n_buffer_frames),
												 mqtt_broker_host(other.mqtt_broker_host),
												 log_home_path(other.log_home_path),
												 text_log_filename(other.text_log_filename) {};

};



#endif /* SRC_LOGPREFERENCES_H_ */
