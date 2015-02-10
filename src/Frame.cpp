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

const shared_ptr<Datum>& Frame::GetDatumRef(const int i) const
{
	if(i < data.size() && i >= 0)
		return data[i];
	else
		return data.back();
}

shared_ptr<Datum>& Frame::GetDatumRef(const int i)
{
	return const_cast<shared_ptr<Datum>&>(GetDatumRef(i));
}

const shared_ptr<Datum> Frame::GetDatum(const int i) const
{
	if(i < data.size() && i >= 0)
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

const Frame::PUSH_t Frame::GetDatumFunctor(const int i)
{
	return std::bind(&shared_ptr<Datum>::reset<Datum>, &GetDatumRef(i), std::placeholders::_1);
}

}


