#ifndef PRIMER_H
#define PRIMER_H

#include <string>
#include <stdint.h>

#include <iostream>

class Primer
{
public:
    Primer(uintmax_t lenMin = 0, uintmax_t lenMax = 0,
           uintmax_t tempMin = 0, uintmax_t tempMax = 0,
           long double contentMin = 0.0, long double contentMax = 0.0,
           bool _validStart = true);

    bool validate(std::string dna);

    inline uintmax_t lengthMin() const { return this->_lengthMin; }
    inline uintmax_t lengthMax() const { return this->_lengthMax; }

protected:
    void countBases();

    bool _validateStart();
    bool _validateLength();
    bool _validateTemp();
    bool _validateContent();

private:
    std::string _dna;
    std::string::size_type _dnaLength;

    uintmax_t _a;
    uintmax_t _c;
    uintmax_t _t;
    uintmax_t _g;

    bool _validStart;

    uintmax_t _lengthMin;
    uintmax_t _lengthMax;

    uintmax_t _tempMin;
    uintmax_t _tempMax;

    long double _contentMin; // % of GC
    long double _contentMax;
};

#endif // PRIMER_H
