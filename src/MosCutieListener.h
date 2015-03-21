/*
 * MosCutieListener.h
 *
 *  Created on: Mar 20, 2015
 *      Author: 3637-DS-1
 */

#ifndef SRC_MOSCUTIELISTENER_H_
#define SRC_MOSCUTIELISTENER_H_

#include <string>

namespace DRR
{

using std::string;

class MosCutieListener
{
private:
	string path;	///< Prefixes all topics with this value

public:
	MosCutieListener(const string &p);
	MosCutieListener(const MosCutieListener& other): MosCutieListener(other.path) {};

public:
	virtual ~MosCutieListener();

public:
	const string GetPath() const {return path;};
	const bool InPath(const string& topic) const;
	const string StripTopic(const string &topic) const;

public:
	/// Dispatched from MosCutie. `topic` is stripped of path
	virtual const int Message(const string &topic, const string &value)=0;
};


}



#endif /* SRC_MOSCUTIELISTENER_H_ */
