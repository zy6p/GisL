/*!
 * @author tau
 * @date 12/31/20
 */

#include "editmenu.h"

EditMenu::EditMenu(QWidget *parent) : QMenu(parent) {

  pCommandHistory = gisl::CommandHistory::getCommandHistory();

  //    connect(this->actions()[0], &QAction::triggered, this,
  //    &EditMenu::on_actionUndo_triggered); connect(this->actions()[1],
  //    &QAction::triggered, this, &EditMenu::on_actionRedo_triggered);
}

void EditMenu::on_actionUndo_triggered() { pCommandHistory->rollBack(1); }

void EditMenu::on_actionRedo_triggered() {}
