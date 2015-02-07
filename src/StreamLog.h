/*
 * StreamLog.h
 *
 *  Created on: Feb 4, 2015
 *      Author: Edward
 */

#ifndef STREAMLOG_H_
#define STREAMLOG_H_

#include "ValueLog.h"

template<typename DATA_TYPE>
class StreamLog: public ValueLog<DATA_TYPE>
{
private:
	ostream &out;
	vector<DATA_TYPE> buf;					///< Buffer of values returned by fn
	unsigned int flushFrames;				///< Number of values buffered before it flushes to output

public:
	StreamLog(ostream &o, const typename ValueLog<DATA_TYPE>::FUNC_t &f, const unsigned int flushVal,
			typename ValueLog<DATA_TYPE>::LOG_EXTENSION_t c=ValueLog<DATA_TYPE>::continueAnyway):
			ValueLog<DATA_TYPE>(f, c), out(o), flushFrames(flushVal)
	{
		buf.reserve(flushFrames);
		out.precision(FLOATING_POINT_SIG_FIGS);
	};
	virtual ~StreamLog() {logCurrent();};

public:
	const int Log() override
	{
		const int ret = ValueLog<DATA_TYPE>::Log();
		if(ret == 1)
		{
			return logCurrent(true);
		}

		buf.push_back(ValueLog<DATA_TYPE>::getPrev());
		if(buf.size() == flushFrames)
			return logCurrent();

		return ret;
	}

	virtual const int logCurrent() override {return logCurrent(false);};

	/// Logs the current buffer immediately
	const int logCurrent(const bool logFail)
	{
		if(buf.size() == 0)
		    return 0;
		for(auto i = buf.begin(); i != buf.end(); i++)
		{
			out<<*i<<std::endl;
		}
		buf.clear();
		if(logFail)
		{
			out<<"ERR_YOUR_CALLBACK_FUCKED_YOU"<<std::endl;
			return 1;
		}
		out.flush();  // Ensures output stream is writing to file
		return 0;
	}
};




#endif /* STREAMLOG_H_ */
