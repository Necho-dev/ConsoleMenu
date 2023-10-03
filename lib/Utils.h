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

// �ļ���дģʽ
enum MODE {
    APPEND = std::ios::out | std::ios::app,  // ׷��
    OVERWRITE = std::ios::out                // ����
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

    // �����ַ��� ģ�庯��
    template<typename T>
    std::string ToString(T fmt) {
        return String::to_string(fmt);
    }
    template<typename T, typename ...Args>
    std::string ToString(T fmt, Args... args) {
        return String::to_string(fmt) + ToString(args...);
    }
    // ָ���ָ��������ַ��� ģ�庯��
    template<typename Value>
    std::string ToString(char _sep, Value fmt) {
        return String::to_string(fmt);
    }
    template<typename Value, typename ...Args>
    std::string ToString(char _sep, Value fmt, Args... args) {
        return String::to_string(fmt) + _sep + ToString(_sep, args...);
    }
    // ָ���ָ��������ַ��� ��������(������)
    static std::string ToString(char _sep, double _attrSize, ...);

    // ��ʽ���ַ��� ģ�庯��
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

    // �ַ���Сдת��Ϊ��д
    std::string ToUpper(const std::string& origin);
    // �ַ�����дת��ΪСд
    std::string ToLower(const std::string& origin);

    // ���Ŀ¼�Ƿ����
    bool CheckDirectory(const std::string& dirPath);
    // �½�Ŀ¼
    bool MakeDirectory(const std::string& dirPath, bool iLog = false);

    // ��ȡ�ļ���
    std::string getFileName(const std::string& filePath);
    // ���ݷָ�����ȡ�ı�ǰ׺
    std::string getPrefix(const std::string &text, const std::string& sep);
    // ���ݷָ�����ȡ�ı���׺
    std::string getSuffix(const std::string &text, const std::string& sep);
    // �ж��ļ���չ��(��׺)�Ƿ���ͬ
    bool ifSuffix(const std::string &fileName, const std::string &suffix);
    // ��ȡָ�����ļ�
//    std::vector<Point> ReadFileToData(const std::string& _fileName);
    // д��ָ�����ļ�
//    void WriteDataToFile(const std::string& _fileName, const std::map<double, std::vector<Point>>& _data, MODE mode = MODE::OVERWRITE);

};


#endif //CONSOLEACTION_UTILS_H
