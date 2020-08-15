#include "search_form.h"
#include "ui_search_form.h"

search_form::search_form(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::search_form)
{
  ui->setupUi(this);
}

search_form::~search_form()
{
  delete ui;
}
