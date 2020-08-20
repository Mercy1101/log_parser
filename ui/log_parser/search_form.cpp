#include "search_form.h"

#include "ui_search_form.h"

search_form::search_form(QWidget *parent)
    : QWidget(parent), ui(new Ui::search_form) {
  ui->setupUi(this);
  QWidget::setTabOrder(this->ui->search_text, this->ui->pushButton);
  QWidget::setTabOrder(this->ui->pushButton, this->ui->search_ignorecase);
}

search_form::~search_form() { delete ui; }

void search_form::on_pushButton_clicked() {
  auto keyword = this->ui->search_text->text().toStdString();
  emit set_search_keyword_sig(keyword);
  this->close();
}

void search_form::on_search_level_clicked() {
  auto keyword = this->ui->search_text->text().toStdString();
  emit set_level_keyword_sig(keyword);
  this->close();
}

void search_form::on_hide_btn_clicked() {
  auto keyword = this->ui->search_text->text().toStdString();
  emit set_hidden_sig(keyword);
  this->close();
}

void search_form::on_search_ignorecase_clicked() {
  auto keyword = this->ui->search_text->text().toStdString();
  emit set_search_keyword_ignorecase_sig(keyword);
  this->close();
}

void search_form::on_search_whole_clicked() {
  auto keyword = this->ui->search_text->text().toStdString();
  emit set_search_whole_sig(keyword);
  this->close();
}
