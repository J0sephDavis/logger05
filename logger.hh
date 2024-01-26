#ifndef RSS_LOGGER
#define RSS_LOGGER
#include <filesystem>
#include <fstream>
#include <iostream>
#include <chrono>
#include <ctime>
#include <mutex>
#include <queue>
#include <logger_config.h>
//
namespace rssfeed {
//begin namespace
enum logLevel_t {
	logDEBUG, 	//
	logTRACE, 	//trace exeuction across project. What logic was done
	logWARN, 	//Things that might have caused problems but don't affect the end functionality of the system
	logINFO, 	//In gist, what has been/is being done
	logERROR 	//a real problem that is detrimental to the functionality of the system.
};
class logger {
	//https://stackoverflow.com/questions/1008019/how-do-you-implement-the-singleton-design-pattern
	//Modified from: https://drdobbs.com/cpp/logging-in-c/201804215
	//TODO: have log file update during program runtime, not just when it exits successfully...
	public:
		inline static logger& getInstance(logLevel_t level = logINFO);
		inline logger(logger const &) = delete;
		inline void operator=(logger const &) = delete;
		inline ~logger();
		inline void trace(std::string message);
		inline void debug(std::string message);
		inline void info(std::string message);
		inline void warn(std::string message);
		inline void error(std::string message);
	private:
		inline logger(logLevel_t level);
	private:
		inline std::string levelString(logLevel_t level);
		inline void clear_queue();
		//sends a message to the log
		inline void send(std::string message, logLevel_t level = logINFO);
	private:
		logLevel_t loggerLevel;
		//the actual output stream
		std::ostringstream os;
		std::queue<std::ostringstream>  messages;
		std::mutex queue_write;
};
static logger& log = logger::getInstance(logTRACE);
//end namespace
}
#endif
