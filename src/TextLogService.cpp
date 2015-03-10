/*
 * TextLogService.cpp
 *
 *  Created on: Mar 8, 2015
 *      Author: 3637-DS-1
 */

#include <sstream>

#include "TextLogService.h"
#include "TextLogFile.h"

namespace DRR
{

TextLogService::TextLogService(): textThread(nullptr)
{

}

TextLogService::TextLogService(const shared_ptr<TextLog> &toInstall, const shared_ptr<Pusher> &toPush, const MILLISECONDS mils)
{
	AddService(toInstall, toPush, mils);
}

TextLogService::TextLogService(const string &file, const unsigned int mils)
{
	AddService(file, mils);
}

void TextLogService::AddService(const shared_ptr<TextLog> &toInstall, const shared_ptr<Pusher> &toPush, const unsigned int mils)
{
	TextLog::SetFrameStamp(DiagnosticService::GetTimePoll());
	TextLog::AddHandler(toInstall);

	if(toPush == nullptr)
		return;

	if(textThread == nullptr)
	{
		textThread = ThreadList::Create({toPush}, mils);
		AddThread(textThread);
	}
	else
		textThread->AddToList(toPush);
}

void TextLogService::AddService(const string &file, const unsigned int mils)
{
	auto filePusher = TextLogFile::Create(file);
	AddService(filePusher, filePusher, mils);
}

const int TextLogService::Log(const string &service, const string &message, const LEVEL_t level)
{
	TextLog::Log(service, message, level);
}

StreamHandle TextLogService::Log(const string &service, const LEVEL_t level)
{
	return TextLog::Log(service, level);
}
}


