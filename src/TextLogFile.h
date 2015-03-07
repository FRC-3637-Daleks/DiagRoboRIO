/*
 * TextLogFile.h
 *
 *  Created on: Mar 6, 2015
 *      Author: edward
 */

#ifndef SRC_TEXTLOGFILE_H_
#define SRC_TEXTLOGFILE_H_

#include "FilePusher.h"
#include "TextLog.h"

namespace DRR
{

class TextLogFile: public TextLog, public FilePusher
{
public:
	TextLogFile(const string& file): FilePusher(file) {};

protected:
	virtual const int LogInternal(const string& message) {if(FilePusher::Log(message)) return 0; else return -1;};
};



}



#endif /* SRC_TEXTLOGFILE_H_ */
