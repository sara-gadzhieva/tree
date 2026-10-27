//
// Created by Bogdan Sirotich on 26.10.2026.
//
#include "counter.h"

namespace utils {
    namespace counter {
        Counter::Counter() : count_{0} {}

        void Counter::increment() {
            ++count_;
        }

        int Counter::value() const {
            return count_;
        }
    }
}



