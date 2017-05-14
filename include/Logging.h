#ifndef LOGGING_H
#define LOGGING_H

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
