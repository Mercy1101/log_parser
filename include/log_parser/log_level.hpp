/// Copyright (c) 2019,2020 Lijiancong. All rights reserved.
///
/// Use of this source code is governed by a MIT license
/// that can be found in the License file.
/// @file   log_level.hpp
/// @brief  用于保存日志等级的数据结构
///
/// @author lijiancong, pipinstall@163.com
/// @date   2020-08-02 17:29:32

#ifndef INCLUDE_LOG_PARSER_LOG_LEVEL_HPP_
#define INCLUDE_LOG_PARSER_LOG_LEVEL_HPP_

#include <cassert>
#include <string>
#include <unordered_map>

namespace lee {
inline namespace log_detail {
/// @name     log_level
/// @brief    用于保存日志中的等级
///
/// @author   Lijiancong, pipinstall@163.com
/// @date     2020-08-01 17:36:27
/// @warning  线程不安全
class log_level {
  static inline const std::unordered_map<std::string, int> level_map{
      {"trace", 0}, {"debug", 1},    {"info", 2},    {"warn", 3},
      {"error", 4}, {"critrial", 5}, {"unknow", 100}};

 public:
  log_level(const std::string& level) {
    level_str_ = level;
    auto it = level_map.find(level);
    if (it != level_map.end()) {
      level_num_ = it->second;
    } else {
      assert(false && "error log level");
    }
  }
  log_level(const int level) {
    level_num_ = level;
    for (const auto& element : level_map) {
      if (element.second == level) {
        level_str_ = element.first;
        return;
      }
    }
    assert(false && "error log level");
  }
  log_level() : log_level(100) {}

  const int get(const std::string&) { return level_num_; }
  const std::string get(const int&) { return level_str_; }

 private:
  std::string level_str_;
  int level_num_;
};
}  // namespace log_detail
}  // namespace lee
#endif  // INCLUDE_LOG_PARSER_LOG_LEVEL_HPP_
