// Implements concept-based run-time polymorphism a la Sean Parent (runtime-concept idiom)
// A sink (loggable) satisfies the log concept for a given message (meta + msg)
// In this implementation logging is down via a call operator
//   log(loggable, meta, msg)
//   -> loggable(meta, msg)
#ifndef LOGSINK_HPP
#define LOGSINK_HPP

#include <utils/LogMsg.hpp>

#include <memory>
#include <fstream>

namespace attpcfe {

  class LogSink {

    struct concept_t {

      virtual ~concept_t() = default;
      //virtual std::unique_ptr<concept_t> copy_() const = 0;
      virtual void log_(LogMsg::Meta const& meta, std::string const& msg) const = 0;
    };

    template <typename T>
    struct model_t final : public concept_t {
      
      model_t(T data);

      //std::unique_ptr<concept_t> copy_() const override
      //{
      //  return std::make_unique<model_t<T>>(*this);
      //}
      
      void log_(LogMsg::Meta const& meta, std::string const& msg) const override;

      T _data;
    };

    //std::unique_ptr<concept_t> _self;
    std::shared_ptr<concept_t const> _self;
    
  public:
    template<typename T>
    LogSink(T impl);
    
    //LogSink(LogSink const&);
    //LogSink(LogSink&&) noexcept = default;
    //LogSink& operator=(LogSink const& logSink)
    //{
    //  return *this = LogSink(logSink);
    //}
    //LogSink& operator=(LogSink&&) noexcept = default;

    friend void log(LogSink const& sink, LogMsg::Meta const&, std::string const& msg);
  };

  // Would usually move this to a separate header.
  LogSink makeConsoleSink();
  
  class FileSink {

  public:
    FileSink(std::string const& filename);

    void operator()(LogMsg::Meta const& meta, std::string const& msg) const;

    std::unique_ptr<std::ofstream> _pFile;
  };
  
  LogSink makeFileSink(std::string const& filename);
}
#include <utils/LogSink.inl>
#endif
