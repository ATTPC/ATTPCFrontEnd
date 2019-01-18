#define LOGSINK_CPP
#include <utils/LogSink.hpp>
#include <utils/LogMsg.hpp>

#include <iostream>
#include <chrono>
#include <ctime>
#include <iomanip>

namespace attpcfe {

  //LogSink::LogSink(LogSink const& logSink) : _self(logSink._self->copy_()) {}

  //LogSink& LogSink::operator=(LogSink const& logSink) {

  //  return *this = LogSink(logSink);
  //}

  void log(LogSink const& sink, LogMsg::Meta const& meta, std::string const& msg)
  {
    sink._self->log_(meta, msg);
  }

  LogSink makeConsoleSink()
  {
    return [](LogMsg::Meta const& meta, std::string const& msg){
      std::cout << meta._level
		<< "("
		<< meta._file << ':' << meta._line
		<< "): " 
		<< msg << '\n'; };
  }

  FileSink::FileSink(std::string const& filename) : _pFile{std::make_unique<std::ofstream>(filename)}
  {
    if (!_pFile->good())
    {
      std::string msg{"Failed to open file: "};
      msg.append(filename);
      try {
	throw std::runtime_error(msg);
      }
      catch (std::runtime_error const& e) {

	std::cerr << "> runtime exception: " << e.what() << '\n';
      }
       
    }
  }

  void FileSink::operator()(LogMsg::Meta const& meta, std::string const& msg) const
  {
    auto now = std::chrono::system_clock::now();
    auto time_t = std::chrono::system_clock::to_time_t(now);
    auto localTime = std::localtime(&time_t);
    
    *_pFile << std::put_time(localTime, "[%H:%M:%S]")
	    << meta._level
	    << msg
	    << " ("
	    << meta._file << ':' << meta._line
	    << ")\n";
  }
  
  LogSink makeFileSink(std::string const& filename)
  {
    return FileSink(filename);
  }
}
