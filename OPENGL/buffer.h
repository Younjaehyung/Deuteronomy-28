#pragma once
#include "common_include.h"

CLASS_PTR ( Buffer )
class Buffer {
public:
    static BufferUPtr CreateWithData (
        uint32_t bufferType , uint32_t usage ,const void* data , size_t stride , size_t count );
    ~Buffer ( );
    size_t GetStride ( ) const { return m_stride; }
    size_t GetCount ( ) const { return m_count; }
    void Bind ( ) const;

private:
    Buffer ( ) {}
    bool Init ( uint32_t bufferType , uint32_t usage ,
      const void* data , size_t stride , size_t count );

    uint32_t m_buffer{ 0 };
    uint32_t m_bufferType{ 0 };
    uint32_t m_usage{ 0 };

    //data size
    size_t m_stride{ 0 };
    size_t m_count{ 0 };
};
