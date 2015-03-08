#ifndef _DEFAULTS_H_
#define _DEFAULTS_H_

#define DEFAULT_LOG_VALUE_OUT "values.csv"
#define DEFAULT_LOG_TEXT_OUT "states.txt"
#define DEFAULT_LOG_HOME_PATH "/home/lvuser/log/"
#define DEFAULT_MQTT_HOST "localhost"

#define DEFAULT_LOG_BUF_LENGTH 20

#define FRAME_TEXT_WIDTH 7
#define FLOATING_POINT_SIG_FIGS 8
#define DEFAULT_LOG_PERIOD 200 	//milliseconds
#define DEFAULT_MQTT_PERIOD -1	//milliseconds
#define DEFAULT_DASH_PERIOD 100	//milliseconds
#define DEFAULT_MONITOR_PERIOD 25   // milliseconds
#define DEFAULT_POLL_PERIOD 50 // milliseconds
#define DEFAULT_DASHBOARD_FEED "console"
#define DEFAULT_FILE_FACTORY [](const string& s, const MILLISECONDS t) -> const shared_ptr<FileMatrix> {return FileMatrix::Create(s, t);}
#define DEFAULT_DASH_FACTORY [](const MILLISECONDS t) -> const shared_ptr<DashboardPusher> {return shared_ptr<DashboardPusher>(MosCutiePusher::Create(t));}

namespace DRR
{
typedef unsigned int MILLISECONDS;
}


#endif /*_DEFAULTS_H_*/
