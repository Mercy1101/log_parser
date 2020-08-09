/// Copyright (c) 2019,2020 Lijiancong. All rights reserved.
///
/// Use of this source code is governed by a MIT license
/// that can be found in the License file.

/// @file   data_struct_define.hpp
/// @brief  文件读取辅助类
///
/// @author lijiancong, pipinstall@163.com
/// @date   2020-07-23 20:13:41

#ifndef INCLUDE_DATA_STRUCT_DEFINE_HPP_
#define INCLUDE_DATA_STRUCT_DEFINE_HPP_

#include <string>
#include <utility>
#include <vector>


namespace lee {
inline namespace log_detail {
// folder separator
#ifdef _WIN32
static const char folder_sep = '/';
#else
constexpr static const char folder_sep = '/';
#endif

class log_info;

/// @name     VISABLE_STATE
/// @brief    用于记录日志可不可见
///
/// @author   Lijiancong, pipinstall@163.com
/// @date     2020-08-04 20:01:40
/// @warning  线程不安全
enum VISABLE_STATE : int {
  HIDDEN = 0,     ///< 隐藏状态
  DEFAULT = 1,    ///< 默认状态
  VISABLE = 2,    ///< 可见状态
  HIGHLIGHT = 3,  ///< 高亮状态
};

/// 用于存放过滤条件的vector
using cond = std::pair<std::string, VISABLE_STATE>;
using cond_vec = std::vector<cond>;
/// 用于保存高亮文本的坐标
using highlight_pos = std::pair<size_t, size_t>;
struct log_info_state {
  VISABLE_STATE state = VISABLE_STATE::DEFAULT;
  highlight_pos pos{0, 0};
};

using log_view = std::pair<std::reference_wrapper<log_info>, log_info_state>;
using log_view_vec = std::vector<log_view>;

/* 用于日志的排序 */
enum SORT_KINDS : int {
  TIME,   ///< 以时间顺序排序
  INDEX,  ///< 以日志出现顺序排序
  LEVEL,  ///< 以日志等级顺序排序
};
}  // namespace data_struct
}  // namespace lee

#endif  // INCLUDE_DATA_STRUCT_DEFINE_HPP_
