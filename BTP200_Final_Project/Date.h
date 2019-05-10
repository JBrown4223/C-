// Final Project Milestone 1
// Version 1.0
// Date: March-19-2018
// Author: Jonathan Brown
// Description

#ifndef AMA_DATE_H
#define AMA_DATE_H
#include <iostream>

#define NO_ERROR 0    //No error - the date is valid
#define CIN_FAILED 1  //istream failed on information entry
#define YEAR_ERROR 2  //Year value is invalid
#define MON_ERROR  3  // Month value is invalid
#define DAY_ERROR 4   //Day value is invalid


namespace AMA {
 const int min_year = 2000;
 const int max_year = 2030;
  
 class Date {
    
    int m_year, m_month, m_day, m_error, m_comparator;
    int mdays(int, int)const;
    void errCode(int errorCode);

  public:
    Date();
    Date(int, int, int);
    bool isEmpty() const;
    bool operator==(const Date& rhs) const;
    bool operator!=(const Date& rhs) const;
    bool operator<(const Date& rhs) const;
    bool operator>(const Date& rhs) const;
    bool operator<=(const Date& rhs) const;
    bool operator>=(const Date& rhs) const;
    int errCode() const;
    bool bad() const;

    std::istream& read(std::istream& istr);
    std::ostream& write(std::ostream& ostr) const;
  
  };

  std::ostream& operator<<(std::ostream& out, const Date& date);
  std::istream& operator>>(std::istream& in, Date& date);






};
#endif