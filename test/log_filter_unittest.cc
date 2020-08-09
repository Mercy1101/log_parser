/// Copyright (c) 2019,2020 Lijiancong. All rights reserved.
///
/// Use of this source code is governed by a MIT license
/// that can be found in the License file.

#include "log_parser/log_filter.hpp"
#include "log_parser/data_struct_define.hpp"
#include "log_parser.hpp"

#include <catch2/catch.hpp>

TEST_CASE("log_filter 基类简单测试", "[log_parser][log_filter]") {
  std::string path = "./test/detail_log.log";
  lee::log_parser log(path);
  lee::log_filter_single filter(log.get_log_view_vec());

}