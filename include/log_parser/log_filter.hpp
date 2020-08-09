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

#include <optional>

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
  log_filter_base(log_view_vec& vec) : vec_(vec){};
  virtual ~log_filter_base() = default;

  virtual void filter() = 0;
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

 protected:
  log_view_vec& vec_;
  lee::SORT_KINDS sort_cond_;  ///< 用于保存排序的规则
  lee::cond_vec condition_;
  void set_sort_cond(const SORT_KINDS sort) { sort_cond_ = sort; }
};

/// @name     log_filter_single
/// @brief    用于单条条件过滤
///
/// @author   lijiancong, pipinstall@163.com
/// @date     2020-08-05 12:19:31
/// @warning  线程不安全
class log_filter_single : public log_filter_base {
 public:
  log_filter_single() = default;

  void filter() override {
    auto sort = [](const log_view& lhs, const log_view& rhs) -> bool {
      return lhs.first.get() < rhs.first.get();
    };
    std::stable_sort(vec_.begin(), vec_.end(), sort);

    for (auto& it : vec_) {
      auto pos = find_keyword(condition_.at(0).first, it.first.get().get_log());
      if (pos) {
        it.second.pos = pos.value();
        it.second.state = condition_.at(0).second;
      }
    }
  }
};

class log_filter_multi : public log_filter_base {
 public:
  log_filter_multi() = default;

  void filter() override {
    for (auto& it : vec_) {
      for (auto& it_cond : condition_) {
        auto pos = find_keyword(it_cond.first, it.first.get().get_log());
        if (pos) {
          it.second.pos = pos.value();
          it.second.state = it_cond.second;
        }
      }
    }
  }
};

}  // namespace log_detail
}  // namespace lee
#endif
