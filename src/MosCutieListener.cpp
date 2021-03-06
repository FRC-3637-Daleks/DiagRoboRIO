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
	if(path.back() != '/')
		path.push_back('/');
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

void MosCutieListener::Publish(const string &subtopic, const string &value, const bool retain)
{
	MosCutie::Publish(GetPath()+subtopic, value, retain);
}

const bool MosCutieListener::Has(const string &subtopic)
{
	return MosCutie::Has(GetPath()+subtopic);
}

const string MosCutieListener::Get(const string &subtopic)
{
	return MosCutie::Get(GetPath()+subtopic);
}

const bool MosCutieListener::AddVerifier(const string &subtopic, const Verifier &ver)
{
	return MosCutie::AddVerifier(GetPath()+subtopic, ver);
}

}


