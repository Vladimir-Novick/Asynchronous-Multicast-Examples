#pragma once

#ifndef Accumulator_H
#define Accumulator_H

#include <mutex>
#include <string>
#include <iostream> 

class Accumulator
{
public:

private:
	std::mutex _mutex;
public:
	void CallBackFunction(std::string message);
	Accumulator();
	~Accumulator();
};

#endif 

