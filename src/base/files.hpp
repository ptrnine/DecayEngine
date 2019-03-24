#ifndef DECAYENGINE_FILES_HPP
#define DECAYENGINE_FILES_HPP

#include <iostream>
#include <fstream>
#include <mutex>
#include <string_view>

#include "concepts.hpp"
#include "serialization.hpp"
#include "baseTypes.hpp"

namespace base {
    class FileWriter {
    public:
        FileWriter(const std::string_view& name);

        template <SizeT _Size>
        void write(const ftl::Array<Byte, _Size>& array) {
            auto lock = std::lock_guard(_mutex);
            _ofs.write(reinterpret_cast<const char*>(array.data()), _Size);
        }

        void write(const ftl::Vector<Byte>& bytes) {
            auto lock = std::lock_guard(_mutex);
            _ofs.write(reinterpret_cast<const char*>(bytes.data()), bytes.size());
        }

        template <typename T>
        void write(const T& value) {
            write(srlz::serialize(value));
        }

    protected:
        std::ofstream _ofs;
        std::mutex    _mutex;
    };



} // namespace base


#endif //DECAYENGINE_FILES_HPP
