#include "Utils.h"

std::string Utils::getFileName(const std::string &path) {
    std::string fileName = getSuffix(path, "\\");
    return getPrefix(fileName, ".");
}

std::string Utils::getPrefix(const std::string &text, const std::string& sep) {
    unsigned position = text.find_last_of(sep);
    return text.substr(0, position);
}

std::string Utils::getSuffix(const std::string &text, const std::string& sep) {
    unsigned position = text.find_last_of(sep);
    return text.substr(position + 1);
}

bool Utils::ifSuffix(const std::string &fileName, const std::string &suffix) {
    return getSuffix(fileName, ".") == suffix;
}

std::string Utils::ToString(char _sep, double _attrSize, ...) {
    double *attrSize = &_attrSize;
    std::string String = std::to_string((int)*++attrSize);
    for (int i = 1; i < _attrSize; ++i) {
        String += _sep + std::to_string((int)*++attrSize);
    }
    return String;
}

std::string Utils::ToUpper(const std::string& origin) {
    std::string result;
    for (char ch: origin) {
        if (ch >= 'a' && ch <= 'z') {
            ch += 'A'-'a';
        }
        result.push_back(ch);
    }
    return result;
}

std::string Utils::ToLower(const std::string& origin) {
    std::string result;
    for (char ch: origin) {
        if (ch >= 'A' && ch <= 'Z') {
            ch += 'a'-'A';
        }
        result.push_back(ch);
    }
    return result;
}

//std::vector<Point> Utils::ReadFileToData(const std::string& _fileName) {
//    std::vector<Point> PointSet;
//    std::vector<double> dataVec;
//    std::ifstream fs(_fileName, std::ios::in);
//    if (fs.is_open()) {
//        std::string line;
//        while (getline(fs, line)) {
//            Point dataPoint;
//            std::string item;
//            std::istringstream dataTemp(line);
//            /*
//             * 如果文件扩展名为 .csv，则按照逗号分隔
//             * 如果文件扩展名为 .txt，则按照制表符分隔
//             */
//            if (ifSuffix(_fileName, "csv")) {
//                while (getline(dataTemp, item, ',')) {
//                    dataVec.emplace_back(std::stod(item));
//                }
//            } else if (ifSuffix(_fileName, "txt")) {
//                while (getline(dataTemp, item, '\t')) {
//                    dataVec.emplace_back(std::stod(item));
//                }
//            }
//            dataPoint.Set(dataVec);
//            PointSet.push_back(dataPoint);
//            //清空 dataVec 容器内容
//            std::vector<double>().swap(dataVec);
//        }
//        fs.close();
//    } else {
//        Logs::error(Utils::ToString("File '", _fileName, "' Not Found!"));
//        exit(1);
//    }
//    return PointSet;
//}
//
//void Utils::WriteDataToFile(const std::string &_fileName, const std::map<double, std::vector<Point>> &_data, MODE mode) {
//    // 初始化文件流
//    std::ofstream fs(_fileName, static_cast<std::ios::openmode>(mode));
//    if (fs.is_open()) {
//        /*
//        * 如果文件扩展名为 .csv，则按照逗号分隔
//        * 如果文件扩展名为 .txt，则按照制表符分隔
//        */
//        if (ifSuffix(_fileName, "csv")) {
//            for (const auto & item : _data) {
//                for (const Point& dataLine : item.second) {
//                    fs << ToString(',', dataLine.GetX<int>(), dataLine.GetY<int>(), dataLine.GetZ<int>(), dataLine.GetS<int>()) << std::endl;
//                }
//            }
//        } else if (ifSuffix(_fileName, "txt")) {
//            for (const auto & item : _data) {
//                for (const Point& dataLine : item.second) {
//                    fs << ToString('\t', dataLine.GetX<int>(), dataLine.GetY<int>(), dataLine.GetZ<int>(), dataLine.GetS<int>()) << std::endl;
//                }
//            }
//        }
//        fs.close();
//    } else {
//        Logs::error(Utils::ToString("File '", _fileName, "' Failed Write!"));
//        exit(1);
//    }
//}

bool Utils::CheckDirectory(const std::string &dirPath) {
    return _access(dirPath.c_str(), 0) == 0;
}

bool Utils::MakeDirectory(const std::string &dirPath, bool iLog) {
    // 检查目录是否存在 如果不存在则创建 存在则返回FALSE
    if (!CheckDirectory(dirPath)) {
        bool result = _mkdir(dirPath.c_str()) == 0;
        // 检查目录是否创建成功 如果创建失败则返回FALSE
        if (!result) {
            iLog ? Logs::error(Utils::ToString("Directory '", dirPath, "' Create Failed!")) : void ();
            return false;
        }
        iLog ? Logs::success(Utils::ToString("Directory '", dirPath, "' Created!")) : void ();
        return true;
    }
    iLog ? Logs::warn(Utils::ToString("Directory '", dirPath, "' Already Exists!")) : void ();
    return false;
}
