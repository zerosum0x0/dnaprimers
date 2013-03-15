#ifndef DNASEARCH_H
#define DNASEARCH_H

#include <algorithm>
#include "primer.h"

class DNASearch
{
public:
    DNASearch(Primer p, std::string dna);

    bool findPrimers(uintmax_t productMin,
                     std::string &primer1_5to3, uintmax_t &product1,
                     std::string &primer2_5to3, uintmax_t &product2);

protected:
    bool findPrimer(uintmax_t productMin, std::string dna,
                    std::string &primer, uintmax_t &product);

    std::string _complementDNA(std::string dna);

    // A <-> T, G <-> C
    inline char _basePair(const char c) { return ((c & 2) ? '\x8a' - c : '\x95' - c); }


private:
    std::string _dna;
    std::string::size_type _dnaLength;
    std::string _dnaComplement;

    Primer _primer;
};

#endif // DNASEARCH_H
