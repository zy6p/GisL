/*!
 * @author tau
 * @date 12/31/20
 */

#ifndef GISL_EDITMENU_H
#define GISL_EDITMENU_H

#include <QMenu>
#include <QWidget>

#include "command/commandhistory.h"

class EditMenu : public QMenu {
  Q_OBJECT
public:
  explicit EditMenu(QWidget *parent);

public slots:

  void on_actionUndo_triggered();

  void on_actionRedo_triggered();

private:
  gisl::CommandHistory *pCommandHistory;
};

#endif // GISL_EDITMENU_H
