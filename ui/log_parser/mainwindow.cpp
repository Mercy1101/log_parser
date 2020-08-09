#include "mainwindow.h"

#include <QFileDialog>
#include <iostream>

#include "log_parser/data_struct_define.hpp"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  ui->tableWidget->setRowCount(10);
  ui->tableWidget->setColumnCount(5);
  ui->tableWidget->setWindowTitle("QTableWidget & Item");
  ui->tableWidget->resize(400, 300);  //设置表格
  QStringList header;
  header << "Name"
         << "Age";  //表头
  ui->tableWidget->setHorizontalHeaderLabels(header);
  ui->tableWidget->setItem(0, 0, new QTableWidgetItem("张飞"));
  ui->tableWidget->setItem(1, 0, new QTableWidgetItem("关羽"));
  ui->tableWidget->setItem(2, 0, new QTableWidgetItem("吕布"));

  ui->tableWidget->setItem(0, 1, new QTableWidgetItem("35"));
  ui->tableWidget->setItem(1, 1, new QTableWidgetItem("36"));
  ui->tableWidget->setItem(2, 1, new QTableWidgetItem("32"));

  auto open_folder =
      QDir::currentPath() + lee::folder_sep + "log" + lee::folder_sep;
  QString filename = QFileDialog::getOpenFileName(
      this, tr("打开日志文件"), open_folder, "log file(*.log *.text)");
  (void)filename;
  std::cout << filename.toStdString() << std::endl;
  /// QDir::currentPath()
  /// qApp->applicationDirPath();
  /// const char* ch;
  /// QByteArray ba=filename.toLatin1();
  /// ch=ba.data();
  /// File * file=fopen(ch,"r");
  /// fread(myImage,sizeof(unsigned char),515*512,file);
  /// fclose(file);
}

MainWindow::~MainWindow() { delete ui; }
