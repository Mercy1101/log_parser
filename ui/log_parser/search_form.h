#ifndef SEARCH_FORM_H
#define SEARCH_FORM_H

#include <QWidget>

namespace Ui {
class search_form;
}

class search_form : public QWidget {
  Q_OBJECT
 signals:
  void set_search_keyword_sig(const std::string keyword);
  void set_level_keyword_sig(const std::string keyword);
  void set_hidden_sig(const std::string keyword);
  void set_search_keyword_ignorecase_sig(const std::string keyword);
  void set_search_whole_sig(const std::string keyword);

 public:
  explicit search_form(QWidget *parent = nullptr);
  ~search_form();

 private slots:
  void on_pushButton_clicked();
  void on_search_level_clicked();
  void on_hide_btn_clicked();

  void on_search_ignorecase_clicked();

  void on_search_whole_clicked();

 private:
  Ui::search_form *ui;
};

#endif  // SEARCH_FORM_H
