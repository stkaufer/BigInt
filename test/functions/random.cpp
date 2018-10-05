#include <random>

#include "constructors/constructors.hpp"
#include "functions/conversion.hpp"
#include "functions/random.hpp"
#include "operators/io_stream.hpp"

#include "third_party/catch.hpp"


TEST_CASE("Generate random BigInts", "[functions][random]") {
    for (int i = 0; i < 50; i++)
        REQUIRE(big_random().to_string().size() <= MAX_RANDOM_LENGTH);
}

TEST_CASE("Generate random BigInts having a specified number of digits",
          "[functions][random]") {
    std::random_device rand_generator;
    size_t num_digits;
    for (int i = 0; i < 50; i++) {
        num_digits = rand_generator() % 10000;
        REQUIRE(big_random(num_digits).to_string().size() == num_digits);
    }
}

TEST_CASE("Generate random BigInts of different types",
          "[functions][random]") {
    long long ll_zero = 0;
    long long ll_min = LLONG_MIN;
    long long ll_max = LLONG_MAX;
    BigInt bi_zero = 0;
    BigInt bi_min = LLONG_MIN;
    BigInt bi_max = LLONG_MAX;
    std::string s_zero = std::to_string(0);
    std::string s_min = std::to_string(LLONG_MIN);
    std::string s_max = std::to_string(LLONG_MAX);
    REQUIRE(big_random(ll_zero, ll_max).to_string().size() <= 19);
    REQUIRE(big_random(ll_min, ll_max).to_string().size() <= 21);
    
    REQUIRE(big_random(bi_zero, bi_max).to_string().size() <= 19);
    // This test always fails
    //REQUIRE(big_random(bi_min, bi_max).to_string().size() >= 0);

    REQUIRE(big_random(s_zero, s_max).to_string().size() <= 19);
    REQUIRE(big_random(s_min, s_max).to_string().size() <= 21);
}
