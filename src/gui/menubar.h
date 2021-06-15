/*!
 * @file menubar.h
 * @author omega
 * @date 25/12/2020
 *
 * @brief menubar
 * @details
 *
 *
 */

#ifndef GISL_MENUBAR_H
#define GISL_MENUBAR_H

#include <QAction>
#include <QMenu>
#include <QMenuBar>

#include "../codecvt/dadecoder.h"
#include "../codecvt/daencoder.h"
#include "sld.h"
#include "core/provider/vectorprovider.h"

// QT_BEGIN_NAMESPACE
// namespace Ui { class MenuBar; }
// QT_END_NAMESPACE

class MenuBar : public QMenuBar {
  Q_OBJECT
public:
  explicit MenuBar(QWidget* parent);

  ~MenuBar() override;

public slots:

private:
  //    QWidget *pmWidget;
  //
  //    gisl::VectorProvider *pProvider;
  //    gisl::Sld *pSld;
};

#endif // GISL_MENUBAR_H
