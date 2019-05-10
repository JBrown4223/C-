//BTP_Final_Project
// Milestone 5
//Name: Jonathan Brown
//Date: April 16, 2018
// Student Number: 135918175

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <cstring>
#include "Product.h"
#include "ErrorState.h"
using namespace std;
using namespace AMA;

namespace AMA{
	void Product::name(const char* name){
		int length = strlen(name);
		
		if (name != nullptr){
			this->m_productName = new char[length + 1];
			strcpy(m_productName, name);
		}
		else{
			delete[] m_productName;
		}
	}
	Product::Product(char type){
		m_type = type;
		m_productSku[0] = '\0';
		m_unitType[0] = '\0';
		m_productName = nullptr;
		m_onHand = 0;
		m_needed = 0;
		m_price = 0;
		m_taxable = true;
	}
	Product::Product(const char *sku, const char *address, const char *unit, 
	 int quantity, bool taxable, double beforeTax, int needed){
		strncpy(m_productSku, sku, max_sku_length);
		name(address);
		strncpy(m_unitType, unit, max_unit_length);
		m_onHand = quantity;
		m_taxable = taxable;
		m_price = beforeTax;
		m_needed = needed;
	}
	Product::~Product(){
		delete[]  m_productName;
	}
	
	Product::Product(const Product &P1){
		m_type = P1.m_type;
		strcpy(m_productSku, P1.m_productSku);
		strcpy(m_unitType, P1.m_unitType);
		m_price = P1.m_price;
		m_taxable = P1.m_taxable;
		m_needed = P1.m_needed;
		m_onHand = P1.m_onHand;
		if (P1.m_productName != nullptr) {
			m_productName = new char[max_name_length];
			for (int i = 0; i < max_name_length; ++i)
				m_productName[i] = P1.m_productName[i];
		}
		else {
			m_productName = nullptr;
		}
	}


	const char *Product::name() const{
		return ( m_productName[0] == '\0') ? nullptr :  m_productName;
	}
	const char *Product::sku() const{
		return m_productSku;
	}
	const char *Product::unit() const{
		return m_unitType;
	}
	bool Product::taxed() const{
		return m_taxable;
	}
	double Product::price() const{
		return m_price;
	}
	double Product::cost() const{
		return (m_taxable) ? price() * (tax_rate + 1) : price();
	}
	void Product::message(const char *addressError){
		em.message(addressError);
	}
	bool Product::isClear() const{
		return em.isClear();
	}
	Product &Product::operator=(const Product &P1){
		if (this != &P1){
			strncpy(m_productSku, P1.m_productSku, max_sku_length);
			m_type = P1.m_type;
			strncpy(m_unitType, P1.m_unitType, max_unit_length);
			m_price = P1.m_price;
			m_taxable = P1.m_taxable;
			m_needed = P1.m_needed;
			m_onHand = P1.m_onHand;
			delete[] m_productName;
			if (P1.m_productName != nullptr) {
				m_productName = new char[max_name_length];
				for (int i = 0; i < max_name_length; ++i)
					m_productName[i] = P1.m_productName[i];
			}
			else {
				m_productName = nullptr;
			}
		}
		return *this;
	}

	std::fstream& Product::store(std::fstream &file, bool newLine) const{
		file << m_type;
		file <<"," << m_productSku << "," << m_productName << "," 
		 << m_unitType<<"," << m_taxable <<","<< m_price <<","<< m_onHand << ","
		 << m_needed;
		if (newLine)
			file << endl;
		return file;
	}
	std::fstream& Product::load(std::fstream &file) {
		char sku[max_sku_length + 1];
		char name[max_name_length + 1];
		char unit[max_unit_length + 1];
		int  qty, needed;
		double price;
		char tax;
		bool taxable;

		if (file.is_open())
		{
			file.getline(sku, max_sku_length, ',');
			sku[strlen(sku)] = '\0';

			file.getline(name, max_name_length, ',');
			name[strlen(name)] = '\0';

			file.getline(unit, max_unit_length, ',');
			unit[strlen(unit)] = '\0';

			file >> tax;

			if (tax == '1')
				taxable = true;
			else if (tax == '0')
				taxable = false;

			file.ignore();

			file >> price;
			file.ignore();

			file >> qty;
			file.ignore();

			file >> needed;
			file.ignore();

			*this = Product(sku, name, unit, qty, taxable, price, needed);
		}

		return file;
	}
	std::ostream& Product::write(std::ostream& os, bool linear) const {
		if (!(em.isClear())){
			os << em.message();
		}

		else if (linear){
			os << setw(max_sku_length) << left << m_productSku << '|'
				<< setw(20) << left << m_productName << '|'
				<< setw(7) << right << fixed << setprecision(2) << cost() << '|'
				<< setw(4) << right << m_onHand << '|'
				<< setw(10) << left << m_unitType << '|'
				<< setw(4) << right << m_needed << '|';
		}
		else{
			os << " Sku: " << m_productSku << endl
				<< " Name (no spaces): " << m_productName << endl
				<< " Price: " << m_price << endl;

			if (m_taxable)
				os << " Price after tax: " << cost() << endl;
			else{
				os << " Price after tax: N/A" << endl;
			}

			os << " Quantity on Hand: " << m_onHand << ' ' << m_unitType << endl
				<< " Quantity needed: " << m_needed;
		}

		return os;
	}
	std::istream& Product::read(std::istream &is){
		char taxed;
		char * address = new char[max_name_length + 1];
		int qty, need;
		double _price;

		if (!is.fail()){

			cout << " Sku: ";
			is >> m_productSku;
			cout << " Name (no spaces): ";
			is >> address;
			name(address);
			cout << " Unit: ";
			is >> m_unitType;
			cout << " Taxed? (y/n): ";
			is >> taxed;


			if (!is.fail()){
				em.clear();

				if (taxed){
					bool y_valid = taxed == 'y' || taxed == 'Y';
					bool n_valid = taxed == 'n' || taxed == 'N';

					if (y_valid)
						m_taxable = true;

					if (n_valid)
						m_taxable = false;

					if (!(y_valid || n_valid)){
						is.setstate(std::ios::failbit);
						em.message("Only (Y)es or (N)o are acceptable");
						return is;
					}
				}
			}
			else{
				is.setstate(std::ios::failbit);
				em.message("Only (Y)es or (N)o are acceptable");
				return is;
			}

			cout << " Price: ";
			is >> _price;

			if (is.fail()){
				em.clear();
				is.setstate(ios::failbit);
				em.message("Invalid Price Entry");
				return is;
			} else
		
				p(_price);

			cout << " Quantity on hand: ";
			is >> qty;

			if (is.fail()){
				em.clear();
				is.setstate(ios::failbit);
				em.message("Invalid Quantity Entry");
				return is;
			}else
				quantity(qty);

			cout << " Quantity needed: ";
			is >> need;
			cin.ignore();

			if (is.fail()){
				em.clear();
				is.setstate(ios::failbit);
				em.message("Invalid Quantity Needed Entry");
				return is;
			} else
				n(need);

			if (!is.fail()){
				em.clear();
			}

		}
		return is;
	}

	bool Product::operator==(const char *s) const{
		return strcmp(s, this->m_productSku) == 0;
	}
	double Product::total_cost() const{
		return m_onHand *(this->cost());
	}
	void Product::quantity(int units)
	{
		m_onHand = units;
	}
	void Product::p(double price)
	{
		m_price = price;
	}
	void Product::n(int needed)
	{
		m_needed = needed;
	}
	bool Product::isEmpty() const{
		return m_productName == nullptr;
	}
	int Product::qtyNeeded() const{
		return m_needed;
	}
	int Product::quantity() const{
		return m_onHand;
	}
	bool Product::operator>(const char *s) const{
		if (strcmp(m_productSku, s) > 0)
			return true;
		else
			return false;
	}
	bool Product::operator>(const iProduct &P1) const{
		return strcmp( m_productName, P1.name()) > 0;
	}
	int Product::operator+=(int added){
		this->m_onHand += added;
		return this->m_onHand;
	}
	std::ostream &operator<<(std::ostream &os, const iProduct &P1){
		return P1.write(os, true);
	}
	std::istream &operator>>(std::istream &is, iProduct &P1){
		return P1.read(is);
	}
	double operator+=(double &total, const iProduct &P1){
		return total + P1.total_cost();
	}
}