//BTP_Final_Project
// Milestone 5
//Name: Jonathan Brown
//Date: April 12, 2018
// Student Number: 135918175
#include <iostream>
#include "Date.h"

using namespace std;

namespace AMA {

 Date::Date(){
     m_year = 0;
     m_month = 0;
     m_day = 0;
     m_comparator = 0;
     errCode(NO_ERROR);
 }

 bool Date::isEmpty() const
	{
		if (m_year == 0 && m_month == 0 && m_day == 0 && m_comparator == 0)
			return true;
		else
			return false;
	}


 Date::Date(int year, int mon, int day){
     *this = Date();
        if (year >= min_year && year <= max_year) {
			if (mon >= 1 && mon <= 12) {
				if (day >= 1 && day <= mdays(mon, year)) {
					m_day = day;
					m_year = year;
					m_month = mon;
					m_comparator = year * 372 + mon * 13 + day;
					errCode(NO_ERROR);
				}
				else
					errCode(DAY_ERROR);
			}
			else
				errCode(MON_ERROR);
		}
		else
			errCode(YEAR_ERROR);
        

    }

  // number of days in month mon_ and year year_
 int Date::mdays(int mon, int year) const {
     int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31, -1 };
     int month = mon >= 1 && mon <= 12 ? mon : 13;
     month--;
     return days[month] + int((month == 1)*((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0));
    }
 
  void Date::errCode(int errorCode){
      m_error = errorCode; 
    }

  bool Date::bad() const {
      if((m_error == 0)){
          return true;
      } else {
          return false;
      }
    }
    bool Date::operator==(const Date& rhs) const
	{
		if (!isEmpty() && !rhs.isEmpty() && m_comparator == rhs.m_comparator)
			return true;
		else
			return false;
	}
	bool Date::operator!=(const Date & rhs) const
	{
		if (!isEmpty() && !rhs.isEmpty() && m_comparator != rhs.m_comparator)
			return true;
		else
			return false;
	}

	bool Date::operator<(const Date & rhs) const
	{
		if (!isEmpty() && !rhs.isEmpty() && m_comparator < rhs.m_comparator)
			return true;
		else
			return false;
	}

	bool Date::operator>(const Date & rhs) const
	{
		if (!isEmpty() && !rhs.isEmpty() && m_comparator > rhs.m_comparator)
			return true;
		else
			return false;
	}

	bool Date::operator<=(const Date & rhs) const
	{
		if (!isEmpty() && !rhs.isEmpty() && m_comparator <= rhs.m_comparator)
			return true;
		else
			return false;
	}

	bool Date::operator>=(const Date & rhs) const
	{
		if (!isEmpty() && !rhs.isEmpty() && m_comparator >= rhs.m_comparator)
			return true;
		else
			return false;
	}
    int Date::errCode() const
	{
		return m_error;
	}

    std::istream& Date::read(std::istream& istr) {
		int Year = 0, Mon = 0, Day = 0;

		istr >> Year;
		if (istr.get() != '/') {
			m_error = CIN_FAILED;
			return istr;
		}

		istr >> Mon;
		if (istr.get() != '/') {
			m_error = CIN_FAILED;
			return istr;
		}
		istr >> Day;
		*this = Date(Year, Mon, Day);
		return istr;
	}

    std::ostream& Date::write(std::ostream& ostr)const {

		cout.width(1);
		cout.fill('0');
		cout << m_year << '/';
		cout.width(2);
		cout.fill('0');
		cout << m_month << '/';
		cout.width('0');
		cout.width(2);
		cout << m_day;

		return ostr;
	}

	std::ostream & operator<<(std::ostream & out, const Date& date)
	{
		return date.write(out);	
	}

	std::istream & operator>>(std::istream & in, Date& date)
	{
		return date.read(in);
	}


};