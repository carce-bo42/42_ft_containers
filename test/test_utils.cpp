#include "test_utils.hpp"
#include <utility>
#include <sys/time.h>

long current_timestamp() {
    struct timeval te; 
    gettimeofday(&te, NULL);
    long milliseconds = te.tv_sec*1000L + te.tv_usec/1000;
    return milliseconds;
}

#define PAIR_INT_STRING(a, b) \
        std::pair<int, std::string>(a, b)

#define PAIR_STRING_MAP_INT_STRING(a, b) \
        std::pair<std::string, std::map<int, std::string> >(a, b)

void LoadErrorMaps() {

  vector_errors.insert(PAIR_INT_STRING(KO_INSERT, INSERT_TAG));
  vector_errors.insert(PAIR_INT_STRING(KO_ERASE, ERASE_TAG));
  vector_errors.insert(PAIR_INT_STRING(KO_CONSTRUCTOR, CONSTRUCTOR_TAG));

  error_map.insert(PAIR_STRING_MAP_INT_STRING(VECTOR_TAG, vector_errors));
}