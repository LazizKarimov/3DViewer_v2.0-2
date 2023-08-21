#include "DataContainer.h"

s21::DataContainer* s21::DataContainer::instance_ = nullptr;

s21::DataContainer::DataContainer() {
  instance_ = nullptr;
  facets_amount_ = 0;
  points_amount_ = 0;
}

s21::DataContainer::~DataContainer() { delete instance_; }

double s21::DataContainer::FindMinValueInVector(char plane) {
  int start = 0;
  if (plane == 'x') {
    start = 0;
  } else if (plane == 'y') {
    start = 1;
  } else if (plane == 'z') {
    start = 2;
  }
  double findMin = points_vector_[start];
  for (int i = start; i < (int)points_vector_.size(); i += 3) {
    if (points_vector_[i] < findMin) {
      findMin = points_vector_[i];
    }
  }
  return findMin;
}

double s21::DataContainer::FindMaxValueInVector(char plane) {
  int start = 0;
  if (plane == 'x') {
    start = 0;
  } else if (plane == 'y') {
    start = 1;
  } else if (plane == 'z') {
    start = 2;
  }
  double findMax = points_vector_[start];
  for (int i = start; i < (int)points_vector_.size(); i += 3) {
    if (points_vector_[i] > findMax) {
      findMax = points_vector_[i];
    }
  }
  return findMax;
}

s21::DataContainer* s21::DataContainer::get_instance() {
  if (!instance_) {
    instance_ = new DataContainer();
  }

  return instance_;
}

std::vector<int> s21::DataContainer::get_facets_vector() {
  return facets_vector_;
}

std::vector<double> s21::DataContainer::get_points_vector() {
  return points_vector_;
}

int s21::DataContainer::get_facets_amount() { return facets_amount_; }

int s21::DataContainer::get_points_amount() { return points_amount_; }

void s21::DataContainer::set_facets_vector(double value) {
  facets_vector_.push_back(value);
}

void s21::DataContainer::set_points_vector(double value) {
  points_vector_.push_back(value);
}

void s21::DataContainer::IncrementPointsAmount() { points_amount_++; }

void s21::DataContainer::IncrementFacetsAmount() { facets_amount_++; }

void s21::DataContainer::RefreshInDataContainer() {
  facets_vector_.clear();
  points_vector_.clear();

  points_amount_ = 0;
  facets_amount_ = 0;
}

void s21::DataContainer::RotateObject(double degree, char coordinate) {
  double radian = degree * M_PI / 180;

  for (int index = 0; index < (int)points_vector_.size() - 2; index += 3) {
    double x = points_vector_[index];
    double y = points_vector_[index + 1];
    double z = points_vector_[index + 2];
    switch (coordinate) {
      case 'x':
        points_vector_[index + 1] = y * cos(radian) - sin(radian) * z;
        points_vector_[index + 2] = y * sin(radian) + cos(radian) * z;
        break;
      case 'y':
        points_vector_[index] = x * cos(radian) + sin(radian) * z;
        points_vector_[index + 2] = -x * sin(radian) + cos(radian) * z;
        break;
      case 'z':
        points_vector_[index] = x * cos(radian) - sin(radian) * y;
        points_vector_[index + 1] = x * sin(radian) + cos(radian) * y;
        break;
      default:;
    }
  }
}

void s21::DataContainer::NormalizeObject() {
  double min_x = FindMinValueInVector('x');
  double min_y = FindMinValueInVector('y');
  double min_z = FindMinValueInVector('z');
  double max_x = FindMaxValueInVector('x');
  double max_y = FindMaxValueInVector('y');
  double max_z = FindMaxValueInVector('z');

  double mean_x = max_x - min_x;
  double mean_y = max_y - min_y;
  double mean_z = max_z - min_z;

  double center_x = min_x + (max_x - min_x) / 2;
  double center_y = min_y + (max_y - min_y) / 2;
  double center_z = min_z + (max_z - min_z) / 2;

  for (int i = 0; i < (int)points_vector_.size(); i += 3) {
    points_vector_[i] -= center_x;
    points_vector_[i + 1] -= center_y;
    points_vector_[i + 2] -= center_z;
  }

  double dmax = std::max(std::max(mean_x, mean_y), mean_z);

  double value = 1;
  double scale = (value - (value * (-3))) / dmax;
  ScaleObject(scale);
}

void s21::DataContainer::ScaleObject(double scale) {
  for (int index = 0; index < (int)points_vector_.size(); index++) {
    points_vector_[index] *= scale;
  }
}

void s21::DataContainer::MoveObject(double position, char coordinate) {
  for (int i = 0; i < (int)points_vector_.size(); i += 3) {
    switch (coordinate) {
      case 'x':
        points_vector_[i] += position;
        break;
      case 'y':
        points_vector_[i + 1] += position;
        break;
      case 'z':
        points_vector_[i + 2] += position;
        break;
      default:
        break;
    }
  }
}
