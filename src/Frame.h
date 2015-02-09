/*
 * Frame.h
 *
 *  Created on: Feb 9, 2015
 *      Author: edward
 */

#ifndef SRC_FRAME_H_
#define SRC_FRAME_H_

#include <vector>
#include <utility>
#include <memory>

#include "Datum.h"

namespace DRR
{

using std::string;
using std::pair;
using std::vector;
using std::shared_ptr;

/** Frame represents a single frame of data. In essence it's a list of keys and a list of values
 */
class Frame
{
private:
	shared_ptr<const vector<string>> keys;	///< A shared list of key names
	vector<shared_ptr<Datum>> data;		///< A list of shared data values

public:
	Frame(const shared_ptr<const vector<string>> k): keys(k) {};
	Frame(const shared_ptr<const vector<string>> k, const vector<shared_ptr<Datum>> d): keys(k), data(d) {};
	Frame(const Frame& other): keys(other.keys), data(other.data) {};
	virtual ~Frame() {};

public:
	const string GetKey(const int i) const;	///< Gets the key at i
	const shared_ptr<Datum> GetDatum(const int i) const;	///< Gets the Datum at i
	const int GetSize() const;	///< Returns the size of the vectors, or -1 if they have different sizes
	pair<string, shared_ptr<Datum>> Get(const int i) const;		///< Returns a Key,Datum pair at i, if i is less than both sizes, otherwise one will be empty

public:	/// Data Access
	vector<shared_ptr<Datum>> * const operator->() {return &data;};
	const vector<shared_ptr<Datum>> * const operator->() const {return &data;};
	vector<shared_ptr<Datum>>& GetData() {return data;};
	const vector<shared_ptr<Datum>>& GetData() const {return data;};
};


}



#endif /* SRC_FRAME_H_ */
