#include "Date.h"

using namespace std;

int Date::getMonthDay(const int year, const int month) const
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

void Date::Print() const
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

Date* Date::operator&()
{
    return this;
}

const Date* Date::operator&() const
{
    return this;
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

Date Date::operator+(int day) const
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
    
Date Date::operator-(int day) const
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
  *this -= 1;

  return temp;
}

bool Date::operator>(const Date& d) const
{
  if (_year > d._year)
    return true;
  else if (_year == d._year && _month > d._month)
    return true;
  else if (_year == d._year && _month == d._month && _day > d._day)
    return true;

  return false;
}

bool Date::operator==(const Date& d) const
{
  return _year == d._year &&
      _month == d._month &&
      _day == d._day;
}
    
bool Date::operator>=(const Date& d) const
{
  return (*this > d) || (*this == d);
}
   
bool Date::operator<(const Date& d) const
{
  return !(*this >= d);
}

bool Date::operator<=(const Date& d) const
{
  return (*this < d) || (*this == d);
}

bool Date::operator!=(const Date& d) const
{
  return !(*this == d);
}
    
//int Date::operator-(const Date& d)
//{
//  // 左大右小 flag = 1
//  int flag = 1;
//  Date max(*this);
//  Date min(d);
//  
//  if (max < min)
//  {
//    min = *this;
//    max = d;
//    flag = -1;
//  }
//
//  int n = 0;
//  while (min < max)
//  {
//    min++;
//    n++;
//  }
//  
//  return n * flag;
//}
//

int Date::operator-(const Date& d) const
{
  Date d1(_year, 1, 1);
  Date d2(d._year, 1, 1);

  // 算出日的差距
  int diff = (_day - 1) - (d._day - 1);

  // 加上月份的差距
  int i = 1;
  for (i = 1; i < _month; i++)
  {
    diff += getMonthDay(_year, i);
  }

  for (i = 1; i < d._month; i++)
  {
    diff -= getMonthDay(d._year, i);
  }
 
  // 加上年的差距
  int flag = 1;
  int max = _year;
  int min = d._year;
  if (max < min)
  {
    max = d._year;
    min = _year;
    flag = -1;
  }
 
  while (min < max)
  {
    if ((min%4==0 && min%100!=0) || (min%400==0))
    {
      diff += flag * 366;
    }
    else 
    {
      diff += flag * 365;
    }
    min++;
  }

  return diff;
}

ostream& operator<<(ostream& out, const Date& d)
{
    out << d._year << '-' << d._month << '-' << d._day; 
}

istream& operator>>(istream& in, Date& d)
{
    in >> d._year >> d._month >> d._day;
}
