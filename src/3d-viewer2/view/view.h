#ifndef CPP4_3DVIEWER_V2_0_2_SRC_3D_VIEWER2_VIEW_VIEW_H_
#define CPP4_3DVIEWER_V2_0_2_SRC_3D_VIEWER2_VIEW_VIEW_H_

#include <QColorDialog>
#include <QFileDialog>
#include <QMainWindow>

#include "../controller/controller.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class View;
}
QT_END_NAMESPACE

namespace s21 {
class View : public QMainWindow {
  Q_OBJECT

 public:
  View(Controller *controller, QWidget *parent = nullptr);
  ~View();

 private slots:

  void on_load_image_button_clicked();

  void on_scaleSpinBox_valueChanged(double arg1);

  void on_rotate_x_spinbox_valueChanged(double arg1);

  void on_rotate_y_spinbox_valueChanged(double arg1);

  void on_rotate_z_spinbox_valueChanged(double arg1);

  void on_pos_x_spinbox_valueChanged(double arg1);

  void on_pos_y_spinbox_valueChanged(double arg1);

  void on_pos_z_spinbox_valueChanged(double arg1);

  void on_parallel_projection_checkbox_stateChanged();

  void on_dotted_line_checkbox_stateChanged();

  void on_dot_type_combobox_currentIndexChanged(int index);

  void on_dot_size_spinbox_valueChanged(int arg1);

  void on_line_thickness_spinbox_valueChanged(double arg1);

  void on_font_color_button_clicked();

  void on_dot_color_button_clicked();

  void on_line_color_button_clicked();

  void on_save_as_jpeg_clicked();

  void on_save_as_bmp_clicked();

  void on_save_gif_button_clicked();

  void ChangeGifButtonColor();

 private:
  Ui::View *ui;
  Controller *controller_;

  QColor colors_;

  void LoadSettings();
};

}  // namespace s21
#endif  // CPP4_3DVIEWER_V2_0_2_SRC_3D_VIEWER2_VIEW_VIEW_H_
