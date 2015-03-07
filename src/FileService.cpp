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
	Add("log/frame_number", &FileService::Tick);
	Add("log/milliseconds", &FileService::Tock);
}

const long long FileService::Tick()
{
	static long long n = 0;
	return n++;
}

const long long FileService::Tock()
{
	static std::chrono::time_point<std::chrono::system_clock> begin = std::chrono::system_clock::now();
	return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - begin).count();
}

}


