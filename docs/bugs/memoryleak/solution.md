## 方案一

现改为指针new DaEncoder和DaDecoder

```C++
int main(int argc, char *argv[]) {
    gisl::DaEncoder *pEncoder = new gisl::DaEncoder();
    pEncoder->loadTextFile2Text("../resource/practise_1/Decode2.txt");
    pEncoder->encode();
    pEncoder->writeBinaryFile("../resource/practise_1/Ddddecode2.da");
    delete pEncoder;
    gisl::DaDecoder *pDecoder = new gisl::DaDecoder();
    pDecoder->loadBinaryFile("../resource/practise_1/Ddddecode2.da");
    pDecoder->decode();
    pDecoder->writeTextFile("../resource/practise_1/BDsdDecode2.txt");
    return 1;
}
```

实测可以运行，均调用析构

## 方案二

main()函数加一句encoder.clean()

## 方案三

改进构造函数