/*
 * Verifier.h
 *
 *  Created on: Mar 28, 2015
 *      Author: Edward
 */

#ifndef SRC_VERIFIER_H_
#define SRC_VERIFIER_H_

#include <string>
#include <sstream>
#include <functional>

namespace DRR
{

using std::string;

class Verifier
{
public:
	typedef std::function<const bool(const string&)> CHECK_t;
	static const bool DoNothing(const string &in) {return true;};
	template<typename T>
	static const Verifier Convert(const std::function<const bool(const T&)> &chk)
	{
		return Verifier([chk](const string& value)
			{
				std::stringstream ss;
				ss<<value;
				T val;
				ss>>val;
				if(ss.fail())
					return false;
				return chk(val);
			});
	}

private:
	CHECK_t check;

public:
	Verifier(): check(&Verifier::DoNothing) {};
	Verifier(const CHECK_t &fn): check(fn) {};

	/*template<typename T>
	Verifier(const std::function<const bool(const T&)> &fn): check(std::bind(&Verifier::Convert<T>, std::placeholders::_1, fn)) {};
	*/

	Verifier(const Verifier& other): check(other.check) {};

public:
	virtual ~Verifier() {};

public:
	const bool Verify(const string& val) {return check(val);};
};



}

#endif /* SRC_VERIFIER_H_ */
