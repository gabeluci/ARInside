#ifndef RAPIDJSON_GENERICWRITESTREAM_H_
#define RAPIDJSON_GENERICWRITESTREAM_H_

#include "rapidjson.h"
#include <iostream>

namespace rapidjson {

//! Wrapper of std::ostream for output.
class GenericWriteStream {
public:
    typedef char Ch;    //!< Character type. Only support char.

    //! Constructor
    /*!
        \param os Output stream.
    */
    GenericWriteStream(std::ostream& os) : os_(os) {
    }

    void Put(char c) {
        os_.put(c);
    }

    void PutN(char c, size_t n) {
        for (size_t i = 0; i < n; ++i) {
            Put(c);
        }
    }

    void Flush() {
        os_.flush();
    }

    size_t Tell() const {
        return (int)os_.tellp();
    }

    // Not implemented
    char Peek() const { RAPIDJSON_ASSERT(false); }
    char Take() { RAPIDJSON_ASSERT(false); }
    char* PutBegin() { RAPIDJSON_ASSERT(false); return 0; }
    size_t PutEnd(char*) { RAPIDJSON_ASSERT(false); return 0; }

private:
    std::ostream& os_;
};

template<>
inline void PutN(GenericWriteStream& stream, char c, size_t n) {
    stream.PutN(c, n);
}

} // namespace rapidjson

#endif // RAPIDJSON_GENERICWRITESTREAM_H_
