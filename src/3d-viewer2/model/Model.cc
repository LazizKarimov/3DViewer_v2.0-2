//
// Created by Carr Johnny on 8/1/23.
//

#include "Model.h"

void s21::Model::ParseFile(std::string file_path) {
  img_parser_->set_file_path(std::move(file_path));

  img_parser_->OpenObjFile();

  img_parser_->StartParsingProcess();

  if (!CheckParsingCorrectness()) {
    throw std::runtime_error("Invalid object file");
  }
}

s21::ImgParser* s21::Model::get_img_parser() { return img_parser_; }

s21::Model::Model() { img_parser_ = new ImgParser(); }

s21::Model::~Model() { delete img_parser_; }

void s21::Model::RefreshInModel() { img_parser_->RefreshInImgParser(); }

bool s21::Model::CheckParsingCorrectness() {
  return (img_parser_->get_data_container()->get_points_amount() > 0 &&
          img_parser_->get_data_container()->get_facets_amount() > 0);
}
