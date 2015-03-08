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
	SetService(toInstall, toPush, mils);
}

TextLogService::TextLogService(const string &file, const unsigned int mils)
{
	SetService(file, mils);
}

void TextLogService::SetService(const shared_ptr<TextLog> &toInstall, const shared_ptr<Pusher> &toPush, const unsigned int mils)
{
	TextLog::SetFrameStamp(DiagnosticService::GetFramePoll());
	TextLog::SetHandler(toInstall);

	if(toPush == nullptr)
		return;

	textThread = ThreadList::Spawn({toPush}, mils);
	AddThread(textThread);
}

void TextLogService::SetService(const string &file, const unsigned int mils)
{
	auto filePusher = TextLogFile::Create(file);
	TextLog::SetFrameStamp(DiagnosticService::GetFramePoll());
	TextLog::SetHandler(filePusher);
	textThread = ThreadList::Spawn({filePusher}, mils);
	AddThread(textThread);
}

const int TextLogService::Log(const string &service, const LEVEL_t level, const string &message)
{
	TextLog::Log(service, level, message);
}

}


