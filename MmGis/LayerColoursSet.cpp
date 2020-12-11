#include "LayerColoursSet.h"


LayerColoursSet::LayerColoursSet(QWidget *parent)
	:QWidget(parent)
{
	ui.setupUi(this);
	ui.lineEdit->setEnabled(false);
}


LayerColoursSet::~LayerColoursSet(void)
{
}

void LayerColoursSet::setAttribute(int layerID,QString layerNAME,QList<QString> propsKey){
	this->layerID = layerID;
	this->layerNAME = layerNAME;
	this->propsKey = propsKey;
	ui.lineEdit->setText(layerNAME);
	ui.comboBox->clear();
	for(int i=0;i<propsKey.size();i++){
		ui.comboBox->addItem(propsKey.at(i));
	}
}

void LayerColoursSet::continueClick(){
	emit setLayerClours(layerID,ui.comboBox->currentText());
	this->close();
}

void LayerColoursSet::cancelClick(){
	this->close();
}
