/*
 * FilePusher.cpp
 *
 *  Created on: Feb 17, 2015
 *      Author: Edward
 */

#include "FilePusher.h"

namespace DRR
{

FilePusher::FilePusher(FilePusher &&other): output(other.output.release()),
		doubleBuffer(std::move(other.doubleBuffer)), flip(other.flip)
{
}

const bool FilePusher::Log(const string& text)
{
	if(!doubleBuffer)
		return false;

	if(doubleBuffer[flip].eof())
		doubleBuffer[flip].clear();

	doubleBuffer[flip? 1:0] << text;
	return true;
}

const int FilePusher::Push()
{
	const bool push = flip;
	flip = !flip;	// flip buffer
	if(!doubleBuffer[push] || !output)
		return -1;

	if(doubleBuffer[push].rdbuf()->in_avail() > 0)	// Pushes what's in the opposite buffer
	{
		doubleBuffer[push] >> output->rdbuf();
		doubleBuffer[push].str("");
		output->flush();
	}

	return 0;
}

}


