/// Copyright (c) 2019,2020 Lijiancong. All rights reserved.
///
/// Use of this source code is governed by a MIT license
/// that can be found in the License file.

/// @file   log_filter.hpp
/// @brief  用于过滤日志文件的函数
///
/// @author lijiancong, pipinstall@163.com
/// @date   2020-08-05 11:55:40

#ifndef INCLUDE_LOG_FILTER_HPP_
#define INCLUDE_LOG_FILTER_HPP_

#include "log_parser/data_struct_define.hpp"
#include "log_parser/log_info.hpp"

namespace lee {
inline namespace log_detail {
/// @name     log_filter
/// @brief    纯虚基类，用于通过等级来过滤日志显示
///
/// @author   lijiancong, pipinstall@163.com
/// @date     2020-08-05 12:00:00
/// @warning  线程不安全
class log_filter_base {
 public:
  log_filter() = default;
  virtual ~log_filter() = default;

  virtual bool set_condition(const SORT_KINDS sort, const cond_vec& vec) = 0;
  bool set_condition(const cond_vec& vec,
                     const SORT_KINDS sort = SORT_KINDS::TIME) {
    set_sort_cond(sort);
    if (vec.empty()) {
      return false;
    }
    condition_.clear();
    condition_ = vec;
    return true;
  }
  virtual void filter(log_view_vec* vec) = 0;
  std::optional<highlight_pos> find_keyword(const std::string& key_word,
                                            const std::string& log) {
    if (log.find(key_word) != std::string::npos) {
      return cal_highlight_pos(key_word, log);
    } else {
      return {};
    }
  }

  highlight_pos cal_highlight_pos(const std::string& key_word,
                                  const std::string& log) {
    size_t begin = log.find(key_word);
    size_t end = begin + key_word.size();
    return std::make_pair(begin, end);
  }

 private:
  SORT_KINDS sort_cond_;  ///< 用于保存排序的规则
  cond_vec condition_;
  void set_sort_cond(const SORT_KINDS cond) { sort_cond_ = sort; }
};

/// @name     log_filter_single
/// @brief    用于单条条件过滤
///
/// @author   lijiancong, pipinstall@163.com
/// @date     2020-08-05 12:19:31
/// @warning  线程不安全
class log_filter_single : log_filter_base {
 public:
  log_filter_single() = default;

  void filter(log_view_vec* vec) override {
    for (auto& it : *vec) {
      auto pos = find_keyword(condition_.at(0), it.first.get_log());
      if (pos) {
        it.second.hight_pos = pos.value();
        it.second.state = condition_;
      }
    }
  }
};

class log_filter_multi_cond : log_filter_base {
 public:
  log_filter_multi_cond() = default;

  void filter(log_view_vec* vec) override {
    for (auto& it : *vec) {
      for (auto& it_cond : condition_) {
        auto pos = find_keyword(it_cond, it.first.get_log());
        if (pos) {
          it.second.hight_pos = pos.value();
          it.second.state = it_cond;
        }
      }
    }
  }
};

}  // namespace log_detail
}  // namespace lee
#endif