#include "KernelWidget.h"


KernelWidget::KernelWidget(QWidget *parent)
	: QOpenGLWidget(parent)
{
	ui.setupUi(this);
	offsetX = 0;
	offsetY = 0;
	newOffsetX = 0;
	newOffsetY = 0;
	scale = 1.0;
	finished = false;
}


KernelWidget::~KernelWidget(void)
{
}

void KernelWidget::initializeGL(){
	initializeOpenGLFunctions();
	// 设置初始屏幕颜色和透明度
	glClearColor(1.0f,1.0f,1.0f,0.0f);
}
void KernelWidget::paintGL() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(offsetX,offsetY,0);
	glScalef(scale,scale,0);
	if(!finished)
		return;
	for(int i=0;i<1000;i++)
	{
		for(int j=0;j<1000;j++)
		{
			float a=(this->loc[i][j]-this->minLoc)/(this->maxLoc-this->minLoc); 
			if(a>0&&a<0.25)
				glColor3f(207.0/255,170.0/255,158.0/255);
			else if(a>=0.25&&a<0.5)
				glColor3f(222.0/255,126.0/255,115.0/255);
			else if(a>=0.5&&a<0.75)
				glColor3f(237.0/255,146.0/255,130.0/255);
			else if(a>=0.75&&a<=1)
				glColor3f(247.0/255,170.0/255,151.0/255);
			float x,y;
			glBegin(GL_POLYGON);
			x=-1.0+0.002*i;
			y=-1.0+0.002*j;
			glVertex2f(x,y);
			glVertex2f(x+0.002,y);
			glVertex2f(x+0.002,y+0.002);
			glVertex2f(x,y+0.002);
			glEnd();
		}
	}
}
void KernelWidget::resizeGL(int w,int h) {
	glViewport(0,0,w,h);
}

void KernelWidget::KDEAnalyze(float bandWidth,float **loc,float maxLoc,float minLoc){
	this->loc = loc;
	this->bandWidth = bandWidth;
	this->maxLoc = maxLoc;
	this->minLoc = minLoc;
	finished = true;
	this->show();
	update();
}
void KernelWidget::mousePressEvent(QMouseEvent *event){
	if (event->buttons() == Qt::LeftButton)
	{
		// 切换光标样式
		setCursor(Qt::ClosedHandCursor);
		mouseX = event->x();
		mouseY = event->y();
	}
	if (event->buttons() == Qt::RightButton)
	{
		offsetX = 0;
		offsetY = 0;
		update();
	}
}

void KernelWidget::mouseMoveEvent(QMouseEvent *event)
{
	if (event->buttons() == Qt::LeftButton)
	{
		// 计算图像偏移量
		newOffsetX = (event->x() - mouseX) / this->width();
		newOffsetY = (mouseY - event->y()) / this->height();
		offsetX += newOffsetX;
		offsetY += newOffsetY;
		update();
	}
}

void KernelWidget::mouseReleaseEvent(QMouseEvent *event)
{
	unsetCursor();
	offsetX += newOffsetX;
	offsetY += newOffsetY;
	newOffsetX = 0;
	newOffsetY = 0;
}

void KernelWidget::wheelEvent(QWheelEvent *event)
{
	scale -=  (event->delta()/(15*8))*0.2;
	// 限制缩小倍数
	if (scale < 0.2f)
	{
		scale = 0.2f;
	}
	update();
}