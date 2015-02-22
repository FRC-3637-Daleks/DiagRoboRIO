/*
 * Frame.cpp
 *
 *  Created on: Feb 9, 2015
 *      Author: edward
 */

#include "Frame.h"

namespace DRR
{

Frame::Frame(const vector<PAIR_t> p): Frame()
{
	for(auto i = p.begin(); i != p.end(); i++)
	{
		keys->push_back(i->first);
		data.push_back(i->second);
	}
}

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

const string Frame::DataString() const
{
	string ret;
	for(int i = 0; i < data.size(); i++)
	{
		ret += data[i]->toString();
		if(i < data.size() - 1)
			ret += ',';
	}

	return ret;
}

const string Frame::KeyString() const
{
	string ret;
	for(int i = 0; i < keys->size(); i++)
	{
		ret += keys->at(i);
		if(i < data.size() - 1)
			ret += ',';
	}

	return ret;
}

void Frame::Add(const PAIR_t pair)
{
	keys->push_back(pair.first);
	data.push_back(pair.second);
}

}
