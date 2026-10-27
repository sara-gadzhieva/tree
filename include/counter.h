//
// Created by Bogdan Sirotich on 26.10.2026.
//

#ifndef OC26_COUNTER_H
#define OC26_COUNTER_H

namespace utils {

namespace counter {

    class Counter {
    public:
        Counter();
        void increment();
        int value() const;
    private:
        int count_;
    };

} // namespace counter
} // namespace utils
#endif //OC26_COUNTER_H
