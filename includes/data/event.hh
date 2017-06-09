#ifndef EVENT_HH
#define EVENT_HH

#include "data/time.hh"
#include <memory>

class Event{
private:
  Time timestamp;
  std::string user;
  std::string status;

  Event & affect(const Event &);
public:
  Event();

  Event(const Event&);
  Event(std::string);

  Event(std::string,
	unsigned long,
	std::string);
  
  unsigned long getTimestamp();
  unsigned long getDailyTime();
  std::shared_ptr<Time> getTime();

  std::string getStatus();
  std::string getUser();
  bool equals(Event);
  std::string toString();
  //Event& operator=(const Event &);
  
};

#endif // EVENT_HH
