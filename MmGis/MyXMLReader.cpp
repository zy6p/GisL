#include "MyXMLReader.h"


MyXMLReader::MyXMLReader(void) {
}


MyXMLReader::~MyXMLReader(void) {
}

void hexToRgb(int mode, QString hex, CGeoLayer *layer);

bool MyXMLReader::readSLDFile(const QString fileName, CGeoLayer *layer) {
    if (fileName.isEmpty())
        return false;

    QFile *file = new QFile(fileName);
    if (!file->open(QFile::ReadOnly | QFile::Text)) {
        QMessageBox::information(NULL, QString("title"), QString("open error!"));
        return false;
    }
    reader.setDevice(file);

    while (!reader.atEnd()) {
        //�ж��Ƿ��ǿ�ʼԪ��
        if (reader.isStartElement()) {
            //�ж϶�ȡ�ĸ���ǩ�Ƿ���bookindex
            qDebug() << reader.name();
            if (reader.name().compare("NamedLayer") == 0) {
                //��bookindex ���¶�ȡ
                readNamedLayer(layer);
            } else {
                reader.readNext();
            }
        } else {
            reader.readNext();
        }
    }
    //�ļ��ǵùر�
    file->close();
    if (reader.hasError()) {
        return false;
    } else if (file->error() != QFile::NoError) {
        return false;
    }
    return true;
}

void MyXMLReader::readNamedLayer(CGeoLayer *layer) {
    //Q_ASSERT()�Ӷ���  ����������ʱ�� StartElement״̬������˵��ǩ���� NamedLayer������Ϊ����
    Q_ASSERT(reader.isStartElement() && reader.name() == "NamedLayer");
    //���¶�ȡ
    reader.readNext();
    while (!reader.atEnd()) {
        //�ж��ǽ����ڵ㣬����
        if (reader.isEndElement()) {
            reader.readNext();
            break;
        }

        if (reader.isStartElement()) {
            qDebug() << reader.name();
            if (reader.name() == "Name") {
                readName(layer);
            } else if (reader.name() == "UserStyle") {
                readUserStyle(layer);
            } else {
                //û����entry�ڵ� ����
                skipUnknownElement();
            }
        } else {
            reader.readNext();
        }
    }
}

void MyXMLReader::readName(CGeoLayer *layer) {
    //��ȡname
    QString name = reader.readElementText();
    qDebug() << name;
    if (reader.isEndElement()) {
        reader.readNext();
    }
}


void MyXMLReader::readUserStyle(CGeoLayer *layer) {
    //Q_ASSERT()�Ӷ���  ����������ʱ�� StartElement״̬������˵��ǩ���� NamedLayer������Ϊ����
    Q_ASSERT(reader.isStartElement() && reader.name() == "UserStyle");
    //���¶�ȡ
    reader.readNext();
    while (!reader.atEnd()) {
        //�ж��ǽ����ڵ㣬����
        if (reader.isEndElement()) {
            reader.readNext();
            break;
        }

        if (reader.isStartElement()) {
            qDebug() << reader.name();
            if (reader.name() == "Title") {
                readTitle(layer);
            } else if (reader.name() == "Abstract") {
                readAbstract(layer);
            } else if (reader.name() == "FeatureTypeStyle") {
                readFeatureTypeStyle(layer);
            } else {
                //û����entry�ڵ� ����
                skipUnknownElement();
            }
        } else {
            reader.readNext();
        }
    }
}

void MyXMLReader::readFeatureTypeStyle(CGeoLayer *layer) {
    //Q_ASSERT()�Ӷ���  ����������ʱ�� StartElement״̬������˵��ǩ���� NamedLayer������Ϊ����
    Q_ASSERT(reader.isStartElement() && reader.name() == "FeatureTypeStyle");
    //���¶�ȡ
    reader.readNext();
    while (!reader.atEnd()) {
        //�ж��ǽ����ڵ㣬����
        if (reader.isEndElement()) {
            reader.readNext();
            break;
        }

        if (reader.isStartElement()) {
            qDebug() << reader.name();
            if (reader.name() == "Rule") {
                readRule(layer);
            } else {
                //û����entry�ڵ� ����
                skipUnknownElement();
            }
        } else {
            reader.readNext();
        }
    }
}

void MyXMLReader::readRule(CGeoLayer *layer) {
    //Q_ASSERT()�Ӷ���  ����������ʱ�� StartElement״̬������˵��ǩ���� NamedLayer������Ϊ����
    Q_ASSERT(reader.isStartElement() && reader.name() == "Rule");
    //���¶�ȡ
    reader.readNext();
    while (!reader.atEnd()) {
        //�ж��ǽ����ڵ㣬����
        if (reader.isEndElement()) {
            reader.readNext();
            break;
        }

        if (reader.isStartElement()) {
            qDebug() << reader.name();
            if (reader.name() == "Name") {
                readName(layer);
            } else if (reader.name() == "Title") {
                readTitle(layer);
            } else if (reader.name() == "Abstract") {
                readAbstract(layer);
            } else if (reader.name() == "PolygonSymbolizer") {
                readPolygonSymbolizer(layer);
            } else {
                //û����entry�ڵ� ����
                skipUnknownElement();
            }
        } else {
            reader.readNext();
        }
    }
}

void MyXMLReader::readPolygonSymbolizer(CGeoLayer *layer) {
    //Q_ASSERT()�Ӷ���  ����������ʱ�� StartElement״̬������˵��ǩ���� NamedLayer������Ϊ����
    Q_ASSERT(reader.isStartElement() && reader.name() == "PolygonSymbolizer");
    //���¶�ȡ
    reader.readNext();
    while (!reader.atEnd()) {
        //�ж��ǽ����ڵ㣬����
        if (reader.isEndElement()) {
            reader.readNext();
            break;
        }
        qDebug() << reader.name();
        if (reader.isStartElement()) {
            if (reader.name() == "Fill") {
                readFill(layer);
            } else if (reader.name() == "Stroke") {
                readStroke(layer);
            } else {
                //û����entry�ڵ� ����
                skipUnknownElement();
            }
        } else {
            reader.readNext();
        }
    }
}

void MyXMLReader::readFill(CGeoLayer *layer) {
    //Q_ASSERT()�Ӷ���  ����������ʱ�� StartElement״̬������˵��ǩ���� NamedLayer������Ϊ����
    Q_ASSERT(reader.isStartElement() && reader.name() == "Fill");
    //���¶�ȡ
    reader.readNext();
    while (!reader.atEnd()) {
        //�ж��ǽ����ڵ㣬����
        if (reader.isEndElement()) {
            reader.readNext();
            break;
        }

        if (reader.isStartElement()) {
            qDebug() << reader.name();
            if (reader.name() == "CssParameter") {
                readCssParameter(layer);
            } else {
                skipUnknownElement();
            }
        } else {
            reader.readNext();
        }
    }
}

void MyXMLReader::readStroke(CGeoLayer *layer) {
    //Q_ASSERT()�Ӷ���  ����������ʱ�� StartElement״̬������˵��ǩ���� NamedLayer������Ϊ����
    Q_ASSERT(reader.isStartElement() && reader.name() == "Stroke");
    //���¶�ȡ
    reader.readNext();
    while (!reader.atEnd()) {
        //�ж��ǽ����ڵ㣬����
        if (reader.isEndElement()) {
            reader.readNext();
            break;
        }
        if (reader.isStartElement()) {
            qDebug() << reader.name();
            if (reader.name() == "CssParameter") {
                readCssParameter(layer);
            } else {
                //û����entry�ڵ� ����
                skipUnknownElement();
            }
        } else {
            reader.readNext();
        }
    }
}

void MyXMLReader::readCssParameter(CGeoLayer *layer) {
    QString name = reader.attributes().value("name").toString();
    if (name.compare("fill") == 0) {
        QString fillColor = reader.readElementText();
        hexToRgb(0, fillColor, layer);
    }
    if (name.compare("stroke") == 0) {
        QString strokeColor = reader.readElementText();
        hexToRgb(1, strokeColor, layer);
    }
    if (name.compare("stroke-width") == 0) {
        QString strokeWidth = reader.readElementText();
        bool ok;
        for (int i = 0; i < layer->geoObjects.size(); i++) {
            layer->geoObjects[i]->strokeWidth = strokeWidth.toDouble(&ok);
        }
    }
    if (reader.isEndElement()) {
        reader.readNext();
    }
}


void hexToRgb(int mode, QString hex, CGeoLayer *layer) {
    /*
    hex: {String}, "#333", "#AF0382"
    */
    hex = hex.remove(QChar('#'), Qt::CaseInsensitive);
    if (hex.size() == 3) {
        hex = hex.left(1) + hex.at(0) + hex.at(1) + hex.at(1) + hex.at(2) + hex.at(2);
    }

    float r, g, b;
    bool ok;
    r = hex.left(2).toInt(&ok, 16);
    g = hex.mid(2, 2).toInt(&ok, 16);
    b = hex.mid(4, 2).toInt(&ok, 16);
    if (mode == 0) {
        for (int i = 0; i < layer->geoObjects.size(); i++) {
            layer->geoObjects[i]->fillR = r / 255;
            layer->geoObjects[i]->fillG = g / 255;
            layer->geoObjects[i]->fillB = b / 255;
            layer->geoObjects[i]->fillAlpha = 1.0;
        }
    } else if (mode == 1) {
        for (int i = 0; i < layer->geoObjects.size(); i++) {
            layer->geoObjects[i]->strokeR = r / 255;
            layer->geoObjects[i]->strokeG = g / 255;
            layer->geoObjects[i]->strokeB = b / 255;
            layer->geoObjects[i]->strokeAlpha = 1.0;

        }
    }
}

void MyXMLReader::readTitle(CGeoLayer *layer) {
    //��ȡname
    QString name = reader.readElementText();
    if (reader.isEndElement()) {
        reader.readNext();
    }
}

void MyXMLReader::readAbstract(CGeoLayer *layer) {
    //��ȡname
    QString name = reader.readElementText();
    if (reader.isEndElement()) {
        reader.readNext();
    }
}

void MyXMLReader::skipUnknownElement() {
    reader.readNext();
    //û�н���
    while (!reader.atEnd()) {
        //����
        if (reader.isEndElement()) {
            reader.readNext();
            break;
        }
        //����������ȡ��
        if (reader.isStartElement()) {
            skipUnknownElement();
        } else {
            reader.readNext();
        }
    }
}