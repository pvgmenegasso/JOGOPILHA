/* 
 * File:   Jogador.h
 * Author: pvgmenegasso
 *  jogador
 * Created on May 21, 2015, 5:57 PM
 */

#ifndef JOGADOR_H
#define	JOGADOR_H

#include "Armas.h"
#include "Armaduras.h"
#include "pilha/pilha.h"
class Jogador {
public:
    void setVida(int vida)
    {
        this->Vida = vida ;
    }
    void setLvl(int lvl)
    {
        this->Lvl = lvl ;
    }
    Jogador()
    {
     
    this->Vida = 100 ;
    this->VidaMax = 100 ;
    this->Lvl = 1 ;
    this->Score = 0 ;
    this->Xp = 0 ;
    
   
    };
    void Mudavida(int modulo, bool pramais) ;
    void Mudalvl() ;
    void Mudaxp() ;
    int GetLvl() ;
    int GetVida() ;
private:
    int Vida ;
    int VidaMax;
    int Lvl ;
    int Score ;
    int Xp ;
};

int Jogador::GetVida()
{
    return this->Vida ;
}
void Jogador::Mudalvl()
{
    this->Lvl = Xp/4*Lvl ;
    if(this->Lvl>1)
    {
        this->VidaMax = 16*this->Lvl ;
    }
}
void Jogador::Mudavida(int modulo, bool pramais)
{
    if(pramais == true)
    {
        this->Vida += modulo ;
    }
    else
    {
        this->Vida -= modulo ;
    }
    
}
void Jogador::Mudaxp()
{
    this->Xp ++ ;
}
int Jogador::GetLvl()
{
    return this->Lvl ;
}
/*void Jogador::DestroiArma()
{
    pilha <Arma> auxiliar(3) ;
    while(Minhasarmas.Vazia() == false)
    {
        Arma aux ;
        Minhasarmas.Desempilha(aux) ;
        if(aux.GetDur() == 0)
        {
            
        }
        else
        {
            auxiliar.Empilha(aux) ;
        }
    }
    Minhasarmas = auxiliar ;
    
}
void Jogador::DestroiArmadura()
{
    pilha<Armadura> auxiliar(2) ;
    while(this->Minhasarmaduras.Vazia() == false)
    {
        Armadura aux ;
        Minhasarmaduras.Desempilha(aux) ;
        if(aux.GetDur() == 0)
        {
            
        }
        else
        {
            auxiliar.Empilha(aux) ;
        }
    }
    Minhasarmaduras = auxiliar ;
}
*/ 
#endif	/* JOGADOR_H */

