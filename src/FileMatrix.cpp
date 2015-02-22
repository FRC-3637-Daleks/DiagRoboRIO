/*
 * FileMatrix.cpp
 *
 *  Created on: Feb 17, 2015
 *      Author: Edward
 */

#include "FileMatrix.h"

namespace DRR
{

const shared_ptr<FileMatrix> FileMatrix::Create(const string& filename, const MILLISECONDS mils)
{
	return shared_ptr<FileMatrix>(new FileMatrix(filename, mils));
}


FileMatrix::FileMatrix(const string& filename, const MILLISECONDS mils): FilePusher(filename), BufferMatrix(mils), headers(false)
{
}

const int FileMatrix::Push()
{
	if(!headers)
	{
		headers = true;
		if(!FilePusher::Log(BufferMatrix::GetCurrentFrame().KeyString()+'\n'))
			return -1;
	}
	if(!FilePusher::Log(BufferMatrix::GetCurrentFrame().DataString()+'\n'))
		return -1;

	return FilePusher::Push();
}

}

