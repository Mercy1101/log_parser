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

#include <algorithm>
#include <locale>
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
  log_text(const std::string& text) : text_(text) {
    /// 擦除行首行尾的空格
    text_.erase(0, text_.find_first_not_of(' '));
    text_.erase(text_.find_last_not_of(' ') + 1);
    if (text_.size() != 0) {
      lowercase_text_ = text_;
      std::transform(
          lowercase_text_.cbegin(), lowercase_text_.cend(),
          lowercase_text_.begin(), [](const char& c) -> char {
            return static_cast<char>(std::tolower(static_cast<int>(c)));
          });
    }
  }
  log_text() : log_text("") {}
  std::string get() const { return text_; }
  std::string get_lowercase() const { return lowercase_text_; }

 private:
  std::string text_;
  std::string lowercase_text_;
};

}  // namespace log_detail
}  // namespace lee

#endif  // INCLUDE_LOG_PARSER_LOG_TEXT_HPP_
