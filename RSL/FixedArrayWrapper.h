#pragma once

template<class T>
class FixedArrayWrapper
{
public:
    FixedArrayWrapper() = default;
    FixedArrayWrapper(T*& ElementPointer_, int ArraySize_, int NumberOfElements_) : Elements(ElementPointer_), ArraySize(ArraySize_), NumberOfElements(NumberOfElements_) { _Initialized = true; }
    void Init(T*& ElementPointer_, int ArraySize_, int NumberOfElements_, std::string Name) //Needed for arrays who's locations are only known at runtime.
    {
        Elements = ElementPointer_;
        ArraySize = ArraySize_;
        NumberOfElements = NumberOfElements_;
        _Name = Name;
        _Initialized = true;
    }
    T& operator[](int Index)
    {
        if(!_Initialized)
        {
            throw std::exception(fmt::format("Error! Tried accessing {} before it was initialized. You can use .Initialized() to check if this container is initialized before using it.", _Name).c_str());
        }
        return Elements[Index];
    }

    [[nodiscard]] int Size() const { return NumberOfElements; }
    [[nodiscard]] int Length() const { return NumberOfElements; }
    [[nodiscard]] int Capacity() const { return ArraySize; }
    [[nodiscard]] bool Initialized() const { return _Initialized; }
    [[nodiscard]] T* GetRawPointer() const { return Elements; };

private:
    T* Elements = nullptr;
    int ArraySize = 0;
    int NumberOfElements = 0;
    bool _Initialized = false;
    std::string _Name = "Default FixedArrayWrapper";
};