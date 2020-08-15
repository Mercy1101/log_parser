#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <string>

#include "log_parser.hpp"
#include "log_parser/data_struct_define.hpp"
#include "search_form.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
  Q_OBJECT
 signals:
 public slots:
  void open_file_slot();
  void add_condtion_slot();
  void search_log_slot(const std::string keyword);
  void search_level_slot(const std::string level);
  void hidden_log_slot(const std::string hidden_keyword);
  void clear_filter_slot();
  void search_log_ignorecase_slot(const std::string log);
  void search_log_wholeword_slot(const std::string whole_word);

 public:
  explicit MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private:
  Ui::MainWindow *ui;
  lee::log_parser *log_ = nullptr;
  search_form *search_form_;
  void create_menu();
  std::string get_file_name();
  void add_data_into_table();
  void add_data_into_table(lee::log_view_vec &vec);
  Qt::GlobalColor get_level_color(const std::string &level);
  void create_search_panel();
  void clear_filter();
};

#endif  // MAINWINDOW_H
