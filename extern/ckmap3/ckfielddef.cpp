#include "ckfielddef.h"

CKFieldDef::CKFieldDef( ) {

}

CKFieldDef::CKFieldDef( QString key, QJsonValue value ) {
    this->field_name = key;
    if ( value.isDouble())
        dValue = value.toDouble();
    else if ( value.isString())
        strValue = value.toString();

}

QString CKFieldDef::getField_name( ) const {
    return field_name;
}

QString CKFieldDef::getStrValue( ) const {
    return strValue;
}
