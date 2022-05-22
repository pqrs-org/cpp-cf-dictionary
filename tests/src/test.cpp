#include <boost/ut.hpp>
#include <pqrs/cf/dictionary.hpp>

int main(void) {
  using namespace boost::ut;
  using namespace boost::ut::literals;

  "make_cf_mutable_dictionary"_test = [] {
    {
      auto dictionary = pqrs::cf::make_cf_mutable_dictionary();
      expect(dictionary);
      expect(CFGetRetainCount(*dictionary) == 1);
      expect(CFDictionaryGetCount(*dictionary) == 0);

      CFDictionarySetValue(*dictionary, CFSTR("key1"), CFSTR("value1"));
      CFDictionarySetValue(*dictionary, CFSTR("key2"), CFSTR("value2"));

      expect(CFDictionaryGetCount(*dictionary) == 2);
    }
  };

  return 0;
}
