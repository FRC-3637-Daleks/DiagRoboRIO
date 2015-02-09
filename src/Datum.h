/*
 * Datum.h
 *
 *  Created on: Feb 9, 2015
 *      Author: root
 */

#ifndef SRC_DATUM_H_
#define SRC_DATUM_H_

#include <string>

namespace DRR
{

using std::string;
	/** Base class for DatumValue<T>
 * Allows for list creation of generic data which can be moved around in lists of data of different types
 */
	class Datum
{
public:
	virtual ~Datum() {};

public:
	operator const string() const {return toString();};		///< Implicitly converts encapsulated data to a string
	virtual const string toString() const=0;  ///< Converts the encapsulated data into a string

	virtual const unsigned int fill(const void* *memPtr) const=0;	///< Sets memPtr to allocated with encapsulated data and returns the number of bytes memPtr points to.
	const unsigned int fill(const void* &memRef) const {return fill(&memRef);};

	virtual const string getType() const=0;	///< Gets string representation of type
};

}

#endif /* SRC_DATUM_H_ */
