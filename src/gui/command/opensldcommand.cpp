/*!
 * @author tau
 * @date 12/30/20
 */

#include "opensldcommand.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QObject>

#include "../../utils/ptroperate.h"
#include "../sld.h"

void gisl::OpenSldCommand::execute(QWidget *parent) {
  QString openFileName = QFileDialog::getOpenFileName(
      parent, QObject::tr("open an sld file."), "../",
      QObject::tr("Sld(*.sld);;All files(*.*)"), nullptr,
      QFileDialog::DontUseNativeDialog);
  if (openFileName.isEmpty()) {
    QMessageBox::warning(parent, QObject::tr("Warning!"),
                         QObject::tr("Cancel to open the file!"));
  } else {
    pSld = new gisl::Sld(openFileName.toStdString());
    // todo sld do what
  }
}

const std::string &gisl::OpenSldCommand::output() { return sldName; }

void gisl::OpenSldCommand::reverse() { PtrOperate::clear(pSld); }

gisl::OpenSldCommand::~OpenSldCommand() { PtrOperate::clear(pSld); }
