#include "primer.h"

Primer::Primer(uintmax_t lenMin, uintmax_t lenMax, uintmax_t tempMin,
               uintmax_t tempMax, long double contentMin, long double contentMax, bool start)
    :
      _lengthMin(lenMin),
      _lengthMax(lenMax),
      _tempMin(tempMin),
      _tempMax(tempMax),
      _contentMin(contentMin),
      _contentMax(contentMax),
      _validStart(start)
{
}

bool Primer::validate(std::string dna)
{
    this->_dna = dna;
    this->_dnaLength = dna.size();

    if (this->_dnaLength == 0)
        return false; // empty string??

    if (!this->_validateStart())
        return false;

    if (!this->_validateLength())
        return false;

    this->countBases();

    if (!this->_validateTemp())
        return false;

    if (!this->_validateContent())
        return false;

    return true;
}

bool Primer::_validateStart()
{
    return (this->_validStart) &&
            (this->_dna[0] == 'G') ||
            (this->_dna[0] == 'C');
}

bool Primer::_validateLength()
{
    return (this->_lengthMax > 0) &&
            (this->_dnaLength >= this->_lengthMin) &&
            (this->_dnaLength <= this->_lengthMax);
}

void Primer::countBases()
{
    this->_a = this->_c = this->_g = this->_t = 0;

    std::string::iterator dnaEnd = this->_dna.end();
    for (std::string::iterator it = this->_dna.begin(); it != dnaEnd; ++it)
    {
        switch (*it)
        {
            case 'A':
                ++this->_a;
                break;

            case 'C':
                ++this->_c;
                break;

            case 'G':
                ++this->_g;
                break;

            case 'T':
                ++this->_t;
                break;
        }
    }
}

bool Primer::_validateTemp()
{
    uintmax_t temp = (2 * (this->_a + this->_t)) +
                        (4 * (this->_g + this->_c));

    return (this->_tempMax > 0) &&
            (temp >= this->_tempMin) &&
            (temp <= this->_tempMax);

}

bool Primer::_validateContent()
{
    long double content = (this->_g + this->_c) / (this->_dnaLength * 1.0);

    return (this->_contentMax > 0.0) &&
            (content >= this->_contentMin) &&
            (content <= this->_contentMax);
}


