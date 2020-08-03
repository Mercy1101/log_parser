/// Copyright (c) 2019,2020 Lijiancong. All rights reserved.
///
/// Use of this source code is governed by a MIT license
/// that can be found in the License file.

#include "log_parser/log_info.hpp"
#include <string>
#include <catch2/catch.hpp>

TEST_CASE("log_info construct test", "[my_log][log_info]") {
  std::string str(
      "[2020-07-22 20:43:36.931] [trace] trace 15 <In Function: main, File: "
      "main.cc, Line: 20, PID: 15808>");
  lee::log_info temp(str);
  REQUIRE(temp.get_level() == "trace");
  REQUIRE(temp.get_time_milli_sec() == 1595421816931);
  REQUIRE(temp.get_log() == "trace 15");
  auto tuple = std::make_tuple("main", "main.cc", 20, 15808);
  REQUIRE(temp.get_location() == tuple);
}