#pragma once
#include <vector>
#include <list>
#include <map>
#include <set>
#include <cstring>
#include <iostream>
#include <cassert>
#include <algorithm>
#include "serializable.hpp"

namespace HW
{
    namespace SERIALIZE
    {
        class DataStream
        {
        public:

            enum BetyOrder{
                Little_endian=0,   //  LITTLE_ENDIAN
                Big_endian
            };
            enum DataType
            {
                BOOL = 0,
                CHAR,
                INT32,
                INT64,
                FLOAT,
                DOUBLE,
                STRING,
                VECTOR,
                LIST,
                MAP,
                SET,
                CUSTOM
            };
            DataStream() : m_pos(0){};
            DataStream(const BetyOrder& endian) :m_pos(0),m_typeOrder(endian){};
            ~DataStream(){};
            void show() const;
            void write(const char *ch, int len);
            void write(const bool val);
            void write(const char ch);
            void write(const int32_t val);
            void write(const int64_t val);
            void write(const float val);
            void write(const double val);
            void write(const std::string val);

            template <typename T>
            void write(const std::vector<T> &val);
            template <typename T>
            void write(const std::list<T> &val);
            template <typename T, typename U>
            void write(const std::map<T, U> &val);
            template <typename T>
            void write(const std::set<T> &val);
            void write(const Serializable& val);

            template<typename T, typename ...Args>
            void write_args(const T&val,const Args& ...args);
            void write_args();


            bool read(char* val,int len);
            bool read(bool &val);
            bool read(char &val);
            bool read(int32_t &val);
            bool read(int64_t &val);
            bool read(float &val);
            bool read(double &val);
            bool read(std::string &val);
            template <typename T>
            bool read(std::vector<T> &val);
            template <typename T>
            bool read(std::list<T> &val);
            template <typename T, typename U>
            bool read(std::map<T, U> &val);
            template <typename T>
            bool read(std::set<T> &val);
            bool read(Serializable &val);
            template<typename T,typename ...Args>
            bool read_args(T& val, Args& ...agrs);
            bool read_args();

            DataStream &operator<<(const bool &val);
            DataStream &operator<<(const char &val);
            DataStream &operator<<(const int32_t &val);
            DataStream &operator<<(const int64_t &val);
            DataStream &operator<<(const float &val);
            DataStream &operator<<(const double &val);
            DataStream &operator<<(const std::string &val);
            template <typename T>
            DataStream &operator<<(const std::vector<T> &val);
            template <typename T>
            DataStream &operator<<(const std::list<T> &val);
            template <typename T, typename U>
            DataStream &operator<<(const std::map<T, U> &val);
            template <typename T>
            DataStream &operator<<(const std::set<T> &val);
            DataStream& operator<<(const Serializable& val);

            DataStream &operator>>(bool &val);
            DataStream &operator>>(char &val);
            DataStream &operator>>(int32_t &val);
            DataStream &operator>>(int64_t &val);
            DataStream &operator>>(float &val);
            DataStream &operator>>(double &val);
            DataStream &operator>>(std::string &val);
            template <typename T>
            DataStream &operator>>(std::vector<T> &val);
            template <typename T>
            DataStream &operator>>(std::list<T> &val);
            template <typename T, typename U>
            DataStream &operator>>(std::map<T, U> &val);
            template <typename T>
            DataStream &operator>>(std::set<T> &val);
            DataStream& operator>>(Serializable& val);

        private:
            std::vector<char> m_buf;
            int m_pos;
            BetyOrder m_typeOrder = BetyOrder::Little_endian;
        };
    }
}

void HW::SERIALIZE::DataStream::write(const Serializable& val)
{
    val.serialize(*this);
}

bool HW::SERIALIZE::DataStream::read(Serializable &val)
{
    return val.unserialize(*this);
}

template<typename T, typename ...Args>
void  HW::SERIALIZE::DataStream::write_args(const T&val,const Args& ...args)
{
    write(val);
    write_args(args...);
}

void HW::SERIALIZE::DataStream::write_args()
{

}

template<typename T, typename ...Args>
bool HW::SERIALIZE::DataStream::read_args(T& val, Args& ...agrs)
{
    read(val);
    return read_args(agrs...);
}
bool HW::SERIALIZE::DataStream::read_args()
{
    return true;
}

HW::SERIALIZE::DataStream &HW::SERIALIZE::DataStream::operator>>(bool &val)
{
    read(val);
    return *this;
}
HW::SERIALIZE::DataStream &HW::SERIALIZE::DataStream::operator>>(char &val)
{
    read(val);
    return *this;
}
HW::SERIALIZE::DataStream &HW::SERIALIZE::DataStream::operator>>(int32_t &val)
{
    read(val);
    return *this;
}
HW::SERIALIZE::DataStream &HW::SERIALIZE::DataStream::operator>>(int64_t &val)
{
    read(val);
    return *this;
}
HW::SERIALIZE::DataStream &HW::SERIALIZE::DataStream::operator>>(float &val)
{
    read(val);
    return *this;
}

HW::SERIALIZE::DataStream &HW::SERIALIZE::DataStream::operator>>(double &val)
{
    read(val);
    return *this;
}

HW::SERIALIZE::DataStream &HW::SERIALIZE::DataStream::operator>>(std::string &val)
{
    read(val);
    return *this;
}

inline HW::SERIALIZE::DataStream &HW::SERIALIZE::DataStream::operator>>(Serializable &val)
{
    read(val);
    return *this;
}

inline bool HW::SERIALIZE::DataStream::read(char *val, int len)
{
    std::memcpy(val,(char*)&m_buf[m_pos],len);
    m_pos += len;
    return false;
}

bool HW::SERIALIZE::DataStream::read(bool &val)
{
    if (m_buf[m_pos] != DataType::BOOL)
        return false;
    ++m_pos;
    val = m_buf[m_pos];
    ++m_pos;
    return true;
}

bool HW::SERIALIZE::DataStream::read(char &val)
{
    if (m_buf[m_pos] != DataType::CHAR)
        return false;
    ++m_pos;
    val = *(char *)(&m_buf[m_pos]);
    ++m_pos;
    return true;
}

bool HW::SERIALIZE::DataStream::read(int32_t &val)
{
    if (m_buf[m_pos] != DataType::INT32)
        return false;
    ++m_pos;
    if(m_typeOrder ==BetyOrder::Big_endian)
    {
        char* first = (char*)&m_buf[m_pos];
        char* last = first + sizeof(int32_t);
        std::reverse(first,last);
    }
    val = *(int32_t *)(&m_buf[m_pos]);
    m_pos += sizeof(int32_t);
    return true;
}

bool HW::SERIALIZE::DataStream::read(int64_t &val)
{
    if (m_buf[m_pos] != DataType::INT64)
        return false;
    ++m_pos;
    if(m_typeOrder ==BetyOrder::Big_endian)
    {
        char* first = (char*)&m_buf[m_pos];
        char* last = first + sizeof(int64_t);
        std::reverse(first,last);
    }
    val = *(int64_t *)(&m_buf[m_pos]);
    m_pos += sizeof(int64_t);
    return true;
}

bool HW::SERIALIZE::DataStream::read(float &val)
{
    if (m_buf[m_pos] != DataType::FLOAT)
        return false;
    ++m_pos;
    if(m_typeOrder ==BetyOrder::Big_endian)
    {
        char* first = (char*)&m_buf[m_pos];
        char* last = first + sizeof(float);
        std::reverse(first,last);
    }
    val = *(float *)(&m_buf[m_pos]);
    m_pos += sizeof(float);
    return true;
}

bool HW::SERIALIZE::DataStream::read(double &val)
{
    if (m_buf[m_pos] != DataType::DOUBLE)
        return false;
    ++m_pos;
    if(m_typeOrder ==BetyOrder::Big_endian)
    {
        char* first = (char*)&m_buf[m_pos];
        char* last = first + sizeof(double);
        std::reverse(first,last);
    }
    val = *(double *)(&m_buf[m_pos]);
    m_pos += sizeof(double);
    return true;
}

bool HW::SERIALIZE::DataStream::read(std::string &val)
{
    if (m_buf[m_pos] != DataType::STRING)
        return false;
    ++m_pos;
    int32_t len;
    read(len);
    assert(len >= 0);
    // m_pos += sizeof(int);
    val = std::string(&m_buf[m_pos], len);
    m_pos += len;
    return true;
}

HW::SERIALIZE::DataStream &HW::SERIALIZE::DataStream::operator<<(const bool &val)
{
    this->write(val);
    return *this;
}
HW::SERIALIZE::DataStream &HW::SERIALIZE::DataStream::operator<<(const char &val)
{
    this->write(val);
    return *this;
}

HW::SERIALIZE::DataStream &HW::SERIALIZE::DataStream::operator<<(const int32_t &val)
{
    this->write(val);
    return *this;
}

HW::SERIALIZE::DataStream &HW::SERIALIZE::DataStream::operator<<(const int64_t &val)
{
    this->write(val);
    return *this;
}
HW::SERIALIZE::DataStream &HW::SERIALIZE::DataStream::operator<<(const float &val)
{
    this->write(val);
    return *this;
}

HW::SERIALIZE::DataStream &HW::SERIALIZE::DataStream::operator<<(const double &val)
{
    this->write(val);
    return *this;
}

HW::SERIALIZE::DataStream &HW::SERIALIZE::DataStream::operator<<(const std::string &val)
{
    this->write(val);
    return *this;
}

HW::SERIALIZE::DataStream& HW::SERIALIZE::DataStream::operator<<(const Serializable& val)
{
    write(val);
    return *this;
}

void HW::SERIALIZE::DataStream::show() const
{
    std::cout << "length:" << m_buf.size() << std::endl;
    int i = 0;
    while (i < m_buf.size())
    {
        switch ((DataType)m_buf[i])
        {
        case DataType::BOOL:
        {
            (bool)m_buf[++i] == 0 ? std::cout << "false" : std::cout << "true";
            std::cout << std::endl;
            ++i;
            break;
        }

        case DataType::CHAR:
        {
            std::cout << (char)m_buf[++i] << std::endl;
            ++i;
            break;
        }
        case DataType::INT32:
        {
            std::cout << *(int32_t *)(&m_buf[++i]) << std::endl;
            i += sizeof(int32_t);
            break;
        }
        case DataType::INT64:
        {
            std::cout << *(int64_t *)(&m_buf[++i]) << std::endl;
            i += sizeof(int64_t);
            break;
        }
        case DataType::FLOAT:
        {
            std::cout << *(float *)(&m_buf[++i]) << std::endl;
            i += sizeof(float);
            break;
        }
        case DataType::DOUBLE:
        {
            std::cout << *(double *)(&m_buf[++i]) << std::endl;
            i += sizeof(double);
            break;
        }
        case DataType::STRING:
        {
            if (DataType::INT32 == (DataType)m_buf[++i])
            {
                int32_t len = *((int32_t *)(&m_buf[++i])); // 字符串的长度
                i += sizeof(int32_t);
                std::cout << std::string(&m_buf[i], len) << std::endl;
                i += len;
            }
            else
            {
                throw std::logic_error("parse string error!");
            }
            break;
        }
        default:
            break;
        }
    }
    // for (const auto& val:m_buf)
    // {
    //     std::cout<<val<<" ";
    // }
    // std::cout<<'\n';
}

void HW::SERIALIZE::DataStream::write(const char *ch, int len)
{
    int size = m_buf.size();
    m_buf.resize(size + len);
    std::memcpy(&m_buf[size], ch, len);
}

void HW::SERIALIZE::DataStream::write(bool val)
{
    char type = DataType::BOOL;
    write((char *)&type, sizeof(char));
    write((char *)&val, sizeof(val));
}

void HW::SERIALIZE::DataStream::write(char val)
{
    char type = DataType::CHAR;
    write((char *)&type, sizeof(char));
    write((char *)&val, sizeof(val));
}

void HW::SERIALIZE::DataStream::write(int32_t val)
{
    char type = DataType::INT32;
    write((char *)&type, sizeof(char));
    if(m_typeOrder == BetyOrder::Big_endian)
    {
        char* first = (char*)&type;
        char* last = first + sizeof(int32_t);
        std::reverse(first,last);           //指向的地址指针进行翻转
    }
    write((char *)&val, sizeof(val));
}

void HW::SERIALIZE::DataStream::write(int64_t val)
{
    char type = DataType::INT64;
    write((char *)&type, sizeof(char));
    if(m_typeOrder == BetyOrder::Big_endian)
    {
        char* first = (char*)&type;
        char* last = first + sizeof(int64_t);
        std::reverse(first,last);
    }
    write((char *)&val, sizeof(val));
}

void HW::SERIALIZE::DataStream::write(float val)
{
    char type = DataType::FLOAT;
    write((char *)&type, sizeof(char));
    if(m_typeOrder == BetyOrder::Big_endian)
    {
        char* first = (char*)&type;
        char* last = first + sizeof(float);
        std::reverse(first,last);
    }
    write((char *)&val, sizeof(val));
}
void HW::SERIALIZE::DataStream::write(double val)
{
    char type = DataType::DOUBLE;
    write((char *)&type, sizeof(char));
    if(m_typeOrder == BetyOrder::Big_endian)
    {
        char* first = (char*)&type;
        char* last = first + sizeof(double);
        std::reverse(first,last);
    }
    write((char *)&val, sizeof(val));
}
void HW::SERIALIZE::DataStream::write(std::string val)
{
    char type = DataType::STRING;
    int size = val.size();
    write((char *)&type, sizeof(char));
    write(size);
    write(val.data(), val.size());
}
// void HW::SERIALIZE::DataStream::write(std::vector val)
// {
//     char type = DataType::VECTOR;
//     write((char*)&type,sizeof(char));
//     write((char*)&val,sizeof(VECTOR));
// }

template <typename T>
void HW::SERIALIZE::DataStream::write(const std::vector<T> &val)
{
    char type = DataType::VECTOR;
    this->write((char *)&type, sizeof(char));
    int size = val.size();
    this->write(size);
    for (int i = 0; i < size; i++)
    {
        this->write(val[i]);
    }
}

template <typename T>
void HW::SERIALIZE::DataStream::write(const std::list<T> &val)
{
    char type = DataType::LIST;
    this->write((char *)&type, sizeof(char));
    int32_t size = val.size();
    this->write(size);
    for (auto it = val.begin(); it != val.end(); it++)
    {
        write(*it);
    }
}

template <typename T, typename U>
void HW::SERIALIZE::DataStream::write(const std::map<T, U> &val)
{
    char type = DataType::MAP;
    write((char *)&type, sizeof(char));
    int32_t size = val.size();
    write(size);
    for (auto it : val)
    {
        write(it.first);
        write(it.second);
    }
}

template <typename T>
void HW::SERIALIZE::DataStream::write(const std::set<T> &val)
{
    char type = DataType::SET;
    write((char *)&type, sizeof(char));
    int32_t size = val.size();
    write(size);
    for (auto it : val)
    {
        write(it);
    }
}

template <typename T>
bool HW::SERIALIZE::DataStream::read(std::set<T> &val)
{
    val.clear();
    if ((DataType)m_buf[m_pos] != DataType::SET)
        return false;
    ++m_pos;
    int32_t len;
    read(len);
    for (int32_t i = 0; i < len; i++)
    {
        T v;
        read(v);
        val.insert(v);
    }
    return true;
}

template <typename T>
inline HW::SERIALIZE::DataStream &HW::SERIALIZE::DataStream::operator<<(const std::vector<T> &val)
{
    write(val);
    return *this;
}

template <typename T>
inline HW::SERIALIZE::DataStream &HW::SERIALIZE::DataStream::operator<<(const std::list<T> &val)
{
    write(val);
    return *this;
}

template <typename T, typename U>
inline HW::SERIALIZE::DataStream &HW::SERIALIZE::DataStream::operator<<(const std::map<T, U> &val)
{
    write(val);
    return *this;
}

template <typename T>
inline HW::SERIALIZE::DataStream &HW::SERIALIZE::DataStream::operator<<(const std::set<T> &val)
{
    write(val);
    return *this;
}

template <typename T>
inline HW::SERIALIZE::DataStream &HW::SERIALIZE::DataStream::operator>>(std::vector<T> &val)
{
    read(val);
    return *this;
}

template <typename T>
inline HW::SERIALIZE::DataStream &HW::SERIALIZE::DataStream::operator>>(std::list<T> &val)
{
    read(val);
    return *this;
}

template <typename T, typename U>
inline HW::SERIALIZE::DataStream &HW::SERIALIZE::DataStream::operator>>(std::map<T, U> &val)
{
    read(val);
    return *this;
}

template <typename T>
inline HW::SERIALIZE::DataStream &HW::SERIALIZE::DataStream::operator>>(std::set<T> &val)
{
    read(val);
    return *this;
}

template <typename T>
bool HW::SERIALIZE::DataStream::read(std::vector<T> &val)
{
    val.clear();
    if (!(DataType)m_buf[m_pos] == DataType::VECTOR)
        return false;
    m_pos++;
    // int32_t len = *(int32_t*)(&m_buf[m_pos]);
    int32_t len;
    read(len);
    for (int32_t i = 0; i < len; i++)
    {
        T v;
        read(v);
        val.emplace_back(v);
    }
    return true;
}
template <typename T>
bool HW::SERIALIZE::DataStream::read(std::list<T> &val)
{
    val.clear();
    if (!(DataType)m_buf[m_pos] == DataType::LIST)
        return false;
    ++m_pos;
    int32_t len;
    read(len);
    for (int32_t i = 0; i < len; i++)
    {
        T v;
        read(v);
        val.emplace_back(v);
    }
    return true;
}

template <typename T, typename U>
bool HW::SERIALIZE::DataStream::read(std::map<T, U> &val)
{
    val.clear();
    if (!(DataType)m_buf[m_pos] == DataType::MAP)
        return false;
    ++m_pos;
    int32_t len;
    read(len);
    for (int32_t i = 0; i < len; i++)
    {
        T k;
        read(k);
        U v;
        read(v);
        val[k] = v;
    }
    return true;
}
