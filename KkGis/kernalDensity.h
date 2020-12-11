#ifndef KERNALDENSITY_H
#define KERNALDENSITY_H

#include <QDialog>
#include<GeoMap.h>
#include<GeoLayer.h>
#include<GeoFeature.h>
#include<qfiledialog.h>

namespace Ui {
class KernalDensity;
}

class KernalDensity : public QDialog
{
    Q_OBJECT

public:
    explicit KernalDensity(QWidget *parent = nullptr);
    ~KernalDensity();

	QString getRasterSize();
	QString getSearchR();
	int getAreaUnits();
	int getOutValues();
	int getMethod();
	int getInputFile();
	QString getOutputFile();
	QString getPopulation();

	void setMap(GeoMap *mapPtr);

public slots:
	void getRasterOut();//获得输出栅格的路径
	void getInputLayer();//获得需要进行分析的图层
	void getPopulationField();

private:
    Ui::KernalDensity *ui;
	GeoMap *map;
	int currentLayerId;
};

#endif // KERNALDENSITY_H
