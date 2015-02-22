/*
 * FileService.h
 *
 *  Created on: Feb 21, 2015
 *      Author: edward
 */

#ifndef SRC_FILESERVICE_H_
#define SRC_FILESERVICE_H_

#include "FileMatrix.h"
#include "DiagnosticService.h"
#include "PollBuffer.h"

namespace DRR
{

class FileService: private DiagnosticService
{
private:
	shared_ptr<FileMatrix> matrix;

public:
	FileService(const string& filename, const MILLISECONDS mils): matrix(FileMatrix::Create(filename, mils)) {AddThread(matrix);};

public:
	virtual ~FileService() {};

public:
	template<typename T>
	const shared_ptr<BufferPoll<T>> Add(const Frame::KEY_t& name, const typename BufferPoll<T>::POLL_t &fn)
	{
		auto pushFN = matrix->Add<T>(name);
		auto ret(BufferPoll<T>::Create(fn, pushFN));
		AddPoll(ret);
		return ret;
	};
};




}



#endif /* SRC_FILESERVICE_H_ */
