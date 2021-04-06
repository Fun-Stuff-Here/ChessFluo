#pragma once

#include <stdexcept>
//cours log1410 Polytechnique
class NotImplemented : public std::logic_error
{
public:
    NotImplemented() : std::logic_error{ "Methode non implementee." } {}
};