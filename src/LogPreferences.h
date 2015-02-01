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
	unsigned int n_buffer_frames;
	const char * log_home_path;
	const char * text_log_filename;

public:
	LogPreferences(const char * tlf=DEFAULT_LOG_TEXT_OUT,
				   const unsigned int nbf=DEFAULT_LOG_BUF_LENGTH,
				   const char * lhp=DEFAULT_LOG_HOME_PATH,
				   const MILLISECONDS lp=DEFAULT_LOG_PERIOD):
					   log_period(lp), n_buffer_frames(nbf), log_home_path(lhp), text_log_filename(tlf) {};
	LogPreferences(const LogPreferences& other): log_period(other.log_period),
												 n_buffer_frames(other.n_buffer_frames),
												 log_home_path(other.log_home_path),
												 text_log_filename(other.text_log_filename) {};

};



#endif /* SRC_LOGPREFERENCES_H_ */
