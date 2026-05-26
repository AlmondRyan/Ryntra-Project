#pragma once

#include <cstdint>
#include <memory>
#include <string>
#include <variant>
#include <vector>

namespace Ryntra::VM {
    class VMValue;
    struct ArrayData {
        std::vector<VMValue> elements;
    };
    struct ArrayElementRef {
        std::shared_ptr<ArrayData> array;
        int32_t index;
    };

    // Runtime value representation
    class VMValue {
    public:
        enum class Type {
            Void,
            Int32,
            Int64,
            String,
            FunctionPtr,
            Array,
            Reference,    // holds an int32 slot index (local)
            Pointer,      // holds an int32 slot index (local) or array element index
            HeapPointer,   // holds an int32 slot index (heap)
            ArrayElementRef // reference to an array element (arr[i])
        };

        using ValueData = std::variant<std::monostate, int32_t, int64_t, std::string, void *, std::shared_ptr<ArrayData>, ArrayElementRef>;

        VMValue() : type_(Type::Void), data_(std::monostate{}) {}
        explicit VMValue(int32_t val) : type_(Type::Int32), data_(val) {}
        explicit VMValue(int64_t val) : type_(Type::Int64), data_(val) {}
        explicit VMValue(const std::string &val) : type_(Type::String), data_(val) {}
        explicit VMValue(void *ptr) : type_(Type::FunctionPtr), data_(ptr) {}
        explicit VMValue(std::shared_ptr<ArrayData> arr) : type_(Type::Array), data_(std::move(arr)) {}
        explicit VMValue(ArrayElementRef elemRef) : type_(Type::ArrayElementRef), data_(elemRef) {}

        Type getType() const { return type_; }

        int32_t asInt32() const { return std::get<int32_t>(data_); }
        int64_t asInt64() const { return std::get<int64_t>(data_); }
        const std::string &asString() const { return std::get<std::string>(data_); }
        void *asFunctionPtr() const { return std::get<void *>(data_); }
        std::shared_ptr<ArrayData> asArray() const { return std::get<std::shared_ptr<ArrayData>>(data_); }

        bool isVoid() const { return type_ == Type::Void; }
        bool isInt32() const { return type_ == Type::Int32; }
        bool isInt64() const { return type_ == Type::Int64; }
        bool isString() const { return type_ == Type::String; }
        bool isArray() const { return type_ == Type::Array; }
        bool isArrayElementRef() const { return type_ == Type::ArrayElementRef; }
        ArrayElementRef asArrayElementRef() const { return std::get<ArrayElementRef>(data_); }

        // Reference support — refs are stored as int32 slot indices
        void setReferenceSlot(int32_t slot) { type_ = Type::Reference; data_ = slot; }
        int32_t getReferenceSlot() const { return std::get<int32_t>(data_); }
        bool isReference() const { return type_ == Type::Reference; }

        // Pointer support — pointers are stored as int32 slot indices
        // May also have an optional array ref for array element pointers (from ptr(arr))
        void setPointerSlot(int32_t slot) { type_ = Type::Pointer; data_ = slot; ptrArrayData_ = nullptr; }
        int32_t getPointerSlot() const { return std::get<int32_t>(data_); }
        bool isPointer() const { return type_ == Type::Pointer; }

        void setArrayPointer(int32_t index, std::shared_ptr<ArrayData> arr) { type_ = Type::Pointer; data_ = index; ptrArrayData_ = std::move(arr); }
        bool isArrayPointer() const { return isPointer() && ptrArrayData_ != nullptr; }
        std::shared_ptr<ArrayData> getArrayPointerData() const { return ptrArrayData_; }

        // Heap pointer support — heap pointers are stored as int32 heap indices
        void setHeapPointerSlot(int32_t slot) { type_ = Type::HeapPointer; data_ = slot; }
        int32_t getHeapPointerSlot() const { return std::get<int32_t>(data_); }
        bool isHeapPointer() const { return type_ == Type::HeapPointer; }

    private:
        Type type_;
        ValueData data_;
        std::shared_ptr<ArrayData> ptrArrayData_; // optional: non-null for array element pointers
    };
} // namespace Ryntra::VM
