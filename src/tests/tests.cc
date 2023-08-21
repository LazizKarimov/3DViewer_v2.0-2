#include <gtest/gtest.h>

#include <filesystem>

#include "../3d-viewer2/model/Model.h"

class ImgParserTest : public testing::Test {
 protected:
  s21::Model *model_;
  bool parsing_status_;
  void SetUp() override { model_ = new s21::Model(); }
  void TearDown() override { delete model_; }
};

TEST_F(ImgParserTest, TestStartParsingProcess) {
  model_->ParseFile(std::filesystem::current_path() / "tests/cube.txt");
  std::vector<double> points_vector =
      model_->get_img_parser()->get_data_container()->get_points_vector();

  std::vector<int> facets_vector =
      model_->get_img_parser()->get_data_container()->get_facets_vector();

  std::vector<double> expected_points_vector = {
      -1.0, -1.0, -1.0, -1.0, -1.0, 1.0, -1.0, 1.0, -1.0, -1.0, 1.0, 1.0,
      1.0,  -1.0, -1.0, 1.0,  -1.0, 1.0, 1.0,  1.0, -1.0, 1.0,  1.0, 1.0};

  std::vector<int> expected_facets_vector = {
      0, 6, 6, 4, 4, 0, 0, 2, 2, 6, 6, 0, 0, 3, 3, 2, 2, 0, 0, 1,
      1, 3, 3, 0, 2, 7, 7, 6, 6, 2, 2, 3, 3, 7, 7, 2, 4, 6, 6, 7,
      7, 4, 4, 7, 7, 5, 5, 4, 0, 4, 4, 5, 5, 0, 0, 5, 5, 1, 1, 0};

  EXPECT_EQ(points_vector, expected_points_vector);
  EXPECT_EQ(facets_vector, expected_facets_vector);
}

TEST_F(ImgParserTest, TestOpenObjFile) {
  EXPECT_NO_THROW(
      model_->ParseFile(std::filesystem::current_path() / "tests/correct.txt"));
}

TEST_F(ImgParserTest, TestNonexistentFile) {
  EXPECT_THROW(model_->ParseFile(std::filesystem::current_path() /
                                 "tests/nonexistent_file.txt"),
               std::runtime_error);
}

int main(int argc, char *argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}