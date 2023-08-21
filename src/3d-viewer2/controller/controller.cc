#include "controller.h"

s21::Controller::Controller(Model *model) : model_(model) {}

void s21::Controller::PassFileToModelAndParse(std::string file_name) {
  model_->RefreshInModel();
  model_->ParseFile(file_name);
}

s21::DataContainer *s21::Controller::get_data_container() {
  return model_->get_img_parser()->get_data_container();
}

void s21::Controller::RotateObjectInDataContainer(double degree,
                                                  char coordinate) {
  model_->get_img_parser()->get_data_container()->RotateObject(degree,
                                                               coordinate);
}

void s21::Controller::NormalizeObjectBeforePrint() {
  model_->get_img_parser()->get_data_container()->NormalizeObject();
}
