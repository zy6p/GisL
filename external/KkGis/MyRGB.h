#pragma once
class MyRGB
{
public:
	MyRGB();
	~MyRGB();
	int R();
	int G();
	int B();  //256色 [0-255]
	float NR(); //标准化 [0-1.0]
	float NG();
	float NB();
	void setR(int r);
	void setG(int g);
	void setB(int b);
	void setNR(float nr);
	void setNG(float ng);
	void setNB(float nb);
	void fromRGB(int r, int g, int b);
	void fromNRGB(float r, float g, float b);
private:
	int r;
	int g;
	int b;
};

