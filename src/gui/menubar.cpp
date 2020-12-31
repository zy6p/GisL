/*!
 * @file menubar.cpp
 * @author omega 
 * @date 25/12/2020
 * 
 * @brief
 * @details
 *
 */

#include "menubar.h"

#include <QLabel>
#include <QString>
#include <QFileDialog>
#include <QMessageBox>

#include "command/commandhistory.h"
#include "command/command.h"
#include "command/openvectorcommand.h"
#include "../utils/ptroperate.h"

MenuBar::MenuBar( QWidget *parent ) : QMenuBar( parent ) {


}


MenuBar::~MenuBar( ) {
}
