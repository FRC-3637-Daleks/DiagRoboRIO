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
	const string GetFilename() const {return filename;};
	const string GetFilePath() const {return "/home/lvuser/";};

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
	template<typename T> void SetValue(const string& key, const T& value)
	{
		stringstream ss;
		ss<<value;
		SetValue(key, ss.str());
	}

	const unordered_map<string, string>::const_iterator Begin() const {return config.begin();};
	const unordered_map<string, string>::const_iterator End() const {return config.end();};

public:
	const int Save(const string& file);
	const int Save() {return Save(filename);};
	const int Reload(const string &file);
	const int Reload() {return Reload(filename);};
};


}

#endif /* SRC_CONFIGFILE_H_ */
