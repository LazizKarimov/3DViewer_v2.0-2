#include "glmodule.h"

s21::GLModule::GLModule(QWidget *parent) : QOpenGLWidget(parent) {}

void s21::GLModule::set_controller(Controller *controller) {
  controller_ = controller;
}

void s21::GLModule::initializeGL() {
  glEnable(GL_DEPTH_TEST);
  LoadSavedState();
}

void s21::GLModule::resizeGL(int w, int h) { glViewport(0, 0, w, h); }

void s21::GLModule::paintGL() {
  float size = 3, fov = 60.0 * M_PI / 180, far = 15;
  float heapHeight = size / (2 * tan(fov / 2));

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  if (type_projection_ == 0) {
    glOrtho(-3, 3, -3, 3, -15, 15);
  } else {
    glFrustum(-size, size, -size, size, heapHeight, far);
  }
  glClearColor(red_back_, green_back_, blue_back_, 1);

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glTranslatef(0, 0, -3 * heapHeight);

  SaveCurrentSettings();
  // viewer

  if (controller_->get_data_container()) {
    points_vector_ = controller_->get_data_container()->get_points_vector();
    glVertexPointer(3, GL_DOUBLE, 0, &points_vector_[0]);

    glEnableClientState(GL_VERTEX_ARRAY);
    if (dot_type_) {
      if (dot_type_ == 1) glEnable(GL_POINT_SMOOTH);
      glColor3d(red_point_, green_point_, blue_point_);
      glPointSize(dot_depth_);
      glDrawArrays(GL_POINTS, 0,
                   controller_->get_data_container()->get_points_amount());
    }

    glEnable(GL_LINE_STIPPLE);
    glLineWidth(line_depth_);
    glColor3d(red_line_, green_line_, blue_line_);
    if (dotted_line_)
      glLineStipple(2, 0x00FF);
    else
      glLineStipple(2, 0xFFFF);

    facets_vector_ = controller_->get_data_container()->get_facets_vector();

    glDrawElements(GL_LINES, facets_vector_.size(), GL_UNSIGNED_INT,
                   facets_vector_.data());
    if (dot_type_ == 1) glDisable(GL_POINT_SMOOTH);

    glDisable(GL_LINE_STIPPLE);
    glDisableClientState(GL_VERTEX_ARRAY);
  }
}

void s21::GLModule::mousePressEvent(QMouseEvent *mo) {
  m_pos_ = mo->pos();
  start_x_ = mo->pos().x();
  start_y_ = mo->pos().y();
}

void s21::GLModule::mouseMoveEvent(QMouseEvent *mo) {
  x_rot_ = 1 / M_PI * (mo->pos().y() - start_y_);
  y_rot_ = 1 / M_PI * (mo->pos().x() - start_x_);

  controller_->RotateObjectInDataContainer(x_rot_, 'x');
  controller_->RotateObjectInDataContainer(y_rot_, 'y');

  start_x_ = mo->pos().x();
  start_y_ = mo->pos().y();
  update();
}

double s21::GLModule::get_prev_scale() { return prev_scale_; }

void s21::GLModule::set_prev_scale(double value) { prev_scale_ = value; }

double s21::GLModule::get_x_pos() const { return x_pos_; }

void s21::GLModule::set_x_pos(double new_x_pos) { x_pos_ = new_x_pos; }

double s21::GLModule::get_y_pos() const { return y_pos_; }

void s21::GLModule::set_y_pos(double new_y_pos) { y_pos_ = new_y_pos; }

double s21::GLModule::get_z_pos() const { return z_pos_; }

void s21::GLModule::set_z_pos(double new_z_pos) { z_pos_ = new_z_pos; }

void s21::GLModule::set_type_projection(int new_type_projection) {
  type_projection_ = new_type_projection;
}

void s21::GLModule::set_dotted_line(int new_dotted_line) {
  dotted_line_ = new_dotted_line;
}

void s21::GLModule::set_dot_type(int new_dot_type) { dot_type_ = new_dot_type; }

void s21::GLModule::set_dot_depth(double new_dot_depth) {
  dot_depth_ = new_dot_depth;
}

void s21::GLModule::set_line_depth(double new_line_depth) {
  line_depth_ = new_line_depth;
}

void s21::GLModule::set_red_back(double new_red_back) {
  red_back_ = new_red_back;
}

void s21::GLModule::set_green_back(double new_green_back) {
  green_back_ = new_green_back;
}

void s21::GLModule::set_blue_back(double new_blue_back) {
  blue_back_ = new_blue_back;
}

void s21::GLModule::set_red_point(double new_red_point) {
  red_point_ = new_red_point;
}

void s21::GLModule::set_green_point(double new_green_point) {
  green_point_ = new_green_point;
}

void s21::GLModule::set_blue_point(double new_blue_point) {
  blue_point_ = new_blue_point;
}

void s21::GLModule::set_red_line(double new_red_line) {
  red_line_ = new_red_line;
}

void s21::GLModule::set_green_line(double new_green_line) {
  green_line_ = new_green_line;
}

void s21::GLModule::set_blue_line(double new_blue_line) {
  blue_line_ = new_blue_line;
}

void s21::GLModule::SaveCurrentSettings() {
  settings_.setValue("redLine", red_line_);
  settings_.setValue("greenLine", green_line_);
  settings_.setValue("blueLine", blue_line_);
  settings_.setValue("redPoint", red_point_);
  settings_.setValue("greenPoint", green_point_);
  settings_.setValue("bluePoint", blue_point_);
  settings_.setValue("redBack", red_back_);
  settings_.setValue("greenBack", green_back_);
  settings_.setValue("blueBack", blue_back_);
  settings_.setValue("save", 1);
  settings_.setValue("dotDepth", dot_depth_);
  settings_.setValue("lineDepth", line_depth_);
  settings_.setValue("dottedLine", dotted_line_);
  settings_.setValue("dotType", dot_type_);
}

void s21::GLModule::LoadSavedState() {
  if (settings_.value("save").toInt() == 1) {
    red_line_ = settings_.value("redLine").toDouble();
    green_line_ = settings_.value("greenLine").toDouble();
    blue_line_ = settings_.value("blueLine").toDouble();
    red_point_ = settings_.value("redPoint").toDouble();
    green_point_ = settings_.value("greenPoint").toDouble();
    blue_point_ = settings_.value("bluePoint").toDouble();
    red_back_ = settings_.value("redBack").toDouble();
    green_back_ = settings_.value("greenBack").toDouble();
    blue_back_ = settings_.value("blueBack").toDouble();
    dot_depth_ = settings_.value("dotDepth").toDouble();
    line_depth_ = settings_.value("lineDepth").toDouble();
    dotted_line_ = settings_.value("dottedLine").toInt();
    dot_type_ = settings_.value("dotType").toInt();
  }
}

void s21::GLModule::Gif() {
  index_time_++;
  gif_image_->addFrame(GLModule::grabFramebuffer());
  if (index_time_ == 50) {
    timer_->stop();
    gif_image_->save(name_gif_);
    index_time_ = 0;
    emit StopRecord();
    check_timer_ = 1;
    delete timer_;
    delete gif_image_;
  }
}

QSettings *s21::GLModule::get_settings() { return &settings_; }

int s21::GLModule::get_check_timer() { return check_timer_; }

void s21::GLModule::set_name_gif(QString new_name_gif) {
  name_gif_ = std::move(new_name_gif);
}

void s21::GLModule::Record() {
  gif_image_ = new QGifImage();
  timer_ = new QTimer();
  check_timer_ = 0;
  timer_->start(100);
  connect(timer_, SIGNAL(timeout()), this, SLOT(Gif()));
}
