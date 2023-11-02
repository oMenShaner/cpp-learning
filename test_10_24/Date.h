#pragma once 
#include <iostream>
#include <assert.h>

class Date
{
  public:
    int getMonthDay(int year, int month);
    void Print();
    
    Date(int year = 1970, int month = 1, int day = 1);
    Date(const Date& d);
    ~Date();
    
    Date& operator=(const Date& d);
    Date& operator+=(int day);
    Date operator+(int day);
    Date& operator-=(int day);
    Date operator-(int day);

    Date& operator++();
    Date operator++(int);
    Date& operator--();
    Date operator--(int);

    bool operator>(const Date& d);
    bool operator==(const Date& d);
    bool operator>=(const Date& d);
    bool operator<(const Date& d);
    bool operator<=(const Date& d);
    bool operator!=(const Date& d);
    int operator-(const Date& d);
  private:
    int _year;
    int _month;
    int _day;
};
