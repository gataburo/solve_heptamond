// https://qiita.com/bellvine/items/428601f5742e483c7aa7 より

#include "CSVHandler.h"

CSVFile::CSVFile() {
    isHeader = false;
    isIndex = false;
    delim = ',';
}

uint8_t CSVFile::cast_cell(string str) {
    return (uint8_t)stoi(str);
}

// CSVファイルを読みこむ
void CSVFile::csv_read(string filepath, bool isHeader, bool isIndex, char delim) {
    this->filepath = filepath;
    this->isHeader = isHeader;
    this->isIndex = isIndex;
    this->delim = delim;

    string str_buf;
    string str_comma_buf;

    // 読み込むcsvファイルを開く(ifstreamのコンストラクタで開く)
    ifstream ifs_csv_file(filepath);

    // getline関数で1行ずつ読み込む(読み込んだ内容は str_buf に格納)
    for (int i = 0; getline(ifs_csv_file, str_buf); i++) {
        cell.push_back(vector<uint8_t>());

        // delim 区切りごとにデータを読み込むために istringstream にする
        istringstream i_stream(str_buf);

        for (int j = 0; getline(i_stream, str_comma_buf, delim); j++) {
            if (isHeader && isIndex) {
                if (i == 0 && j == 0) continue;
                if (i == 0 && j != 0) header.push_back(str_comma_buf);
                if (i != 0 && j == 0) index.push_back(str_comma_buf);
                if (i != 0 && j != 0) cell.at(i - 1).push_back(cast_cell(str_comma_buf));
            }
            else if (isHeader) {
                if (i == 0) header.push_back(str_comma_buf);
                if (i != 0 && j == 0) index.push_back(string());
                if (i != 0) cell.at(i - 1).push_back(cast_cell(str_comma_buf));
            }
            else if (isIndex) {
                if (i == 0 && j != 0) header.push_back(string());
                if (j == 0) index.push_back(str_comma_buf);
                if (j != 0) cell.at(i).push_back(cast_cell(str_comma_buf));
            }
            else {
                if (i == 0) header.push_back(string());
                if (j == 0) index.push_back(string());
                cell.at(i).push_back(cast_cell(str_comma_buf));
            }
        }
    }
}

// CSVファイルをファイル出力する
void CSVFile::csv_write(string filepath, char delim) {
    // 書き込むcsvファイルを開く(ofstreamのコンストラクタで開く)
    ofstream ofs_csv_file(filepath);

    if (isHeader) {
        for (int j = 0; j < header.size(); j++) {
            if (isIndex && j == 0) ofs_csv_file << delim;
            ofs_csv_file << header.at(j) << delim;
        }
        ofs_csv_file << endl;
    }
    for (int i = 0; i < index.size(); i++) {
        if (isIndex) {
            ofs_csv_file << index.at(i) << delim;
        }
        for (int j = 0; j < header.size(); j++) {
            ofs_csv_file << cell.at(i).at(j) << delim;
        }
        ofs_csv_file << endl;
    }
    ofs_csv_file << endl;
}

// CSVファイルをコンソール出力する
void CSVFile::csv_show() {
    cout << "filepath = " << filepath << ", ";
    cout << "isHeader = " << int(isHeader) << ", ";
    cout << "isIndex = " << int(isIndex) << ", ";
    cout << "delim = " << delim << endl;
    cout << "header size = " << header.size() << ", ";
    cout << "index size = " << index.size() << endl;

    if (isHeader) {
        for (int j = 0; j < header.size(); j++) {
            if (isIndex && j == 0) cout << "\t";
            cout << header.at(j) << "(h)" << "\t";
        }
        cout << endl;
    }
    for (int i = 0; i < index.size(); i++) {
        if (isIndex) {
            cout << index.at(i) << "(i)" << "\t";
        }
        for (int j = 0; j < header.size(); j++) {
            cout << (int)(cell.at(i).at(j)) << "\t";
        }
        cout << endl;
    }
    cout << endl;
}
