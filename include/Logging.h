#ifndef LOGGING_H
#define LOGGING_H

// Boost logging slows down compile times.
// Uncomment to speed up the compilation.
// #define NOLOGGING

#if defined(NOLOGGING)

#include <iostream>

inline void InitLogging() { }

#define LOG_TRACE std::cout
#define LOG_DEBUG std::cout
#define LOG_INFO std::cout
#define LOG_WARN std::cout
#define LOG_ERROR std::cout
#define LOG_FATAL std::cout

#else

#include <boost/log/trivial.hpp>
#include <boost/log/utility/setup/file.hpp>

namespace logging = boost::log;

inline void InitLogging() {
    logging::add_file_log("map_solver.log");
}


#define LOG_TRACE BOOST_LOG_TRIVIAL(trace)
#define LOG_DEBUG BOOST_LOG_TRIVIAL(debug)
#define LOG_INFO BOOST_LOG_TRIVIAL(info)
#define LOG_WARN BOOST_LOG_TRIVIAL(warning)
#define LOG_ERROR BOOST_LOG_TRIVIAL(error)
#define LOG_FATAL BOOST_LOG_TRIVIAL(fatal)

#endif

#endif // LOGGING_H
