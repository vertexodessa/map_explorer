#ifndef LOGGING_H
#define LOGGING_H

// Boost logging slows down compile times.
// Uncomment to speed up the compilation.
//#define NOLOGGING

#if defined(NOLOGGING)

#include <iostream>

namespace Logging {

inline void InitLogging() { }

class DummyLogger {
public:

    static DummyLogger& Singleton() {
        static DummyLogger d;
        return d;
    };

    template <class T>
    DummyLogger& operator << (T) {
        return *this;
    }

};

}

#define LOG_TRACE Logging::DummyLogger::Singleton()
#define LOG_DEBUG Logging::DummyLogger::Singleton()
#define LOG_INFO Logging::DummyLogger::Singleton()
#define LOG_WARN Logging::DummyLogger::Singleton()
#define LOG_ERROR Logging::DummyLogger::Singleton()
#define LOG_FATAL Logging::DummyLogger::Singleton()

#else

#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/utility/setup/file.hpp>

namespace logging = boost::log;
namespace src = boost::log::sources;
namespace sinks = boost::log::sinks;
namespace keywords = boost::log::keywords;
namespace expr = boost::log::expressions;


namespace Logging {

inline void initLogging() {
//    logging::add_file_log("map_solver.log");
    logging::add_file_log
    (
        keywords::file_name = "sample_%N.log",                                        /*< file name pattern >*/
        // This makes the sink to write log records that look like this:
        // 1: <normal> A normal severity message
        // 2: <error> An error severity message
        keywords::format =
        (
            expr::stream
            << expr::attr< unsigned int >("LineID")
            << ": <" << logging::trivial::severity
            << "> " << expr::smessage
        )
    );

}

}

#define LOG_TRACE BOOST_LOG_TRIVIAL(trace)
#define LOG_DEBUG BOOST_LOG_TRIVIAL(debug)
#define LOG_INFO BOOST_LOG_TRIVIAL(info)
#define LOG_WARN BOOST_LOG_TRIVIAL(warning)
#define LOG_ERROR BOOST_LOG_TRIVIAL(error)
#define LOG_FATAL BOOST_LOG_TRIVIAL(fatal)

#endif

#endif // LOGGING_H
