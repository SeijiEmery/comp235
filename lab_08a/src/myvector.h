#pragma once
#include <string>
#include "utility/util/mem_bench.hpp"

class MyVector {
public:
    MyVector () {}
    ~MyVector () { if (m_data) { delete[] m_data; m_data = nullptr; } }

    size_t size () const { return m_size; }
    void addEntry (const std::string& value) {
        std::string* newData = new std::string[++m_size];
        std::copy(&m_data[0], &m_data[m_size - 1], &newData[0]);
        delete[] m_data;
        m_data = newData;
        m_data[m_size - 1] = value;
    }
    bool deleteEntry (const std::string& value) {
        for (size_t i = 0; i < size(); ++i) {
            if (m_data[i] == value) {
                if (--m_size) {
                    std::string* newData = new std::string[m_size];
                    std::copy(&m_data[0], &m_data[i], &newData[0]);
                    std::copy(&m_data[i+1], &m_data[m_size+1], &newData[i]);
                    delete[] m_data;
                    m_data = newData;
                } else {
                    m_data = nullptr;
                }
                return true;
            }
        }
        return false;
    }
    std::string getEntry (size_t i) const {
        return i < size() ?
            m_data[i] :
            "";
    }
private:
    std::string*    m_data = nullptr;
    size_t          m_size = 0;
};
