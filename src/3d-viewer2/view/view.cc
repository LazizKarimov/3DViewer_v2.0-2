#include "view.h"

#include "ui_view.h"

s21::View::View(Controller *controller, QWidget *parent)
    : QMainWindow(parent), ui(new Ui::View), controller_(controller) {
  ui->setupUi(this);
  setFixedSize(1226, 782);
  ui->glwidget->set_controller(controller_);
  LoadSettings();

  connect(ui->glwidget, SIGNAL(StopRecord()), this,
          SLOT(ChangeGifButtonColor()));
}

s21::View::~View() { delete ui; }

void s21::View::on_load_image_button_clicked() {
  QString filters("OBJ (*.obj)");
  QString file_name =
      QFileDialog::getOpenFileName(this, "Open file", "", filters);

  if (file_name.isEmpty() == false) {
    try {
      controller_->PassFileToModelAndParse(file_name.toStdString());

      ui->file_info_label->setText(file_name);
      ui->count_of_points->setText(QString::number(
          controller_->get_data_container()->get_points_amount(), 'g', 15));
      ui->count_of_ribs->setText(QString::number(
          controller_->get_data_container()->get_facets_amount(), 'g', 15));

      controller_->NormalizeObjectBeforePrint();
      ui->glwidget->update();
    } catch (...) {
      ui->file_info_label->setText("FILE PARSING ERROR !!!");
    }
  }
}

void s21::View::on_scaleSpinBox_valueChanged(double arg1) {
  controller_->get_data_container()->ScaleObject(
      1 / ui->glwidget->get_prev_scale());
  controller_->get_data_container()->ScaleObject(arg1);
  ui->glwidget->set_prev_scale(arg1);
  ui->glwidget->update();
}

void s21::View::on_rotate_x_spinbox_valueChanged(double arg1) {
  controller_->get_data_container()->RotateObject(arg1, 'x');
  ui->glwidget->update();
}

void s21::View::on_rotate_y_spinbox_valueChanged(double arg1) {
  controller_->get_data_container()->RotateObject(arg1, 'y');
  ui->glwidget->update();
}

void s21::View::on_rotate_z_spinbox_valueChanged(double arg1) {
  controller_->get_data_container()->RotateObject(arg1, 'z');
  ui->glwidget->update();
}

void s21::View::on_pos_x_spinbox_valueChanged(double arg1) {
  controller_->get_data_container()->MoveObject(-ui->glwidget->get_x_pos(),
                                                'x');
  controller_->get_data_container()->MoveObject(arg1, 'x');
  ui->glwidget->set_x_pos(arg1);
  ui->glwidget->update();
}

void s21::View::on_pos_y_spinbox_valueChanged(double arg1) {
  controller_->get_data_container()->MoveObject(-ui->glwidget->get_y_pos(),
                                                'y');
  controller_->get_data_container()->MoveObject(arg1, 'y');
  ui->glwidget->set_y_pos(arg1);
  ui->glwidget->update();
}

void s21::View::on_pos_z_spinbox_valueChanged(double arg1) {
  controller_->get_data_container()->MoveObject(-ui->glwidget->get_z_pos(),
                                                'z');
  controller_->get_data_container()->MoveObject(arg1, 'z');
  ui->glwidget->set_z_pos(arg1);
  ui->glwidget->update();
}

void s21::View::on_parallel_projection_checkbox_stateChanged() {
  ui->glwidget->set_type_projection(
      ui->parallel_projection_checkbox->isChecked());
  ui->glwidget->update();
}

void s21::View::on_dotted_line_checkbox_stateChanged() {
  ui->glwidget->set_dotted_line(ui->dotted_line_checkbox->isChecked());
  ui->glwidget->update();
}

void s21::View::on_dot_type_combobox_currentIndexChanged(int index) {
  ui->glwidget->set_dot_type(index);
  ui->glwidget->update();
}

void s21::View::on_dot_size_spinbox_valueChanged(int arg1) {
  ui->glwidget->set_dot_depth(arg1);
  ui->glwidget->update();
}

void s21::View::on_line_thickness_spinbox_valueChanged(double arg1) {
  ui->glwidget->set_line_depth(arg1);
  ui->glwidget->update();
}

void s21::View::on_font_color_button_clicked() {
  colors_ = QColorDialog::getColor(Qt::white, this);
  ui->glwidget->set_red_back(colors_.redF());
  ui->glwidget->set_green_back(colors_.greenF());
  ui->glwidget->set_blue_back(colors_.blueF());

  ui->glwidget->update();
}

void s21::View::on_dot_color_button_clicked() {
  colors_ = QColorDialog::getColor(Qt::white, this);
  ui->glwidget->set_red_point(colors_.redF());
  ui->glwidget->set_green_point(colors_.greenF());
  ui->glwidget->set_blue_point(colors_.blueF());

  ui->glwidget->update();
}

void s21::View::on_line_color_button_clicked() {
  colors_ = QColorDialog::getColor(Qt::white, this);
  ui->glwidget->set_red_line(colors_.redF());
  ui->glwidget->set_green_line(colors_.greenF());
  ui->glwidget->set_blue_line(colors_.blueF());

  ui->glwidget->update();
}

void s21::View::LoadSettings() {
  if (this->ui->glwidget->get_settings()->value("save").toInt() == 1) {
    ui->dot_size_spinbox->setValue(
        this->ui->glwidget->get_settings()->value("dotDepth").toInt());
    ui->line_thickness_spinbox->setValue(
        this->ui->glwidget->get_settings()->value("lineDepth").toDouble());
    ui->dot_type_combobox->setCurrentIndex(
        this->ui->glwidget->get_settings()->value("dotType").toInt());
    ui->dotted_line_checkbox->setChecked(
        this->ui->glwidget->get_settings()->value("dottedLine").toInt());
    ui->parallel_projection_checkbox->setChecked(
        this->ui->glwidget->get_settings()->value("projection").toInt());
  }
}

void s21::View::on_save_as_jpeg_clicked() {
  QString file = QFileDialog::getSaveFileName(
      this, "Save as...", "~/ourViewer/saved/name.jpeg", tr("JPEG (*.jpeg)"));
  ui->glwidget->grabFramebuffer().save(file, NULL, 100);
}

void s21::View::on_save_as_bmp_clicked() {
  QString file = QFileDialog::getSaveFileName(
      this, "Save as...", "../saved/name.bmp", tr("BMP (*.bmp)"));
  ui->glwidget->grabFramebuffer().save(file, NULL, 100);
}

void s21::View::on_save_gif_button_clicked() {
  QString name = QFileDialog::getSaveFileName(
      this, "Save as...", "../saved/name.gif", tr("GIF (*.gif)"));
  if (!name.isEmpty() && this->ui->glwidget->get_check_timer() == 1) {
    ui->save_gif_button->setStyleSheet("background-color:#FF0000");
    this->ui->glwidget->set_name_gif(name);
    this->ui->glwidget->Record();
  }
}

void s21::View::ChangeGifButtonColor() {
  ui->save_gif_button->setStyleSheet(
      "QPushButton {background-color: rgb(102, 192, 220);color:white;} "
      "QPushButton:hover{background-color: rgb(152, 185, 255);color:rgb(78, "
      "120, 254);} ");
}
