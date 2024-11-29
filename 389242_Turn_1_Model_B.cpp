// FlightControlSystem.cpp

#include <assert.h>

class FlightControlSystem {
public:
    void update(float altitude) {
        // Some processing logic here

        // Assertion to check altitude safety
        assert(altitude >= 0 && altitude <= 10000); // Safety limit of 10000 feet

        // Continue with flight control updates
    }
};
