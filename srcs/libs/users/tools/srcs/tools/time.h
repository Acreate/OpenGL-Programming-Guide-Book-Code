#ifndef TIME_H_H_HEAD__FILE__
#define TIME_H_H_HEAD__FILE__
#pragma once

#include "toolsNamespace.h"
#include <string>
#include <chrono>
class TOOLS_EXPORT cyl::tools::time {
public:
	using Ratio = std::ratio< 1, 10000000 >;
	using l_time_t = long long;
	using Duration = std::chrono::duration< l_time_t, Ratio >;
	using Clock = std::chrono::system_clock;
	using TimePoint = std::chrono::time_point< Clock >;
	/// @brief 获取格林时间到本地时间的相差-小时
	/// @return 相差小时
	static int getUtcToLocalAtHourSepTime( );
	/// @brief 时间数据格式化输出字符串 - utc 格式
	/// @brief %Y - xxxx 年
	/// @brief %m - xx 月
	/// @brief %d - xx 日
	/// @brief %H - xx 小时
	/// @brief %M - xx 分钟
	/// @brief %S - xx 秒
	/// @see std::put_time
	/// @param form_time_string 格式化字符串
	/// @param to_string_time 转换时间点
	/// @return 转换后的字符串
	static std::string toStdStringOnUTC( const std::string &form_time_string, const TimePoint &to_string_time );

	/// @brief 时间数据格式化输出字符串 - 本地格式
	/// @brief %Y - xxxx 年
	/// @brief %m - xx 月
	/// @brief %d - xx 日
	/// @brief %H - xx 小时
	/// @brief %M - xx 分钟
	/// @brief %S - xx 秒
	/// @param form_time_string 格式化字符串
	/// @param to_string_time 转换时间点
	/// @return 转换后的字符串
	static std::string toStringOnLocal( const std::string &form_time_string, const TimePoint &to_string_time );

	/// <summary>
	/// 比较一个时间，并且返回时间差
	/// </summary>
	/// <param name="left_date_time">被减数</param>
	/// <param name="right_date_time">减数</param>
	/// <returns>时间差</returns>
	static std::chrono::milliseconds compareDateTime( const TimePoint &left_date_time, const TimePoint &right_date_time ) {
		auto leftTimeSinceEpoch = std::chrono::duration_cast< std::chrono::milliseconds >( left_date_time.time_since_epoch( ) );
		auto rightTimeSinceEpoch = std::chrono::duration_cast< std::chrono::milliseconds >( right_date_time.time_since_epoch( ) );
		std::chrono::milliseconds stdMilliseconds = leftTimeSinceEpoch - rightTimeSinceEpoch;
		return stdMilliseconds;
	}
	/// @brief 从时间点上获取年份
	/// @param time_point 时间点
	/// @return 年份
	static l_time_t getYear( const TimePoint &time_point );
	/// @brief 从时间点上获取月份
	/// @param time_point 时间点
	/// @return 月份
	static l_time_t getMon( const TimePoint &time_point );
	/// @brief 从时间点上获取当前日
	/// @param time_point 时间点
	/// @return 月份中的日
	static l_time_t getDay( const TimePoint &time_point );
	/// @brief 从时间点上获取小时
	/// @param time_point 时间点
	/// @return 小时
	static l_time_t getHour( const TimePoint &time_point );
	/// @brief 从时间点上获取分钟
	/// @param time_point 时间点
	/// @return 分钟
	static l_time_t getMinute( const TimePoint &time_point );
	/// @brief 从时间点上获取秒
	/// @param time_point 时间点
	/// @return 秒
	static l_time_t getSecond( const TimePoint &time_point );
	/// @brief 从时间点上获取毫秒
	/// @param time_point 时间点
	/// @return 毫秒
	static l_time_t getMillisecond( const TimePoint &time_point );
};

#endif // TIME_H_H_HEAD__FILE__
