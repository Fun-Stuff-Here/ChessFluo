/*
* Définition des classes d'exeptions, Projet-INF1015
*\file		exeptions.hpp
*\author	Elizabeth Michaud 2073093, Nicolas Dépelteau 2083544
*\date		12 avril 2021
* Créé le	10 avril 2021
*/
#pragma once

#include <stdexcept>
#include "Piece.h"

namespace ChessModel
{

//cours log1410 Polytechnique
class NotImplemented : public std::logic_error
{
public:
    NotImplemented() : std::logic_error{ "Methode non implementee." } {}
};


class ImpossibleMove : public std::logic_error
{
public:
    ImpossibleMove() : std::logic_error{ "Move is not possible" } {}
};


    class Check : public std::domain_error
    {
    public:
        Check(std::shared_ptr<Piece>& piece, const std::string& color) : std::domain_error{ "Check on " + color + " King by" + piece->getColor() } {}
    };
}
