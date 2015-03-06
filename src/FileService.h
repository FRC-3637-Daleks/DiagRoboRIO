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
	static const long long Tick();	///< Returns an incrementing frame id
	static const long long Tock();	///< Returns the time since its first call in milliseconds

public:
	static const long long GetTimeElapsed() {return Tock();};

private:
	shared_ptr<FileMatrix> matrix;

public:
	FileService(const shared_ptr<FileMatrix> mat);
	FileService(const MILLISECONDS mils, const string& filename): FileService(FileMatrix::Create(filename, mils)) {};

public:
	virtual ~FileService() {};

public:
	void SetMatrix(const shared_ptr<FileMatrix>& mat);
	const shared_ptr<FileMatrix> GetMatrix() const {return matrix;};

public:
	template<typename T>
	const shared_ptr<BufferPoll<T>> Add(const Frame::KEY_t& name, const T (*fn)())
	{
		return Add(name, std::function<T()>(fn));
	}

	template<typename T>
	const shared_ptr<BufferPoll<T>> Add(const Frame::KEY_t& name, const std::function<T()> &fn)
	{
		auto pushFN = matrix->Add<T>(name);
		auto ret(BufferPoll<T>::Create(fn, pushFN));
		AddPoll(ret);
		return ret;
	};
};




}



#endif /* SRC_FILESERVICE_H_ */
