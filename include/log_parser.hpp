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

#include "log_parser/file_helper.hpp"
#include "log_parser/log_info.hpp"

namespace lee {
inline namespace log {
class log_parser {
 public:
  log_parser(const std::string& file_path) { parse(file_path); }

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
    if (lee::file_helper_::read(file, &file_data_)) {
      assert(false && "cannot open the file");
      return false;
    }

    lee::file_helper_::filter(&file_data_);
    /// log_view.insert(log_view.end(), file_data_.begin(), file_data_.end());
    log_view_.reserve(file_data_.size());
    for (const auto& it : file_data_) {
      log_info info(it);
      log_view_.push_back(it);
    }
    std::sort(log_view_.begin(), log_view_.end());
    return true;
  }

  /// @name     STATE
  /// @brief    用于记录日志可不可见
  ///
  /// @author   Lijiancong, pipinstall@163.com
  /// @date     2020-08-04 20:01:40
  /// @warning  线程不安全
  enum STATE : int {
    HIDDEN = 0,     ///< 隐藏状态
    DEFAULT = 1,    ///< 默认状态
    VISABLE = 2,    ///< 可见状态
    HIGHLIGHT = 3,  ///< 高亮状态
  };

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
  std::vector<log_info> find(STATE state = VISABLE) {
    std::vector<log_info> ret;
    for (auto& it : log_view_) {
      if (it.second > state) {
        ret.push_back(it.first);
      }
    }
    return ret;
  }

 private:
  lee::file_helper file_helper_;  ///< 文件帮助类，用于读取文件
  std::vector<std::string> file_data_;  ///< 用于存放文件内容
  std::vector<std::pair<log_info, STATE>> log_view_;  ///< 保存日志的数据结构
  std::multi_map<STATE, std::string> condition_;  ///< 用于显示日志的关键字

  /// @name     add_condition
  /// @brief    用于添加各种状态的优先级
  /// @details  该条件的优先级比
  ///
  /// @param    key_word  [in]  关键字
  ///
  /// @return   NONE
  ///
  /// @author   Lijiancong, pipinstall@163.com
  /// @date     2020-08-04 20:06:01
  /// @warning  线程不安全
  void add_condition(const std::string& key_word, const STATE state) {
    condition_[state] = key_word;
    refresh_all_state();
  }
  void mark(const STATE state, const std::string& key_word) {
    for (auto& it : log_view_) {
      if (it.first.get_log().find(key_word) != std::string::npos) {
        it.second = state;
      }
    }
  }

  void refresh_all_state() {
    for (const auto& it : condition_) {
      mark(it.first, it.second);
    }
  }

  void clean_all_condition() {
    condition_.clear();
    for (auto& it : log_view_) {
      it.second = STATE::DEFAULT;
    }
  }
};
}  // namespace log
}  // namespace lee

#endif  // INCLUDE_LOG_PARSER_HPP_
