#include <iostream>
#include <pqrs/cf/dictionary.hpp>
#include <pqrs/cf/string.hpp>

int main(void) {
  if (auto dictionary_ptr = pqrs::cf::make_cf_mutable_dictionary(0)) {
    CFDictionarySetValue(*dictionary_ptr, CFSTR("key1"), CFSTR("value1"));
    CFDictionarySetValue(*dictionary_ptr, CFSTR("key2"), CFSTR("value2"));

    std::cout << "count: " << CFDictionaryGetCount(*dictionary_ptr) << std::endl;
  }

  return 0;
}
