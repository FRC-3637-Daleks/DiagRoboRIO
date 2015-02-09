/*
 * Frame.cpp
 *
 *  Created on: Feb 9, 2015
 *      Author: edward
 */

#include "Frame.h"

namespace DRR
{

const string Frame::GetKey(const int i) const
{
	if(i < keys->size())
		return keys->at(i);
	return string();
}

const shared_ptr<Datum> Frame::GetDatum(const int i) const
{
	if(i < data.size())
		return data[i];
	return nullptr;
}

const int Frame::GetSize() const
{
	if(data.size() == keys->size())
		return data.size();
	return -1;
}

pair<string, shared_ptr<Datum>> Frame::Get(const int i) const
{
	return pair<string, shared_ptr<Datum>>(GetKey(i), GetDatum(i));
}


}


