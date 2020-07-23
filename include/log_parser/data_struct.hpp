
///////// ///////// ///////// ///////// ///////// ///////// ///////// /////////
/// Copyright (c) 2019,2020 Lijiancong. All rights reserved.
///
/// Use of this source code is governed by a MIT license
/// that can be found in the License file.
///
/// @file   data_struct.hpp
/// @brief  用于保存日志结构的数据结构的定义
///
/// @author lijiancong, pipinstall@163.com
/// @date   2020-07-23 20:13:41
///////// ///////// ///////// ///////// ///////// ///////// ///////// /////////

#ifndef INCLUDE_DATA_STRUCT_HPP_
#define INCLUDE_DATA_STRUCT_HPP_

#include <string>
#include <unordered_map>

namespace lee {
inline namespace data_struct {
class log_time {
 public:
  get() {}

 private:
};

class log_level {
  static std::unordered_map<std::string, int> log_level{
      {"trace", 0}, {"debug", 1}, {"info", 2},
      {"warn", 3},  {"error", 4}, {"critrial", 5},
  };  ///< <level, int>
};
class log_text {
 public:
  void set(std::string&& text) { text_ = std::move(text); }
  void set(const std::string& text) { text_ = text; }
  const std::string& get() { return text_; }

 private:
  std::string text_;
};

class log_information {
 public:
  set(const size_t line_, const size_t thread_id,
      const std::string& function_name) {
    line_ = line;
    thread_id_ = thread_id;
    function_name_ = function_name;
  }

 private:
  size_t line_;
  /// std::string file_name_;
  size_t thread_id_;
  std::string function_name_;
};

class log_data_struct {
 public:
  void set() {}
  const log_data_struct& get() {}

 private:
  log_time time_;
  log_level level_;
  log_text log_;
  log_information info_;
};

}  // namespace data_struct
}  // namespace lee

#endif