/*
 * Verifier.cpp
 *
 *  Created on: Mar 28, 2015
 *      Author: Edward
 */

#include "Verifier.h"

namespace DRR
{

const Verifier Verifier::do_nothing(&Verifier::DoNothing);
const Verifier Verifier::read_only(&Verifier::ReadOnly);


}
