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
	static const shared_ptr<TextLogFile> Create(const string& file)
	{
		return shared_ptr<TextLogFile>(new TextLogFile(file));
	}

protected:
	TextLogFile(const string& file): FilePusher(file) {};
	TextLogFile(TextLogFile&& other): TextLog(std::move(other)), FilePusher(std::move(other)) {};

protected:
	virtual const int LogInternal(const string& message);
};



}



#endif /* SRC_TEXTLOGFILE_H_ */
