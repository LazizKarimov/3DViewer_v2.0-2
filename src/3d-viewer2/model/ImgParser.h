#ifndef CPP4_3DVIEWER_V2_0_2_SRC_3D_VIEWER2_MODEL_IMGPARSER_H_
#define CPP4_3DVIEWER_V2_0_2_SRC_3D_VIEWER2_MODEL_IMGPARSER_H_
#include <fstream>
#include <iostream>

#include "DataContainer.h"
#include "StringUtils.h"

namespace s21 {
class ImgParser {
 public:
  ImgParser();
  ~ImgParser();

  void set_file_path(std::string file_path);
  void OpenObjFile();
  void StartParsingProcess();

  DataContainer* get_data_container();

  void RefreshInImgParser();

 private:
  std::string file_path_;
  std::ifstream obj_file_;

  DataContainer* data_container_;

  void ParsePoint(const std::string& string_read_from_file);

  void ParseFacet(const std::string& string_read_from_file);
};
}  // namespace s21

#endif  // CPP4_3DVIEWER_V2_0_2_SRC_3D_VIEWER2_MODEL_IMGPARSER_H_