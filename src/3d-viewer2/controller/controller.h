#ifndef CPP4_3DVIEWER_V2_0_2_SRC_3D_VIEWER2_CONTROLLER_CONTROLLER_H_
#define CPP4_3DVIEWER_V2_0_2_SRC_3D_VIEWER2_CONTROLLER_CONTROLLER_H_

#include "../model/Model.h"

namespace s21 {
class Controller {
 public:
  Controller(Model *model);

  void PassFileToModelAndParse(std::string file_name);

  DataContainer *get_data_container();

  void RotateObjectInDataContainer(double degree, char coordinate);

  void NormalizeObjectBeforePrint();

 private:
  Model *model_;
};

}  // namespace s21

#endif  // CPP4_3DVIEWER_V2_0_2_SRC_3D_VIEWER2_CONTROLLER_CONTROLLER_H_
