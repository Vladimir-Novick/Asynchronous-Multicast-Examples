#include "pch.h"
#include "Accumulator.h"



Accumulator::Accumulator()
{
}


Accumulator::~Accumulator()
{
}

void Accumulator::CallBackFunction(std::string message) {
	std::lock_guard<std::mutex> lck(_mutex);
	std::cout << message << std::endl;
}
