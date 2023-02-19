// https://qiita.com/bellvine/items/428601f5742e483c7aa7 より

#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

class CSVFile {
public:
    string filepath;
    bool isHeader;
    bool isIndex;
    char delim;
    // ヘッダー名保管
    vector<string> header;
    // インデックス名保管
    vector<string> index;
    // 要素保管
    vector<vector<uint8_t>> cell;

    // コンストラクタ関数
    CSVFile();
    uint8_t cast_cell(string);
    void csv_read(string, bool, bool, char);
    void csv_write(string, char);
    void csv_show();
};

