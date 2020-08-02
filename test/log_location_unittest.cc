/// Copyright (c) 2019,2020 Lijiancong. All rights reserved.
///
/// Use of this source code is governed by a MIT license
/// that can be found in the License file.

#include "log_parser/log_location.hpp"

#include <catch2/catch.hpp>


TEST_CASE("log_location construct test", "[my_log][log_location]") {
  lee::log_location location(
      "<In Function: main, File: main.cpp, Line: 20, PID: 15808>");
  REQUIRE(location.get_file_name() == "main.cpp");
  REQUIRE(location.get_function_name() == "main");
  REQUIRE(location.get_file_line() == 20);
  REQUIRE(location.get_thread_id() == 15808);
}

TEST_CASE("log_location empty construct test", "[my_log][log_location]") {
  lee::log_location location;
  REQUIRE(location.get_file_name() == "");
  REQUIRE(location.get_function_name() == "");
  REQUIRE(location.get_file_line() == 0);
  REQUIRE(location.get_thread_id() == 0);
}
