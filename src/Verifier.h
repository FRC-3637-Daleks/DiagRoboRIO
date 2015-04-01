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
	typedef enum {PASS=0, FAIL, FAIL_PERSIST} VERIFY_t;
	typedef std::function<const VERIFY_t(const string&)> CHECK_t;

private:
	static const VERIFY_t DoNothing(const string &in) {return PASS;};
	static const VERIFY_t ReadOnly(const string &in) {return FAIL;};
	static const VERIFY_t ReadOnlyPersist(const string &in) {return FAIL_PERSIST;};

public:
	static const Verifier do_nothing;
	static const Verifier read_only;
	static const Verifier read_only_persist;

	template<typename T>
	static const Verifier Convert(const std::function<const VERIFY_t(const T&)> &chk, const VERIFY_t onTypeFailure=FAIL_PERSIST)
	{
		return Verifier([chk, onTypeFailure](const string& value)
			{
				std::stringstream ss;
				ss<<value;
				T val;
				ss>>val;
				if(ss.fail())
					return onTypeFailure;
				return chk(val);
			});
	}

	static const Verifier And(const Verifier& a, const Verifier& b)
	{
		return Verifier([a, b](const string &value)
			{
				VERIFY_t va = a.Verify(value), vb = b.Verify(value);
				if(va == FAIL_PERSIST || vb == FAIL_PERSIST)
					return FAIL_PERSIST;
				if(va == FAIL || vb == FAIL)
					return FAIL;
				return PASS;
			});
	}

	static const Verifier Or(const Verifier& a, const Verifier& b)
	{
		return Verifier([a, b](const string &value)
			{
				VERIFY_t va = a.Verify(value), vb = b.Verify(value);
				if(va == PASS || vb == PASS)
					return PASS;
				if(va == FAIL_PERSIST || vb == FAIL_PERSIST)
					return FAIL_PERSIST;
				return FAIL;
			});
	}

private:
	CHECK_t check;

public:
	Verifier(): check(&Verifier::DoNothing) {};
	Verifier(const CHECK_t &fn): check(fn) {};
	Verifier(const Verifier& other): check(other.check) {};

public:
	virtual ~Verifier() {};

public:
	const VERIFY_t Verify(const string& val) const {return check(val);};
};



}

#endif /* SRC_VERIFIER_H_ */
