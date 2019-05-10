
//BTP_Final_Project
// Milestone 5
//Name: Jonathan Brown
//Date: April 12, 2018
// Student Number: 135918175

#include "Product.h"
#include "Perishable.h"

namespace AMA {

	iProduct* CreateProduct() {
		return new Product();
	}
	iProduct* CreatePerishable() {
		return new Perishable();
	}
}