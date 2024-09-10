#pragma once
#include <iostream>

namespace HW
{
    namespace SERIALIZE
    {
        class DataStream;   //前向声明
        class Serializable
        {
            public:
                virtual void serialize(DataStream& stream) const =0;
                virtual bool unserialize(DataStream& stream) =0;
        };
        #define SERIALIZE_OR_UNSERIALIZE(...)                        \
        void serialize(DataStream& stream) const      \
        {                                             \
            char type = DataStream::CUSTOM;           \
            stream.write((char*)&type,sizeof(char));  \
            stream.write_args(__VA_ARGS__);           \
        }                                             \
        bool unserialize(DataStream& stream)          \
        {                                             \
            char type;                                \
            stream.read(&type,sizeof(char));                    \
            if ((DataStream::DataType)type != DataStream::CUSTOM)           \
            {                                         \
            return false;                             \
        }                                             \
            stream.read_args(__VA_ARGS__);            \
            return true;                              \
        }   


    }

}