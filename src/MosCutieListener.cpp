/*
 * MosCutieListener.cpp
 *
 *  Created on: Mar 20, 2015
 *      Author: 3637-DS-1
 */

#include "MosCutieListener.h"
#include "MosCutie.h"

namespace DRR
{

MosCutieListener::MosCutieListener(const string &p): path(p)
{
	MosCutie::AddListener(this);
}

MosCutieListener::~MosCutieListener()
{
	MosCutie::RemoveListener(this);
}

const bool MosCutieListener::InPath(const string &topic) const
{
	if(topic.size() < path.size())
		return false;

	return topic.substr(0, path.size()) == path;
}

const string MosCutieListener::StripTopic(const string &topic) const
{
	if(!InPath(topic))
		return "";

	return topic.substr(path.size());
}

}


