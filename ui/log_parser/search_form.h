#ifndef SEARCH_FORM_H
#define SEARCH_FORM_H

#include <QWidget>

namespace Ui {
class search_form;
}

class search_form : public QWidget
{
  Q_OBJECT

public:
  explicit search_form(QWidget *parent = nullptr);
  ~search_form();

private:
  Ui::search_form *ui;
};

#endif // SEARCH_FORM_H
