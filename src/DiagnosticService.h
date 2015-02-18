/*
 * DiagnosticService.h
 *
 *  Created on: Feb 17, 2015
 *      Author: Edward
 */

#ifndef SRC_DIAGNOSTICSERVICE_H_
#define SRC_DIAGNOSTICSERVICE_H_


#include <vector>
#include <memory>

#include "ThreadList.h"
#include "FileMatrix.h"


namespace DRR
{

using std::vector;
using std::unique_ptr;

class DiagnosticService
{
private:
	static vector<ThreadList::TL_HANDLER> threads;

public:

};

}




#endif /* SRC_DIAGNOSTICSERVICE_H_ */
