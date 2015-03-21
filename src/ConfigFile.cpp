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
	std::ifstream configFile(filename);
	if(configFile.fail())	///< Likely first time created file
		return;

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

		config[string(buf, separator)] = string(buf+separator+1, end);
	}
}

const bool ConfigFile::HasValue(const string& key) const
{
	return config.count(key);
}

const string& ConfigFile::GetValue(const string &key, const string& defaultVal)
{
	if(!HasValue(key))
		config[key] = defaultVal;

	return config.at(key);
}

void ConfigFile::SetValue(const string& key, const string& value)
{
	config[key] = value;
}

const int ConfigFile::Save(const string &file)
{
	std::ofstream configFile(file);
	if(configFile.fail())
		return -1;

	for(auto i = config.begin(); i != config.end(); i++)
	{
		configFile<<i->first<<':'<<i->second<<'\n';
	}

	configFile.flush();
	return 0;
}

}

