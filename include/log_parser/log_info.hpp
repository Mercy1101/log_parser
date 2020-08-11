/// Copyright (c) 2019,2020 Lijiancong. All rights reserved.
///
/// Use of this source code is governed by a MIT license
/// that can be found in the License file.

/// @file   log_info.hpp
/// @brief  用于保存日志信息的数据结构
///
/// @author lijiancong, pipinstall@163.com
/// @date   2020-08-02 20:50:25

#ifndef INCLUDE_LOG_PARSER_LOG_INFO_HPP_
#define INCLUDE_LOG_PARSER_LOG_INFO_HPP_

#include <string>
#include <tuple>

#include "log_parser/log_level.hpp"
#include "log_parser/log_location.hpp"
#include "log_parser/log_text.hpp"
#include "log_parser/log_time.hpp"

namespace lee {
inline namespace log_detail {
/// @name     log_info
/// @brief    用于保存解析后的单条log
///
/// @author   Lijiancong, pipinstall@163.com
/// @date     2020-08-01 17:39:55
/// @warning  线程不安全
class log_info {
 public:
  /// [2020-07-22 20:43:36.931] [trace] trace 15 <In Function: main, File:
  /// main.cc, Line: 20, PID: 15808>
  log_info(const std::string& str) {
    auto begin = str.find_first_of('[');
    auto end = str.find_first_of(']');
    log_time t(str.substr(begin, end - begin + 1));
    time_ = t;

    begin = str.find_first_of('[', end + 1);
    end = str.find_first_of(']', begin);
    log_level level(str.substr(begin, end - begin + 1));
    level_ = level;

    begin = end + 1;
    end = str.find_first_of('<', end + 1);
    log_text text(str.substr(begin, end - begin));
    text_ = text;

    begin = end + 1;
    log_location location(str.substr(begin));
    location_ = location;
  }

  time_t get_time_milli_sec() const { return time_.get_time_stamp_millisec(); }
  std::string get_time_str() const { return time_.get_time_str(); }

  std::string get_level() const { return level_.get_level_str(); }

  std::string get_log() const { return text_.get(); }

  enum LOCATION {
    FUNC = 0,
    FILE = 1,
    LINE = 2,
    PID = 3,
  };
  using location_tuple = std::tuple<std::string, std::string, int, unsigned long long>;
  location_tuple get_location() {
    auto func = location_.get_function_name();
    auto file = location_.get_file_name();
    auto line = location_.get_file_line();
    auto pid = location_.get_thread_id();
    return std::make_tuple(func, file, line, pid);
  }

  bool operator<(const log_info& lhs) const {
    return get_time_milli_sec() < lhs.get_time_milli_sec();
  }
 private:
  log_time time_;
  log_level level_;
  log_text text_;
  log_location location_;
};

}  // namespace log_detail
}  // namespace lee

#endif  // INCLUDE_LOG_PARSER_LOG_INFO_HPP_
