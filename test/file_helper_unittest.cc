/// Copyright (c) 2019,2020 Lijiancong. All rights reserved.
///
/// Use of this source code is governed by a MIT license
/// that can be found in the License file.

#include "log_parser/file_helper.hpp"

#include <catch2/catch.hpp>
#include <string>
#include <vector>

static char ENTER_SPLICE = '\n';
TEST_CASE("file_helper简单测试", "[log_parser][file_helper]") {
  /// std::ofstream file("./detail_log.log");
  /// if (file) {
  ///   file << '\n';
  ///   file << "[2020-07-22 20:43:38.584] [debug] debug 732 "
  ///           "<In Function: main, Line: 23, PID: 15808>"
  ///        << ENTER_SPLICE;
  ///   file << "[2020-07-22 20:43:37.9] [trace] trace 90 <In Function: main, "
  ///           "Line: 20, PID: 15808>"
  ///        << ENTER_SPLICE;
  ///   file << "[2020-07-22 20:43:44.354] [info] info 688 <In Function: main, "
  ///           "Line: 26, PID: 15808>"
  ///        << ENTER_SPLICE;
  ///   file << "[2020-07-22 20:43:48.747] [warn] warn 379 <In Function: main, "
  ///           "Line: 29, PID: 15808>"
  ///        << ENTER_SPLICE;
  ///   file << "[2020-07-22 20:43:40.976] [error] error 606 <In Function: main,
  ///   "
  ///           "Line: 32, PID: 15808>"
  ///        << ENTER_SPLICE;
  ///   file << "[2020-07-22 20:43:46.199] [critical] critical 442 <In Function:
  ///   "
  ///           "main, Line: 35, PID: 15808>"
  ///        << ENTER_SPLICE;

  ///   file.close();
  /// }

  std::vector<std::string> vec;
  std::string path = "./test/detail_log.log";
  REQUIRE(lee::file_helper::read(path, &vec));

  std::vector<std::string> res{
      "[2020-07-22 20:43:38.584] [debug] debug 732 <In Function: main, File: "
      "main.cpp, Line: 23, PID: 15808>",
      "[2020-07-22 20:43:37.9] [trace] trace 90 <In Function: main, File: "
      "main.cpp, Line: 20, PID: 15808>",
      "[2020-07-22 20:43:44.354] [info] info 688 <In Function: main, File: "
      "main.cpp, Line: 26, PID: 15808>",
      "[2020-07-22 20:43:48.747] [warn] warn 379 <In Function: main, File: "
      "main.cpp, Line: 29, PID: 15808>",
      "[2020-07-22 20:43:40.976] [error] error 606 <In Function: main, File: "
      "main.cpp, Line: 32, PID: 15808>",
      "[2020-07-22 20:43:46.199] [critical] critical 442 <In Function: main, "
      "Line: 3"};
  REQUIRE(vec == res);
  lee::file_helper::filter(&vec);
  res.erase(res.begin());
  res.erase(std::prev(res.end()));
  REQUIRE(vec == res);
}