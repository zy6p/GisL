1. 整体设计

Codecvt是父类，有clean()函数，构造和析构都会调用 DaDecoder和DaEncoder是子类，均继承构造、clean()、析构

2. 他们的构造函数如下

class Codecvt

```C++
DaCodecvt::DaCodecvt() {
unitCount = 0;
pUnits = nullptr;
this->clear();
}
```

class DaDecoder : public DaCodecvt

```C++
DaDecoder::DaDecoder() : DaCodecvt() {}
```

class DaEncoder : public DaCodecvt

```C++
DaEncoder::DaEncoder() : DaCodecvt() {}
```

3. main()函数如下

```C++
int main(int argc, char *argv[]) {
GisL::DaEncoder encoder;
encoder.loadTextFile2Text("../resource/practise_1/Decode2.txt");
encoder.encode();
encoder.writeBinaryFile("../resource/practise_1/Ddddecode2.da");
GisL::DaDecoder decoder;
decoder.loadBinaryFile("../resource/practise_1/Ddddecode2.da");
decoder.decode();
decoder.writeTextFile("../resource/practise_1/BDsdDecode2.txt");
return 1;
}
```

4. 我的猜测

* mian()函数里面先encode()，write后我想让它析构，但没有析构，(因为它是Codecvt类，下面还有一个Codecvt类对象decoder?)
* encoder没析构导致decoder构造函数里面，pUnits = nullptr
* 但pUnits数组里面指针都没有delete
* 然后decoder在构造运行clean，也没有delete pUnits[]
* decoder在decode时又运行如下语句
  ```C++
  pUnits = new DaUnit *[unitCount];
  DaUnit *pTempUnit;
  buffer = new char[filesize];
  ifs.read(buffer, filesize);
  int positionInFile = 0;
  for (int ii = 0; ii < unitCount; ii++) {
      pTempUnit = new DaUnit(*(buffer + positionInFile), *(int *) (buffer + positionInFile + 1));
      pUnits[ii] = pTempUnit;
      positionInFile += 5;
  }
  delete pTempUnit;
  ```
* pUnits和pUnits[ii]均new
* 导致内存泄漏