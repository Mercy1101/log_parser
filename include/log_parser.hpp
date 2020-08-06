/// Copyright (c) 2019,2020 Lijiancong. All rights reserved.
///
/// Use of this source code is governed by a MIT license
/// that can be found in the License file.

/// @file   log_parser.hpp
/// @brief  日志解析器的封装
///
/// @author lijiancong, pipinstall@163.com
/// @date   2020-07-23 19:06:52

#ifndef INCLUDE_LOG_PARSER_HPP_
#define INCLUDE_LOG_PARSER_HPP_

#include <funtional>
#include <map>
#include <string>
#include <vector>

#include "log_parser/data_struct_define.hpp"
#include "log_parser/file_helper.hpp"
#include "log_parser/log_info.hpp"
#include "log_parser/log_filter.hpp"

namespace lee {
inline namespace log {
class log_parser {
 public:
 public:
  log_parser(const std::string& file_path) {
    if (!parse(file_path)) {
      assert(false && "read file failed!");
    }
  }

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
    if (lee::file_helper::read(file, &file_data_)) {
      assert(false && "cannot open the file");
      return false;
    }

    lee::file_helper::filter(&file_data_);
    log_info_.reserve(file_data_.size());
    int count = 0;
    for (const auto& it : file_data_) {
      log_info info(it);
      log_info_state state;
      log_info_.push_back(it, count);
      log_view_.push_back(
          std::make_pair(std::cref(log_info_.back()), state)));
      count++;
    }
    /// std::sort(log_view_.begin(), log_view.end());
    return true;
  }

  /// @name     find
  /// @brief    返回大于该等级的日志内容
  ///
  /// @param    state [in]
  ///
  /// @return   符合条件的日志
  ///
  /// @author   Lijiancong, pipinstall@163.com
  /// @date     2020-07-23 19:13:51
  /// @warning  线程不安全
  std::vector<log_info> find(cond_vec& condition_vec) {
    return filter(&log_view);
  }

 private:
  std::vector<std::string> file_data_;  ///< 用于存放文件内容
  std::vector<log_info> log_info_;  ///< 用于存放解析好的日志内容
  log_view_vec log_view_;           ///< 用于存放日志内容的引用
  lee::log_filter filter_;
};
}  // namespace log
}  // namespace lee

#endif  // INCLUDE_LOG_PARSER_HPP_
