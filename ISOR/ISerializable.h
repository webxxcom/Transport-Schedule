#pragma once
#include "stdafx.h"
#include "stdafx.cpp"

template<typename T>
concept Streamable = std::is_base_of_v< std::ios, T>;

template<typename ObjectType, Streamable WriteToBuffer, Streamable ReadFrom>
class ISerializable
{
public:
    virtual ObjectType getType() const = 0;
    virtual std::string_view getTypeString() const = 0;
    virtual void serialize(WriteToBuffer& out) const = 0;
    virtual void deserialize(ReadFrom& ss) = 0;

    virtual ~ISerializable() = default;
};