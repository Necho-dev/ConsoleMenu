#ifndef CONSOLEACTION_UTILS_H
#define CONSOLEACTION_UTILS_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <direct.h>
#include <map>
#include "Logs.h"

#ifdef _WIN32
#include <io.h>
#else
#include <unistd.h>
#endif

// 文件读写模式
enum MODE {
    APPEND = std::ios::out | std::ios::app,  // 追加
    OVERWRITE = std::ios::out                // 覆盖
};

namespace Utils {

    inline namespace String {
        template<typename T>
        typename std::enable_if<std::is_integral<T>::value, std::string>::type to_string(const T& value) {
            return std::to_string(value);
        }
        template<typename T>
        typename std::enable_if<std::is_floating_point<T>::value, std::string>::type to_string(const T& value) {
            return std::to_string(value);
        }
        template<typename T>
        typename std::enable_if<std::is_enum<T>::value, std::string>::type to_string(const T& value) {
            return std::to_string(value);
        }
        static std::string to_string(const std::string& value) {
            return value;
        }
        static std::string to_string(const char* value) {
            return value;
        }
    }

    // 连接字符串 模板函数
    template<typename T>
    std::string ToString(T fmt) {
        return String::to_string(fmt);
    }
    template<typename T, typename ...Args>
    std::string ToString(T fmt, Args... args) {
        return String::to_string(fmt) + ToString(args...);
    }
    // 指定分隔符连接字符串 模板函数
    template<typename Value>
    std::string ToString(char _sep, Value fmt) {
        return String::to_string(fmt);
    }
    template<typename Value, typename ...Args>
    std::string ToString(char _sep, Value fmt, Args... args) {
        return String::to_string(fmt) + _sep + ToString(_sep, args...);
    }
    // 指定分隔符连接字符串 不定参数(已弃用)
    static std::string ToString(char _sep, double _attrSize, ...);

    // 格式化字符串 模板函数
    template<typename ...Args>
    std::string Format(const char *fmt, const Args... args) {
        std::string text;
        const auto length = std::snprintf(nullptr, 0, fmt, args...);
        if (length <= 0) return "";
        text.resize(static_cast<size_t>(length) + 1);
        std::snprintf(&text.front(), length + 1, fmt, args...);
        text.resize(static_cast<size_t>(length));
        return text;
    }

    // 字符串小写转换为大写
    std::string ToUpper(const std::string& origin);
    // 字符串大写转换为小写
    std::string ToLower(const std::string& origin);

    // 检查目录是否存在
    bool CheckDirectory(const std::string& dirPath);
    // 新建目录
    bool MakeDirectory(const std::string& dirPath, bool iLog = false);

    // 获取文件名
    std::string getFileName(const std::string& filePath);
    // 根据分隔符获取文本前缀
    std::string getPrefix(const std::string &text, const std::string& sep);
    // 根据分隔符获取文本后缀
    std::string getSuffix(const std::string &text, const std::string& sep);
    // 判断文件扩展名(后缀)是否相同
    bool ifSuffix(const std::string &fileName, const std::string &suffix);
    // 读取指定的文件
//    std::vector<Point> ReadFileToData(const std::string& _fileName);
    // 写到指定的文件
//    void WriteDataToFile(const std::string& _fileName, const std::map<double, std::vector<Point>>& _data, MODE mode = MODE::OVERWRITE);

};


#endif //CONSOLEACTION_UTILS_H
