//
// Created by Carr Johnny on 8/1/23.
//

#ifndef CPP4_3DVIEWER_V2_0_2_SRC_3D_VIEWER2_MODEL_MODEL_H_
#define CPP4_3DVIEWER_V2_0_2_SRC_3D_VIEWER2_MODEL_MODEL_H_

#include "ImgParser.h"

namespace s21 {
class Model {
 public:
  Model();
  ~Model();

  void ParseFile(std::string file_path);

  ImgParser* get_img_parser();

  void RefreshInModel();

 private:
  ImgParser* img_parser_;

  bool CheckParsingCorrectness();
};

}  // namespace s21
#endif  // CPP4_3DVIEWER_V2_0_2_SRC_3D_VIEWER2_MODEL_MODEL_H_
