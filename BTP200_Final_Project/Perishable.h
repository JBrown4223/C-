//BTP_Final_Project
// Milestone 5
//Name: Jonathan Brown
//Date: April 12, 2018
// Student Number: 135918175

#ifndef AMA_PERISHABLE_H
#define AMA_PERISHABLE_H
#include "Date.h"
#include "Product.h"

namespace AMA {
    class Perishable : public Product {
     Date m_expiration;

     public:
     Perishable(char type = 'P');
     std::fstream& store(std::fstream& file, bool newline = true) const;
     std::fstream& load(std::fstream& file);
     std::ostream& write(std::ostream& os, bool linear) const;
     std::istream& read(std::istream& is);
     const Date& expiry() const;

    };
}

#endif //!PERISHABLE_H