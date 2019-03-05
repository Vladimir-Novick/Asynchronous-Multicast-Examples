#pragma once

#ifndef ItemWriter_H
#define ItemWriter_H

#include <mutex>

class ItemWriter
{
public:
	template<typename Func>
	void ExecuteFunc(Func &&f) {
		std::unique_lock<std::mutex> lock{ m_mut };
		f();
	}

private:
	std::mutex m_mut;
public:
	ItemWriter();
	~ItemWriter();
};

#endif 

