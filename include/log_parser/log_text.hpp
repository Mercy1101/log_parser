///////// ///////// ///////// ///////// ///////// ///////// ///////// /////////
/// Copyright (c) 2019,2020 Lijiancong. All rights reserved.
///
/// Use of this source code is governed by a MIT license
/// that can be found in the License file.
///
/// @file   log_text.hpp
/// @brief  用于保存日志内容的数据结构
///
/// @author lijiancong, pipinstall@163.com
/// @date   2020-08-02 17:34:30
///////// ///////// ///////// ///////// ///////// ///////// ///////// /////////

#ifndef INCLUDE_LOG_PARSER_LOG_TEXT_HPP_
#define INCLUDE_LOG_PARSER_LOG_TEXT_HPP_

#include <string>

namespace lee {
inline namespace log_detail {
/// @name     log_text
/// @brief    用于保存日志内容
///
/// @author   Lijiancong, pipinstall@163.com
/// @date     2020-08-01 17:37:52
/// @warning  线程不安全
class log_text {
 public:
  log_text(std::string text) : text_(text) {}
  log_text() : log_text("") {}
  std::string get() { return text_; }

 private:
  std::string text_;
};

}  // namespace log_detail

#endif  // INCLUDE_LOG_PARSER_LOG_TEXT_HPP_