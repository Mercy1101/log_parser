#include "mainwindow.h"

#include <QDebug>
#include <QFileDialog>
#include <iostream>

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  /// QDir::currentPath()
  /// qApp->applicationDirPath();
  /// const char* ch;
  /// QByteArray ba=filename.toLatin1();
  /// ch=ba.data();
  /// File * file=fopen(ch,"r");
  /// fread(myImage,sizeof(unsigned char),515*512,file);
  /// fclose(file);
  create_menu();
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::create_menu() {
  // 第一个菜单
  QMenu *menu1 = menuBar()->addMenu(tr("File"));

  // 创建子菜单，第一个参数QIcon为添加图标，注意路径是否正确，第二个参数是子菜单的显示文本
  QAction *act1 = new QAction(tr("Open File"), this);

  // 创建快捷方式：Ctrl+N，如果想自定义快捷键，可以设置为act->setShortcut(QKeySequence(Qt::CTRL
  // + Qt::Key_N));
  /// act1->setShortcuts(QKeySequence::New);
  act1->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_N));

  // 子菜单触发时执行槽函数，不明白的可以参见前文：信号与槽
  connect(act1, SIGNAL(triggered()), this, SLOT(open_file_slot()));

  // 菜单栏添加子菜单
  menu1->addAction(act1);

  // 第二个菜单：添加二级菜单
  /// QMenu *menu2 = menuBar()->addMenu(tr("菜单栏2"));
  /// QAction *act2 = new QAction(QIcon("../Image/act2.png"), tr("一级菜单"),
  /// this);

  /// QMenu *submenu = new QMenu();
  /// QAction *subact =
  ///     new QAction(QIcon("../Image/subact.png"), tr("二级菜单"), this);
  /// submenu->addAction(subact);
  /// connect(subact, SIGNAL(triggered()), this, SLOT(subSlot()));

  /// act2->setMenu(submenu);  // 将二级菜单添加到一级菜单上
  /// menu2->addAction(act2);  // 将一级菜单添加到菜单栏上
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
  ui->tableWidget->setRowCount(vec.size());
  ui->tableWidget->setColumnCount(8);
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
    ui->tableWidget->setItem(i, 0, new QTableWidgetItem(QString(num.c_str())));
    ui->tableWidget->setItem(i, 1,
                             new QTableWidgetItem(QString(time_str.c_str())));
    ui->tableWidget->setItem(i, 2,
                             new QTableWidgetItem(QString(level.c_str())));
    ui->tableWidget->setItem(i, 3, new QTableWidgetItem(QString(log.c_str())));
    ui->tableWidget->setItem(i, 4,
                             new QTableWidgetItem(QString(function.c_str())));
    ui->tableWidget->setItem(i, 5, new QTableWidgetItem(QString(pid.c_str())));
    ui->tableWidget->setItem(i, 6, new QTableWidgetItem(QString(file.c_str())));
    ui->tableWidget->setItem(i, 7, new QTableWidgetItem(QString(line.c_str())));

    vec.at(i).second.pos;
    vec.at(i).second.state;
  }
}
