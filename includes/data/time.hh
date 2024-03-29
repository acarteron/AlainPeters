/**
 * \class Time
 *
 * \brief 
 *
 * \note 
 *
 * \author : Adrien Carteron$
 *
 * \version : 0.1 $
 *
 * \date : mer. févr. 18 10:30:19 CET 2015 $
 *
 * Contact: acarteron@openmailbox.org
 *
 * Created on: mer. févr. 18 10:30:19 CET 2015
 *
 *
 */

#ifndef TIME_HH
#define TIME_HH

#include <string>
#include <fstream>
#include <ctime>

class Time{

private:
  int msec;
  long long timestamp;
  long long dailytimstmp;

  std::tm timestmp;
 
  void parse(std::string);
  void parse(std::string,std::string);

  bool greater(const Time&);
  bool less(const Time&);
  bool equal(const Time&);
  bool greater_equal(const Time&);
  bool less_equal(const Time&);
  Time& affect(const Time &);

  long long plus(const Time&);
  long long minus(const Time&);

  void to_timestamp();
  void to_time();
public:
  /** \brief Void constructor
   * 
   * add desc 
   * 
   */
  Time();
  Time(const Time &);
  Time(std::string );
  Time(std::string ,std::string);
  Time(std::time_t);
  Time(long long);
  /** \brief Destructor
   * 
   * add desc
   *
   */
  ~Time();

  long long get_timestamp();
  long long get_timestamp_ms();
  long long get_daily_timestamp();
  long long get_day_as_timestamp();
  
  std::string to_string()const;
  std::string to_string(int)const;

  
  bool operator>(const Time& );
  bool operator<(const Time& );
  bool operator==(const Time& );
  bool operator>=(const Time& );
  bool operator<=(const Time& );
  Time& operator=(const Time& );
  Time& operator=(std::string );
  long long operator+(const Time& );
  long long operator-(const Time& );
  Time& operator+=(const Time& );
  Time& operator-=(const Time& );

  bool is_null();
  bool is_null(Time&);
  
  long long minus_day_(const Time& );
 
  int date_compare(const Time&);
  
  std::string get_day_str() const;
  std::string get_hour_str()const;
  
  friend std::ostream& operator<<(std::ostream& out, const Time& a);
  
};



#endif // TIME_HH
