/// Copyright (c) 2019,2020 Lijiancong. All rights reserved.
///
/// Use of this source code is governed by a MIT license
/// that can be found in the License file.

/// @file   file_helper.hpp
/// @brief  文件读取辅助类
///
/// @author lijiancong, pipinstall@163.com
/// @date   2020-07-23 20:13:41

#ifndef INCLUDE_FILE_HELPER_HPP_
#define INCLUDE_FILE_HELPER_HPP_

#include <fstream>
#include <iostream>
#include <regex>
#include <vector>

namespace lee {
inline namespace log_detail {
class file_helper {
 public:
  file_helper() {}
  /// @name     read
  /// @brief    读取文件中的内容到容器中
  ///
  /// @param    path  [in]  文件路径名
  /// @param    vec   [out] 文件内容存储容器
  ///
  /// @return   读取成功或者失败
  ///
  /// @author   Lijiancong, pipinstall@163.com
  /// @date     2020-07-23 19:47:54
  /// @warning  线程不安全
  static bool read(const std::string& path, std::vector<std::string>* vec) {
    std::ifstream f(path);
    if (!f) {
      return false;
    }
    char buffer[256 * 2] = {0};
    while (!f.eof()) {
      f.getline(buffer, 1024);  //读入每行
      vec->emplace_back(std::string(buffer));
    }
    f.close();

    return true;
  }

  /// @name     filter
  /// @brief    用于过滤无效的日志
  ///
  /// @param    vec  [out]
  ///
  /// @return   NONE
  ///
  /// @author   lijiancong, pipinstall@163.com
  /// @date     2020-08-04 08:18:09
  /// @warning  线程不安全
  static void filter(std::vector<std::string>* vec) {
    /// 正则匹配 \[.*\].*\[.*\].*<.*>
    std::regex e("\\[.*\\].*\\[.*\\].*<.*>");
    vec->erase(std::remove_if(vec->begin(), vec->end(),
                              [&](const std::string& it) {
                                return !std::regex_match(it, e);
                              }),
               vec->end());
  }
};
}  // namespace log_detail
}  // namespace lee
#endif  // INCLUDE_FILE_HELPER_HPP_
