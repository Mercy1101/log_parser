/// Copyright (c) 2019,2020 Lijiancong. All rights reserved.
///
/// Use of this source code is governed by a MIT license
/// that can be found in the License file.

/// @file   condition_parser.hpp
/// @brief  条件解析器
///
/// @author lijiancong, pipinstall@163.com
/// @date   2020-08-06 21:30:02

#ifndef INCLUDE_CONDITION_PARSER_HPP_
#define INCLUDE_CONDITION_PARSER_HPP_

#include <string>
#include <vector>

#include "log_parser/data_struct_define.hpp"

namespace lee {
inline namespace condition_detail {
class condition_parser {
 public:
  /// +error, -info, *[regex], +\+, -\-, +\*,
  ///"+error", "-info", "*[regex]", "+\\+",
  static cond_vec parser(std::string raw_condition) {
    raw_condition = replace_backslash(raw_condition);
    raw_condition = strip_space(raw_condition);
    std::vector<std::string> vec;
    vec = splice_by_string(raw_condition, ",");
  }

 private:
  void replace_backslash(string& raw_condition) {
    /// TODO(lijiancong): 目前还不确定获取到的字符串读取时能否读取到两个反斜杠
  }
  static void strip_space(string& raw_condition) {
    auto begin = raw_condition.find_first_not_of(' ');
    auto end = raw_condition.find_last_not_of(' ');
    raw_condition = raw_condition.substr(begin, end);
  }

  static std::vector<std::string> split(const string& raw_condition,
                                        const std::string& token = ",") {
    using size = std::string::size_type;
    std::vector<std::string> vec;
    size begin = raw_condition.find_first_not_of(token, 0);
    size end = raw_condition.find_first_of(token, begin);
    while (std::string::npos != begin && std::string::npos != end) {
      vec.push_back(raw_condition.substr(begin, end - begin));
      end = raw_condition.find_first_not_of(token, begin);
      begin = raw_condition.find_first_of(token, end);
    }
  };
}  // namespace condition_detail
}  // namespace condition_detail
#endif  // INCLUDE_CONDITION_PARSER_HPP_