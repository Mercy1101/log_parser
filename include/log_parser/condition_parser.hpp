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
  static cond_vec parser(const std::string& raw_condition) {
    raw_condition = strip_space(raw_condition);
    raw_condition = splice_by_string(raw_condition, ",");
  }

 private:
  static std::string strip_space(const string& raw_condition) {
    auto begin = raw_condition.find_first_not_of(' ');
    auto end = raw_condition.find_last_not_of(' ');
    return raw_condition.substr(begin, end);
  }

  static std::string split(const string& raw_condition,
                           const std::string& token = ",") {
                             
                           }
};
}  // namespace condition_detail
}  // namespace lee
#endif  // INCLUDE_CONDITION_PARSER_HPP_