/*
 * FileService.cpp
 *
 *  Created on: Mar 5, 2015
 *      Author: edward
 */

#include "FileService.h"
#include <chrono>

namespace DRR
{

FileService::FileService(const shared_ptr<FileMatrix> mat): matrix(mat)
{
	SetMatrix(matrix);
}

void FileService::SetMatrix(const shared_ptr<FileMatrix>& mat)
{
	if(IsInitialized())
		return;
	matrix = mat;
	if(!AddThread(matrix))
		return;
	Add("log/frame_number", &DiagnosticService::GetCurrentFrame);
	Add("log/milliseconds", &DiagnosticService::GetTimeElapsed);
	LogText(LEVEL_t::INIT)<<"FileMatrix set to push data to "<<matrix->GetFileName();
}

}


