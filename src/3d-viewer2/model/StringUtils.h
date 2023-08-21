//
// Created by Carr Johnny on 8/1/23.
//

#ifndef CPP4_3DVIEWER_V2_0_2_SRC_3D_VIEWER2_MODEL_STRINGUTILS_H_
#define CPP4_3DVIEWER_V2_0_2_SRC_3D_VIEWER2_MODEL_STRINGUTILS_H_

#include <iostream>

namespace s21 {
class StringUtils {
 public:
  //      additional function to check if "str" starts with "prefix"

  static bool StringStartsWith(const std::string &str,
                               const std::string &prefix) {
    if (str.length() < prefix.length()) {
      return false;
    }
    return str.substr(0, prefix.length()) == prefix;
  }

  static double GetDoubleFromString(std::string::const_iterator &i) {
    double double_value = 0;

    int count_symbols_read = 0;

    int sscanf_result =
        sscanf(&i[0], "%le %n", &double_value, &count_symbols_read);

    i += count_symbols_read - 1;

    if (!sscanf_result) {
      throw std::runtime_error("Failed to parse double from string.");
    }

    return double_value;
  }
};

}  // namespace s21
#endif  // CPP4_3DVIEWER_V2_0_2_SRC_3D_VIEWER2_MODEL_STRINGUTILS_H_
