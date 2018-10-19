#ifndef FROGPRINCE_H
#define FROGPRINCE_H

#include <string>

namespace Fantasy {

    class Princess;

    class FrogPrince {
    public:
        FrogPrince(const std::string& name);
        void display() const;
        void setSpouse(Princess* pp);
    private:
        std::string name;
        Princess* spouse;
    };

}

#endif
