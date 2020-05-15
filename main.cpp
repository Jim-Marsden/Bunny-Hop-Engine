#include <iostream>
#include <boost/timer/timer.hpp>
#include <cmath>

int main() {

    for(auto inte{0}; inte < 0xffff; ++inte) {
        boost::timer::auto_cpu_timer t;

        for (long i = 0; i < 100000000; ++i)
            std::sqrt(123.456L); // burn some time
    }
    return 0;
}

[[maybe_unused]] int test(){

}
