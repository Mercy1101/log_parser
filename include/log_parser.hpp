///////// ///////// ///////// ///////// ///////// ///////// ///////// /////////
/// Copyright (c) 2019,2020 Lijiancong. All rights reserved.
///
/// Use of this source code is governed by a MIT license
/// that can be found in the License file.
///
/// @file   log_parser.hpp
/// @brief  日志解析器的封装
///
/// @author lijiancong, pipinstall@163.com
/// @date   2020-07-23 19:06:52
///////// ///////// ///////// ///////// ///////// ///////// ///////// /////////

#ifndef INCLUDE_LOG_PARSER_HPP_
#define INCLUDE_LOG_PARSER_HPP_

#include "log_parser/file_helper.hpp"
#include <string>
#include <vector>

namespace lee {
inline namespace log {
class log_parser {
 public:
  log_parser() {}
  /// @name     parse
  /// @brief    解析文件
  ///
  /// @param    file  [in]
  ///
  /// @return   文件不存在或读取失败则返回false
  ///
  /// @author   Lijiancong, pipinstall@163.com
  /// @date     2020-07-23 19:07:48
  /// @warning  线程不安全
  bool parse(const std::string& file) {
    /// 读取文件所有内容
    lee::file_helper_::read(file, &file_data_);
    lee::file_helper_::filter(&file_data_);
    /// 解析器来解析这个vector
    /// parser_.parse();
    return true;
  }

  /// @name     find
  /// @brief    查询文件中内容
  ///
  /// @param
  ///
  /// @return
  ///
  /// @author   Lijiancong, pipinstall@163.com
  /// @date     2020-07-23 19:13:51
  /// @warning  线程不安全
  void find() {}

 private:
  lee::file_helper file_helper_;  ///< 文件帮助类，用于读取文件
  /// lee::parser parser_;           ///< 解析每句话的类
  std::vector<std::string> file_data_;  ///< 用于存放文件内容
};
}  // namespace log
}  // namespace lee

#endif // INCLUDE_LOG_PARSER_HPP_
