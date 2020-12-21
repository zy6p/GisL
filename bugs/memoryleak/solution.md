## 方案一

现改为指针new DaEncoder和DaDecoder

```C++
int main(int argc, char *argv[]) {
    GisL::DaEncoder *pEncoder = new GisL::DaEncoder();
    pEncoder->loadTextFile2Text("../data/practise_1/Decode2.txt");
    pEncoder->encode();
    pEncoder->writeBinaryFile("../data/practise_1/Ddddecode2.da");
    delete pEncoder;
    GisL::DaDecoder *pDecoder = new GisL::DaDecoder();
    pDecoder->loadBinaryFile("../data/practise_1/Ddddecode2.da");
    pDecoder->decode();
    pDecoder->writeTextFile("../data/practise_1/BDsdDecode2.txt");
    return 1;
}
```

实测可以运行，均调用析构

## 方案二

main()函数加一句encoder.clean()

## 方案三

改进构造函数