#ifndef PRINCESS_H
#define PRINCESS_H

#include <string>
#include <iostream>

//using namespace std; // Don't!

namespace Fantasy {

    class FrogPrince;

    class Princess {
        friend std::ostream& operator<<(std::ostream&, const Princess&);
    public:
        Princess(const std::string& name);
        void display() const;
        void marries(FrogPrince& betrothed);
    private:
        std::string name;
        FrogPrince* spouse = nullptr;
    };

}

#endif
