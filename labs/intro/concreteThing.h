#include "abstractThing.h"

class ConcreteThing : public AbstractThing {
public:
    // Virtual functions use a vtable to support dynamic dispatch
    // An inherited function cannot have its implementation determined at
    // compile time because a derived class could be cast as its parent class
    // This means that at runtime the function call involves reading a 
    // function pointer before calling the funciton.
    virtual int af() {
        return 1;
    }
};

