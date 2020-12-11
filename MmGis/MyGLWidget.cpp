#include "MyGLWidget.h"
#include <GL/glu.h>

MyGLWidget::MyGLWidget(QWidget *parent)
        : QOpenGLWidget(parent) {
    ui.setupUi(this);
    VBO = (GLuint *) malloc(16);
    VAO = (GLuint *) malloc(16);
    len = (int *) malloc(16);
    map = new CGeoMap();
    choosed = new CGeoObject();
    seek = new SeekEleAttri();
    kernel = new KernelWidget();
    coloursLayer = new CGeoLayer();
    size = 0;
    layerColours = false;
    QCursor cursor;
    cursor.setShape(Qt::ArrowCursor);
    setCursor(cursor);
    prevFillColor.setNamedColor("#8e2121");
    prevStrokeColor.setNamedColor("#ca590a");
    prevStrokeWidth = 2;
    this->setWindowFlags(Qt::FramelessWindowHint);
    viewLayer = new CGeoLayer();
    QObject::connect(this, SIGNAL(showAttriTable(CGeoObject * , int)), seek, SLOT(showAttri(CGeoObject * , int)));
    QObject::connect(seek, SIGNAL(restore(int)), this, SLOT(restore(int)));
    QObject::connect(seek, SIGNAL(sendColorAndWidthData(int, QColor, QColor, float)), this,
                     SLOT(getColorAndWidthOneObj(int, QColor, QColor, float)));
    QObject::connect(this, SIGNAL(KDEAnalyze(float, float * *, float, float)), kernel,
                     SLOT(KDEAnalyze(float, float * *, float, float)));
    //this->showIndexGrid = false;
}

MyGLWidget::~MyGLWidget(void) {
    glDeleteVertexArrays(size, VAO);
    glDeleteBuffers(size, VBO);
}

void MyGLWidget::createShader(const char *vertexPath, const char *fragmentPath) {
    // 1. retrieve the vertex/fragment source code from filePath
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;
    // ensure ifstream objects can throw exceptions:
    vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try {
        // open files
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);
        std::stringstream vShaderStream, fShaderStream;
        // read file's buffer contents into streams
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();
        // close file handlers
        vShaderFile.close();
        fShaderFile.close();
        // convert stream into string
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    }
    catch (std::ifstream::failure e) {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
    }
    const char *vShaderCode = vertexCode.c_str();
    const char *fShaderCode = fragmentCode.c_str();
    // 2. compile shaders
    unsigned int vertex, fragment;
    // vertex shader
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, NULL);
    glCompileShader(vertex);
    checkCompileErrors(vertex, "VERTEX");
    // fragment Shader
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, NULL);
    glCompileShader(fragment);
    checkCompileErrors(fragment, "FRAGMENT");
    // shader Program
    ID = glCreateProgram();
    glAttachShader(ID, vertex);
    glAttachShader(ID, fragment);
    glLinkProgram(ID);
    checkCompileErrors(ID, "PROGRAM");
    // delete the shaders as they're linked into our program now and no longer necessary
    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

void MyGLWidget::initializeGL() {
    initializeOpenGLFunctions();
    // ���ó�ʼ��Ļ��ɫ��͸����
    glClearColor(25, 35, 45, 1);
    createShader("G:\\qt_project\\shader.vs", "G:\\qt_project\\shader.fs");
    if (mode == 0) { //==0��ʾ����geojson
        readDataFromGeoJSON(filename);
    } else if (mode == 1) {//==1��ʾ����shapefile
        readDataFromShape(filename);
    } else if (mode == 6) {// ==5��ʾ��ȡ���ݿ�����
        readDataFromPostgresql();
    }
    loadData();
    if (mode == 0 || mode == 1 || mode == 3 || mode == 4 || mode == 5 || mode == 6) {
        if (viewLayer->getRect().width() != 0) {
            rect = viewLayer->getRect();
        } else {
            rect = viewLayer->getScope();
        }
    }
}

void MyGLWidget::resizeGL(int w, int h) {
    glViewport(0, 0, w, h);
}

void MyGLWidget::paintGL() {
    glClearColor(25.0 / 255, 35.0 / 255, 45.0 / 255, 1);
    //glClearColor(255,255,255,1);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(ID);
    if (mode != 0 && mode != 1 && mode != 3 && mode != 4 && mode != 5 && mode != 6)
        return;
    if (size == 0) {
        return;
    }

    QMatrix4x4 model;
    QMatrix4x4 view;
    QMatrix4x4 ortho;
    float screen_width = width();
    float screen_height = height();
    //ortho.scale(1+scaleParam);
    qDebug() << "run";
    // ��ͶӰ����
    float ratio = -rect.width() / rect.height();
    float ratio2 = screen_width / screen_height;
    if (ratio2 > ratio) {
        ortho.scale(ratio / ratio2, 1);
    } else {
        ortho.scale(1, ratio2 / ratio);
    }
    ortho.ortho(rect);
    //ortho.translate(offset.x(),-offset.y());

    //ortho.ortho(70.0f,140.0f,3.0f,60.0f,0.0f,15.0f);
    view.lookAt(QVector3D(0, 0, 0), QVector3D(0, 0, 0), QVector3D(0, 1, 0));
    //model.scale(QVector3D(0.5f,0.5f,1.0f));
    // ��д���ţ���дͶӰ��ʵ��������ͶӰ������

    //model.rotate(-55.0f,QVector3D(1.0f, 0.0f, 0.0f));

    GLuint modeLoc = glGetUniformLocation(ID, "model");
    GLuint viewLoc = glGetUniformLocation(ID, "view");
    GLuint projLoc = glGetUniformLocation(ID, "ortho");
    GLuint colorLoc = glGetUniformLocation(ID, "mycolor");
    // ������ɫ��
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, view.data());
    glUniformMatrix4fv(modeLoc, 1, GL_FALSE, model.data());
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, ortho.data());
    modelTemp = model;
    viewTemp = view;
    orthoTemp = ortho;
    int count = 0;

    for (int i = 0; i < map->geoLayers.size(); i++) {
        if (!map->geoLayers[i]->getVisible() && map->geoLayers[i]->type == 2) {
            count += map->geoLayers[i]->geoObjects.size() * 2; // Խ������
            count++; //Խ������

            continue;
        } else if (!map->geoLayers[i]->getVisible() && map->geoLayers[i]->type == 1) {
            count++; //Խ������
            count += map->geoLayers[i]->geoObjects.size();
            continue;
        } else if (!map->geoLayers[i]->getVisible() && map->geoLayers[i]->type == 0) {
            count += map->geoLayers[i]->geoObjects.size();;
            count++; //Խ������
            continue;
        }
        if (map->geoLayers[i]->getVisible() && map->geoLayers[i]->type == 2) {
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            for (int j = 0; j < map->geoLayers[i]->geoObjects.size(); j++) { // �������
                CGeoObject *obj = map->geoLayers[i]->geoObjects[j];
                // ����������
                glEnable(GL_BLEND);
                glEnable(GL_POLYGON_SMOOTH);
                glHint(GL_POLYGON_SMOOTH_HINT, GL_FASTEST);  // Antialias the lines
                glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
                glUniform4f(colorLoc, obj->fillR, obj->fillG, obj->fillB, obj->fillAlpha);
                glBindVertexArray(VAO[count]);
                glDrawArrays(GL_TRIANGLES, 0, len[count]);
                count++;
            }
            for (int j = 0; j < map->geoLayers[i]->geoObjects.size(); j++) { // ��������
                CGeoObject *obj = map->geoLayers[i]->geoObjects[j];
                // ����������
                glEnable(GL_BLEND);
                glEnable(GL_POLYGON_SMOOTH);
                glHint(GL_POLYGON_SMOOTH_HINT, GL_FASTEST);  // Antialias the lines
                glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
                glLineWidth(obj->strokeWidth);
                glUniform4f(colorLoc, obj->strokeR, obj->strokeG, obj->strokeB, obj->strokeAlpha);
                glBindVertexArray(VAO[count]);
                glDrawArrays(GL_LINE_STRIP, 0, len[count]);
                count++;
            }
        } else if (map->geoLayers[i]->getVisible() && map->geoLayers[i]->type == 0) {
            for (int j = 0; j < map->geoLayers[i]->geoObjects.size(); j++) {
                CGeoObject *obj = map->geoLayers[i]->geoObjects[j];
                // ����������
                glEnable(GL_BLEND);
                glEnable(GL_POINT_SMOOTH);
                glHint(GL_POINT_SMOOTH_HINT, GL_FASTEST);  // Antialias the lines
                glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
                glUniform4f(colorLoc, obj->fillR, obj->fillG, obj->fillB, obj->fillAlpha);
                glPointSize(obj->strokeWidth);
                glBindVertexArray(VAO[count]);
                glDrawArrays(GL_POINTS, 0, len[count]);
                count++;
            }
        } else if (map->geoLayers[i]->getVisible() && map->geoLayers[i]->type == 1) {
            for (int j = 0; j < map->geoLayers[i]->geoObjects.size(); j++) {
                CGeoObject *obj = map->geoLayers[i]->geoObjects[j];
                //���÷�����
                glEnable(GL_BLEND);
                glEnable(GL_LINE_SMOOTH);
                glHint(GL_LINE_SMOOTH_HINT, GL_FASTEST);  // Antialias the lines
                glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
                glUniform4f(colorLoc, obj->strokeR, obj->strokeG, obj->strokeB, obj->strokeAlpha);
                // �߿�
                glLineWidth(obj->strokeWidth);
                glBindVertexArray(VAO[count]);
                glDrawArrays(GL_LINE_STRIP, 0, len[count]);
                count++;
            }
        }
        if (map->geoLayers[i]->showIndexGrid) {
            glBindVertexArray(VAO[count]);
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            glDrawArrays(GL_QUADS, 0, len[count]);
        }
        count++;
    }

}

void MyGLWidget::checkCompileErrors(unsigned int shader, std::string type) {
    int success;
    char infoLog[1024];
    if (type != "PROGRAM") {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog
                      << "\n -- --------------------------------------------------- -- " << std::endl;
        }
    } else {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog
                      << "\n -- --------------------------------------------------- -- " << std::endl;
        }
    }
}

void MyGLWidget::readDataFromGeoJSON(const char *filename) {
    // ��ȡlayer
    GeoJsonTool geo;
    CGeoLayer *layer = geo.readGeoJSON(filename);
    if (layer != nullptr) {
        map->addLayer(layer);
        viewLayer = map->geoLayers[layerID];
    }
}

void MyGLWidget::readDataFromShape(const char *filename) {
    // ��ȡlayer
    GdalTool gdal;
    CGeoLayer *layer = gdal.readShape(filename);
    if (layer != nullptr) {
        // ʹ�õڶ��ַ�ʽ����map�ķ�Χ
        map->addLayer(layer);
        viewLayer = map->geoLayers[layerID];
    }
}

void MyGLWidget::readDataFromPostgresql() {
    Connect_Sql connectSql;
    CGeoLayer *layer = connectSql.ConnectToDBGetShpByGdal(dbname, port, host, user, password, table);
    if (layer != nullptr) {
        map->addLayer(layer);
        viewLayer = map->geoLayers[layerID];
    }
}


void MyGLWidget::loadData() {

    size = 0;
    for (int i = 0; i < map->geoLayers.size(); i++) {
        if (/*map->geoLayers[i]->getVisible() &&*/ map->geoLayers[i]->type == 2) { // �ɼ���ΪPOLYGON
            // ��ÿһ��POLYGON LAYER��ÿһ��object��������VBO��VAO���� �ڲ����+�ⲿ����
            size += map->geoLayers[i]->geoObjects.size() * 2;
        } else if (/*map->geoLayers[i]->getVisible() &&*/ (map->geoLayers[i]->type == 0 ||
                                                           map->geoLayers[i]->type == 1)) { // �ɼ���ΪPOINT or POLYLINE
            // ��ÿһ��POINT LAYERÿһ��object����һ��VBO��VAO����
            size += map->geoLayers[i]->geoObjects.size();
        }
        /*else if(map->geoLayers[i]->getVisible() && map->geoLayers[i]->type==1){ // �ɼ���ΪPOLYLINE
        // ��ÿһ��POLYINE LAYER������һ��VBO��VAO����
        size += 1;
        }
        */
    }
    qDebug() << size;
    // ���·����ڴ�
    size += map->geoLayers.size(); // ÿһ��layer��һ������
    VAO = new GLuint[size];
    VBO = new GLuint[size];
    len = new int[size];
    glGenVertexArrays(size, VAO);
    glGenBuffers(size, VBO);
    int num = 0;
    for (int j = 0; j < map->geoLayers.size(); j++) {
        CGeoLayer *temp = map->geoLayers[j];
        if (/*temp->getVisible() &&*/ temp->type == 2) { // ��Ҫ�ʷ�
            CGeoLayer *tessaLayer = temp->tessaLayer;
            for (int i = 0; i < tessaLayer->geoObjects.size(); i++) { // �ڲ����
                // ����ÿһ��VAO��VBO,count��Geobject�Ķ����������Ŀ
                /*float *vertices =  new float();
                int *count = new int();
                *count = 0; // ��ʼֵΪ��
                vertices = tessaLayer->geoObjects[i]->getVert(vertices,count);
                len[num] = *count/3;
                */
                CGeoObject *obj = tessaLayer->geoObjects[i];
                float *vertices;
                vertices = tessaLayer->geoObjects[i]->getVert2(vertices);
                int count = 3 * ((CGeoPolygon *) obj)->pts.size();
                len[num] = count / 3;

                // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
                glBindVertexArray(VAO[num]);
                glBindBuffer(GL_ARRAY_BUFFER, VBO[num]);
                glBufferData(GL_ARRAY_BUFFER, count * sizeof(float), vertices, GL_STATIC_DRAW);
                glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *) 0);
                glEnableVertexAttribArray(0);
                // color attribute
                //glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
                //glEnableVertexAttribArray(1);
                // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
                glBindBuffer(GL_ARRAY_BUFFER, 0);

                // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
                // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
                glBindVertexArray(0);
                delete[] vertices;
                num++;
            }
            for (int i = 0; i < temp->geoObjects.size(); i++) { // �ⲿ����
                // ����ÿһ��VAO��VBO,count��Geobject�Ķ����������Ŀ
                /*float *vertices =  new float();
                int *count = new int();
                *count = 0; // ��ʼֵΪ��
                vertices = temp->geoObjects[i]->getVert(vertices,count);
                len[num] = *count/3;*/
                CGeoObject *obj = temp->geoObjects[i];
                float *vertices;
                vertices = temp->geoObjects[i]->getVert2(vertices);
                int count = 3 * ((CGeoPolygon *) obj)->pts.size();
                len[num] = count / 3;
                // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
                glBindVertexArray(VAO[num]);
                glBindBuffer(GL_ARRAY_BUFFER, VBO[num]);
                glBufferData(GL_ARRAY_BUFFER, count * sizeof(float), vertices, GL_STATIC_DRAW);
                glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *) 0);
                glEnableVertexAttribArray(0);
                // color attribute
                //glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
                //glEnableVertexAttribArray(1);
                // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
                glBindBuffer(GL_ARRAY_BUFFER, 0);

                // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
                // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
                glBindVertexArray(0);
                delete[] vertices;
                num++;
            }
        } else if (/*temp->getVisible() &&*/  temp->type == 1) {
            for (int i = 0; i < temp->geoObjects.size(); i++) {
                // ����ÿһ��VAO��VBO,count��Geobject�Ķ����������Ŀ
                /*float *vertices =  new float();
                int *count = new int();
                *count = 0; // ��ʼֵΪ��
                vertices = temp->geoObjects[i]->getVert(vertices,count);
                len[num] = *count/3;*/
                CGeoObject *obj = temp->geoObjects[i];
                float *vertices;
                vertices = temp->geoObjects[i]->getVert2(vertices);
                int count = 3 * ((CGeoPolygon *) obj)->pts.size();
                len[num] = count / 3;
                // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
                glBindVertexArray(VAO[num]);
                glBindBuffer(GL_ARRAY_BUFFER, VBO[num]);
                glBufferData(GL_ARRAY_BUFFER, count * sizeof(float), vertices, GL_STATIC_DRAW);
                glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *) 0);
                glEnableVertexAttribArray(0);
                // color attribute
                //glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
                //glEnableVertexAttribArray(1);
                // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
                glBindBuffer(GL_ARRAY_BUFFER, 0);

                // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
                // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
                glBindVertexArray(0);
                delete[] vertices;
                num++;
            }
        } else if (/*temp->getVisible() &&*/ temp->type == 0) {
            for (int i = 0; i < temp->geoObjects.size(); i++) {
                // ����ÿһ��VAO��VBO,count��Geobject�Ķ����������Ŀ
                /*float *vertices =  new float();
                int *count = new int();
                *count = 0; // ��ʼֵΪ��
                vertices = temp->geoObjects[i]->getVert(vertices,count);
                len[num] = *count/3;*/
                CGeoObject *obj = temp->geoObjects[i];
                float *vertices;
                vertices = temp->geoObjects[i]->getVert2(vertices);
                int count = 3;
                len[num] = count / 3;
                // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
                glBindVertexArray(VAO[num]);
                glBindBuffer(GL_ARRAY_BUFFER, VBO[num]);
                glBufferData(GL_ARRAY_BUFFER, count * sizeof(float), vertices, GL_STATIC_DRAW);
                glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *) 0);
                glEnableVertexAttribArray(0);
                // color attribute
                //glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
                //glEnableVertexAttribArray(1);
                // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
                glBindBuffer(GL_ARRAY_BUFFER, 0);

                // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
                // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
                glBindVertexArray(0);
                delete[] vertices;
                num++;
            }
        }
        float *vertices = new float();
        int count = 0;
        vector<QuadNode *> arrNode;
        TraversalQuadTree(temp->tree->root, arrNode);
        for (int i = 0; i < arrNode.size(); i++) {
            vertices = (float *) realloc(vertices, sizeof(float) * (count + 12));
            vertices[count] = arrNode[i]->Box.left();
            vertices[count + 1] = arrNode[i]->Box.top();
            vertices[count + 2] = 0.0f;
            vertices[count + 3] = arrNode[i]->Box.left();
            vertices[count + 4] = arrNode[i]->Box.bottom();
            vertices[count + 5] = 0.0f;
            vertices[count + 6] = arrNode[i]->Box.right();
            vertices[count + 7] = arrNode[i]->Box.bottom();
            vertices[count + 8] = 0.0f;
            vertices[count + 9] = arrNode[i]->Box.right();
            vertices[count + 10] = arrNode[i]->Box.top();
            vertices[count + 11] = 0.0f;
            count += 12;
        }
        len[num] = count / 3;
        // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
        glBindVertexArray(VAO[num]);
        glBindBuffer(GL_ARRAY_BUFFER, VBO[num]);
        glBufferData(GL_ARRAY_BUFFER, count * sizeof(float), vertices, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *) 0);
        glEnableVertexAttribArray(0);
        // color attribute
        //glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
        //glEnableVertexAttribArray(1);
        // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
        // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
        glBindVertexArray(0);
        delete[] vertices;
        num++;
    }

}

void MyGLWidget::updateMyGLSlot(int mode, const char *filename, int layerID) {
    this->mode = mode;
    this->filename = filename;
    this->layerID = layerID;
    makeCurrent();
    initializeGL();
    update();

}

void MyGLWidget::getColorAndWidthData2(int layerID, QColor fillColor, QColor strokeColor, float width) {//������Ⱦ�ź�
    CGeoLayer *layer = map->geoLayers[layerID];
    prevFillColor = fillColor;
    prevStrokeColor = strokeColor;
    prevStrokeWidth = width;
    for (int i = 0; i < layer->geoObjects.size(); i++) {
        CGeoObject *obj = layer->geoObjects[i];
        obj->fillR = fillColor.redF();
        obj->fillG = fillColor.greenF();
        obj->fillB = fillColor.blueF();
        obj->fillAlpha = fillColor.alphaF();
        obj->strokeR = strokeColor.redF();
        obj->strokeG = strokeColor.greenF();
        obj->strokeB = strokeColor.blueF();
        obj->strokeAlpha = strokeColor.alphaF();
        obj->strokeWidth = width;
    }
    update();
}

void
MyGLWidget::getColorAndWidthOneObj(int objID, QColor fillColor, QColor strokeColor, float width) {//������Ⱦһ��object
    //objFillColor = fillColor;
    //objStrokeColor = strokeColor;
    //objStrokeWidth = width;
    CGeoObject *obj = viewLayer->geoObjects[objID];
    obj->fillR = fillColor.redF();
    obj->fillG = fillColor.greenF();
    obj->fillB = fillColor.blueF();
    obj->fillAlpha = fillColor.alphaF();
    obj->strokeR = strokeColor.redF();
    obj->strokeG = strokeColor.greenF();
    obj->strokeB = strokeColor.blueF();
    obj->strokeAlpha = strokeColor.alphaF();
    obj->strokeWidth = width;
    update();
}

void MyGLWidget::getColorAndWidthObjs(vector<QString> names, QColor fillColor, QColor strokeColor,
                                      float width) {//������Ⱦһ��object
    seek->close();
    for (int i = 0; i < this->objID.size(); i++) { // ���ϴβ鵽�Ļָ�
        CGeoObject *obj = viewLayer->geoObjects[this->objID.at(i)];
        obj->fillR = prevFillColor.redF();
        obj->fillG = prevFillColor.greenF();
        obj->fillB = prevFillColor.blueF();
        obj->fillAlpha = prevFillColor.alphaF();
        obj->strokeR = prevStrokeColor.redF();
        obj->strokeG = prevStrokeColor.greenF();
        obj->strokeB = prevStrokeColor.blueF();
        obj->strokeAlpha = prevStrokeColor.alphaF();
        obj->strokeWidth = prevStrokeWidth;
        update();
    }
    // �����ѡ��Ҳû��
    choosed->fillR = prevFillColor.redF();
    choosed->fillG = prevFillColor.greenF();
    choosed->fillB = prevFillColor.blueF();
    choosed->fillAlpha = prevFillColor.alphaF();
    choosed->strokeR = prevStrokeColor.redF();
    choosed->strokeG = prevStrokeColor.greenF();
    choosed->strokeB = prevStrokeColor.blueF();
    choosed->strokeAlpha = prevStrokeColor.alphaF();
    choosed->strokeWidth = prevStrokeWidth;
    this->names = names;
    for (int i = 0; i < names.size(); i++) {
        for (int j = 0; j < viewLayer->geoObjects.size(); j++) {
            CGeoObject *obj = viewLayer->geoObjects[j];
            if (obj->getProps()["NAME"].compare(names[i]) == 0 || obj->getProps()["name"].compare(names[i]) == 0) {
                obj->fillR = fillColor.redF();
                obj->fillG = fillColor.greenF();
                obj->fillB = fillColor.blueF();
                obj->fillAlpha = fillColor.alphaF();
                obj->strokeR = strokeColor.redF();
                obj->strokeG = strokeColor.greenF();
                obj->strokeB = strokeColor.blueF();
                obj->strokeAlpha = strokeColor.alphaF();
                obj->strokeWidth = width;
                this->objID.push_back(j);
            }
        }
    }
    update();
}

void MyGLWidget::restore(int objID) {
    //objFillColor = prevFillColor;
    //objStrokeColor = prevStrokeColor;
    //objStrokeWidth = prevStrokeWidth;
    CGeoObject *obj = viewLayer->geoObjects[objID];
    obj->fillR = prevFillColor.redF();
    obj->fillG = prevFillColor.greenF();
    obj->fillB = prevFillColor.blueF();
    obj->fillAlpha = prevFillColor.alphaF();
    obj->strokeR = prevStrokeColor.redF();
    obj->strokeG = prevStrokeColor.greenF();
    obj->strokeB = prevStrokeColor.blueF();
    obj->strokeAlpha = prevStrokeColor.alphaF();
    obj->strokeWidth = prevStrokeWidth;
    update();
}

void
MyGLWidget::updateMyGLPostgresqlSlot(int mode, int layerID, QString port, QString dbname, QString host, QString user,
                                     QString password, QString table) { // ��ȡ���ݿ⣬������Ⱦ
    this->mode = mode;
    this->dbname = dbname;
    this->host = host;
    this->user = user;
    this->password = password;
    this->table = table;
    this->layerID = layerID;
    this->port = port;
    makeCurrent();
    initializeGL();
    update();

}

void MyGLWidget::updateData(int mode, CGeoMap *map, int layerID, int size) {
    this->mode = mode;
    this->map = map;

    makeCurrent();
    if (size > 0) {
        initializeGL();
    }
    update();
}

void MyGLWidget::updateLayerID(int mode, int layerID) {
    this->mode = mode;
    this->layerID = layerID;
    viewLayer = map->geoLayers[layerID];
    rect = viewLayer->getRect();
    //offset.setX(0);
    //offset.setY(0);
    //scaleParam = 0;
    makeCurrent();
    update();
}


void MyGLWidget::wheelEvent(QWheelEvent *event) {
    /*
    QRect tmp=this->geometry();
    if(event->delta()>0){//����������Ϲ�
    // �Ŵ�
    scaleParam += (event->delta()/(15*8))*0.4;
    }else{
    // ����
    scaleParam -= -event->delta()/(15*8)*0.4;
    }

    update();
    event->accept();
    */

    if (event->delta() > 0) {   //��ͼ��С
        Scale(event->pos(), 1.0 / 0.5);
        update();
    } else if (event->delta() < 0) {      //��ͼ�Ŵ�
        Scale(event->pos(), 0.5);
        update();
    }
    event->accept();

}

void MyGLWidget::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        QCursor cursor;
        cursor.setShape(Qt::ClosedHandCursor);
        QApplication::setOverrideCursor(cursor);
        //globalPos()�����ָ���������Ļ���Ͻǵ����꣬ pos()�Ǵ������Ͻ��������Ļ���Ͻǵ����� ����ȡδ�ƶ�ǰ�Ĵ���λ�ã�
        beginRect = event->pos();
        originWorldRect = rect;
    } else if (event->button() == Qt::RightButton) {
        if (layerColours) {
            for (int j = 0; j < coloursLayer->geoObjects.size(); j++) {
                CGeoObject *object = coloursLayer->geoObjects[j];
                // ��ԭ
                object->fillR = prevFillColor.redF();
                object->fillG = prevFillColor.greenF();
                object->fillB = prevFillColor.blueF();
                object->fillAlpha = prevFillColor.alphaF();
                object->strokeR = prevStrokeColor.redF();
                object->strokeG = prevStrokeColor.greenF();
                object->strokeB = prevStrokeColor.blueF();
                object->strokeAlpha = prevStrokeColor.alphaF();
                object->strokeWidth = prevStrokeWidth;
            }
        }
        for (int i = 0; i < this->objID.size(); i++) { // ���ϴβ鵽�Ļָ�
            CGeoObject *obj = viewLayer->geoObjects[this->objID.at(i)];
            obj->fillR = prevFillColor.redF();
            obj->fillG = prevFillColor.greenF();
            obj->fillB = prevFillColor.blueF();
            obj->fillAlpha = prevFillColor.alphaF();
            obj->strokeR = prevStrokeColor.redF();
            obj->strokeG = prevStrokeColor.greenF();
            obj->strokeB = prevStrokeColor.blueF();
            obj->strokeAlpha = prevStrokeColor.alphaF();
            obj->strokeWidth = prevStrokeWidth;
            update();
        }
        //globalPos()�����ָ���������Ļ���Ͻǵ����꣬ pos()�Ǵ������Ͻ��������Ļ���Ͻǵ����� ����ȡδ�ƶ�ǰ�Ĵ���λ�ã�
        QPointF query(event->pos().rx(), event->pos().ry());
        QPointF trans = screenToWorld3(query);
        vector<int> ItemSearched;
        choosed->fillR = prevFillColor.redF();
        choosed->fillG = prevFillColor.greenF();
        choosed->fillB = prevFillColor.blueF();
        choosed->fillAlpha = prevFillColor.alphaF();
        choosed->strokeR = prevStrokeColor.redF();
        choosed->strokeG = prevStrokeColor.greenF();
        choosed->strokeB = prevStrokeColor.blueF();
        choosed->strokeAlpha = prevStrokeColor.alphaF();
        choosed->strokeWidth = prevStrokeWidth;
        if (viewLayer->tree->root)
            PtSearchQTree(viewLayer->tree->root, trans.x(), trans.y(), ItemSearched);
        if (ItemSearched.size() == 0) {
            update();
            seek->close();
            return;
        }
        QColor color("#b97016");
        choosed = viewLayer->geoObjects[ItemSearched.at(ItemSearched.size() - 1)];
        seek->show();
        emit showAttriTable(choosed, ItemSearched.at(ItemSearched.size() - 1));
        choosed->fillR = color.redF();
        choosed->fillG = color.greenF();
        choosed->fillB = color.blueF();
        choosed->fillAlpha = color.alphaF();
        choosed->strokeR = color.redF();
        choosed->strokeG = color.greenF();
        choosed->strokeB = color.blueF();
        choosed->strokeAlpha = color.alphaF();
        update();
    }
}

void MyGLWidget::mouseReleaseEvent(QMouseEvent *event) {
    QApplication::restoreOverrideCursor();
}

void MyGLWidget::mouseMoveEvent(QMouseEvent *event) {
    if (event->buttons() & Qt::LeftButton) {//������
        //QPointF temp;
        //temp = event->globalPos() -pos() -begin;//
        //offset.setX(offset.x()+screenToWorld(temp).x());
        //offset.setY(offset.y()-screenToWorld(temp).y());
        //float x = event->pos().rx();
        //float y = event->pos().ry();
        //move(offset);//�ƶ������������
        //paintGL();
        endRect = event->pos();
        QPointF worldPointBegin = screenToWorld3(beginRect);
        QPointF worldPointEnd = screenToWorld3(endRect);
        QPointF moveVector = worldPointEnd - worldPointBegin;
        QPointF leftTopPoint = originWorldRect.topLeft();
        QPointF rightBottomPoint = originWorldRect.bottomRight();
        rect = QRectF(leftTopPoint - moveVector, rightBottomPoint - moveVector);
        qDebug() << "globalPos" << event->globalPos() << endl;
        qDebug() << "pos" << pos() << endl;
        update();
    }
}

void MyGLWidget::Scale(QPoint originScreen, float scale) {
    QPointF originWorld = screenToWorld3(originScreen);
    QPointF leftTop = rect.topLeft();
    QPointF rightBottom = rect.bottomRight();
    QPointF newLeftTop = (leftTop - originWorld) * scale + originWorld;
    QPointF newRightBottom = (rightBottom - originWorld) * scale + originWorld;
    rect = QRectF(newLeftTop, newRightBottom);
}

/*
// ƽ��ʹ��
QPointF MyGLWidget::screenToWorld(QPointF screenPoint){
QPointF p;
double w = this->width() * 1.0;
double h = this->height() * 1.0;
double x = screenPoint.x() * 1.0;
double y = screenPoint.y() * 1.0;

p.setX(x / w * rect.width()/(10*(1+scaleParam)));
p.setY(y/h * rect.height()/(10*(1+scaleParam)));

return p;

}
*/

QPointF MyGLWidget::screenToWorld3(QPointF screenPoint) {
    QPointF normalizedPoint = screenToNormalizedPos(screenPoint);
    QVector4D normalizedPoint4D(normalizedPoint);
    QVector4D worldPoint4D = viewTemp.inverted() * orthoTemp.inverted() * normalizedPoint4D;
    QPointF worldCenter = rect.center();
    return worldPoint4D.toPointF() + worldCenter;
}

QPointF MyGLWidget::screenToNormalizedPos(QPointF screenPoint) {
    QPointF normalizedPoint;
    double w = this->width() * 1.0;
    double h = this->height() * 1.0;
    double x = screenPoint.x() * 1.0;
    double y = screenPoint.y() * 1.0;

    normalizedPoint.setX((2 * x / w) - 1);
    normalizedPoint.setY(1 - (2 * y / h));

    return normalizedPoint;
}

void MyGLWidget::KDEAnaly(int layerID) {
    // ���ܶ�
    float bandWidth;
    float **loc;
    float maxLoc;
    float minLoc;
    CGeoLayer *kdeLayer = map->geoLayers[layerID];
    vector<double> Distance;
    float Avex = 0, Avey = 0;
    for (int i = 0; i < kdeLayer->geoObjects.size(); i++) {
        CGeoPoint *point = (CGeoPoint *) kdeLayer->geoObjects[i];
        Avex += point->getPoint().x();
        Avey += point->getPoint().y();
    }
    Avex /= kdeLayer->geoObjects.size();
    Avey /= kdeLayer->geoObjects.size();
    for (int i = 0; i < kdeLayer->geoObjects.size(); i++) {
        CGeoPoint *point = (CGeoPoint *) kdeLayer->geoObjects[i];
        // Gauss distance
        float Dis = sqrt(pow(point->getPoint().x() - Avex, 2) + pow(point->getPoint().y() - Avey, 2));
        Distance.push_back(Dis);
    }
    sort(Distance.begin(), Distance.end());
    float Dm = Distance.at(Distance.size() / 2);
    double SDx = 0, SDy = 0;
    for (int i = 0; i < kdeLayer->geoObjects.size(); i++) {
        CGeoPoint *point = (CGeoPoint *) kdeLayer->geoObjects[i];
        SDx += pow(point->getPoint().x() - Avex, 2);
        SDy += pow(point->getPoint().y() - Avey, 2);
    }
    double SD = sqrt(SDx / kdeLayer->geoObjects.size() + SDy / kdeLayer->geoObjects.size());
    if (SD > (sqrt(1 / log(2)) * Dm))
        bandWidth = 0.9 * (sqrt(1 / log(2)) * Dm) * pow(kdeLayer->geoObjects.size(), -0.2);
    else
        bandWidth = 0.9 * SD * pow(kdeLayer->geoObjects.size(), -0.2);
    int rasterNum = 1000;
    loc = new float *[rasterNum];
    for (int i = 0; i < rasterNum; i++) {
        loc[i] = new float[rasterNum];
    }
    //calculateKde
    float temp;
    float dis2;
    float width = (kdeLayer->getRect().right() - kdeLayer->getRect().left()) / rasterNum;
    float height = (kdeLayer->getRect().top() - kdeLayer->getRect().bottom()) / rasterNum;
    for (int i = 0; i < rasterNum; i++) {
        float x, y;
        x = kdeLayer->getRect().left() + width * i + width / 2;
        for (int j = 0; j < rasterNum; j++) {
            temp = 0;
            y = kdeLayer->getRect().bottom() + height * j + height / 2;
            for (int m = 0; m < kdeLayer->geoObjects.size(); m++) {
                CGeoPoint *point = (CGeoPoint *) kdeLayer->geoObjects[m];
                dis2 = pow(x - point->getPoint().x(), 2) + pow(y - point->getPoint().y(), 2);
                if (dis2 < (bandWidth * bandWidth)) {
                    temp += 3 / 3.1415926 * pow((1 - dis2 / pow(bandWidth, 2)), 2);
                }
            }
            temp = temp / kdeLayer->geoObjects.size() / pow(bandWidth, 2);
            loc[i][j] = temp;
            if (i == 0 && j == 0) {
                maxLoc = minLoc = temp;
            } else if (temp > maxLoc)
                maxLoc = temp;
            else if (temp < minLoc)
                minLoc = temp;
        }
    }
    emit KDEAnalyze(bandWidth, loc, maxLoc, minLoc);
}

void MyGLWidget::setLayerClours(int layerID, QString attribute) {
    coloursLayer = map->geoLayers[layerID];
    // �õ������Сֵ
    double maxAttri, minAttri;
    for (int i = 0; i < coloursLayer->geoObjects.size(); i++) {
        CGeoObject *obj = coloursLayer->geoObjects[i];
        bool ok;
        double attri = obj->getProps()[attribute].toDouble(&ok);
        if (!ok) {
            for (int j = 0; j < coloursLayer->geoObjects.size(); j++) {
                CGeoObject *object = coloursLayer->geoObjects[j];
                // ��ԭ
                object->fillR = prevFillColor.redF();
                object->fillG = prevFillColor.greenF();
                object->fillB = prevFillColor.blueF();
                object->fillAlpha = prevFillColor.alphaF();
                object->strokeR = prevStrokeColor.redF();
                object->strokeG = prevStrokeColor.greenF();
                object->strokeB = prevStrokeColor.blueF();
                object->strokeAlpha = prevStrokeColor.alphaF();
                object->strokeWidth = prevStrokeWidth;
            }
            QMessageBox::critical(NULL, QString::fromLocal8Bit("��֧�ֵ�����"),
                                  QString::fromLocal8Bit("�������޷����зֲ���ɫ��"), QMessageBox::Yes, QMessageBox::Yes);
            return;
        }
        if (i == 0) {
            maxAttri = minAttri = attri;
        } else if (attri > maxAttri)
            maxAttri = attri;
        else if (attri < minAttri)
            minAttri = attri;
    }
    // ��Area���Խ��зֲ���ɫ
    for (int i = 0; i < coloursLayer->geoObjects.size(); i++) {
        CGeoObject *obj = coloursLayer->geoObjects[i];
        double attri = obj->getProps()[attribute].toDouble();
        float a = (attri - minAttri) / (maxAttri - minAttri);
        if (a >= 0 && a < 0.25) {
            QColor fillColor("#CFAA9E");
            QColor strokeColor("#CFAA9E");
            obj->fillR = fillColor.redF();
            obj->fillG = fillColor.greenF();
            obj->fillB = fillColor.blueF();
            obj->fillAlpha = fillColor.alphaF();
            obj->strokeR = strokeColor.redF();
            obj->strokeG = strokeColor.greenF();
            obj->strokeB = strokeColor.blueF();
            obj->strokeAlpha = strokeColor.alphaF();
        } else if (a >= 0.25 && a < 0.5) {
            QColor fillColor("#DE7E73");
            QColor strokeColor("#DE7E73");
            obj->fillR = fillColor.redF();
            obj->fillG = fillColor.greenF();
            obj->fillB = fillColor.blueF();
            obj->fillAlpha = fillColor.alphaF();
            obj->strokeR = strokeColor.redF();
            obj->strokeG = strokeColor.greenF();
            obj->strokeB = strokeColor.blueF();
            obj->strokeAlpha = strokeColor.alphaF();
        } else if (a >= 0.5 && a < 0.75) {
            QColor fillColor("#ED9282");
            QColor strokeColor("#ED9282");
            obj->fillR = fillColor.redF();
            obj->fillG = fillColor.greenF();
            obj->fillB = fillColor.blueF();
            obj->fillAlpha = fillColor.alphaF();
            obj->strokeR = strokeColor.redF();
            obj->strokeG = strokeColor.greenF();
            obj->strokeB = strokeColor.blueF();
            obj->strokeAlpha = strokeColor.alphaF();
        } else if (a >= 0.75 && a <= 1) {
            QColor fillColor("#F7AA97");
            QColor strokeColor("#F7AA97");
            obj->fillR = fillColor.redF();
            obj->fillG = fillColor.greenF();
            obj->fillB = fillColor.blueF();
            obj->fillAlpha = fillColor.alphaF();
            obj->strokeR = strokeColor.redF();
            obj->strokeG = strokeColor.greenF();
            obj->strokeB = strokeColor.blueF();
            obj->strokeAlpha = strokeColor.alphaF();
        }
    }
    choosed = new CGeoObject();
    layerColours = true;
    update();
}