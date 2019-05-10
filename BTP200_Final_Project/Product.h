#ifndef AMA_PRODUCT_H
#define AMA_PRODUCT_H
#include <iostream>
#include <fstream>
#include "ErrorState.h"
#include "iProduct.h"

namespace AMA{

	const int max_sku_length = 7;
	const int max_unit_length = 10;
	const int max_name_length = 75;
	const double tax_rate = 0.13;

	class Product : public iProduct{

		char m_type;
		char m_productSku[max_sku_length];
		char m_unitType[max_unit_length];
		char* m_productName;
		int m_onHand;
		int m_needed;
		double m_price;
		bool m_taxable;
	protected:
		ErrorState em;
		void name(const char* name);
		const char* name() const;
		const char* sku() const;
		const char* unit() const;
		bool taxed() const;
		double price() const;
		double cost() const;
		void message(const char* name);
		bool isClear() const;
	public:
		Product(char type = 'N');
		Product(const char* sku, const char* Name, const char* Unit, int quantity = 0, 
		bool taxable = true, double price = 0.0, int required = 0);
		Product(const Product& other);
		Product& operator=(const Product& other);
		~Product();

		std::fstream& store(std::fstream& file, bool newLine = true) const;
		std::fstream& load(std::fstream& file);
		std::ostream& write(std::ostream& os, bool linear) const;
		std::istream& read(std::istream& is);

		bool operator==(const char* name) const;
		double total_cost() const;
		void quantity(int units);
		void p(double price);
		void n(int needed);
		bool isEmpty() const;
		int qtyNeeded() const;
		int quantity() const;
		bool operator>(const char* productSKU) const;
		bool operator>(const iProduct& other) const;
		int operator+=(int added);
	};
	std::ostream& operator<<(std::ostream& os, const iProduct& P1);
	std::istream& operator>>(std::istream& is, iProduct& P1);
	double operator+=(double& num, const iProduct& P1);
}

#endif // !AMA_PRODUCT_H