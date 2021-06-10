#ifndef CKFIELDDEF_H
#define CKFIELDDEF_H

#include <QJsonValue>
#include <QString>

class CKFieldDef {
public:
  CKFieldDef();

  CKFieldDef(QString key, QJsonValue value);

  QString getField_name() const;

  QString getStrValue() const;

private:
  QString field_name;
  double dValue;
  QString strValue;

  enum FieldType { ft_double, ft_string };
};

#endif // CKFIELDDEF_H
