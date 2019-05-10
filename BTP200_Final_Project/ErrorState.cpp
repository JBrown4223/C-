//BTP_Final_Project
// Milestone 5
//Name: Jonathan Brown
//Date: April 16, 2018
// Student Number: 135918175


#include <iostream>
#include <cstring>
#include "ErrorState.h"

using namespace std;

namespace AMA {
  
    ErrorState::~ErrorState(){
         delete[] m_message;
    }

    ErrorState::ErrorState(const char* errorMessage){
      if( errorMessage == nullptr){
        m_message = nullptr;
        } else {
            m_message = new char[strlen(errorMessage) + 1];
            strcpy(m_message, errorMessage); 
        }
    }

    void ErrorState::clear() {
      m_message = '\0';
    }

    bool ErrorState::isClear() const{
     if (m_message == nullptr)
        return true;
            else 
                return false;
    }

    void ErrorState::message(const char* str) {
        
        delete[] m_message;
        m_message = new char[strlen(str) + 1];
        strcpy(m_message, str); 

    }

    const char* ErrorState::message()const {
        return m_message;
    }

   ostream& operator<<(ostream& os, const ErrorState& em) {
    if (!em.isClear())
			os << em.message();
		return os;
   }
}