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

#include <QFileDialog>
#include <QLabel>
#include <QMessageBox>
#include <QString>

#include "../utils/ptroperate.h"
#include "command/command.h"
#include "command/commandhistory.h"
#include "command/openvectorcommand.h"

MenuBar::MenuBar(QWidget *parent) : QMenuBar(parent) {}

MenuBar::~MenuBar() {}
