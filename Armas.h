/* 
 * File:   Armas.h
 * Author: pvgmenegasso
 *
 * Created on May 21, 2015, 6:09 PM
 */

#ifndef ARMA_H
#define	ARMA_H
#include <string>
class Arma {
public:
    Arma(const int Tipo, const int Dano, const int Dur, const std::string texturename);

    int GetTipo() ;
    int GetDano() ;
    void TiraDur() ;
    int GetDur() ;
    std::string get_textura() ;
    void SetTipo(const int tipo)
    {
        this->Tipo = tipo ;
    }
    void SetDano(const int dano)
    {
        this->Dano = dano ;
    }
    void SetDur(const int Dur)
    {
        this->Dur = Dur ;
    }
    void SetTextura(const std::string texturename)
    {
        this->texturename = texturename ;
    }
private:
    int Dano ;
    int Tipo ;
    int Dur ;
    std::string texturename ;
    
};
int Arma::GetTipo()
{
    return this->Tipo ;
}
int Arma::GetDano()
{
    return this->Dano ;
}
void Arma::TiraDur()
{
    this->Dur -- ;
}
int Arma::GetDur()
{
    return this->Dur ;
}
Arma::Arma(const int Tipo=99, const int Dano = 0,const int Dur = 99, const std::string texturename = "vazio")
{
    this->Tipo = Tipo;
    this->Dano = Dano ;
    this->Dur = Dur ;
    this->texturename = texturename ;
}
std::string Arma::get_textura()
{
    return this->texturename ;
}
#endif	/* ARMAS_H */

