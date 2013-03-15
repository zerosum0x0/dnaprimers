#include "dnasearch.h"

DNASearch::DNASearch(Primer p, std::string dna)
    :
      _primer(p)
{
    if (dna.length() > 0 && dna[0] == '>') // strip fasta file first line
    {
        std::string::size_type pos = dna.find_first_of('\n');
        dna.erase(0, pos + 1);
    }

    dna.erase(std::remove(dna.begin(), dna.end(), '\n'), dna.end());


    this->_dnaLength = dna.size();
    this->_dna = dna;
    this->_dnaComplement = this->_complementDNA(dna);
}

bool DNASearch::findPrimers(uintmax_t productMin,
                            std::string &primer1_5to3, uintmax_t &product1,
                            std::string &primer2_5to3, uintmax_t &product2)
{
    if (!this->findPrimer(productMin, this->_dna, primer1_5to3, product1))
        return false;

    std::reverse(primer1_5to3.begin(), primer1_5to3.end());

    if (!this->findPrimer(productMin, this->_dnaComplement, primer2_5to3, product2))
        return false;

    product2 = this->_dnaLength - primer2_5to3.size() - product2 - 1; // fix indice


    return true;
}


bool DNASearch::findPrimer(uintmax_t productMin, std::string dna, std::string &primer, uintmax_t &product)
{
    for (uintmax_t offset = productMin; offset < this->_dnaLength; ++offset)
    {
        for (uintmax_t size = this->_primer.lengthMin(); size <= this->_primer.lengthMax(); ++size)
        {
            std::string strand = dna.substr(offset, size);
            if (this->_primer.validate(strand))
            {
                primer = this->_complementDNA(strand);
                product = offset;
                return true;
            }
        }

    }
    return false;
}

std::string DNASearch::_complementDNA(std::string dna)
{
    std::string comp = "";
    std::string::iterator dnaEnd = dna.end();
    for (std::string::iterator it = dna.begin(); it != dnaEnd; ++it)
        comp += this->_basePair(*it);

    return comp;
}
