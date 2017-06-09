#include "data/time.hh"
#include <Utils.hpp>
#include <cmath>
#include <cfenv>
#include <iomanip>
#include <sstream>
#include <iostream>
#include <chrono>
#include "Utils.hpp"

Time::Time(){
  parse("1970-01-01 01:00:00.000");
}
Time::Time(const Time & time){
  affect(time);
}
Time::Time(std::string time_full){
  parse(time_full);
}
Time::Time(std::string days,std::string times){
  parse(days,times);
}
Time::Time(std::time_t timestmp_){
  timestmp=*std::localtime(&timestmp_);
  to_timestamp();
  msec=0;
}
Time::Time(unsigned long timestamp_){
  msec=timestamp_%1000;
  time_t timestmp_=timestamp_/1000;
  timestmp=*std::localtime(&timestmp_);
  to_timestamp();
}
Time::~Time(){
}
unsigned long Time::get_timestamp(){
  return timestamp;
}
unsigned long Time::get_timestamp_ms(){
  return timestamp*1000+msec;
}

bool Time::greater(const Time& a){
  return timestamp>a.timestamp;
}
bool Time::less(const Time& a){
  return timestamp<a.timestamp;
}
bool Time::equal(const Time& a){
  if(timestamp==a.timestamp)
    return msec==a.msec;
  return false;
}
bool Time::greater_equal(const Time& a){
  if(timestamp==a.timestamp)
    return msec>=a.msec;
  return timestamp>=a.timestamp;
}
bool Time::less_equal(const Time& a){
  if(timestamp==a.timestamp)
    return msec<=a.msec;
  return timestamp<=a.timestamp;
}

Time& Time::affect(const Time& time){
  dailytimstmp = time.dailytimstmp;
  timestmp.tm_hour = time.timestmp.tm_hour;
  timestmp.tm_min = time.timestmp.tm_min;
  timestmp.tm_sec = time.timestmp.tm_sec;
  timestmp.tm_year = time.timestmp.tm_year;
  timestmp.tm_mon = time.timestmp.tm_mon ;
  timestmp.tm_mday = time.timestmp.tm_mday;
  timestmp.tm_isdst=-1;
  timestamp=time.timestamp;
  msec=time.msec;
  return *this;
}

unsigned long Time::minus(const Time& a){
  if(timestamp>a.timestamp)
    return (timestamp-a.timestamp);
  else return (a.timestamp-timestamp);
}
unsigned long Time::minus_day_(const Time& a){
  if(timestamp>a.timestamp)
    return (timestamp-a.timestamp)/3600/24;
  else
    return (a.timestamp-timestamp)/3600/24;
}

void Time::to_timestamp(){
  dailytimstmp = timestmp.tm_hour*3600+timestmp.tm_min*60+timestmp.tm_sec;
  std::time_t truc=mktime(&timestmp);
  timestamp=truc;
}
void Time::to_time(){}

void Time::parse(std::string time_full){
  std::istringstream ss(time_full);
  ss >> std::get_time(&timestmp, "%Y-%m-%d %H:%M:%S");
  size_t finsec=time_full.find_last_of(".");
  if(finsec==std::string::npos){
    msec=0;
  }else{
    msec=Utils::stringTo<unsigned int>(time_full.substr(finsec,
							time_full.size()-finsec));
  }
  timestmp.tm_isdst=-1;
  to_timestamp();  
}
void Time::parse(std::string days,std::string times){
  days.append(" ");
  days.append(times);
  parse(days);
}
unsigned long Time::get_daily_timestamp(){
  return dailytimstmp;
}
unsigned long Time::get_day_as_timestamp(){
  Time time_(get_day_str(),"00:00:00.000");
  return time_.get_timestamp_ms();
}
std::string Time::to_string(unsigned int changer)const{
  std::string out="";
  switch(changer){
  case 0:
    out=get_day_str();
    out+=" ";
    out+=get_hour_str();
    break;
  case 1:
    out=Utils::toString<unsigned long>(timestamp);
    break;
  default:
    out=Utils::toString<unsigned long>(timestamp*1000+msec);
    break;
  }
  return out;
}

std::string Time::to_string()const {
  std::string out=Utils::toString<unsigned long>(timestamp*1000+msec);
  return out;
}
std::string Time::get_day_str() const{
  char buffer_date[80];
  strftime(buffer_date,80,"%F" ,&timestmp);
  std::string day(buffer_date);
  return day;
}
std::string Time::get_hour_str() const{
  char buffer_time[80];
  strftime(buffer_time,80,"%T",&timestmp);
  std::string hour(buffer_time);
  return hour;
}

bool Time::operator>(const Time& a){
  return greater(a);
}
bool Time::operator<(const Time& a){
  return less(a);
}
bool Time::operator==(const Time& a){
  return equal(a);
}
bool Time::operator>=(const Time& a){
  return greater_equal(a);
}
bool Time::operator<=(const Time& a){
  return less_equal(a);
}
Time& Time::operator=(const Time& a){
  return affect(a);
}
Time& Time::operator=(std::string time_full){
  const Time a(time_full);
  return affect(a);
}
unsigned long Time::operator-(const Time& a){
  return minus(a);
}

std::ostream& operator<<(std::ostream& out, const Time& a){
  out<<a.to_string();
  return out;
}

bool Time::is_null(){
  Time a;
  if(timestamp==a.timestamp)
    return msec<=a.msec;
  return timestamp<=a.timestamp;
}
bool Time::is_null(Time & a){
  if(timestamp==a.timestamp)
    return msec<=a.msec;
  return timestamp<=a.timestamp;
}

int Time::date_compare(const Time & time_){
  if(timestmp.tm_year == time_.timestmp.tm_year)
    if(timestmp.tm_mon == time_.timestmp.tm_mon)
      if(timestmp.tm_mday == time_.timestmp.tm_mday)
	return 0;
      else{
	if(timestmp.tm_mday < time_.timestmp.tm_mday)
	  return -1;
	return 1;
      }
    else{
      if(timestmp.tm_mon < time_.timestmp.tm_mon)
	return -1;
      return 1;
    }
  else{
    if(timestmp.tm_year < time_.timestmp.tm_year)
      return -1;
    return 1;
  }
}
