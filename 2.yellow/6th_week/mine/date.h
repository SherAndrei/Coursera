#pragma once
#include <iostream>
#include <string>

class Date {
 public:
    Date(int year = 1, int month = 1, int day = 1);

 public:
    int year()  const;
    int month() const;
    int day()   const;

    std::string to_string() const;

 public:
    bool operator == (const Date& other) const;
    bool operator != (const Date& other) const;
    bool operator <  (const Date& other) const;
    bool operator <= (const Date& other) const;
    bool operator >  (const Date& other) const;
    bool operator >= (const Date& other) const;
    Date operator =  (const Date& other);

    friend std::ostream& operator<<(std::ostream& out, const Date& date);

 private:
    int m_year;
    int m_month;
    int m_day;
};

Date ParseDate(std::istream& is);
