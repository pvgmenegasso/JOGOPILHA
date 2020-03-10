/* 
 * File:   pilha.h
 * Author: pvgmenegasso
 *
 * Created on May 21, 2015, 2:05 PM
 */

#ifndef PILHA_H
#define	PILHA_H
template <class T>
class pilha {
private:
    int NumeroElementos;
    int NumeroAtualElementos;
    T* Elementos ;
    
public:
    pilha(const int);
   ~pilha();
    bool Empilha(T Elemento) ;
    bool Desempilha(T& Elemento) ;
    bool Cheia();
    bool Vazia();


};
template <class T>
pilha<T>::pilha(const int n_elementos)
    {
        this->NumeroElementos = n_elementos ;
        this->NumeroAtualElementos = 0 ;
        this->Elementos = new T[n_elementos] ;
    }
template <class T>
pilha<T>::~pilha()
    {
        {
        delete[] Elementos ;
        }
    }
template <class T>
bool pilha<T>::Cheia()
{
    if(this->NumeroAtualElementos == NumeroElementos)
    {
        return true ;
    }
    else
    {
        return false ;
    }
}
template <class T>
bool pilha<T>::Desempilha(T& Elemento)
{
    if(this->NumeroAtualElementos == 0)
    {
        return false;
    }
    else
    {
        Elemento = Elementos[NumeroAtualElementos-1] ;
        NumeroAtualElementos --;
        return true ;
    }
}
template <class T>
bool pilha<T>::Empilha(T Elemento)
{
    if(   (this->NumeroAtualElementos) == this->NumeroElementos)
    {
        return false ;
    }
    else
    {
        this->Elementos[this->NumeroAtualElementos] = Elemento ;
        NumeroAtualElementos ++ ;
        return true ;
    }
}
template <class T>
bool pilha<T>::Vazia()
{
    if(this->NumeroAtualElementos == 0 )
    {
        return true ;
    }
    else
    {
        return false ;
    }
}
#endif	/* PILHA_H */

