﻿/// Copyright (c) 2019,2020 Lijiancong. All rights reserved.
///
/// Use of this source code is governed by a MIT license
/// that can be found in the License file.
///
/// @file   log_location.hpp
/// @brief  用于保存日志存在的信息
///
/// @author lijiancong, pipinstall@163.com
/// @date   2020-08-02 19:10:26

#ifndef INCLUDE_LOG_PARSER_LOG_LOCATION_HPP__
#define INCLUDE_LOG_PARSER_LOG_LOCATION_HPP__

#include <string>

namespace lee {
inline namespace log_detail {
/// @name     log_location
/// @brief    用于保存记录日志位置的信息
///
/// @author   Lijiancong, pipinstall@163.com
/// @date     2020-08-01 17:38:35
/// @warning  线程不安全
class log_location {
 public:
  /// <In Function: main, File: main.cpp, Line: 20, PID: 15808>
  log_location(std::string str) {
    if (str.empty()) {
      return;
    }
    auto begin = str.find("Function: ");
    auto end = begin;
    if(begin != std::string::npos){
        begin = str.find(' ', begin) + 1;
        end = str.find(',', begin);
        function_name_ = str.substr(begin, end - begin);
    } else {
      function_name_ = "unkonw";
    }

    begin = str.find("File: ");
    if(begin != std::string::npos){
      begin = str.find(' ', begin) + 1;
      end = str.find(',', begin);
      file_name_ = str.substr(begin, end - begin);
    } else {
      file_name_ = "unkonw";
    }

    begin = str.find("Line: ");
    if(begin != std::string::npos){
       begin = str.find(' ', begin) + 1;
       end = str.find(',', begin);
       line_ = std::stoull(str.substr(begin, end - begin));
    } else {
      line_ = 0;
    }

    begin = str.find("PID: ");
    if(begin != std::string::npos){
       begin = str.find(' ', begin) + 1;
       end = str.find(',', begin);
       if (std::string::npos == end) {
         end = str.find('>', begin);
       }
       auto temp = str.substr(begin, end - begin);
       thread_id_ = std::stoull(temp);
    } else {
      thread_id_ = 0;
    }
  }

  log_location() : log_location("") {}

  const std::string get_file_name() const { return file_name_; }
  const unsigned long long get_file_line() const { return line_; }
  const unsigned long long get_thread_id() const { return thread_id_; }
  const std::string get_function_name() const { return function_name_; }

 private:
  std::string function_name_;
  std::string file_name_;
  unsigned long long line_ = 0;
  unsigned long long thread_id_ = 0;
};
}  // namespace log_detail
}  // namespace lee
#endif  // INCLUDE_LOG_PARSER_LOG_LOCATION_HPP__
