/*
 * File:   Monstro.h
 * Author: pvgmenegasso
 *
 * Created on May 21, 2015, 7:07 PM
 */

#ifndef MONSTRO_H
#define	MONSTRO_H

#include "Armas.h"
#include "Jogador.h"
#include <string>
#include <time.h>

using namespace std ;


class Monstro {
public:
    Monstro(int Vida, int Ataque, int TipoDano, int Tipo, int Lvl, string texturename);
    string get_textura() ;
    void SetTextura(string textura) ;
    void SetVida(int vida) ;
    void SetAtaque(int atk) ;
    void SetTipoDano(int tipo) ;
    void SetLvl(int lvl) ;
    void SetTipo(int tipo) ;
    int GetTipo()
    {
        return this->Tipo ;
    }
    int GetVida()
    {
        return this->Vida ;
    }
    int GetLvl()
    {
        return this->Lvl ;
    }

   bool Combate(Arma& ArmaOponente, Armadura& ArmaduraOponente, Jogador& Atacante) ; // retorna se o monstro morreu no combate ou não
private:
    int Vida ;
    int Lvl ;
    int Ataque ;
    int TipoDano ;
    int Tipo ;

    string texturename ;

};
bool Monstro::Combate(Arma& ArmaOponente, Armadura& ArmaduraOponente, Jogador& Atacante)
{
    srand(time(NULL)) ;
    int Danotomado ;
    int Danocausado ;
    switch(ArmaOponente.GetTipo())
    {
            case 0: //Normal
                Danotomado = ArmaOponente.GetDano()*Atacante.GetLvl() ;
                break;
            case 1: //Fogo
                if(this->Tipo == 0)
                {
                    Danotomado = ArmaOponente.GetDano()*Atacante.GetLvl()*2*(rand()%8) ;
                    break ;
                }
                else
                    if(this->Tipo == 1)
                    {
                        Danotomado = ArmaOponente.GetDano()*Atacante.GetLvl()*0.75*(rand()%3) ;
                        break ;
                    }
                    else
                    {
                        Danotomado = ArmaOponente.GetDano()*Atacante.GetLvl()*(rand()%5) ;
                        break ;
                    }
            case 2: //Mágico
                if(this->Tipo == 2)
                {
                    Danotomado = ArmaOponente.GetDano()*Atacante.GetLvl()*2*(rand()%8) ;
                    break ;
                }
                else
                    if(this->Tipo == 0)
                    {
                        Danotomado = ArmaOponente.GetDano()*Atacante.GetLvl()*0.75*(rand()%3) ;
                        break ;
                    }
                    else
                    {
                        Danotomado = ArmaOponente.GetDano()*Atacante.GetLvl()*(rand()%5) ;
                        break ;
                    }

            case 3: //Sagrado
                if(this->Tipo == 1)
                {
                    Danotomado = ArmaOponente.GetDano()*Atacante.GetLvl()*2*(rand()%8) ;
                    break ;
                }
                else
                    if(this->Tipo == 2)
                    {
                        Danotomado = ArmaOponente.GetDano()*Atacante.GetLvl()*0.75*(rand()%3) ;
                        break ;
                    }
                    else
                    {
                        Danotomado = ArmaOponente.GetDano()*Atacante.GetLvl()*(rand()%5) ;
                        break ;
                    }
            case 99: //desarmado
            {
                Danotomado = Atacante.GetLvl()*rand()%5 ;
                break ;
            }

    }
    this->Vida = this->Vida - Danotomado ;
    ArmaOponente.TiraDur() ;
    if(this->Vida <= 0)
    {
        return true ;
    }
    else
    {


        if (this->TipoDano == ArmaduraOponente.GetTipo())
        {

           Danocausado = (this->Ataque*this->Lvl*(rand()%3))/(1+ArmaduraOponente.GetProtecao()/10) ;
        }
        else
        {
            if(ArmaduraOponente.GetTipo()== 99)
            {
                Danocausado = ((this->Ataque*this->Lvl*(rand()%5))/10) ;
            }
            else
            {

                Danocausado = (this->Ataque*this->Lvl*(rand()%5))/(1+ArmaduraOponente.GetProtecao()/10) ;
            }
        }
    }
    Atacante.Mudavida(Danocausado, false) ;
    ArmaduraOponente.TiraDur() ;
    return false ;

}
Monstro::Monstro(int Vida= 0, int Ataque=0, int TipoDano=0, int Tipo=0, int Lvl=0, string texturename = "zero")
{
    this->Vida = Vida ;
    this->Ataque = Ataque ;
    this->TipoDano = TipoDano ;
    this->Tipo = Tipo ;
    this->Lvl = Lvl ;

    this->texturename = texturename ;
}

string Monstro::get_textura()
{
    return this->texturename ;
}

void Monstro::SetTextura(string textura)
{
    this->texturename = textura ;
}
void Monstro::SetVida(int vida)
{
    this->Vida = vida ;
}
void Monstro::SetAtaque(int atk)
{
    this->Ataque = atk;
}
void Monstro::SetTipoDano(int tipo)
{
    this->TipoDano = tipo ;
}
void Monstro::SetLvl(int lvl)
{
    this->Lvl = lvl ;
}
void Monstro::SetTipo(int tipo)
{
    this->Tipo = tipo ;
}
#endif	/* MONSTRO_H */

