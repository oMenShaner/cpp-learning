#pragma once 
#include <iostream>
#include <assert.h>

using std::istream;
using std::ostream;

class Date
{
  public:
    int getMonthDay(const int year, const int month) const; 
    void Print() const;
    
    Date(int year = 1970, int month = 1, int day = 1);
    Date(const Date& d);
    ~Date();
    Date* operator&();
    const Date* operator&() const;

    Date& operator=(const Date& d);
    Date& operator+=(int day);
    Date operator+(int day) const;
    Date& operator-=(int day);
    Date operator-(int day) const;

    Date& operator++();
    Date operator++(int);
    Date& operator--();
    Date operator--(int);

    bool operator>(const Date& d) const;
    bool operator==(const Date& d) const;
    bool operator>=(const Date& d) const;
    bool operator<(const Date& d) const;
    bool operator<=(const Date& d) const;
    bool operator!=(const Date& d) const;
    int operator-(const Date& d) const;

friend ostream& operator<<(ostream& out, const Date& d);
friend istream& operator>>(istream& in, Date& d);
  private:
    int _year;
    int _month;
    int _day;
};
    
ostream& operator<<(ostream& out, const Date& d);
istream& operator>>(istream& in, Date& d);
