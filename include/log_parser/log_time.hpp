/// Copyright (c) 2019,2020 Lijiancong. All rights reserved.
///
/// Use of this source code is governed by a MIT license
/// that can be found in the License file.

/// @file   log_time.hpp
/// @brief  用于保存日志时间的数据结构
///
/// @author lijiancong, pipinstall@163.com
/// @date   2020-08-02 17:01:35

#ifndef INCLUDE_LOG_PARSER_LOG_TIME_HPP_
#define INCLUDE_LOG_PARSER_LOG_TIME_HPP_

#include <cassert>
#include <time.h>
#include <exception>
#include <string>
#include <vector>

namespace lee {
inline namespace log_detail {
/// @name     log_time
/// @brief    用于保存日志中的时间
///
/// @author   Lijiancong, pipinstall@163.com
/// @date     2020-08-01 17:35:14
/// @warning  线程不安全
class log_time {
 public:
  log_time(std::string s) {
    if (s.empty()) {
      return;
    }
    s = s.substr(1, s.size() - 2);
    time_str_ = s;
    auto vec = set(s);
    if (vec.size() != 7) {
      assert(false && "error param in log_time");
    }
    year_ = vec.at(0);
    mouth_ = vec.at(1);
    day_ = vec.at(2);
    hour_ = vec.at(3);
    min_ = vec.at(4);
    sec_ = vec.at(5);
    millisec_ = vec.at(6);
    time_stamp_ =
        get_specific_timestamp(year_, mouth_, day_, hour_, min_, sec_);
    time_stamp_millisec_ = time_stamp_ * 1000 + millisec_;
  }
  log_time() : log_time("") {}

  /// 2020-08-02 15:40:35.783 => {2020, 8, 2, 15, 40, 35, 783}
  std::vector<int> set(const std::string& s) {
    auto date = s.substr(0, s.find_first_of(' '));
    auto date_vec = get_date(date);

    auto begin = s.find_first_of(' ') + 1;
    auto end = s.find_first_of('.');
    auto time = s.substr(begin, end - begin);
    auto time_vec = get_time(time);

    auto milli_sec_t = get_millisec(s.substr(s.find_first_of('.') + 1));

    std::vector<int> res;
    res.reserve(7);
    res.insert(res.end(), date_vec.begin(), date_vec.end());
    res.insert(res.end(), time_vec.begin(), time_vec.end());
    res.push_back(milli_sec_t);

    return res;
  }
  int get_year() const { return year_; }
  int get_mouth() const { return mouth_; }
  int get_day() const { return day_; }
  int get_hour() const { return hour_; }
  int get_min() const { return min_; }
  int get_sec() const { return sec_; }
  int get_millisec() const { return millisec_; }
  time_t get_time_stamp() const { return time_stamp_; }
  time_t get_time_stamp_millisec() const { return time_stamp_millisec_; }
  std::string get_time_str() const { return time_str_; }

 private:
  int year_ = 0;
  int mouth_ = 0;
  int day_ = 0;
  int hour_ = 0;
  int min_ = 0;
  int sec_ = 0;
  int millisec_ = 0;
  time_t time_stamp_ = 0;
  time_t time_stamp_millisec_ = 0;
  std::string time_str_;

  std::vector<int> get_date(const std::string& date) {
    size_t begin = 0;
    auto end = date.find_first_of('-');
    int year = std::stoul(date.substr(begin, end));
    begin = end + 1;
    end = date.find_first_of('-', begin);
    int mouth = std::stoul(date.substr(begin, end));
    begin = end + 1;
    int day = std::stoul(date.substr(begin));
    if (confirm_date_valid(year, mouth, day)) {
      return std::vector<int>{year, mouth, day};
    } else {
      throw("invalid date param");
    }
  }

  std::vector<int> get_time(const std::string& time) {
    size_t begin = 0;
    auto end = time.find_first_of(':');
    auto hour = std::stoi(time.substr(begin, end));
    begin = end + 1;
    end = time.find_first_of(':', begin);
    auto min = std::stoi(time.substr(begin, end));
    begin = end + 1;
    end = std::string::npos;
    auto sec = std::stoi(time.substr(begin, end));
    if (confirm_time_valid(hour, min, sec)) {
      return std::vector<int>{hour, min, sec};
    } else {
      throw("invalid time param");
    }
  }
  int get_millisec(const std::string& millisec) {
    auto res = std::stoi(millisec);
    if (confirm_milli_valid(res)) {
      return res;
    } else {
      throw("invalid millisec");
    }
  }

  bool confirm_date_valid(const int year, const int mouth, const int day) {
    if (year < 1900 || year > 2070) {
      return false;
    }
    if (mouth > 12 || mouth < 1) {
      return false;
    }
    if (day < 1 || day > 31) {
      return false;
    }
    return true;
  }
  bool confirm_time_valid(const int hour, const int min, const int sec) {
    if (hour > 23 || hour < 0) {
      return false;
    }
    if (min > 59 || min < 0) {
      return false;
    }
    if (sec > 59 || sec < 0) {
      return false;
    }
    return true;
  }
  bool confirm_milli_valid(const int res) {
    if (res > 999 || res < 0) {
      return false;
    }
    return true;
  }
  /// @name     get_specific_timestamp
  /// @brief    获取特定日期的时间戳
  ///
  /// @param    year  [in]
  /// @param    mouth [in]
  /// @param    day   [in]
  /// @param    hour  [in]
  /// @param    min   [in]
  /// @param    sec   [in]
  ///
  /// @return   特定日期时间戳
  ///
  /// @author   Lijiancong, pipinstall@163.com
  /// @date     2020-08-02 15:47:05
  /// @warning  线程不安全
  inline time_t get_specific_timestamp(const int year, const int mouth,
                                       const int day, const int hour,
                                       const int min, const int sec) {
    tm time;
    time.tm_year = year - 1900;
    time.tm_mon = mouth - 1;
    time.tm_mday = day;
    time.tm_hour = hour;
    time.tm_min = min;
    time.tm_sec = sec;

    return mktime(&time);
  }
};
}  // namespace log_detail
}  // namespace lee
#endif  // INCLUDE_LOG_PARSER_LOG_TIME_HPP_
