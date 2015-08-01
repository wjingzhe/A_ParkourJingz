#pragma once
#include <string>
#include <vector>

//todo 如何通过反射注册消息事件？？
class RegitsteredEvents
{
public:
	static const std::string GOLD_CHANGED;
	static const std::string SHOW_RESTART;
	static const std::string GAME_OVER;
	static const std::string GAME_START;
	static const std::string GAME_RESTART;
};