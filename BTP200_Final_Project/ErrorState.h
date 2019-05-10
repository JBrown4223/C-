//BTP_Final_Project
// Milestone 5
//Name: Jonathan Brown
//Date: April 12, 2018
// Student Number: 135918175
// Workshop: MS2



#ifndef  AMA_ERRORSTATE_H
#define  AMA_ERRORSTATE_H
#include <iostream>

namespace AMA {

    class ErrorState {
        char* m_message;
        
        public:
        explicit ErrorState(const char* errorMessage = nullptr);
        ErrorState(const ErrorState& em) = delete;
        ErrorState& operator=(const ErrorState& em) = delete;
        virtual ~ErrorState();
        void clear();
        bool isClear() const;
        void message(const char* str);
        const char* message()const;    
    };
    
    std::ostream& operator<<(std::ostream& os, const ErrorState& em);
}

#endif 