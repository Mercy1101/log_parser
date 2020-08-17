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

#include <functional>
/// #include <optional>
#include <string>
#include <utility>
#include <vector>
#include <algorithm>
#include <cctype>

#include "log_parser/data_struct_define.hpp"
#include "log_parser/log_info.hpp"

namespace lee {
inline namespace log_detail {

using log_view = std::pair<std::reference_wrapper<log_info>, log_info_state>;
using log_view_vec = std::vector<log_view>;
/// @name     log_filter
/// @brief    纯虚基类，用于通过等级来过滤日志显示
///
/// @author   lijiancong, pipinstall@163.com
/// @date     2020-08-05 12:00:00
/// @warning  线程不安全
class log_filter_base {
 public:
  log_filter_base() = default;
  virtual ~log_filter_base() = default;

  virtual void filter(log_view_vec& vec) = 0;
  bool set_condition(const cond_vec& vec,
                     const SORT_KINDS sort = SORT_KINDS::TIME) {
    set_sort_cond(sort);
    if (vec.empty()) {
      return false;
    }
    /// condition_.clear();
    condition_ = vec;
    return true;
  }

  void clear_condition(){
    set_sort_cond(SORT_KINDS::TIME);
    condition_.clear();
  }

  bool find_keyword(lee::highlight_pos& pos, const std::string& key_word,
                    const std::string& log) {
    if (log.find(key_word) != std::string::npos) {
      pos = cal_highlight_pos(key_word, log);
      return true;
    } else {
      return false;
    }
  }

  highlight_pos cal_highlight_pos(const std::string& key_word,
                                  const std::string& log) {
    size_t begin = log.find(key_word);
    size_t end = begin + key_word.size();
    return std::make_pair(begin, end);
  }

 protected:
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

  void filter(log_view_vec& vec) override {
    auto sort = [](const log_view& lhs, const log_view& rhs) -> bool {
      return lhs.first.get() < rhs.first.get();
    };
    std::stable_sort(vec.begin(), vec.end(), sort);

    lee::highlight_pos pos;
    for (auto& it : vec) {
      auto res = find_keyword(pos, condition_.at(0).first, it.first.get().get_log());
      if (res) {
        it.second.pos = pos;
        it.second.state = condition_.at(0).second;
      }
    }
  }
};

class log_filter_multi : public log_filter_base {
 public:
  log_filter_multi() = default;

  void filter(log_view_vec& vec) override {
    for (auto& it : vec) {
      lee::highlight_pos pos;
      for (auto& it_cond : condition_) {
        auto res = find_keyword(pos ,it_cond.first, it.first.get().get_log());
        if (res) {
          it.second.pos = pos;
          it.second.state = it_cond.second;
        } else {
          /// it.second.state = VISABLE_STATE::HIDDEN;
        }
      }
    }
  }
};

class log_filter_ignorecase : public log_filter_base {
 public:
  log_filter_ignorecase() = default;

  void filter(log_view_vec& vec) override {
    for(auto keyword = condition_.begin(); keyword != condition_.end(); ++keyword){
      std::transform(
          keyword->first.begin(), keyword->first.end(),
          keyword->first.begin(), [](const char& c) -> char {
            return static_cast<char>(std::tolower(static_cast<int>(c)));
          });
    }
    for (auto& it : vec) {
      lee::highlight_pos pos;
      for (auto& it_cond : condition_) {
      auto keyword = it_cond.first;
      auto log = it.first.get().get_log_lowercase();
        auto res = find_keyword(pos , keyword, log);
        if (res) {
          it.second.pos = pos;
          it.second.state = it_cond.second;
        } else {
          /// it.second.state = VISABLE_STATE::HIDDEN;
        }
      }
    }
  }
};

class log_filter_wholeword: public log_filter_base {
 public:
  log_filter_wholeword() = default;

  void filter(log_view_vec& vec) override {
    for (auto& it : vec) {
      lee::highlight_pos pos;
      for (auto& it_cond : condition_) {
      auto keyword = it_cond.first;
      auto log = it.first.get().get_log_lowercase();
        auto res = find_keyword(pos , keyword, log);
        if (res) {
          bool first_bool = pos.first == 0 || !std::isalpha(it.first.get().get_log().at(pos.first-1));
          bool second_bool = pos.second == it.first.get().get_log().size()-1 || !std::isalpha(it.first.get().get_log().at(pos.second+1));
          if(first_bool && second_bool){
          it.second.pos = pos;
          it.second.state = it_cond.second;
          }
        } else {
          /// it.second.state = VISABLE_STATE::HIDDEN;
        }
      }
    }
  }
};


class log_filter_level : public log_filter_base {
 public:
  log_filter_level() = default;

  void filter(log_view_vec& vec) override {
    for (auto& it : vec) {
      lee::highlight_pos pos;
      for (auto& it_cond : condition_) {
        auto res = find_keyword(pos ,it_cond.first, it.first.get().get_level());
        if (res) {
          it.second.pos = pos;
          it.second.state = it_cond.second;
        } else {
          /// it.second.state = VISABLE_STATE::HIDDEN;
        }
      }
    }
  }
};

class log_filter_hidden : public log_filter_base {
 public:
  log_filter_hidden() = default;

  void filter(log_view_vec& vec) override {
    for (auto& it : vec) {
      lee::highlight_pos pos;
      for (auto& it_cond : condition_) {
        auto res = find_keyword(pos ,it_cond.first, it.first.get().get_level());
        if (res) {
          it.second.pos = pos;
          it.second.state = VISABLE_STATE::HIDDEN;
        } else {
          /// it.second.state = it.second.state;
        }
      }
    }
  }
};

}  // namespace log_detail
}  // namespace lee
#endif
