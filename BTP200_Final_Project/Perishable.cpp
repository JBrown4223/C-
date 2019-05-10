//BTP_Final_Project
// Milestone 5
//Name: Jonathan Brown
//Date: April 16, 2018
// Student Number: 135918175

#include <iostream>
#include <fstream>
#include "Product.h"
#include "Perishable.h"
#include "Date.h"

using namespace std;

namespace AMA{
	Perishable::Perishable(char type) : Product(type)
	{
	}

	std::fstream & Perishable::store(std::fstream & file, bool newLine) const{
		Product::store(file, false);
		file <<","<< m_expiration << endl;
		return file;
	}

	std::fstream & Perishable::load(std::fstream & file){
		Product::load(file);
		m_expiration.read(file);
		file.ignore();
		return file;
	}

	std::ostream & Perishable::write(std::ostream & os, bool linear) const{
		Product::write(os, linear);
		if (isClear() && !isEmpty()){
			if (linear == false)
				os << "\n Expiry Date: " << expiry();
			else
			 os << expiry();
		}
		return os;
	}
	std::istream & Perishable::read(std::istream & is){
		Product::read(is);
		if (em.isClear()){
			cout << " Expiry date (YYYY/MM/DD): ";
			m_expiration.read(is);
		}

		if (m_expiration.errCode() == CIN_FAILED){
			em.clear();
			em.message("Invalid Date Entry");
		}

		if (m_expiration.errCode() == YEAR_ERROR)
			
			em.message("Invalid Year in Date Entry");

		if (m_expiration.errCode() == MON_ERROR){
			em.clear();
			em.message("Invalid Month in Date Entry");
		}

		if (m_expiration.errCode() == DAY_ERROR){
			em.clear();
			em.message("Invalid Day in Date Entry");
		}

		if (m_expiration.errCode())
			is.setstate(std::ios::failbit);

		if (m_expiration.errCode() != CIN_FAILED && m_expiration.errCode() != YEAR_ERROR && 
		m_expiration.errCode() != MON_ERROR && m_expiration.errCode() != DAY_ERROR)
			em.clear();

		return is;
	}

	const Date & Perishable::expiry() const{
		return m_expiration;
	}

}