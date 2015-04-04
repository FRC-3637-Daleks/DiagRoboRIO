/*
 * LogPreferences.h
 *
 *  Created on: Jan 30, 2015
 *      Author: edward
 */

#ifndef SRC_LOGPREFERENCES_H_
#define SRC_LOGPREFERENCES_H_

#include "Defaults.h"
#include "FileMatrix.h"
#include "DashboardPusher.h"
#include "MosCutiePusher.h"

namespace DRR
{

typedef const shared_ptr<FileMatrix> (* FileMatrixFactory)(const string&, const MILLISECONDS);
typedef const shared_ptr<DashboardPusher> (* DashboardPusherFactory)(const MILLISECONDS);

class LogPreferences
{
public:
	MILLISECONDS poll_period;
	MILLISECONDS log_period;
	MILLISECONDS monitor_period;
	int dash_period;
	unsigned int n_buffer_frames;
	const char * log_home_path;
	const char * text_log_filename;
	const char * value_log_filename;
	const char * text_dashboard_feed;
	const char * dashboard_root;
	FileMatrixFactory file_fact;
	DashboardPusherFactory dash_fact;

public:
	LogPreferences(const char * tlf=DEFAULT_LOG_TEXT_OUT,
				   const char * vlf=DEFAULT_LOG_VALUE_OUT,
				   const unsigned int nbf=DEFAULT_LOG_BUF_LENGTH,
				   const char * lhp=DEFAULT_LOG_HOME_PATH,
				   const char * dbr=DEFAULT_DASHBOARD_ROOT,
				   const MILLISECONDS mp=DEFAULT_MONITOR_PERIOD,
				   const MILLISECONDS lp=DEFAULT_LOG_PERIOD,
				   const MILLISECONDS pp=DEFAULT_POLL_PERIOD,
				   const int dashp=DEFAULT_DASH_PERIOD,
				   const FileMatrixFactory filef=DEFAULT_FILE_FACTORY,
				   const DashboardPusherFactory dashf=DEFAULT_DASH_FACTORY,
				   const char * const tdf=DEFAULT_DASHBOARD_FEED):
					   poll_period(pp), log_period(lp), monitor_period(mp), dash_period(dashp),
					   n_buffer_frames(nbf), log_home_path(lhp), text_log_filename(tlf), value_log_filename(vlf),
					   text_dashboard_feed(tdf), dashboard_root(dbr), file_fact(filef), dash_fact(dashf) {};

	LogPreferences(const LogPreferences& other): poll_period(other.poll_period),
												log_period(other.log_period),
												 monitor_period(other.monitor_period),
												 dash_period(other.dash_period),
												 n_buffer_frames(other.n_buffer_frames),
												 log_home_path(other.log_home_path),
												 text_log_filename(other.text_log_filename),
												 value_log_filename(other.value_log_filename),
												 text_dashboard_feed(other.text_dashboard_feed),
												 dashboard_root(other.dashboard_root),
												 file_fact(other.file_fact),
												 dash_fact(other.dash_fact) {};

};


}

#endif /* SRC_LOGPREFERENCES_H_ */
