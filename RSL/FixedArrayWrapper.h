#pragma once

template<class T>
class FixedArrayWrapper
{
public:
    FixedArrayWrapper() = default;
    FixedArrayWrapper(T*& ElementPointer_, int ArraySize_, int NumberOfElements_) : Elements(ElementPointer_), ArraySize(ArraySize_), NumberOfElements(NumberOfElements_) { _Initialized = true; }
    void Init(T*& ElementPointer_, int ArraySize_, int NumberOfElements_) //Needed for arrays who's locations are only known at runtime.
    {
        Elements = ElementPointer_;
        ArraySize = ArraySize_;
        NumberOfElements = NumberOfElements_;
        _Initialized = true;
    }
    const T& operator[](int Index)
    {
        if(_Initialized)
        {
            return Elements[Index];
        }
        return {};
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
};