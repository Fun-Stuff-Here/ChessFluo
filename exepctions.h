#pragma once

#include <stdexcept>
//cours log1410 Polytechnique
class NotImplemented : public std::logic_error
{
public:
    NotImplemented() : std::logic_error{ "Methode non implementee." } {}
};

class impossibleMove : public std::logic_error
{
public:
    impossibleMove() : std::logic_error{ "Move is not possible" } {}
};