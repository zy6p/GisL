#include "AccessibilityAnalysisTool.h"
#include "GeoMap.h"
#include <qsqlquery.h>


AccessibilityAnalysisTool::AccessibilityAnalysisTool() {

    dijkstraSql = "select sum(cost) from :arcTableName where gid in (SELECT id2 AS edge FROM pgr_dijkstra('\
		SELECT gid AS id,\
		fnode_ as source,\
		tnode_ as target,\
		length::double precision AS cost,\
		cost_vert ::double precision AS reverse_cost\
		FROM :arcTableName',\
		:start_index, :end_index, false, false))";
    //��̬����
    /*dijkstraSql = "select sum(cost) from arc where gid in (SELECT id2 AS edge FROM pgr_dijkstra('\
        SELECT gid AS id,\
        fnode_ as source,\
        tnode_ as target,\
        length::double precision AS cost,\
        cost_vert ::double precision AS reverse_cost\
        FROM arc',\
        :start_index, :end_index, false, false))";*/
}


AccessibilityAnalysisTool::~AccessibilityAnalysisTool() {
}

//���˺�����ִ��ʱ�����в����Ѿ��������ȷ��
int AccessibilityAnalysisTool::run_tool() {
    GeoLayer *layer = NULL;
    if (option) {
        //�������ݿ�
        db = QSqlDatabase::addDatabase("QPSQL");
        db.setUserName("postgres");
        db.setPassword("zhang002508");
        db.setHostName("127.0.0.1");
        db.setPort(5432);
        db.setDatabaseName("postgis_25_sample");
        db.open();

        if (option->getToolType() == EnumType::ACCESSIBILITY_ANALYSIS) {
            AccessibilityOption *option = (AccessibilityOption *) this->option;
            GeoLayer *oriPointLayer = option->getOriginPointLayer();
            GeoLayer *dirPointLayer = option->getDirPointLayer();
            GeoLayer *arcLayer = option->getArcLayer();
            GeoLayer *nodeLayer = option->getNodeLayer();
            float limitTine = option->getTimeLimit();
            QString saveFieldName = option->getSaveField();

//			QString arcTableName = arcLayer->getName();
            QString nodeLayerName = nodeLayer->getName();

            QList<GeoFeature *> features = option->getUseSelectedFeatures() ?
                                           option->getOriginPointLayer()->getSelectedFeatures()
                                                                            : option->getOriginPointLayer()->getAllFeature();

            QList<float> list;
            for (int i = 0; i < features.size(); i++) {
                GeoFeature *oriPointFeature = features.at(i);
                GeoPoint *oriPoint = (GeoPoint *) oriPointFeature->getGeometry();
                GeoFeature *roadOriNodeFeature = nodeLayer->identify(oriPoint, 9999999999999);
                if (roadOriNodeFeature) {

                    float accessibilityValue = 0;
                    int ori_index = (*(roadOriNodeFeature->getAttributeMap()))["road_featu"].toInt();
                    for (int j = 0; j < dirPointLayer->size(); j++) {
                        GeoPoint *dirPoint = (GeoPoint *) dirPointLayer->getFeatureAt(j)->getGeometry();
                        GeoFeature *roadDirNodeFeature = nodeLayer->identify(dirPoint, 9999999999999);
                        if (roadDirNodeFeature) {
                            //�ٶȹ�����ʱ����
                            GeoPoint *dirP = (GeoPoint *) roadDirNodeFeature->getGeometry();
                            float dis = oriPoint->disToPoint(dirP);
                            if (dis > 0) {
                                if (dis < limitTine) {
                                    int dir_index = (*(roadDirNodeFeature->getAttributeMap()))["road_featu"].toInt();
                                    QSqlQuery query;
                                    query.prepare(dijkstraSql);
                                    //query.bindValue(":arcTableName", arcTableName);
                                    query.bindValue(":start_index", ori_index);
                                    query.bindValue(":end_index", dir_index);
                                    query.exec();
                                    while (query.next()) {
                                        float cost = query.value(0).toFloat();  //��ѯ����ɱ�
                                        if (cost) {
                                            accessibilityValue += 1.0 / cost;  //�����Ŀɴ���֮��
                                        }
                                    }
                                    //accessibilityValue += 1.0;
                                } else {
                                    accessibilityValue += 1.0 / dis;
                                }
                            }
                        }
                    }
                    QMap<QString, QVariant> *map = oriPointFeature->getAttributeMap();
                    map->insert(saveFieldName, accessibilityValue);
                    list.push_back(accessibilityValue);
                }
            }
            //������ݵ�oriͼ����
            QList<QString> names = oriPointLayer->getAttributeNames();
            names.push_back(saveFieldName);
            oriPointLayer->setAttributeNames(names);

            oriPointLayer->setRendererType(EnumType::rendererType::STRETCHRGB);
            oriPointLayer->setAttriToStretch(saveFieldName);
            StretchRenderer *renderer = oriPointLayer->getStretchRenderer();
            /*renderer->setColors(QList<QColor>() << QColor("#FF0000") << QColor("#FF7F00")
                << QColor("#FF7F00") << QColor("#00FF00") << QColor("#00FFFF") << QColor("#00FFFF") << QColor("#00FFFF"));*/
            renderer->setColors(QList<QColor>() << QColor("#00FFFF") << QColor("#00FFFF")
                                                << QColor("#00FFFF") << QColor("#00FF00") << QColor("#FF7F00")
                                                << QColor("#FF7F00") << QColor("#FF0000"));
            renderer->setRange(list);
        }
    }
    return 0;
}
