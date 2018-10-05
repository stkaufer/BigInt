/*
    ===========================================================================
    Random number generating functions for BigInt
    ===========================================================================
*/

#ifndef BIG_INT_RANDOM_FUNCTIONS_HPP
#define BIG_INT_RANDOM_FUNCTIONS_HPP

#include <random>
#include <climits>

#include "BigInt.hpp"

// when the number of digits are not specified, a random value is used for it
// which is kept below the following:
const size_t MAX_RANDOM_LENGTH = 1000;


/*
    big_random (num_digits)
    -----------------------
    Returns a random BigInt with a specific number of digits.
*/

BigInt big_random(size_t num_digits = 0) {
    std::random_device rand_generator;      // true random number generator

    if (num_digits == 0) {   // the number of digits were not specified
        // use a random number for it:
        num_digits = 1 + rand_generator() % MAX_RANDOM_LENGTH;
    }

    BigInt big_rand;
    big_rand.value = "";    // clear value to append digits
    while (big_rand.value.size() < num_digits) {
        big_rand.value += std::to_string(rand_generator());
    }
    if (big_rand.value.size() != num_digits) {
        big_rand.value.erase(num_digits);   // erase extra digits
    }

    return big_rand;
}

static long long ll_digits_count(long long number) {
    long long num_digits = 0;
    while (number) {
        number /= 10;
        num_digits++;
    }
    return num_digits;
}

template <class T>
BigInt big_random(const T& low, const T& high) {
    BigInt result;
    size_t num_low_digits = 0;
    size_t num_high_digits = 0;

    num_low_digits = digits_count(low);
    num_high_digits = digits_count(high);

    result = low + big_random((num_low_digits < num_high_digits ? num_high_digits : num_low_digits))%(high - low);
    return result;
}

template <>
BigInt big_random(const BigInt &low, const BigInt &high) {
    BigInt result;
    BigInt bi_random;
    size_t num_low_digits = 0;
    size_t num_high_digits = 0;

    num_low_digits = ll_digits_count(low.to_long_long());
    num_high_digits = ll_digits_count(high.to_long_long());

    result = stol(low.value) + stol(big_random((num_low_digits < num_high_digits ? num_high_digits : num_low_digits)).value) % (stol(high.value) - stol(low.value));
    return result;
}

template <>
BigInt big_random(const std::string& low, const std::string& high) {
    BigInt result = 0;
    size_t num_low_digits = 0;
    size_t num_high_digits = 0;

    long long ll_low = std::stol(low);
    long long ll_high = std::stol(high);
    num_low_digits = ll_digits_count(ll_low);
    num_high_digits = ll_digits_count(ll_high);

    result = std::stol(low) + big_random((num_low_digits < num_high_digits ? num_high_digits : num_low_digits)).to_long() % (std::stol(high) - std::stol(low));
    return result;
}

template <>
BigInt big_random(const long long &low, const long long &high) {
    BigInt result = 0;
    size_t num_low_digits = 0;
    size_t num_high_digits = 0;

    num_low_digits = ll_digits_count(low);
    num_high_digits = ll_digits_count(high);

    result = low + big_random((num_low_digits < num_high_digits ? num_high_digits : num_low_digits)).to_long() % (high - low);
    return result;
}

#endif  // BIG_INT_RANDOM_FUNCTIONS_HPP
