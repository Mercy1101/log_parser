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
  // 第一个菜单
  QMenu *menu1 = menuBar()->addMenu(tr("File"));

  // 创建子菜单，第一个参数QIcon为添加图标，注意路径是否正确，第二个参数是子菜单的显示文本
  QAction *act1 = new QAction(tr("Open File"), this);

  act1->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_O));

  // 子菜单触发时执行槽函数，不明白的可以参见前文：信号与槽
  connect(act1, SIGNAL(triggered()), this, SLOT(open_file_slot()));

  // 菜单栏添加子菜单
  menu1->addAction(act1);
}

void MainWindow::open_file_slot() {
  auto file_name = get_file_name();
  qDebug() << file_name.c_str();
  log_ = new lee::log_parser(file_name);
  add_data_into_table(log_->get_log_view_vec());
}
std::string MainWindow::get_file_name() {
  auto open_folder =
      QDir::currentPath() + lee::folder_sep + "log" + lee::folder_sep;
  /// QFileDialog dialog(this);
  /// dialog.setFileMode(QFileDialog::AnyFile);
  /// QStringList file_name;
  /// if (dialog.exec()) file_name = dialog.selectedFiles();
  /// QString filename = QFileDialog::getOpenFileName(
  ///     this, tr("打开日志文件"), open_folder, "log file(*.log *.text)");

  QString file_full, file_name, file_path;
  QFileInfo fi;

  file_full =
      QFileDialog::getOpenFileName(this, tr("Open Log File"), open_folder);

  fi = QFileInfo(file_full);
  file_name = fi.fileName();
  file_path = fi.absolutePath();
  return file_path.toStdString() + lee::folder_sep + file_name.toStdString();
}

void MainWindow::add_data_into_table(lee::log_view_vec &vec) {
  ui->tableWidget->setRowCount(static_cast<int>(vec.size()));
  ui->tableWidget->setColumnCount(8);
  ui->tableWidget->setSortingEnabled(true);
  ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
  ui->tableWidget->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
  ui->tableWidget->horizontalHeader()->setSectionResizeMode(3, QHeaderView::ResizeToContents);
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
    ui->tableWidget->setItem(index, 0, new QTableWidgetItem(QString(num.c_str())));
    ui->tableWidget->setItem(index, 1,
                             new QTableWidgetItem(QString(time_str.c_str())));
    auto p_item = new QTableWidgetItem(QString(level.c_str()));
    p_item->setBackground(get_level_color(level));
    ui->tableWidget->setItem(index, 2, p_item);
    ui->tableWidget->setItem(index, 3, new QTableWidgetItem(QString(log.c_str())));
    ui->tableWidget->setItem(index, 4,
                             new QTableWidgetItem(QString(function.c_str())));
    ui->tableWidget->setItem(index, 5, new QTableWidgetItem(QString(pid.c_str())));
    ui->tableWidget->setItem(index, 6, new QTableWidgetItem(QString(file.c_str())));
    ui->tableWidget->setItem(index, 7, new QTableWidgetItem(QString(line.c_str())));

    vec.at(i).second.pos;
    vec.at(i).second.state;
  }
}

Qt::GlobalColor MainWindow::get_level_color(const std::string& level){
auto result = lee::log_level::level_map.find(level);
if(result != lee::log_level::level_map.end()){
    if(result->second == lee::log_level::color::red){
        return Qt::red;
    }
    if(result->second == lee::log_level::color::blue){
        return Qt::blue;
    }
    if(result->second == lee::log_level::color::gray){
        return Qt::gray;
    }
    if(result->second == lee::log_level::color::green){
        return Qt::green;
    }
    if(result->second == lee::log_level::color::white){
        return Qt::white;
    }
    if(result->second == lee::log_level::color::yellow){
        return Qt::yellow;
    }
    return Qt::white;
}
else {
    return Qt::white;
}
}
