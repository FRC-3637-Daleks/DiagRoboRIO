/*
 * Frame.cpp
 *
 *  Created on: Feb 9, 2015
 *      Author: edward
 */

#include "Frame.h"

namespace DRR
{

const Frame::KEY_t Frame::GetKey(const int i) const
{
	if(i < keys->size())
		return keys->at(i);
	return string();
}

const Frame::DATA_t& Frame::GetDatumRef(const int i) const
{
	if(i < data.size() && i >= 0)
		return data[i];
	else
		return data.back();
}

Frame::DATA_t& Frame::GetDatumRef(const int i)
{
	return const_cast<DATA_t&>(GetDatumRef(i));
}

const Frame::DATA_t Frame::GetDatum(const int i) const
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

Frame::PAIR_t Frame::Get(const int i) const
{
	return PAIR_t(GetKey(i), GetDatum(i));
}

const Frame::PUSH_t Frame::GetDatumFunctor(const int i)
{
	return std::bind(static_cast<DATA_t&(const DATA_t&)>(&DATA_t::operator=), &GetDatumRef(i), std::placeholders::_1);
}

}


