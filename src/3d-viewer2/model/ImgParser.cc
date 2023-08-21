#include "ImgParser.h"

#include <utility>

s21::ImgParser::ImgParser() : obj_file_(nullptr) {
  data_container_ = DataContainer::get_instance();
}

s21::ImgParser::~ImgParser() {}

void s21::ImgParser::set_file_path(std::string file_path) {
  file_path_ = std::move(file_path);
}

void s21::ImgParser::OpenObjFile() {
  obj_file_.open(file_path_);

  if (!obj_file_.is_open()) {
    throw std::runtime_error("Error opening file or file doesn't exist.");
  }
}

void s21::ImgParser::StartParsingProcess() {
  if (!obj_file_.is_open()) {
    OpenObjFile();
  }

  std::string string_read_from_file;

  while (std::getline(obj_file_, string_read_from_file)) {
    ParsePoint(string_read_from_file);
    ParseFacet(string_read_from_file);
  }

  if (obj_file_.is_open()) obj_file_.close();
}

void s21::ImgParser::ParsePoint(const std::string& string_read_from_file) {
  if (!StringUtils::StringStartsWith(string_read_from_file, "v ")) {
    return;
  }

  std::string::const_iterator i = string_read_from_file.begin() + 2;

  while (i != string_read_from_file.end()) {
    if (isdigit(*i) || *i == '-') {
      data_container_->set_points_vector(StringUtils::GetDoubleFromString(i));
    }
    i++;
  }
  data_container_->IncrementPointsAmount();
}

void s21::ImgParser::ParseFacet(const std::string& string_read_from_file) {
  if (!StringUtils::StringStartsWith(string_read_from_file, "f ")) {
    return;
  }

  std::string::const_iterator i = string_read_from_file.begin() + 2;

  int first_facet = -1;
  int curr_facet = -1;
  int count_written_values = 0;
  int prev_facet = -1;

  while (i != string_read_from_file.end()) {
    if (isdigit(*i)) {
      curr_facet = (int)StringUtils::GetDoubleFromString(i);

      if (first_facet == -1) {
        first_facet = curr_facet;
      }
      if (count_written_values >= 2) {
        data_container_->set_facets_vector(prev_facet - 1);
      }

      data_container_->set_facets_vector(curr_facet - 1);
      count_written_values++;
      prev_facet = curr_facet;
    }
    while (i != string_read_from_file.end() && *i != ' ') {
      i++;
    }
    if (*i == ' ') i++;
  }
  data_container_->set_facets_vector(prev_facet - 1);
  data_container_->set_facets_vector(first_facet - 1);

  data_container_->IncrementFacetsAmount();
}

s21::DataContainer* s21::ImgParser::get_data_container() {
  return data_container_;
}

void s21::ImgParser::RefreshInImgParser() {
  file_path_.clear();
  data_container_->RefreshInDataContainer();
}
