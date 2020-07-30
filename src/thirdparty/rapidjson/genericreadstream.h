#ifndef RAPIDJSON_GENERICREADSTREAM_H_
#define RAPIDJSON_GENERICREADSTREAM_H_

#include "rapidjson.h"
#include <iostream>

namespace rapidjson {

//! Wrapper of std::istream for input.
class GenericReadStream {
public:
    typedef char Ch;    //!< Character type (byte).

    //! Constructor.
    /*!
        \param is Input stream.
    */
    GenericReadStream(std::istream& is) : is_(is) {
    }

    Ch Peek() const {
        return static_cast<char>(is_.peek());
    }

    Ch Take() {
        return static_cast<char>(is_.get());
    }

    size_t Tell() const {
        return (int)is_.tellg();
    }

    // Not implemented
    void Put(Ch c) { RAPIDJSON_ASSERT(false); }
    void Flush() { RAPIDJSON_ASSERT(false); }
    Ch* PutBegin() { RAPIDJSON_ASSERT(false); return 0; }
    size_t PutEnd(Ch*) { RAPIDJSON_ASSERT(false); return 0; }

    std::istream& is_;
};

} // namespace rapidjson

#endif // RAPIDJSON_GENERICREADSTREAM_H_