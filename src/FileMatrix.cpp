/*
 * FileMatrix.cpp
 *
 *  Created on: Feb 17, 2015
 *      Author: Edward
 */

#include "FileMatrix.h"

namespace DRR
{

FileMatrix::FileMatrix(const string& filename, const MILLISECONDS mils): FilePusher(filename), BufferMatrix(mils)
{
	FilePusher::Log(BufferMatrix::GetCurrentFrame().KeyString()+'\n');
}

const int FileMatrix::Push()
{
	if(FilePusher::Log(BufferMatrix::GetCurrentFrame().DataString()+'\n'))
		return 0;
	return -1;
}

}

