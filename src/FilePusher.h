/*
 * FilePusher.h
 *
 *  Created on: Feb 17, 2015
 *      Author: edward
 */

#ifndef SRC_FILEPUSHER_H_
#define SRC_FILEPUSHER_H_

#include <string>
#include <fstream>
#include <sstream>
#include <memory>

#include "Pusher.h"

namespace DRR
{

using std::string;
using std::ostream;
using std::ofstream;
using std::stringstream;
using std::unique_ptr;
using std::shared_ptr;

class FilePusher: virtual public Pusher
{
public:
	static const shared_ptr<FilePusher> Create(const string& filename);

private:
	unique_ptr<ostream> output;
	stringstream doubleBuffer[2];
	bool flip;

protected:
	FilePusher(const string& filename): output(std::make_unique<ofstream>(filename)), flip(0) {};
	FilePusher(FilePusher&& other);

public:
	virtual ~FilePusher() {};

public:
	const bool Log(const string& text);
	virtual const int Push() override;

};



}



#endif /* SRC_FILEPUSHER_H_ */
