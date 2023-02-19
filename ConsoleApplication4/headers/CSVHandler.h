// https://qiita.com/bellvine/items/428601f5742e483c7aa7 ���

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
    // �w�b�_�[���ۊ�
    vector<string> header;
    // �C���f�b�N�X���ۊ�
    vector<string> index;
    // �v�f�ۊ�
    vector<vector<uint8_t>> cell;

    // �R���X�g���N�^�֐�
    CSVFile();
    uint8_t cast_cell(string);
    void csv_read(string, bool, bool, char);
    void csv_write(string, char);
    void csv_show();
};

