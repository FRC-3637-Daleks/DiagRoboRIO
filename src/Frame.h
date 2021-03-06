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

#include "Buffer.h"
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
public:
	typedef string KEY_t;
	typedef shared_ptr<Datum> DATA_t;
	typedef pair<KEY_t, DATA_t> PAIR_t;

private:
	shared_ptr<vector<KEY_t>> keys;	///< A shared list of key names
	vector<DATA_t> data;		///< A list of shared data values

public:
	Frame(): keys(std::make_shared<vector<KEY_t>>()), data() {};
	Frame(const vector<PAIR_t> p);
	Frame(const shared_ptr<vector<string>> k, const vector<DATA_t> d): keys(k), data(d) {};
	Frame(const vector<string> k, const vector<DATA_t> d): Frame(std::make_shared<vector<string>>(k), d) {};
	Frame(const Frame& other): keys(other.keys), data(other.data) {};
	virtual ~Frame() {};

private:
	const DATA_t& GetDatumRef(const int i) const;
	DATA_t& GetDatumRef(const int i);

public:
	const bool isEmpty() const {return !GetDatum(0);};
	const string GetKey(const int i) const;	///< Gets the key at i
	const DATA_t GetDatum(const int i) const;	///< Gets the Datum at i
	const int GetSize() const;	///< Returns the size of the vectors, or -1 if they have different sizes
	PAIR_t Get(const int i) const;		///< Returns a Key,Datum pair at i, if i is less than both sizes, otherwise one will be empty
	void Add(const PAIR_t p);	///< Adds a Key,Datum pair at the end

public:	/// Data Access
	const vector<DATA_t> * const operator->() const {return &data;};
	const vector<DATA_t>& GetData() const {return data;};
	const shared_ptr<const vector<string>> GetKeys() const {return keys;};

public:
	const string DataString() const;
	const string KeyString() const;
};


}

#endif /* SRC_FRAME_H_ */
