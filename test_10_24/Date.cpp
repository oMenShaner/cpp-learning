#include "Date.h"

using namespace std;

int Date::getMonthDay(int year, int month)
{
  assert(year>=1 && month>=1 && month<=12);

  int day[13] = {0,31,28,31,30,31,30,31,31,30,31,30,31};

  // 如果是二月且是闰年
  if (month == 2 && (((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0)))
  {
    return 29;
  }

  return day[month];
}

void Date::Print()
{
  cout << _year << '-' << _month << '-' << _day << endl;
}
    
Date::Date(int year, int month, int day)
{
  _year = year;
  _month = month;
  _day = day;
  
  // 如果日期非法, 打印并提示
  if (_year < 1 ||
      _month < 1 || _month > 12 ||
      _day < 1 || _day > getMonthDay(_year, _month))
  {
    Print();
    cout << "日期非法" << endl;
  }
}

Date::Date(const Date& d)
{
  _year = d._year;
  _month = d._month;
  _day = d._day;
}

Date::~Date()
{
  _year = _month = _day = 0;
}
    
Date& Date::operator=(const Date& d)
{
  // 如果赋值自己本身, 直接返回自身
  if (&d == this)
  {
    return *this;
  }

  _year = d._year;
  _month = d._month;
  _day = d._day;

  // *this就是类对象
  return *this;
}

Date& Date::operator+=(int day)
{
  // 如果 day 是负数, 直接进行-=
  if (day < 0)
  {
    return (*this -= -day);
  }

  _day += day;
  // 如果日超出则进月份
  while(_day > getMonthDay(_year, _month))
  {
    _day -= getMonthDay(_year, _month);
    ++_month;
    // 如果月超出则进年份
    if (_month == 13)
    {
      ++_year;
      _month = 1;
    }
  }

  return *this;
}

Date Date::operator+(int day)
{
  Date temp(*this);
  temp += day;

  return temp;
}
   
Date& Date::operator-=(int day)
{
  // 如果day<0, 直接调用+=
  if (day < 0)
  {
    return (*this += -day);
  }

  _day -= day;
  // 如果日为负向前一个月得到当月日
  while (_day <= 0)
  {
    --_month;
    // 如果月为0, 向前退一年
    if (_month == 0)
    {
      --_year;
      _month = 12;
    }
    _day += getMonthDay(_year, _month);
  }

  return *this;
}
    
Date Date::operator-(int day)
{
  Date temp(*this);
  temp -= day;

  return temp;
}

Date& Date::operator++()
{
  *this += 1;

  return *this;
}

Date Date::operator++(int)
{
  Date temp(*this);
  *this += 1;

  return temp;
}

Date& Date::operator--()
{
  *this -= 1;

  return *this;
}

Date Date::operator--(int)
{
  Date temp(*this);
  *this += 1;

  return temp;
}

bool Date::operator>(const Date& d)
{
  if (_year > d._year)
    return true;
  if (_month > d._month)
    return true;
  if (_day > d._day)
    return true;

  return false;
}

bool Date::operator==(const Date& d)
{
  return _year == d._year &&
      _month == d._month &&
      _day == d._day;

}
    
bool Date::operator>=(const Date& d)
{
  return (*this > d) || (*this == d);
}
   
bool Date::operator<(const Date& d)
{
  return !(*this >= d);
}

bool Date::operator<=(const Date& d)
{
  return (*this < d) || (*this == d);
}

bool Date::operator!=(const Date& d)
{
  return !(*this == d);
}
    
//int operator-(const Date& d)
