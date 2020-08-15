#include "mainwindow.h"

#include <QDebug>
#include <QFileDialog>
#include <iostream>

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  create_menu();
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::create_menu() {
  QMenu *menu1 = menuBar()->addMenu(tr("File"));
  QAction *act1 = new QAction(tr("Open File"), this);
  act1->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_O));
  connect(act1, SIGNAL(triggered()), this, SLOT(open_file_slot()));
  menu1->addAction(act1);

  QMenu *menu2 = menuBar()->addMenu(tr("Find"));
  QAction *act2 = new QAction(tr("Add keyword"), this);
  act2->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_F));
  connect(act2, SIGNAL(triggered()), this, SLOT(add_condtion_slot()));
  menu2->addAction(act2);

  QAction *act3 = new QAction(tr("Clear filter"), this);
  act3->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_L));
  connect(act3, SIGNAL(triggered()), this, SLOT(clear_filter_slot()));
  menu2->addAction(act3);
}

void MainWindow::open_file_slot() {
  if (log_ != nullptr) {
    delete log_;
  }
  auto file_name = get_file_name();
  log_ = new lee::log_parser(file_name);
  add_data_into_table(log_->get_log_view_vec());
}

std::string MainWindow::get_file_name() {
  /// auto open_folder =
  ///     QDir::currentPath() + lee::folder_sep + "log" + lee::folder_sep;
  /// auto open_folder = "../" + QDir::currentPath();
  QString open_folder = "./";
  auto file_full = QFileDialog::getOpenFileName(
      this, tr("Open Log File"), open_folder, "log files(*.log *.txt)");
  QFileInfo fi = QFileInfo(file_full);
  auto file_name = fi.fileName();
  auto file_path = fi.absolutePath();
  return file_path.toStdString() + lee::folder_sep + file_name.toStdString();
}

void MainWindow::add_data_into_table(lee::log_view_vec &vec) {
  ui->tableWidget->clear();
  ui->tableWidget->setRowCount(static_cast<int>(vec.size()));
  ui->tableWidget->setColumnCount(8);
  ui->tableWidget->setSortingEnabled(true);
  ui->tableWidget->horizontalHeader()->setSectionResizeMode(
      QHeaderView::Stretch);
  ui->tableWidget->horizontalHeader()->setSectionResizeMode(
      0, QHeaderView::ResizeToContents);
  ui->tableWidget->horizontalHeader()->setSectionResizeMode(
      3, QHeaderView::ResizeToContents);
  /// ui->tableWidget->setWindowTitle("QTableWidget & Item");
  /// ui->tableWidget->resize(400, 300);  //设置表格
  QStringList header;
  header << "No"
         << "Time"
         << "Level"
         << "Log"
         << "Function"
         << "PID"
         << "File"
         << "Line";
  ui->tableWidget->setHorizontalHeaderLabels(header);

  for (size_t i = 0; i < vec.size(); i++) {
    auto num = std::to_string(vec.at(i).second.count_);
    auto time_str = vec.at(i).first.get().get_time_str();
    auto level = vec.at(i).first.get().get_level();
    auto log = vec.at(i).first.get().get_log();
    auto location = vec.at(i).first.get().get_location();
    auto function = std::get<lee::log_info::FUNC>(location);
    auto file = std::get<lee::log_info::FILE>(location);
    auto line = std::to_string(std::get<lee::log_info::LINE>(location));
    auto pid = std::to_string(std::get<lee::log_info::PID>(location));
    int index = static_cast<int>(i);
    if (lee::VISABLE_STATE::VISABLE <= vec.at(i).second.state) {
      ui->tableWidget->setItem(index, 0,
                               new QTableWidgetItem(QString(num.c_str())));
      ui->tableWidget->setItem(index, 1,
                               new QTableWidgetItem(QString(time_str.c_str())));
      auto p_item = new QTableWidgetItem(QString(level.c_str()));
      p_item->setBackground(get_level_color(level));
      ui->tableWidget->setItem(index, 2, p_item);
      ui->tableWidget->setItem(index, 3,
                               new QTableWidgetItem(QString(log.c_str())));
      ui->tableWidget->setItem(index, 4,
                               new QTableWidgetItem(QString(function.c_str())));
      ui->tableWidget->setItem(index, 5,
                               new QTableWidgetItem(QString(pid.c_str())));
      ui->tableWidget->setItem(index, 6,
                               new QTableWidgetItem(QString(file.c_str())));
      ui->tableWidget->setItem(index, 7,
                               new QTableWidgetItem(QString(line.c_str())));

      vec.at(i).second.pos;
    } else {
      auto item_num = new QTableWidgetItem(QString(num.c_str()));
      item_num->setBackground(Qt::gray);
      ui->tableWidget->setItem(index, 0, item_num);

      auto item_time = new QTableWidgetItem(QString(time_str.c_str()));
      item_time->setBackground(Qt::gray);
      ui->tableWidget->setItem(index, 1, item_time);

      auto item_level = new QTableWidgetItem(QString(level.c_str()));
      item_level->setBackground(Qt::gray);
      ui->tableWidget->setItem(index, 2, item_level);

      auto item_log = new QTableWidgetItem(QString(log.c_str()));
      item_log->setBackground(Qt::gray);
      ui->tableWidget->setItem(index, 3, item_log);

      auto item_func = new QTableWidgetItem(QString(function.c_str()));
      item_func->setBackground(Qt::gray);
      ui->tableWidget->setItem(index, 4, item_func);

      auto item_pid = new QTableWidgetItem(QString(pid.c_str()));
      item_pid->setBackground(Qt::gray);
      ui->tableWidget->setItem(index, 5, item_pid);

      auto item_file = new QTableWidgetItem(QString(file.c_str()));
      item_file->setBackground(Qt::gray);
      ui->tableWidget->setItem(index, 6, item_file);

      auto item_line = new QTableWidgetItem(QString(line.c_str()));
      item_line->setBackground(Qt::gray);
      ui->tableWidget->setItem(index, 7, item_line);
    }
  }
}

Qt::GlobalColor MainWindow::get_level_color(const std::string &level) {
  auto result = lee::log_level::level_map.find(level);
  if (result != lee::log_level::level_map.end()) {
    if (result->second == lee::log_level::color::red) {
      return Qt::red;
    }
    if (result->second == lee::log_level::color::blue) {
      return Qt::blue;
    }
    if (result->second == lee::log_level::color::gray) {
      return Qt::gray;
    }
    if (result->second == lee::log_level::color::green) {
      return Qt::green;
    }
    if (result->second == lee::log_level::color::white) {
      return Qt::white;
    }
    if (result->second == lee::log_level::color::yellow) {
      return Qt::yellow;
    }
    return Qt::white;
  } else {
    return Qt::white;
  }
}

void MainWindow::create_search_panel() {
  if (search_form_ != nullptr) {
    delete search_form_;
  }
  search_form_ = new search_form();

  connect(search_form_, SIGNAL(set_search_keyword_sig(const std::string)), this,
          SLOT(search_log_slot(const std::string)));
  connect(search_form_, SIGNAL(set_level_keyword_sig(const std::string)), this,
          SLOT(search_level_slot(const std::string)));
  connect(search_form_, SIGNAL(set_hidden_sig(const std::string)), this,
          SLOT(hidden_log_slot(const std::string)));
  connect(search_form_,
          SIGNAL(set_search_keyword_ignorecase_sig(const std::string)), this,
          SLOT(search_log_ignorecase_slot(const std::string)));
  connect(search_form_, SIGNAL(set_search_whole_sig(const std::string)), this,
          SLOT(search_log_wholeword_slot(const std::string)));
  search_form_->show();
}

void MainWindow::add_condtion_slot() { create_search_panel(); }

void MainWindow::search_log_slot(const std::string key_word) {
  lee::cond_vec vec;
  vec.push_back({key_word, lee::VISABLE_STATE::HIGHLIGHT});
  log_->find_log(vec);
  add_data_into_table(log_->get_log_view_vec());
}

void MainWindow::search_level_slot(const std::string level) {
  lee::cond_vec vec;
  vec.push_back({level, lee::VISABLE_STATE::HIGHLIGHT});
  log_->find_level(vec);
  add_data_into_table(log_->get_log_view_vec());
}

void MainWindow::hidden_log_slot(const std::string hidden_keyword) {
  lee::cond_vec vec;
  vec.push_back({hidden_keyword, lee::VISABLE_STATE::HIGHLIGHT});
  log_->hidden_log(vec);
  add_data_into_table(log_->get_log_view_vec());
}

void MainWindow::search_log_ignorecase_slot(const std::string log) {
  lee::cond_vec vec;
  vec.push_back({log, lee::VISABLE_STATE::HIGHLIGHT});
  log_->find_log_ignorecase(vec);
  add_data_into_table(log_->get_log_view_vec());
}

void MainWindow::search_log_wholeword_slot(const std::string whole_word) {
  lee::cond_vec vec;
  vec.push_back({whole_word, lee::VISABLE_STATE::HIGHLIGHT});
  log_->find_log_wholeword(vec);
  add_data_into_table(log_->get_log_view_vec());
}

void MainWindow::clear_filter() {
  log_->clear_condition();
  add_data_into_table(log_->get_log_view_vec());
}

void MainWindow::clear_filter_slot() { clear_filter(); }
