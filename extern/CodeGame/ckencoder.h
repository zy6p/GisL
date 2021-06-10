#ifndef CKENCODER_H
#define CKENCODER_H

#include <string>
#include "ckunit.h"
#include <vector>

using namespace std;

class CKEncoder {
public:
    CKEncoder();

    ~CKEncoder();

    int loadTxtData(string path);

    void encode();

    int outputFile(string o_path);
//    int counter;
private:
    char *buffer;//从文件里面读取的所有字符
    int buf_size;
    CKUnit **pUnits;
    CKUnit **randUnits;

    int getRandNum(int n);

    int getValidPos(int size);
};

#endif // CKENCODER_H
