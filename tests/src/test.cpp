#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <pqrs/cf/dictionary.hpp>

TEST_CASE("make_cf_mutable_dictionary") {
  {
    auto dictionary = pqrs::cf::make_cf_mutable_dictionary();
    REQUIRE(dictionary);
    REQUIRE(CFGetRetainCount(*dictionary) == 1);
    REQUIRE(CFDictionaryGetCount(*dictionary) == 0);

    CFDictionarySetValue(*dictionary, CFSTR("key1"), CFSTR("value1"));
    CFDictionarySetValue(*dictionary, CFSTR("key2"), CFSTR("value2"));

    REQUIRE(CFDictionaryGetCount(*dictionary) == 2);
  }
}
