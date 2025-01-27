#include "time.h"
#include <string>
#include <iostream>
#include <filesystem>
#include <Windows.h>
#include <fstream>
#include <sstream>

int cyl::tools::time::getUtcToLocalAtHourSepTime( ) {
	time_t rawtime = std::time( nullptr );
	tm *lt = std::localtime( &rawtime );
	int ltHour = lt->tm_hour;
	tm *gt = std::gmtime( &rawtime );
	int gtHour = gt->tm_hour;
	int sepHour = ltHour - gtHour;
	return sepHour;
}
std::string cyl::tools::time::toStdStringOnUTC( const std::string &form_time_string, const TimePoint &to_string_time ) {
	std::time_t tt = Clock::to_time_t( to_string_time );
	std::tm tm = *std::gmtime( &tt ); //GMT (UTC)
	std::stringstream ss;
	ss << std::put_time( &tm, form_time_string.c_str( ) );
	return ss.str( );
}
std::string cyl::tools::time::toStringOnLocal( const std::string &form_time_string, const TimePoint &to_string_time ) {
	std::time_t tt = Clock::to_time_t( to_string_time );
	std::tm tm = *std::localtime( &tt ); //Locale time-zone, usually UTC by default.
	std::stringstream ss;
	ss << std::put_time( &tm, form_time_string.c_str( ) );
	return ss.str( );
}

cyl::tools::time::l_time_t cyl::tools::time::getYear( const TimePoint &time_point ) {
	const std::chrono::year_month_day ymd {std::chrono::floor< std::chrono::days >( time_point )};
	auto day = static_cast< int >( ymd.year( ) );
	return day;
}
cyl::tools::time::l_time_t cyl::tools::time::getMon( const TimePoint &time_point ) {
	const std::chrono::year_month_day ymd {std::chrono::floor< std::chrono::days >( time_point )};
	auto day = static_cast< unsigned >( ymd.month( ) );
	return day;
}
cyl::tools::time::l_time_t cyl::tools::time::getDay( const TimePoint &time_point ) {
	const std::chrono::year_month_day ymd {std::chrono::floor< std::chrono::days >( time_point )};
	auto day = static_cast< unsigned >( ymd.day( ) );
	return day;
}
#include <ctime>
cyl::tools::time::l_time_t cyl::tools::time::getHour( const TimePoint &time_point ) {
	TimePoint::duration duration = time_point.time_since_epoch( );
	auto durationCast = std::chrono::duration_cast< std::chrono::hours >( duration );
	int count = durationCast.count( );
	count = count % 24;
	return count + getUtcToLocalAtHourSepTime( );
}
cyl::tools::time::l_time_t cyl::tools::time::getMinute( const TimePoint &time_point ) {
	TimePoint::duration duration = time_point.time_since_epoch( );
	auto durationCast = std::chrono::duration_cast< std::chrono::milliseconds >( duration );
	std::chrono::hh_mm_ss tod( durationCast );
	auto minutes = tod.minutes( );
	return minutes.count( );
}
cyl::tools::time::l_time_t cyl::tools::time::getSecond( const TimePoint &time_point ) {
	TimePoint::duration duration = time_point.time_since_epoch( );
	auto durationCast = std::chrono::duration_cast< std::chrono::milliseconds >( duration );
	std::chrono::hh_mm_ss tod( durationCast );
	auto seconds = tod.seconds( );
	return seconds.count( );
}
cyl::tools::time::l_time_t cyl::tools::time::getMillisecond( const TimePoint &time_point ) {
	TimePoint::duration duration = time_point.time_since_epoch( );
	auto durationCast = std::chrono::duration_cast< std::chrono::milliseconds >( duration );
	return durationCast.count( ) % 1000;
}
