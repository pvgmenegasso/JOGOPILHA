/* 
 * File:   Armaduras.h
 * Author: pvgmenegasso
 *
 * Created on May 21, 2015, 6:09 PM
 */

#ifndef ARMADURA_H
#define	ARMADURA_H

class Armadura {
public:
    Armadura(const int Dur = 99,const int Tipo = 99,const int Protecao = 0, const std::string texturename = "vazio");

    int GetTipo() ;
    void TiraDur() ;
    int GetProtecao() ;
    int GetDur() ;
    std::string get_textura() ;
    void SetTipo(int tipo)
    {
        this->Tipo = tipo ;
    }
    void SetDur(int dur)
    {
        this->Dur = dur ;
    }
    void SetTextura(std::string textura)
    {
        this->texturename = textura ;
    }
    void SetProtecao(int protecao)
    {
        this->Protecao = protecao ;
    }
private:
    int Protecao ;
    int Tipo;
    int Dur ;
    std::string texturename ;
    

};
int Armadura::GetProtecao()
{
    return this->Protecao ;
}
void Armadura::TiraDur() 
{
    this->Dur -- ;
}
int Armadura::GetTipo()
{
    return this->Tipo ;
}
int Armadura::GetDur()
{
    return this->Dur ;
}
Armadura::Armadura(const int Dur,const int Tipo,const int Protecao, const std::string texturename)
{
    this->Dur = Dur ;
    this->Tipo = Tipo ;
    this->Protecao = Protecao ;
}

std::string Armadura::get_textura()
{
    return this->texturename ;
}
#endif	/* ARMADURAS_H */

