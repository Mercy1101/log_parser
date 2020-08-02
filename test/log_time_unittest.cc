/// Copyright (c) 2019,2020 Lijiancong. All rights reserved.
///
/// Use of this source code is governed by a MIT license
/// that can be found in the License file.

#include "log_parser/log_time.hpp"

#include <catch2/catch.hpp>

TEST_CASE("log_time construct test", "[my_log][log_time]") {
  lee::log_time time("[2020-08-02 15:40:35.783]");
  REQUIRE(time.get_day() == 2);
  REQUIRE(time.get_hour() == 15);
  REQUIRE(time.get_millisec() == 783);
  REQUIRE(time.get_min() == 40);
  REQUIRE(time.get_mouth() == 8);
  REQUIRE(time.get_sec() == 35);
  REQUIRE(time.get_time_stamp() == 1596354035);
  REQUIRE(time.get_time_stamp_millisec() == 1596354035783);
  REQUIRE(time.get_year() == 2020);
}

TEST_CASE("log_time empty construct test", "[my_log][log_time]") {
  lee::log_time time;
  REQUIRE(time.get_day() == 0);
  REQUIRE(time.get_hour() == 0);
  REQUIRE(time.get_millisec() == 0);
  REQUIRE(time.get_min() == 0);
  REQUIRE(time.get_mouth() == 0);
  REQUIRE(time.get_sec() == 0);
  REQUIRE(time.get_time_stamp() == 0);
  REQUIRE(time.get_time_stamp_millisec() == 0);
  REQUIRE(time.get_year() == 0);
}
