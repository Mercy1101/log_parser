#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <string>

#include "log_parser.hpp"
#include "log_parser/data_struct_define.hpp"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
  Q_OBJECT
 signals:
 public slots:
  void open_file_slot();

 public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();

 private:
  Ui::MainWindow *ui;
  lee::log_parser *log_ = nullptr;
  void create_menu();
  std::string get_file_name();
  void add_data_into_table();
  void add_data_into_table(lee::log_view_vec &vec);
};

#endif  // MAINWINDOW_H
