#ifndef CKRENDERRULE_H
#define CKRENDERRULE_H

#include <QXmlStreamReader>
#include "cksymbolizer.h"

/**
 * @brief The CKRenderRule class
 * created by kmj
 * 功能：建立feature -> 符号化规则的关联
 */
class CKRenderRule {
public:
    CKRenderRule( );

    CKRenderRule( QXmlStreamReader &sld );

    ~CKRenderRule( );

    CKSymbolizer *getPSymbol( ) const;

    QString getField_name( ) const;

    QString getField_value( ) const;

private:
    CKSymbolizer *pSymbol;
    QString field_name;
    QString field_value;
};

#endif // CKRENDERRULE_H
