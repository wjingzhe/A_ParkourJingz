#pragma once
#include <string>
#include <vector>

//todo 如何通过放射注册消息事件？？
class RegitsteredEvents
{
public:
	static const std::string GOLD_CHANGED;
	static const std::string SHOW_RESTART;

private:
	std::vector<std::string> _vRegisteredEvents;
};