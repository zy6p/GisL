#include "QtFunctionWidget.h"
#include "EnumType.h"
#include <QFile>
#include <cmath>
#include "util.h"
#include <qlist.h>
#include "TextOutWidget.h"

QtFunctionWidget::QtFunctionWidget(QWidget *parent) : QOpenGLWidget(parent), hasSetRect(false), scale(0.8),
                                                      hasWaH(false), currentLayer(NULL), hasTableShowing(false) {
    map = new GeoMap;
    setMouseTracking(true);
    setFocusPolicy(Qt::StrongFocus);
}

QtFunctionWidget::~QtFunctionWidget() {
    makeCurrent();

    shaderProgram.release();
    doneCurrent();
    for (int i = 0; i < map->size(); i++) {
        deleteLayer(map->getLayerAt(i));
    }

    //�����map���Է�ֹ������objΪNULL
    if (map) {
        delete map;
    }
}

void QtFunctionWidget::initializeGL() {
    if (!map) {
        map = new GeoMap;
    }
    this->initializeOpenGLFunctions();

    bool success = shaderProgram.addShaderFromSourceFile(QOpenGLShader::Vertex, "GLConfig//vertexShader1.vsh");
    if (!success) {
        qDebug() << "shaderProgram addShaderFromSourceFile failed!" << shaderProgram.log();
        return;
    }

    success = shaderProgram.addShaderFromSourceFile(QOpenGLShader::Fragment, "GLConfig//fragmentShader1.fsh");
    if (!success) {
        qDebug() << "shaderProgram addShaderFromSourceFile failed!" << shaderProgram.log();
        return;
    }

    success = shaderProgram.link();
    if (!success) {
        qDebug() << "shaderProgram link failed!" << shaderProgram.log();
    }
    glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);  //����������Ϊenable�������õ��size���Ǹ���
    glEnable(GL_POINT_SMOOTH);
    glEnable(GL_LINE_SMOOTH);
    glHint(GL_POINT_SMOOTH_HINT, GL_NICEST); // Make round points, not square points
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);  // Antialias the lines
    glEnable(GL_BLEND); //����ɫ�ʻ��
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void QtFunctionWidget::resizeGL(int w, int h) {

    glViewport(0, 0, w, h);
    if (currentLayer == NULL) {
        return;
    }
    if (!hasWaH) {
        this->w = w;
        this->h = h;
        hasWaH = true;
        return;
    }
    QPointF center = worldRect.center();
    float width = worldRect.width() * w * 1.0 / this->w;
    float height = worldRect.height() * h * 1.0 / this->h;
    worldRect = QRectF(QPointF(center.x() - width / 2, center.y() - height / 2),
                       QPointF(center.x() + width / 2, center.y() + height / 2));
    this->w = w;
    this->h = h;
    project();    //����ͶӰ
}


void QtFunctionWidget::paintGL() {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    loadWaitLayers();   //���еĹ���gl������߼��ڴ�ִ��
    if (!map->size()) {
        return;
    }
    glClear(GL_COLOR_BUFFER_BIT);
    shaderProgram.bind();
    {
        qDebug() << "........................................";
        for (int j = 0; j < map->size(); j++) {   //��map�ĵ�һ��layer�����ƣ���Ϊ��һ��Ϊ��ײ�
            GeoLayer *layer = map->getLayerAt(j);

            int dataType = layer->getDataType();
            int rendererType = layer->getRendererType();
            QString attriToStretch = layer->getAttriToStretch();

            if (layer->isVisable()) {
                int type = layer->getType();
                Render *render = layer->getRender();
                StretchRenderer *streRenderer = layer->getStretchRenderer();
                //�����߿�
                if (type == EnumType::POINT) {
                    shaderProgram.setUniformValue("size", render->getMarkerSymbol()->getSize());
                } //��ʱ��Ч��glPointSize�޷�ʹ��
                else if (type == EnumType::POLYLINE) { glLineWidth(render->getLineSymbol()->getWidth()); }
                else if (type = EnumType::POLYGON) { glLineWidth(render->getFillSymbol()->getOutline()->getWidth()); }
                if (layer->size() && featureVaosMap.size()) {
                    int renderLayerNum = featureVaosMap[layer->getFeatureAt(0)]->size();
                    if (dataType == EnumType::dataRenderType::GRIDTYPE) renderLayerNum = 1;
                    for (int i = 0; i < renderLayerNum; i++) {
                        bool renderColorChanged = true;
                        for (int m = 0; m < layer->size(); m++) {
                            GeoFeature *feature = layer->getFeatureAt(m);
                            QOpenGLVertexArrayObject *vao = featureVaosMap[feature]->at(i);
                            QOpenGLVertexArrayObject::Binder vaoBind(vao);
                            int geoRenderType = vao->property("geoRenderType").toInt();
                            if (renderColorChanged) {  //������Ⱦ����ɫ,��������Ʋ�֧�ֲַ���ɫ����Ҫ֧�֣���Ҫÿ��feature����vao����һ����ɫ
                                setDefaultRenderColor(dataType, rendererType,
                                                      render, geoRenderType, streRenderer,
                                                      (*(feature->getAttributeMap()))[attriToStretch].toFloat());
                                renderColorChanged = false;
                            }
                            if (dataType == EnumType::dataRenderType::GRIDTYPE &&
                                rendererType == EnumType::rendererType::STRETCHRGB) {  //դ��ÿ�ζ�Ҫ�ĸ���ɫ
                                setDefaultRenderColor(dataType, rendererType,
                                                      render, geoRenderType, streRenderer,
                                                      (*(feature->getAttributeMap()))[attriToStretch].toFloat());
                            }
                            if (dataType == EnumType::dataRenderType::GEOMETRYTYPE &&
                                rendererType == EnumType::rendererType::STRETCHRGB) {
                                setDefaultRenderColor(dataType, rendererType,
                                                      render, geoRenderType, streRenderer,
                                                      (*(feature->getAttributeMap()))[attriToStretch].toFloat());
                            }
                            if (layer->getSelectedFeatures().size()) {  //���ñ�ѡ�����ɫ����
                                if (layer->hasSelected(feature)) {
                                    setSelectedRenderColor(render, geoRenderType);
                                    renderColorChanged = true;
                                }
                            }
                            //�ж�buffer���ͣ����ƣ�note��Ĭ����Ҫebo��ֻ�����ʷ���䣬��Ϊ���������Բ�����ebo��Ч��û�����Բ�𣬶��ʷ����ʹ��ebo������Ч��
                            if (vao->property("bufferType").toInt() == EnumType::bufferType::VBO) {
                                switch (vao->property("geoRenderType").toInt()) {
                                    case EnumType::geoRenderType::MARKER_FILL:
                                        glDrawArrays(GL_POINTS, 0, layer->getFeatureAt(m)->getGeometry()->size());
                                        break;
                                    case EnumType::geoRenderType::MARKER_LINE:
                                        glDrawArrays(GL_LINE_LOOP, 0, layer->getFeatureAt(m)->getGeometry()->size());
                                        break;
                                    case EnumType::geoRenderType::LINE_LINE:
                                        glDrawArrays(GL_LINE_STRIP, 0, layer->getFeatureAt(m)->getGeometry()->size());
                                        break;
                                    case EnumType::geoRenderType::FILL_LINE:
                                        glDrawArrays(GL_LINE_LOOP, 0, layer->getFeatureAt(m)->getGeometry()->size());
                                        break;
                                    default:
                                        break;
                                }
                            } else if (vao->property("bufferType").toInt() == EnumType::bufferType::EBO) {
                                switch (vao->property("geoRenderType").toInt()) {
                                    case EnumType::geoRenderType::FILL_FILL:
                                        glDrawElements(GL_TRIANGLES, vao->property("indexNum").toInt(), GL_UNSIGNED_INT,
                                                       0);
                                        break;
                                    default:
                                        break;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    shaderProgram.release();
}


//�������⿪�ţ�ֻ������ȴ���������Ӵ�����ͼ�㣬�Ӷ�ʵ���첽����
void QtFunctionWidget::addlayer(GeoLayer *layer) {
    if (!isExist(layer)) {
        waitLoadedLayers.push_back(layer);
    }
}

void QtFunctionWidget::renderLayer(GeoLayer *layer) {
    if (layer) {
        waitLoadedLayers.push_back(layer);
    }
}

void QtFunctionWidget::switchOpenrateMode(int operateMode) {
    this->operateMode = operateMode;
}

GeoMap *QtFunctionWidget::getMap() {
    return map;
}

void QtFunctionWidget::moveLayerLevel(int from, int to) {
    map->moveLayerLevel(from, to);
}

void QtFunctionWidget::setOutCurrentLayer(GeoLayer *layer) {
    switchLayer(layer);
}

void QtFunctionWidget::changeLayer(GeoLayer *layer) {
    if (isExist(layer)) {
        waitLoadedLayers.push_back(layer);
    }
}

void QtFunctionWidget::changeLayer(QString fullpath) {
    changeLayer(map->getLayerByFullpath(fullpath));
}

GeoLayer *QtFunctionWidget::removeLayer(GeoLayer *layer) {
    if (isExist(layer)) {
        releaseVaos(layer);
        if (!map->size()) {
            hasSetRect = false;
            hasWaH = false;
        }
        return map->remove(layer);
    }
}

GeoLayer *QtFunctionWidget::removeLayer(QString fullpath) {
    return removeLayer(map->getLayerByFullpath(fullpath));
}

bool QtFunctionWidget::isExist(GeoLayer *layer) {
    for (int i = 0; i < map->size(); i++) {
        if (layer == map->getLayerAt(i)) {
            return true;
        }
    }
    return false;
}

bool QtFunctionWidget::isExist(QString fullpath) {
    for (int i = 0; i < map->size(); i++) {
        if (fullpath == map->getLayerAt(i)->getFullPath()) {
            return true;
        }
    }
    return false;
}

void QtFunctionWidget::strongUpdata() {
    project();
    update();
}

//note that ����ҪʹinitLayer�������Ĵ����б���ʾ���ã������ͼ����в�������ʹ��addlayer��deletelayer ����������ԭ������
//��gl��ͼ��صĺ���������init��resize��paintgl�б����ã�����֮�ⲻ����أ������Ҫ�����ݼ��غͻ�ͼ���룬���첽�ķ�ʽ���������������
//�������֪��������������֮����ûط���ʲô�����Լ����ԣ�������debug�˺ܾòȵĿӡ���ʹ��bindVaos������ʱ������һ�����������Ƕ����ڴ��д��������������ƻ�������ԭ��δ֪
void QtFunctionWidget::initLayer(GeoLayer *layer) {
    if (!isExist(layer)) {  //��һ�μ���
        map->addLayer(layer);
        switchLayer(layer);
        bindVaos(layer);
    } else {  //��������
        switchLayer(layer);
        if (layer->getDataChangedType() != EnumType::dataChangedType::NOCHANGEDATA) {
            switch (layer->getDataChangedType()) {
                case EnumType::dataChangedType::SPATICALDATA:
                    releaseVaos(layer);
                    bindVaos(layer);
                    layer->setDataChangedType(EnumType::dataChangedType::NOCHANGEDATA);
                    project();    //�ռ����ݷ����˱仯����˵���һ�Σ����ﲻ����update()
                    break;
                case EnumType::dataChangedType::COLORDATA:  //��Ϊ���������в�����ɫ�����ݣ�ĿǰɶҲ����
                    layer->setDataChangedType(EnumType::dataChangedType::NOCHANGEDATA);
                    break;
                default:
                    break;
            }
        }
    }
    if (!hasSetRect) {   //��һ������
        switchLayer(layer);
        switchWorldRect(layer);
        hasSetRect = true;
    }
}

void QtFunctionWidget::initLayer(QString fullpath) {
    initLayer(map->getLayerByFullpath(fullpath));
}

void QtFunctionWidget::switchLayer(GeoLayer *layer) {
    if (isExist(layer)) {
        currentLayer = layer;
        map->setCurrentLayer(layer);
    }
}

void QtFunctionWidget::switchLayer(QString fullpath) {
    switchLayer(map->getLayerByFullpath(fullpath));
}

void QtFunctionWidget::switchWorldRect(GeoLayer *layer) {
    if (isExist(layer)) {
        switchWorldRect(layer->getRect());
    }
}

void QtFunctionWidget::switchWorldRect(QString fullpath) {
    GeoLayer *layer = map->getLayerByFullpath(fullpath);
    if (layer) {
        switchWorldRect(layer);
    }
}

void QtFunctionWidget::switchWorldRect(GeoFeature *feature) {
    if (feature) {
        switchWorldRect(feature->getGeometry()->getRect());
    }
}

void QtFunctionWidget::switchWorldRect(QRectF rect) {
    initWorldRect(rect);
    project();
    update();
}

//������ش�����ͼ�㣬����paintGL�б�����
void QtFunctionWidget::loadWaitLayers() {
    for (int i = 0; i < waitLoadedLayers.size(); i++) {
        initLayer(waitLoadedLayers.at(i));
    }
    waitLoadedLayers.clear();
}


void QtFunctionWidget::bindVaos(GeoLayer *layer) {
    QList<QOpenGLBuffer *> *boList = new QList<QOpenGLBuffer *>;
    layerBosMap.insert(layer, boList);
    for (int i = 0; i < currentLayer->size(); i++) {
        GeoFeature *feature = layer->getFeatureAt(i);
        GeoGeometry *geometry = feature->getGeometry();
        //���ٿռ䲢�����¼
        int size = 3;
        if (geometry->getType() == EnumType::POINT) {
            GLfloat *vertices = (GLfloat *) malloc(sizeof(GLfloat) * (geometry->size()) * size);
            GeoPoint *point = (GeoPoint *) geometry;
            float x = point->getXf();
            float y = point->getYf();
            vertices[0] = GLfloat(x);
            vertices[1] = GLfloat(y);
            vertices[2] = GLfloat(0.0);

            QList<QOpenGLVertexArrayObject *> *vaoList = new QList<QOpenGLVertexArrayObject *>();
            QOpenGLVertexArrayObject *vao = new QOpenGLVertexArrayObject();
            vaoList->push_back(vao);
            vao->setProperty("bufferType", QVariant(EnumType::bufferType::VBO));
            vao->setProperty("geoType", QVariant(EnumType::geometryType::POINT));
            vao->setProperty("geoRenderType", QVariant(EnumType::geoRenderType::MARKER_FILL));
            featureVaosMap.insert(feature, vaoList);

            QOpenGLVertexArrayObject::Binder vaoBind0(vao);
            QOpenGLBuffer *vbo = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
            vbo->create();
            vbo->bind();
            vbo->allocate(vertices, sizeof(GLfloat) * (geometry->size()) * size);

            boList->push_back(vbo);

            int posAttr = -1;
            //ͨ���������Ӷ�����ɫ���л�ȡ����Ӧ������location
            posAttr = shaderProgram.attributeLocation("aPos");
            shaderProgram.setAttributeBuffer(posAttr, GL_FLOAT, sizeof(GLfloat) * 0, 3, sizeof(GLfloat) * size);
            shaderProgram.enableAttributeArray(posAttr);
            shaderProgram.release();
            vbo->release();
        } else if (geometry->getType() == EnumType::POLYLINE) {
            GLfloat *vertices = (GLfloat *) malloc(sizeof(GLfloat) * (geometry->size()) * size);
            GeoPolyline *polyline = (GeoPolyline *) geometry;
            for (int j = 0; j < geometry->size(); j++) {
                GeoPoint *point = polyline->getPointAt(j);
                float x = point->getXf();
                float y = point->getYf();
                vertices[j * size + 0] = GLfloat(x);
                vertices[j * size + 1] = GLfloat(y);
                vertices[j * size + 2] = GLfloat(0.0);
            }

            QList<QOpenGLVertexArrayObject *> *vaoList = new QList<QOpenGLVertexArrayObject *>();
            QOpenGLVertexArrayObject *vao = new QOpenGLVertexArrayObject();
            vaoList->push_back(vao);
            vao->setProperty("bufferType", QVariant(EnumType::bufferType::VBO));
            vao->setProperty("geoType", QVariant(EnumType::geometryType::POLYLINE));
            vao->setProperty("geoRenderType", QVariant(EnumType::geoRenderType::LINE_LINE));
            featureVaosMap.insert(feature, vaoList);

            QOpenGLVertexArrayObject::Binder vaoBind0(vao);
            QOpenGLBuffer *vbo = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
            vbo->create();
            vbo->bind();
            vbo->allocate(vertices, sizeof(GLfloat) * (geometry->size()) * size);

            boList->push_back(vbo);

            int posAttr = -1;
            //ͨ���������Ӷ�����ɫ���л�ȡ����Ӧ������location
            posAttr = shaderProgram.attributeLocation("aPos");
            shaderProgram.setAttributeBuffer(posAttr, GL_FLOAT, sizeof(GLfloat) * 0, 3, sizeof(GLfloat) * size);
            shaderProgram.enableAttributeArray(posAttr);
            shaderProgram.release();
            vbo->release();
        } else if (geometry->getType() == EnumType::POLYGON) {
            //���ò���
            QList<QOpenGLVertexArrayObject *> *vaoList = new QList<QOpenGLVertexArrayObject *>();
            featureVaosMap.insert(feature, vaoList);
            GeoPolygon *polygon = (GeoPolygon *) geometry;
            GLfloat *vertices = NULL;

            //�����ʷ����� - level0
            if (currentLayer->getDataType() == EnumType::dataRenderType::GEOMETRYTYPE) {

                gpc_tristrip tristrip;
                util::tesselation(polygon, &tristrip);

                int stripNum = tristrip.num_strips;        //���Ƿ�����
                int triNum = 0;        //���Ǹ���
                int vertexNum = 0;        //���������û���ظ�����
                for (int i = 0; i < stripNum; i++) {
                    triNum += tristrip.strip[i].num_vertices - 2;//����һ���ж���������
                    vertexNum += tristrip.strip[i].num_vertices;//����һ���ж��ٶ���
                }

                //������������
                vertices = new GLfloat[size * vertexNum];
                int idx = 0;
                for (int i = 0; i < stripNum; i++) {  //iΪÿ����������
                    gpc_vertex_list list = tristrip.strip[i];
                    for (int j = 0; j < list.num_vertices; j++) {  //jΪ���������е�ÿ������
                        gpc_vertex vertex = list.vertex[j];
                        float x = vertex.x;
                        float y = vertex.y;
                        vertices[idx * size + 0] = GLfloat(x);
                        vertices[idx * size + 1] = GLfloat(y);
                        vertices[idx * size + 2] = GLfloat(0.0);
                        idx++;
                    }
                }

                //������������
                unsigned int *indices = new unsigned int[triNum * 3];
                int idx1 = 0;
                int cumulatedVertex = 0;
                for (int i = 0; i < stripNum; i++) {//iΪÿ����������
                    gpc_vertex_list list = tristrip.strip[i];
                    for (int j = 0; j < list.num_vertices - 2; j++) {//jΪ���������е�ÿ��������
                        for (int k = 0; k < 3; k++) {//kΪ0-3,����ÿ���������������������
                            indices[idx1++] = cumulatedVertex + j + k;
                        }
                    }
                    cumulatedVertex += list.num_vertices;
                }

                QOpenGLVertexArrayObject *fillVao = new QOpenGLVertexArrayObject();
                vaoList->push_back(fillVao);
                fillVao->setProperty("bufferType", QVariant(EnumType::bufferType::EBO));
                fillVao->setProperty("indexNum", triNum * 3);
                fillVao->setProperty("geoType", QVariant(EnumType::geometryType::POLYGON));
                fillVao->setProperty("geoRenderType", QVariant(EnumType::geoRenderType::FILL_FILL));
                QOpenGLVertexArrayObject::Binder vaoBind0(fillVao);
                QOpenGLBuffer *fillVbo = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
                fillVbo->create();
                fillVbo->bind();
                fillVbo->allocate(vertices, sizeof(GLfloat) * size * vertexNum);
                boList->push_back(fillVbo);

                QOpenGLBuffer *fillEbo = new QOpenGLBuffer(QOpenGLBuffer::IndexBuffer);
                fillEbo->create();
                fillEbo->bind();
                fillEbo->allocate(indices, sizeof(unsigned int) * triNum * 3);
                boList->push_back(fillEbo);

                int posAttr = -1;
                //ͨ���������Ӷ�����ɫ���л�ȡ����Ӧ������location
                posAttr = shaderProgram.attributeLocation("aPos");
                shaderProgram.setAttributeBuffer(posAttr, GL_FLOAT, sizeof(GLfloat) * 0, 3, sizeof(GLfloat) * size);
                shaderProgram.enableAttributeArray(posAttr);
                shaderProgram.release();
                fillVbo->release();
            } else if (currentLayer->getDataType() == EnumType::dataRenderType::GRIDTYPE) {

                int vertexNum = 4;
                //������������
                vertices = new GLfloat[size * vertexNum];
                GeoPolygon *polygon = (GeoPolygon *) geometry;
                for (int j = 0; j < vertexNum; j++) {
                    GeoPoint *point = polygon->getPointAt(j);
                    float x = point->getXf();
                    float y = point->getYf();
                    vertices[j * size + 0] = GLfloat(x);
                    vertices[j * size + 1] = GLfloat(y);
                    vertices[j * size + 2] = GLfloat(0.0);
                }
                int triNum = 4;
                //������������
                unsigned int indices[] = {  // note that we start from 0!
                        0, 1, 2,  // first Triangle
                        1, 2, 3   // second Triangle
                };


                QOpenGLVertexArrayObject *fillVao = new QOpenGLVertexArrayObject();
                vaoList->push_back(fillVao);
                fillVao->setProperty("bufferType", QVariant(EnumType::bufferType::EBO));
                fillVao->setProperty("indexNum", triNum * 3);
                fillVao->setProperty("geoType", QVariant(EnumType::geometryType::POLYGON));
                fillVao->setProperty("geoRenderType", QVariant(EnumType::geoRenderType::FILL_FILL));
                QOpenGLVertexArrayObject::Binder vaoBind0(fillVao);
                QOpenGLBuffer *fillVbo = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
                fillVbo->create();
                fillVbo->bind();
                fillVbo->allocate(vertices, sizeof(GLfloat) * size * vertexNum);
                boList->push_back(fillVbo);

                QOpenGLBuffer *fillEbo = new QOpenGLBuffer(QOpenGLBuffer::IndexBuffer);
                fillEbo->create();
                fillEbo->bind();
                fillEbo->allocate(indices, sizeof(unsigned int) * triNum * 3);
                boList->push_back(fillEbo);

                int posAttr = -1;
                //ͨ���������Ӷ�����ɫ���л�ȡ����Ӧ������location
                posAttr = shaderProgram.attributeLocation("aPos");
                shaderProgram.setAttributeBuffer(posAttr, GL_FLOAT, sizeof(GLfloat) * 0, 3, sizeof(GLfloat) * size);
                shaderProgram.enableAttributeArray(posAttr);
                shaderProgram.release();
                fillVbo->release();
            }

            /*************************************************************************/

            //�߽����� - level1
            if (currentLayer->getDataType() == EnumType::dataRenderType::GEOMETRYTYPE) {

                vertices = (GLfloat *) malloc(sizeof(GLfloat) * (geometry->size()) * size);
                for (int j = 0; j < geometry->size(); j++) {
                    GeoPoint *point = polygon->getPointAt(j);
                    float x = point->getXf();
                    float y = point->getYf();
                    vertices[j * size + 0] = GLfloat(x);
                    vertices[j * size + 1] = GLfloat(y);
                    vertices[j * size + 2] = GLfloat(0.0);
                }

                QOpenGLVertexArrayObject *outlineVao = new QOpenGLVertexArrayObject();
                outlineVao->setProperty("bufferType", QVariant(EnumType::bufferType::VBO));
                outlineVao->setProperty("geoType", QVariant(EnumType::geometryType::POLYGON));
                outlineVao->setProperty("geoRenderType", QVariant(EnumType::geoRenderType::FILL_LINE));
                vaoList->push_back(outlineVao);

                QOpenGLVertexArrayObject::Binder vaoBind1(outlineVao);
                QOpenGLBuffer *outlineVbo = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
                outlineVbo->create();
                outlineVbo->bind();
                outlineVbo->allocate(vertices, sizeof(GLfloat) * (geometry->size()) * size);

                int posAttr = -1;
                //ͨ���������Ӷ�����ɫ���л�ȡ����Ӧ������location
                posAttr = shaderProgram.attributeLocation("aPos");
                shaderProgram.setAttributeBuffer(posAttr, GL_FLOAT, sizeof(GLfloat) * 0, 3, sizeof(GLfloat) * size);
                shaderProgram.enableAttributeArray(posAttr);
                shaderProgram.release();
                outlineVbo->release();
            }
        } else {
            qWarning() << "map class not set";
        }
    }
}

void QtFunctionWidget::project() {
    //����ͶӰ
    shaderProgram.bind();   // don't forget to activate/use the shader before setting uniforms!
    // note: currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once.
    view = QMatrix4x4();
    view.translate(QVector3D(0.0f, 0.0f, -3.0f));
    shaderProgram.setUniformValue("view", view);
    projection = QMatrix4x4();

    float left = worldRect.left();
    float right = worldRect.right();
    float bottom = worldRect.bottom();
    float top = worldRect.top();
    projection.ortho(left, right, bottom, top, 0.1f, 100.0f);
    shaderProgram.setUniformValue("projection", projection);

    shaderProgram.release();
}


void QtFunctionWidget::on_addLayerData(GeoLayer *layer) {
    addlayer(layer);
    update();
}

void QtFunctionWidget::on_deleteLayerData(GeoLayer *layer) {
    deleteLayer(layer);
    update();
}

void QtFunctionWidget::on_zoomToLayer(GeoLayer *layer) {
    switchLayer(layer);
    switchWorldRect(layer);
}

void QtFunctionWidget::on_zoomToRect(QRectF rect) {
    switchWorldRect(rect);
}

void QtFunctionWidget::on_transToRect(QRectF rect) {
    refreshWorldRectForTrans(worldRect.center(), rect.center(), EnumType::scaleType::worldScale);
    project();
    update();
}

void QtFunctionWidget::on_selectFeature(GeoFeature *feature) {
    currentLayer->selectFeature(feature);
    update();
}

void QtFunctionWidget::on_setSymbol(Symbol *symbol) {
    Render *render = currentLayer->getRender();
    int type = symbol->getType();
    if (type == EnumType::MARKERSYMBOL) {
        delete render->setMarkerSymbol((MarkerSymbol *) symbol);
    } else if (type == EnumType::LINESYMBOL) {
        delete render->setLineSymbol((LineSymbol *) symbol);
    } else if (type == EnumType::FILLSYMBOL) {
        delete render->setFillSymbol((FillSymbol *) symbol);
    }
    currentLayer->setDataChangedType(EnumType::dataChangedType::COLORDATA);
    renderLayer(currentLayer);   //��ʽ�����˱仯���������Ⱦ
}

void QtFunctionWidget::on_zoomToFeature(GeoFeature *feature) {
    QRectF rect = feature->getGeometry()->getRect();
    refreshWorldRectForScale(rect.center(), rect, EnumType::scaleType::worldScale);  //������
    refreshWorldRectForTrans(rect.center(), worldRect.center(), EnumType::scaleType::worldScale); //��ƽ��
    for (int i = 0; i < map->size(); i++) {
        map->getLayerAt(i)->selectFeature(feature);
    }
    changeTableSelectionSignal(feature);
    project();
    update();
    //switchWorldRect(feature);
}

void QtFunctionWidget::on_transToFeature(GeoFeature *feature) {
    refreshWorldRectForTrans(feature->getGeometry()->getRect().center(), worldRect.center(),
                             EnumType::scaleType::worldScale);
    for (int i = 0; i < map->size(); i++) {
        map->getLayerAt(i)->selectFeature(feature);
    }
    changeTableSelectionSignal(feature);
    project();
    update();
}


void QtFunctionWidget::mousePressEvent(QMouseEvent *e) {
    if (e->button() == Qt::LeftButton) {   //���
        if (operateMode == EnumType::operateMode::IDENTIFY) {
            QPointF worldPoint = screenToWorld(e->pos());
            GeoFeature *feature = currentLayer->identify(&GeoPoint(worldPoint), worldRect.width() / 10);
            if (feature) {
                currentLayer->selectFeature(feature);
                if (hasTableShowing) {
                    emit changeTableSelectionSignal(feature);
                }
            } else if (currentLayer->getSelectMode() == EnumType::selectMode::SINGLEMODE) {
                currentLayer->clearSelections();
                if (hasTableShowing) {
                    emit changeTableSelectionSignal(NULL);
                }
            }
            update();
        }
    } else if (e->button() == Qt::RightButton) {   //�Ҽ�
        if (operateMode == EnumType::operateMode::IDENTIFY) {
            operateMode = EnumType::operateMode::NORMOL;
        }
    } else if (e->button() == Qt::MidButton) {   //���ֵ���
        //��ʼ��
        screenPointBegin = e->pos();
        screenPointDuring = e->pos();
        screenPointEnd = e->pos();
        originWorldRect = worldRect;
    }
}

void QtFunctionWidget::mouseMoveEvent(QMouseEvent *e) {
    if (e->buttons() & Qt::LeftButton) { //����ƶ�����ס���

    } else if (e->buttons() & Qt::RightButton) {   //����ƶ�����ס�Ҽ�

    } else if (e->buttons() & Qt::MidButton) {   //����ƶ�����ס���� ----  ��ͼ�ƶ�
        //�����м������
        screenPointDuring = e->pos();
        refreshWorldRectForTrans(screenPointBegin, screenPointDuring, EnumType::scaleType::screenScale);
        project();
        update();
    }
}

void QtFunctionWidget::mouseReleaseEvent(QMouseEvent *e) {
    if (e->button() == Qt::LeftButton) {   //�Ҽ�

    } else if (e->button() == Qt::RightButton) {   //���

    } else if (e->button() == Qt::MidButton) {   //���ֵ���
        //���½���������
        screenPointEnd = e->pos();
        refreshWorldRectForTrans(screenPointBegin, screenPointDuring, EnumType::scaleType::screenScale);
        project();
        update();
    }
}

void QtFunctionWidget::wheelEvent(QWheelEvent *e) {
    if (e->delta() > 0) {   //Զ���ң���ǰ����----��ͼ��С
        refreshWorldRectForScale(e->pos(), 1.0 / scale, EnumType::scaleType::screenScale);
        project();
        update();
    } else if (e->delta() < 0) {      //�����ң�������----��ͼ�Ŵ�
        refreshWorldRectForScale(e->pos(), scale, EnumType::scaleType::screenScale);
        project();
        update();
    }
}

void QtFunctionWidget::keyPressEvent(QKeyEvent *event) {
    switch (event->key()) {
        case Qt::Key_Control:
            if (operateMode == EnumType::operateMode::IDENTIFY) {
                currentLayer->setSelectMode(EnumType::selectMode::MULTIMODE);
            }
            break;
        default:
            break;
    }
}

void QtFunctionWidget::keyReleaseEvent(QKeyEvent *event) {
    switch (event->key()) {
        case Qt::Key_Control:
            if (operateMode == EnumType::operateMode::IDENTIFY) {
                currentLayer->setSelectMode(EnumType::selectMode::SINGLEMODE);
            }
            break;
        default:
            break;
    }
}

void QtFunctionWidget::setDefaultRenderColor(int dataType, int rendererType,
                                             Render *render, int geoRenderType,
                                             StretchRenderer *streRenderer, float cellValue) {
    if (dataType == EnumType::dataRenderType::GEOMETRYTYPE) {
        if (rendererType == EnumType::rendererType::SIGNALRGB) {
            switch (geoRenderType) {
                case EnumType::geoRenderType::MARKER_FILL:
                    shaderProgram.setUniformValue("color",
                                                  render->getMarkerSymbol()->getColor()); //note:�����setUniformValue���Զ���qcolor�е�0-255��ɫ������һ��
                    break;
                case EnumType::geoRenderType::MARKER_LINE:
                    shaderProgram.setUniformValue("color", render->getMarkerSymbol()->getOutline()->getColor());
                    break;
                case EnumType::geoRenderType::LINE_LINE:
                    shaderProgram.setUniformValue("color", render->getLineSymbol()->getColor());
                    break;
                case EnumType::geoRenderType::FILL_FILL:
                    shaderProgram.setUniformValue("color", render->getFillSymbol()->getColor());
                    break;
                case EnumType::geoRenderType::FILL_LINE:
                    shaderProgram.setUniformValue("color", render->getFillSymbol()->getOutline()->getColor());
                    break;
                default:
                    break;
            }
        } else if (rendererType == EnumType::rendererType::STRETCHRGB) {
            switch (geoRenderType) {
                case EnumType::geoRenderType::MARKER_FILL:
                    shaderProgram.setUniformValue("color", streRenderer->cellColor(
                            cellValue)); //note:�����setUniformValue���Զ���qcolor�е�0-255��ɫ������һ��
                    break;
                case EnumType::geoRenderType::MARKER_LINE:
                    shaderProgram.setUniformValue("color", streRenderer->cellColor(cellValue));
                    break;
                case EnumType::geoRenderType::LINE_LINE:
                    shaderProgram.setUniformValue("color", streRenderer->cellColor(cellValue));
                    break;
                case EnumType::geoRenderType::FILL_FILL:
                    shaderProgram.setUniformValue("color", streRenderer->cellColor(cellValue));
                    break;
                case EnumType::geoRenderType::FILL_LINE:
                    shaderProgram.setUniformValue("color", streRenderer->cellColor(cellValue));
                    break;
                default:
                    break;
            }
        }
    } else if (dataType == EnumType::dataRenderType::GRIDTYPE) {
        if (rendererType == EnumType::rendererType::SIGNALRGB) {

        } else if (rendererType == EnumType::rendererType::STRETCHRGB) {
            shaderProgram.setUniformValue("color", streRenderer->cellColor(cellValue));
        }
    }
}

void QtFunctionWidget::setSelectedRenderColor(Render *render, int type) {
    switch (type) {
        case EnumType::geoRenderType::MARKER_FILL:
            shaderProgram.setUniformValue("color",
                                          render->getSelectionMarkerSymbol()->getColor()); //note:�����setUniformValue���Զ���qcolor�е�0-255��ɫ������һ��
            break;
        case EnumType::geoRenderType::MARKER_LINE:
            shaderProgram.setUniformValue("color", render->getSelectionMarkerSymbol()->getOutline()->getColor());
            break;
        case EnumType::geoRenderType::LINE_LINE:
            shaderProgram.setUniformValue("color", render->getSelectionLineSymbol()->getColor());
            break;
        case EnumType::geoRenderType::FILL_FILL:
            shaderProgram.setUniformValue("color", render->getSelectionFillSymbol()->getColor());
            break;
        case EnumType::geoRenderType::FILL_LINE:
            shaderProgram.setUniformValue("color", render->getSelectionFillSymbol()->getOutline()->getColor());
            break;
        default:
            break;
    }
}

void QtFunctionWidget::releaseVaos(GeoLayer *layer) {
    if (isExist(layer)) {
        QList<QOpenGLBuffer *> *list = layerBosMap[layer];
        for (int j = 0; j < list->size(); j++) {
            list->at(j)->destroy();
            delete list->at(j);
        }
        for (int i = 0; i < layer->size(); i++) {
            GeoFeature *feature = layer->getFeatureAt(i);
            QList<QOpenGLVertexArrayObject *> *list = featureVaosMap[layer->getFeatureAt(i)];
            for (int j = 0; j < list->size(); j++) {
                delete list->at(j);
            }
            delete list;
            featureVaosMap.remove(feature);
        }
    }
}

void QtFunctionWidget::deleteLayer(GeoLayer *layer) {
    if (isExist(layer)) {
        releaseVaos(layer);
        delete map->remove(layer);
        if (!map->size()) {
            hasSetRect = false;
            hasWaH = false;
        } else {
            switchLayer(map->getLayerAt(0));
        }
    }
}

//ƽ��,��worldrectʩ��һ����beginָ��end���ƶ�����
void QtFunctionWidget::refreshWorldRectForTrans(QPointF begin, QPointF end, int scaleType) {
    if (scaleType == EnumType::scaleType::screenScale) {
        QPointF worldPointBegin = screenToWorld(begin);
        QPointF worldPointEnd = screenToWorld(end);
        QPointF moveVector = worldPointEnd - worldPointBegin;
        QPointF leftTopPoint = originWorldRect.topLeft();
        QPointF rightBottomPoint = originWorldRect.bottomRight();
        worldRect = QRectF(leftTopPoint - moveVector, rightBottomPoint - moveVector);
    } else if (scaleType == EnumType::scaleType::worldScale) {
        QPointF moveVector = end - begin;
        QPointF leftTopPoint = worldRect.topLeft();
        QPointF rightBottomPoint = worldRect.bottomRight();
        worldRect = QRectF(leftTopPoint - moveVector, rightBottomPoint - moveVector);
    }
}

//���ţ�ע��������ŵ�˼�룬�������Խ���ıߣ����ƶ����ٶ�Խ��
void QtFunctionWidget::refreshWorldRectForScale(QPointF origin, float scale, int scaleType) {
    if (scaleType == EnumType::scaleType::screenScale) {
        QPointF originWorld = screenToWorld(origin);
        QPointF leftTop = worldRect.topLeft();
        QPointF rightBottom = worldRect.bottomRight();
        QPointF newLeftTop = (leftTop - originWorld) * scale + originWorld;
        QPointF newRightBottom = (rightBottom - originWorld) * scale + originWorld;
        worldRect = QRectF(newLeftTop, newRightBottom);
    } else if (scaleType == EnumType::scaleType::worldScale) {
        QPointF leftTop = worldRect.topLeft();
        QPointF rightBottom = worldRect.bottomRight();
        QPointF newLeftTop = (leftTop - origin) * scale + origin;
        QPointF newRightBottom = (rightBottom - origin) * scale + origin;
        worldRect = QRectF(newLeftTop, newRightBottom);
    }
}

void QtFunctionWidget::refreshWorldRectForScale(QPointF origin, QRectF rect, int scaleType) {
    if (scaleType == EnumType::scaleType::screenScale) {
        float scale = 0.0;
        float targetRadio = rect.width() / rect.height();
        float worldRadio = worldRect.width() / worldRect.height();
        //���ݺ��ݱȻ�ȡscale
        if (abs(targetRadio) > abs(worldRadio)) {
            scale = rect.width() / worldRect.width();
        } else {
            scale = rect.height() / worldRect.height();
        }

        QPointF originWorld = screenToWorld(origin);
        QPointF leftTop = worldRect.topLeft();
        QPointF rightBottom = worldRect.bottomRight();
        QPointF newLeftTop = (leftTop - originWorld) * scale + originWorld;
        QPointF newRightBottom = (rightBottom - originWorld) * scale + originWorld;
        worldRect = QRectF(newLeftTop, newRightBottom);
    } else if (scaleType == EnumType::scaleType::worldScale) {
        float scale = 0.0;
        float targetRadio = rect.width() / rect.height();
        float worldRadio = worldRect.width() / worldRect.height();
        //���ݺ��ݱȻ�ȡscale
        if (abs(targetRadio) > abs(worldRadio)) {
            scale = rect.width() / worldRect.width();
        } else {
            scale = rect.height() / worldRect.height();
        }

        QPointF leftTop = worldRect.topLeft();
        QPointF rightBottom = worldRect.bottomRight();

        QPointF newLeftTop = (leftTop - origin) * scale + origin;
        QPointF newRightBottom = (rightBottom - origin) * scale + origin;
        worldRect = QRectF(newLeftTop, newRightBottom);
    }
}


QPointF QtFunctionWidget::screenToWorld(QPointF screenPoint) {
    QPointF normalizedPoint = screenToNormalizedPos(screenPoint);
    QVector4D normalizedPoint4D(normalizedPoint);
    QVector4D worldPoint4D = view.inverted() * projection.inverted() * normalizedPoint4D;
    QPointF worldCenter = worldRect.center();
    return worldPoint4D.toPointF() + worldCenter;
}

QPointF QtFunctionWidget::screenToNormalizedPos(QPointF screenPoint) {
    QPointF normalizedPoint;
    double w = this->width() * 1.0;
    double h = this->height() * 1.0;
    double x = screenPoint.x() * 1.0;
    double y = screenPoint.y() * 1.0;

    normalizedPoint.setX((2 * x / w) - 1);
    normalizedPoint.setY(1 - (2 * y / h));

    return normalizedPoint;
}

void QtFunctionWidget::initWorldRect(QRectF rect) {
    QPointF center = rect.center();
    float layerWidth = rect.width();
    float layerHeight = rect.height();
    float layerRadio = layerWidth * 1.0 / layerHeight;
    float viewRadio = width() * 1.0 / height();

    //�������ݱ�
    if (abs(layerRadio) > abs(viewRadio)) {
        layerHeight = -abs(layerWidth / viewRadio);
    } else {
        layerWidth = abs(layerHeight * viewRadio);
    }
    QPointF leftTop(center.x() - layerWidth * 1.0 / 2, center.y() - layerHeight * 1.0 / 2);
    worldRect = QRectF(leftTop, QSizeF(layerWidth, layerHeight));
}

//TODO �ж�resize�����췽��
int QtFunctionWidget::getResizeDirection(QRect oriRect, QRect newRect) {
    int oleft = oriRect.left();
    int oright = oriRect.right();
    int otop = oriRect.top();
    int obottom = oriRect.bottom();
    int nleft = newRect.left();
    int nright = newRect.right();
    int ntop = newRect.top();
    int nbottom = newRect.bottom();

    if (oleft != nleft && otop != ntop) {
        return EnumType::LEFTTOP;
    } else if (oright != nright && otop != ntop) {
        return EnumType::RIGHTTOP;
    } else if (oleft != nleft && obottom != nbottom) {
        return EnumType::LRFTBOTTOM;
    } else if (oright != nright && obottom != nbottom) {
        return EnumType::RIGHTBOTTOM;
    } else if (oleft != nleft) {
        return EnumType::LEFT;
    } else if (otop != ntop) {
        return EnumType::TOP;
    } else if (oright != nright) {
        return EnumType::RIGHT;
    } else if (obottom != nbottom) {
        return EnumType::BOTTOM;
    }
    return EnumType::NOCHANGESIZE;
}

void QtFunctionWidget::setHasTableShowing(bool flag) {
    hasTableShowing = flag;
}
