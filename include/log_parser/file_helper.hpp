///////// ///////// ///////// ///////// ///////// ///////// ///////// /////////
/// Copyright (c) 2019,2020 Lijiancong. All rights reserved.
///
/// Use of this source code is governed by a MIT license
/// that can be found in the License file.
///
/// @file   file_helper.hpp
/// @brief  文件辅助类
///
/// @author lijiancong, pipinstall@163.com
/// @date   2020-07-23 20:13:41
///////// ///////// ///////// ///////// ///////// ///////// ///////// /////////

#ifndef INCLUDE_FILE_HELPER_HPP_
#define INCLUDE_FILE_HELPER_HPP_

#include <fstream>
#include <iostream>

namespace lee {
inline namespace log {
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
  bool read(const std::string& path, std::vector<std::string>* vec) {
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
};
}  // namespace log
}  // namespace lee

#endif  // INCLUDE_FILE_HELPER_HPP_
