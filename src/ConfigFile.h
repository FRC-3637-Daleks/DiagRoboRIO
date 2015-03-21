/*
 * ConfigFile.h
 *
 *  Created on: Mar 20, 2015
 *      Author: 3637-DS-1
 */

#ifndef SRC_CONFIGFILE_H_
#define SRC_CONFIGFILE_H_


#include <unordered_map>
#include <sstream>

namespace DRR
{

using std::unordered_map;
using std::string;
using std::stringstream;

class ConfigFile
{
private:
	unordered_map<string, string> config;
	string filename;

public:
	ConfigFile(const string& file=string("robot.conf"));
	ConfigFile(ConfigFile&& other): config(std::move(other.config)), filename(std::move(other.filename)) {};
	virtual ~ConfigFile() {Save();};

public:
	const bool HasValue(const string& key) const;

	const string& GetValue(const string &key, const string& defaultVal = string(""));
	template<typename T> const T GetValue(const string &key, const string& defaultVal = string(""))
	{
		stringstream ss(GetValue(key, defaultVal));
		T ret;
		ss>>ret;
		return ret;
	}

	virtual void SetValue(const string& key, const string& value);	///< Sets or Adds the value to the current configuration
	template<typename T> virtual void SetValue(const string& key, const T& value)
	{
		stringstream ss;
		ss<<value;
		SetValue(key, ss.str());
	}

public:
	const int Save(const string& file);
	const int Save() {return Save(filename);};
};


}

#endif /* SRC_CONFIGFILE_H_ */
