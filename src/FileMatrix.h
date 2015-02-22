/*
 * FileMatrix.h
 *
 *  Created on: Feb 17, 2015
 *      Author: Edward
 */

#ifndef SRC_FILEMATRIX_H_
#define SRC_FILEMATRIX_H_

#include "FilePusher.h"
#include "BufferMatrix.h"

namespace DRR
{

class FileMatrix: public FilePusher, public BufferMatrix
{
public:
	static const shared_ptr<FileMatrix> Create(const string& filename, const MILLISECONDS mils);

private:
	bool headers;

protected:
	FileMatrix(const string& filename, const MILLISECONDS mils);
	FileMatrix(FileMatrix&& other): FilePusher(std::move(other)), BufferMatrix(std::move(other)), headers(other.headers) {};

public:
	virtual ~FileMatrix() {};

public:
	virtual const int Push() override;
};



}



#endif /* SRC_FILEMATRIX_H_ */
