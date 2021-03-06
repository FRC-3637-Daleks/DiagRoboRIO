/*
 * ConfigFile.cpp
 *
 *  Created on: Mar 20, 2015
 *      Author: 3637-DS-1
 */

#include <fstream>
#include "ConfigFile.h"

namespace DRR
{

ConfigFile::ConfigFile(const string& file): filename(file)
{
	Reload();
}

const bool ConfigFile::HasValue(const string& key) const
{
	return config.count(key);
}

const string ConfigFile::GetValue(const string &key) const
{
	if(!HasValue(key))
		return "";
	return config.at(key);
}

const string& ConfigFile::GetValue(const string &key, const string& defaultVal)
{
	if(!HasValue(key))
		config[key] = defaultVal;

	return config.at(key);
}

void ConfigFile::setValue(const string& key, const string& value)
{
	config[key] = value;
}

void ConfigFile::removeValue(const string& key)
{
	config.erase(key);
}

const int ConfigFile::Save(const string &file)
{
	std::ofstream configFile(GetFilePath()+file);
	if(configFile.fail())
		return -1;

	for(auto i = config.begin(); i != config.end(); i++)
	{
		configFile<<i->first<<':'<<i->second<<'\n';
	}

	configFile.flush();
	return 0;
}

const int ConfigFile::Reload(const string &file)
{
	std::ifstream configFile(GetFilePath()+file);
	if(configFile.fail())	//< Likely first time created file
		return -1;

	for(auto i = config.begin(); i != config.end(); i++)	// Empties each config value first as per MessageConfig protocol
		SetValue(i->first, "");

	config.clear();
	while(!configFile.eof())
	{
		char buf[255];
		configFile.getline(buf, 255);
		int separator = -1;
		int end;
		for(end = 0; end < 255 && buf[end] != '\0'; end++)
		{
			if(buf[end] == ':')
				separator = end;
		}
		if(separator < 0)
			continue;
		//config[string(buf, separator)] = string(buf+separator+1, end);
		SetValue(string(buf, separator), string(buf+separator+1));
	}

	return 0;
}

}

