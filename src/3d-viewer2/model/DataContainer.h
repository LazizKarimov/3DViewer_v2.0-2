//
// Created by Carr Johnny on 7/26/23.
//

#ifndef CPP4_3DVIEWER_V2_0_2_SRC_3D_VIEWER2_MODEL_DATACONTAINER_H_
#define CPP4_3DVIEWER_V2_0_2_SRC_3D_VIEWER2_MODEL_DATACONTAINER_H_

#include <cmath>
#include <vector>

namespace s21 {
class DataContainer {
 public:
  static DataContainer *get_instance();

  std::vector<int> get_facets_vector();

  std::vector<double> get_points_vector();

  int get_facets_amount();

  int get_points_amount();

  // mutator: set value to the facets_vector_
  void set_facets_vector(double value);

  void set_points_vector(double value);

  void IncrementPointsAmount();

  void IncrementFacetsAmount();

  void RefreshInDataContainer();

  void RotateObject(double degree, char coordinate);

  void NormalizeObject();

  void ScaleObject(double scale);

  void MoveObject(double position, char coordinate);

 protected:
  DataContainer();

  ~DataContainer();

 private:
  static DataContainer *instance_;

  std::vector<int> facets_vector_;
  std::vector<double> points_vector_;

  int facets_amount_;
  int points_amount_;

  double FindMinValueInVector(char plane);

  double FindMaxValueInVector(char plane);
};
}  // namespace s21
#endif  // CPP4_3DVIEWER_V2_0_2_SRC_3D_VIEWER2_MODEL_DATACONTAINER_H_
