#include <boost/ut.hpp>
#include <pqrs/cf/dictionary.hpp>
#include <pqrs/cf/number.hpp>
#include <pqrs/cf/string.hpp>

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

  "make_cf_mutable_dictionary_copy"_test = [] {
    auto s1 = pqrs::cf::make_cf_string("s1");
    auto s2 = pqrs::cf::make_cf_string("s2");
    auto n1 = pqrs::cf::make_cf_number(1);
    auto n2 = pqrs::cf::make_cf_number(2);
    const void* keys[] = {
        reinterpret_cast<const void*>(*s1),
        reinterpret_cast<const void*>(*s2),
    };
    const void* values[] = {
        reinterpret_cast<const void*>(*n1),
        reinterpret_cast<const void*>(*n2),
    };

    {
      auto dictionary = CFDictionaryCreate(kCFAllocatorDefault,
                                           keys,
                                           values,
                                           2,
                                           &kCFTypeDictionaryKeyCallBacks,
                                           &kCFTypeDictionaryValueCallBacks);
      expect(dictionary);
      expect(CFGetRetainCount(dictionary) == 1);
      expect(CFDictionaryGetCount(dictionary) == 2);

      auto v = reinterpret_cast<CFTypeRef>(CFDictionaryGetValue(dictionary, *s1));
      expect(v);
      expect(pqrs::cf::make_number<int>(v) == 1);

      auto copy = pqrs::cf::make_cf_mutable_dictionary_copy(dictionary);
      expect(copy);
      expect(CFGetRetainCount(*copy) == 1);
      expect(CFDictionaryGetCount(*copy) == 2);

      CFRelease(dictionary);
    }
  };

  return 0;
}
