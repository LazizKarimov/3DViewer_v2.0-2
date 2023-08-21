#ifndef CPP4_3DVIEWER_V2_0_2_SRC_3D_VIEWER2_VIEW_GLMODULE_H_
#define CPP4_3DVIEWER_V2_0_2_SRC_3D_VIEWER2_VIEW_GLMODULE_H_

#include <QMouseEvent>
#include <QOpenGLWidget>
#include <QSettings>
#include <QTimer>

#include "../controller/controller.h"
#include "qgifimage.h"

namespace s21 {
class GLModule : public QOpenGLWidget {
  Q_OBJECT
 public:
  GLModule(QWidget *parent);

  void set_controller(Controller *controller);

  void initializeGL() override;
  void resizeGL(int w, int h) override;
  void paintGL() override;
  void mousePressEvent(QMouseEvent *mo) override;
  void mouseMoveEvent(QMouseEvent *mo) override;

  double get_prev_scale();
  void set_prev_scale(double value);

  double get_x_pos() const;
  void set_x_pos(double new_x_pos);

  double get_y_pos() const;
  void set_y_pos(double new_y_pos);

  double get_z_pos() const;
  void set_z_pos(double new_z_pos);

  void set_type_projection(int new_type_projection);

  void set_dotted_line(int new_dotted_line);

  void set_dot_type(int new_dot_type);

  void set_dot_depth(double new_dot_depth);

  void set_line_depth(double new_line_depth);

  void set_red_back(double new_red_back);

  void set_green_back(double new_green_back);

  void set_blue_back(double new_blue_back);

  void set_red_point(double new_red_point);

  void set_green_point(double new_green_point);

  void set_blue_point(double new_blue_point);

  void set_red_line(double new_red_line);

  void set_green_line(double new_green_line);

  void set_blue_line(double new_blue_line);

  QSettings *get_settings();

  int get_check_timer();

  void set_name_gif(QString new_name_gif);

  void Record();

 signals:
 Q_SIGNALS:
  void StopRecord();

 private slots:
  void Gif();

 private:
  Controller *controller_;

  std::vector<double> points_vector_;

  std::vector<int> facets_vector_;

  int type_projection_ = 0;  // 0 - Ортографическая, 1 - Перспективная проекции
  double red_back_ = 0.0, green_back_ = 0.0, blue_back_ = 0.0;
  double red_line_ = 1.0, green_line_ = 0.0, blue_line_ = 1.0;
  double red_point_ = 0.0, green_point_ = 1.0, blue_point_ = 1.0;
  double x_rot_ = 0.0, y_rot_ = 0.0, z_rot_ = 0.0;
  QPoint m_pos_;
  double x_pos_ = 0.0, y_pos_ = 0.0, z_pos_ = 0.0;
  double start_x_ = 0.0, start_y_ = 0.0;
  double prev_scale_ = 1;

  double line_depth_ = 1.0, dot_depth_ = 1.0;
  int dotted_line_ = 0;  // 0 - сплошная, 1 - пунктир
  int dot_type_ =
      0;  // 0 - отсутствует отображение точек, 1 - круг, 2 - квадрат

  QSettings settings_;

  void SaveCurrentSettings();

  void LoadSavedState();

  int check_timer_ = 1;

  QTimer *timer_ = NULL;

  QString name_gif_;

  QGifImage *gif_image_ = NULL;

  int index_time_ = 0;
};

}  // namespace s21

#endif  // CPP4_3DVIEWER_V2_0_2_SRC_3D_VIEWER2_VIEW_GLMODULE_H_
