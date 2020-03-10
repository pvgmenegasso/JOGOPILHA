    /* 
 * File:   main.cpp
 * Author: pvgmenegasso
 *
 * Created on May 21, 2015, 2:04 PM
 */

#include <cstdlib>
#include <iostream>
#include "pilha/pilha.h"
#include "Jogador.h"
#include "Armaduras.h"
#include "Armas.h"
#include "Monstro.h"
#include <string>
#include <SFML/Graphics.hpp>
#include <sstream>
#include <time.h>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>

//<editor-fold desc="constantes"> 
#define atkhard 7 
#define atkmedium 4
#define atkeasy 1
#define vidahard  50
#define vidamedium 20
#define vidaeasy 5 
#define danoarmaeasy 10
#define danoarmamedium 6
#define danoarmahard 5
#define durarmaeasy 5
#define durarmamedium 3
#define durarmahard 2
#define protecaoarmaduramedium 10
#define protecaoarmadurahard 6
#define protecaoarmaduraeasy 20
//</editor-fold>
using namespace std;
//<editor-fold desc="cabeçalho funções">
void SetStats(Jogador p1,Monstro Monstroatual, Arma armas_jogador[], Armadura armaduras_jogador[], sf::Text &stats, sf::Text &vidamonstro, sf::Text &lvlmonstro, sf::Text cartas[]) ;
template <class tipo>
void embaralha(pilha<tipo>*cards, tipo carta[], int tamanhovetor) ;
template <class tipo>
void draw(pilha <tipo>cards, tipo &cartas) ;
 template <class tipo>
void Texturize(tipo elementoContemTextura, sf::RectangleShape &elementoRecebeTextura, sf::Texture &textura) ;
bool ClickOnElement(sf::RectangleShape shape, sf::RenderWindow &window) ;
bool ClickOnElement(sf::Sprite shape, sf::RenderWindow &window) ;
void popupaviso(string textoamostrar, sf::Font diskontented) ;
void popupaviso(string textoamostrar, sf::Font diskontented, sf::RenderWindow &window) ;
bool isHoveringOver(sf::Sprite& sprite, sf::Window& window) ;


void pollrightbutton(sf::Event event, sf::RenderWindow* window, int n_cartas, sf::RectangleShape cards[], int global_width, int global_height ) ;
//</editor-fold>



int main(int argc, char** argv) 
{
    //<editor-fold desc="declaracoes">
    Jogador p1 ;
    int last_arma = 10 ;
    int last_armadura = 10 ;
    int n_armas = 3 ;
    int n_armaduras = 2 ;
    srand(time(NULL)) ;
    int global_height = sf::VideoMode::getDesktopMode().height ;
    int global_width = sf::VideoMode::getDesktopMode().width ;
    int menuop = 0 ;
    sf::Music musicmenu ;
    sf::Music musicgame ;
    sf::Music hoversound ;
    sf::Music cardsound ;
    hoversound.openFromFile("./Music/hover.wav") ;
    cardsound.openFromFile("./Music/cardselect.wav") ;
    //cardsound.openFromFile("./Music/cardselect.wav") ;
    hoversound.setLoop(false) ;
    cardsound.setLoop(false) ;
    musicmenu.openFromFile("./Music/Devastation_and_Revenge.wav") ;
    musicgame.openFromFile("./Music/Big_Mojo.wav") ;
    musicmenu.setPitch(2); // increase the pitch
    musicmenu.setVolume(50); // reduce the volume
    musicmenu.setLoop(false); // make it loop
   
    
    int cardy = global_height*0.23 ;
    int cardx = global_width*0.08 ;
    
    //<editor-fold desc="declara as pilhas:">
    pilha <Arma> pilha_armas(10) ;
    pilha <Armadura> pilha_armaduras(10) ;
    pilha <Monstro> pilha_monstros(20) ;
    //</editor-fold>
    
    //<editor-fold desc="declara vetores de cartas do jogo">
    Armadura armaduras_jogador[2] ;
    Arma armas_jogador[3] ;
    Arma armas_jogo[10] ;
    Armadura armaduras_jogo[10];
    Monstro Monstros_jogo[20] ;
    Arma Armas_jogo[10] ;
    Monstro MonstroAtual ;
    //</editor-fold>
    
    
    
    // <editor-fold desc="GUI related stuff">
    //declara fonte
     sf::Font diskontented ;
     diskontented.loadFromFile("Diskontented.ttf") ;
     
     sf::Text stats ;
     sf::Text vidamonstro ;
     sf::Text lvlmonstro ;
     sf::Text cartas[5] ;
     stats.setFont(diskontented) ;
     vidamonstro.setFont(diskontented) ;
     lvlmonstro.setFont(diskontented) ;
     for(int i = 0; i< 5; i++)
     {
         cartas[i].setFont(diskontented) ;
     }
     
   
     //botao GO !
     sf::RectangleShape botao(sf::Vector2f(global_width*0.1, global_height*0.1)) ;
     botao.setPosition((float)global_width*0.8, (float)global_height*0.8);
     botao.setFillColor(sf::Color::Transparent) ;
     //Cards 
     sf::RectangleShape cards_armas[3];
     sf::RectangleShape cards_armaduras[2] ;
     
    
    for(int i = 0; i < 5 ; i++)
    {
        if(i <3)
        {
        cards_armas[i].setPosition(global_width*0.6-150*i*global_width/1366, global_height*0.69) ;
        cards_armas[i].setSize((sf::Vector2f(cardx, cardy))) ;
        }
        else
        {
         cards_armaduras[i-3].setPosition(global_width*0.55-160*i*global_width/1366, global_height*0.69) ;
         cards_armaduras[i-3].setSize((sf::Vector2f(cardx, cardy))) ;   
        }
    }
    
    //barra de status 
    //- Retangulo
    sf::RectangleShape statsBar(sf::Vector2f(global_width*0.2, global_height*0.06)) ;
    statsBar.setFillColor(sf::Color::White);
    statsBar.setPosition(global_width*0.389, global_height*0.01) ;
    
    
    
    
    //Próximo monstro:
    sf::RectangleShape NextCard(sf::Vector2f(global_width*0.24, global_height*0.6)) ;
    NextCard.setPosition(global_width*0.37, global_height*0.08) ;
    
    //texturas:
    sf::Texture textura_monstro ;  
    sf::Texture textura_cards[5] ;
    
    // texto
    stats.setPosition(statsBar.getPosition()) ;
    stats.setColor(sf::Color::Black) ;
    stats.setCharacterSize(30*(float)global_width/1366) ;
    stats.setFont(diskontented) ;
    vidamonstro.setCharacterSize(40);
    vidamonstro.setColor(sf::Color::Black) ;
    vidamonstro.setPosition(sf::Vector2f(NextCard.getPosition().x+NextCard.getSize().x*0.75, NextCard.getPosition().y+NextCard.getSize().y*0.85)) ;
    lvlmonstro.setCharacterSize(40) ;
    lvlmonstro.setColor(sf::Color::White) ;
    lvlmonstro.setPosition(sf::Vector2f(NextCard.getPosition().x+NextCard.getSize().x*0.78, NextCard.getPosition().y+NextCard.getSize().y*0.03)) ;
    for(int i = 0; i < 5; i ++)
    {
        cartas[i].setCharacterSize(16*(float)global_width/1366) ;
        cartas[i].setColor(sf::Color::Black) ;
        
    }
    
    sf::Sprite fundo ;
    sf::Texture texturafundo ;
    
    //</editor-fold>
    
    //</editor-fold>
    sf::Event event ;
    //<editor-fold desc="menu">
    bool justarted = true ;
    sf::RenderWindow menu(sf::VideoMode(global_width, global_height), "menu", sf::Style::Close) ;
    sf::Texture tjogar ;
    sf::Texture tconfigurar ;
    sf::Texture thelp ;
    sf::Sprite jogar;
    sf::Sprite configurar;
    sf::Sprite help;      
    jogar.setPosition(global_width*0.345, global_height*0.35) ;
    configurar.setPosition(global_width*0.314, global_height*0.5) ;
    help.setPosition(global_width*0.8, global_height*help.getLocalBounds().height/2) ;
    
    while(menu.isOpen())
    {
        //<editor-fold desc="comecou agr">
        if(justarted == true)
        {
            musicmenu.play() ;
            tjogar.loadFromFile("./Botoes/botao-jogar.png") ;
            tconfigurar.loadFromFile("./Botoes/botao-configurar.png") ;
            thelp.loadFromFile("./Botoes/botao-help.png") ;
            jogar.setTexture(tjogar) ;
            configurar.setTexture(tconfigurar) ;
            help.setTexture(thelp) ;
            justarted = false ;
        }
        //</editor-fold>
        
        //<editor-fold desc="hovers">
        if(isHoveringOver(jogar, menu))
        {
            hoversound.play() ;
            jogar.setColor(sf::Color::Red) ;
           
            
        }
        else
        {
            jogar.setColor(sf::Color::White) ;
        }
        if(isHoveringOver(help, menu))
        {
            help.setColor(sf::Color::Red) ;
            hoversound.play() ;
        }
        else
        {
            help.setColor(sf::Color::White) ;
            
        }
        if(isHoveringOver(configurar, menu))
        {
            configurar.setColor(sf::Color::Red) ;
            hoversound.play() ;
        }
        else
        {
            configurar.setColor(sf::Color::White) ;
            
        }
        //</editor-fold>
        
        //<editor-fold desc="loop">
        while(menu.pollEvent(event))
        {
            if(event.type == sf::Event::MouseButtonPressed)
            {
                if(ClickOnElement(jogar, menu))
                {
                    menu.close() ;
                    musicmenu.pause() ;
                }
                if(ClickOnElement(configurar, menu))
                {
                    sf::Window config(sf::VideoMode(global_width, global_height), "configuracoes") ;
                    while(config.isOpen())
                    {
                        sf::Event eventoconfig ;
                        while(config.pollEvent(eventoconfig))
                        {
                            if(eventoconfig.type == sf::Event::Closed)
                            {
                                config.close() ;
                            }
                        }
                    }
                }
                if(ClickOnElement(help, menu))
                {
                    sf::Texture texthelp ;
                    texthelp.loadFromFile("./Fundos/HELP.png") ;
                    fundo.setTexture(texthelp) ;
                    sf::RenderWindow helpw(sf::VideoMode(global_width, global_height), "help") ;
                    while(helpw.isOpen())
                    {
                        
                        
                        
                        sf::Event eventohelp ;
                        while(helpw.pollEvent(eventohelp))
                        {
                            if(eventohelp.type == sf::Event::Closed)
                            {
                                helpw.close() ;
                                fundo.setTexture(texturafundo) ;
                            }
                        }
                        helpw.clear() ;
                        helpw.draw(fundo) ;
                        helpw.display() ;
                    }
                }
            }
            
            //<editor-fold desc="fechar">
            if(event.type == sf::Event::Closed)
            {
                menu.close() ;
                musicmenu.pause() ;
                return 1 ;
            }
            //</editor-fold>
        }
        //</editor-fold>
        
        //<editor-fold desc="draws">
            texturafundo.loadFromFile("./Fundos/menu-fundo.png") ;
            fundo.setTexture(texturafundo) ;
            menu.clear() ;
            menu.draw(fundo) ;
            menu.draw(jogar) ;
            menu.draw(configurar) ;
            menu.draw(help) ;
            menu.display() ;
        //</editor-fold>
    }
    
    //</editor-fold>
    
    //<editor-fold desc="aplica a dificuldade selecionada">
    switch(menuop)
    {
        case 0:
            
            //<editor-fold desc="insere as armaduras no jogo">

            for(int i = 0; i<10; i++)
            {
                armaduras_jogo[i].SetDur(durarmaeasy+rand()%3) ;
                armaduras_jogo[i].SetProtecao(protecaoarmaduraeasy + rand()%4) ;
                ostringstream convert ;
                convert<<"./Armaduras/"<<i<<".png" ;
                armaduras_jogo[i].SetTextura(convert.str()) ;
                convert.clear() ;
                convert.str("") ;
                if(i<3)
                {
                    armaduras_jogo[i].SetTipo(2) ;
                }
                else
                {
                    if(i<7)
                    {
                        armaduras_jogo[i].SetTipo(1) ;
                    }
                    else
                    {
                        armaduras_jogo[i].SetTipo(0) ;
                    }
                }
            }
            embaralha<Armadura>(&pilha_armaduras, armaduras_jogo, 10) ;
            pilha_armaduras.Desempilha(armaduras_jogador[0]) ;
            pilha_armaduras.Desempilha(armaduras_jogador[1]) ;

            //</editor-fold>

            //<editor-fold desc="insere os monstros no jogo">

            //<editor-fold desc="insere os monstros no vetor monstros_jogo[]">
            for(int i = 0; i<20; i++)
            {
                Monstros_jogo[i].SetLvl(p1.GetLvl()+rand()%3) ;
                ostringstream convert ;
                convert<<"./Monstros/" <<i<<".png" ;
                Monstros_jogo[i].SetTextura(convert.str()) ;
                Monstros_jogo[i].SetVida(vidaeasy+rand()%20) ;
                Monstros_jogo[i].SetAtaque(atkeasy+rand()%5) ;

                if(i<7)
                {
                    Monstros_jogo[i].SetTipo(1) ;

                    if(i == 6)
                    {
                        Monstros_jogo[i].SetTipoDano(0) ;
                    }
                    else
                    {
                        if(i== 0 || i== 3)
                        {
                            Monstros_jogo[i].SetTipoDano(3) ;
                        }
                        else
                        {
                            Monstros_jogo[i].SetTipoDano(1) ;
                        }
                    }

                }
                else
                {
                if(i>=7 && i<14)
                {
                    Monstros_jogo[i].SetTipo(2);

                    if(i == 11)
                    {
                        Monstros_jogo[i].SetTipoDano(0) ;
                    }
                    else
                    {
                        if(i == 10)
                        {
                            Monstros_jogo[i].SetTipoDano(1) ;
                        }
                        else
                        {
                            Monstros_jogo[i].SetTipoDano(3) ;
                        }
                    }

                }
                else
                {
                    Monstros_jogo[i].SetTipo(0) ;

                    Monstros_jogo[i].SetTipoDano(3) ;
                }
                }
            }


            //<editor-fold desc="insere o vetor monstros_jogo[] na pilha de monstros

            embaralha<Monstro>(&pilha_monstros, Monstros_jogo, 20) ;
            //</editor-fold>

            pilha_monstros.Desempilha(MonstroAtual) ;

            //</editor-fold>

            //<editor-fold desc="insere as armas no jogo">

            //<editor-fold desc="insere as armas no vetor">
            for(int i = 0; i<10; i++)
            {
                Armas_jogo[i].SetDano(danoarmaeasy + rand()%5) ;
                Armas_jogo[i].SetDur(durarmaeasy + rand()%2) ;
                ostringstream convert ;
                convert<<"./Armas/"<<i+1<<".png" ;

                Armas_jogo[i].SetTextura(convert.str()) ;

                if(i<5)
                {
                    Armas_jogo[i].SetTipo(3) ;
                }
                else
                {
                    if(i<7)
                    {
                        Armas_jogo[i].SetTipo(1) ;
                    }
                    else
                    {
                        if(i<9)
                        {
                            Armas_jogo[i].SetTipo(2) ;
                        }
                        else
                        {
                            Armas_jogo[i].SetTipo(0) ;
                        }
                    }
                }
            }
            //</editor-fold>

            //<editor-fold desc="embaralha as armas na pilha">

            embaralha<Arma>(&pilha_armas, Armas_jogo, 10) ;

            //</editor-fold>

            //<editor-fold desc="saca as armas iniciais">
            pilha_armas.Desempilha(armas_jogador[0]) ;
            pilha_armas.Desempilha(armas_jogador[1]) ;
            pilha_armas.Desempilha(armas_jogador[2]) ;


            //</editor-fold>

            //</editor-fold>
            
            break ;
            
        case 1:
            
            //<editor-fold desc="insere as armaduras no jogo">

            for(int i = 0; i<10; i++)
            {
                armaduras_jogo[i].SetDur(durarmamedium+rand()%3) ;
                armaduras_jogo[i].SetProtecao(protecaoarmaduramedium + rand()%4) ;
                ostringstream convert ;
                convert<<"./Armaduras/"<<i<<".png" ;
                armaduras_jogo[i].SetTextura(convert.str()) ;
                convert.clear() ;
                convert.str("") ;
                if(i<3)
                {
                    armaduras_jogo[i].SetTipo(2) ;
                }
                else
                {
                    if(i<7)
                    {
                        armaduras_jogo[i].SetTipo(1) ;
                    }
                    else
                    {
                        armaduras_jogo[i].SetTipo(0) ;
                    }
                }
            }
            embaralha<Armadura>(&pilha_armaduras, armaduras_jogo, 10) ;
            pilha_armaduras.Desempilha(armaduras_jogador[0]) ;
            pilha_armaduras.Desempilha(armaduras_jogador[1]) ;

            //</editor-fold>

            //<editor-fold desc="insere os monstros no jogo">

            //<editor-fold desc="insere os monstros no vetor monstros_jogo[]">
            for(int i = 0; i<20; i++)
            {
                Monstros_jogo[i].SetLvl(p1.GetLvl()+rand()%3) ;
                ostringstream convert ;
                convert<<"./Monstros/" <<i<<".png" ;
                Monstros_jogo[i].SetTextura(convert.str()) ;
                Monstros_jogo[i].SetVida(vidamedium+rand()%20) ;
                Monstros_jogo[i].SetAtaque(atkmedium+rand()%5) ;

                if(i<7)
                {
                    Monstros_jogo[i].SetTipo(1) ;

                    if(i == 6)
                    {
                        Monstros_jogo[i].SetTipoDano(0) ;
                    }
                    else
                    {
                        if(i== 0 || i== 3)
                        {
                            Monstros_jogo[i].SetTipoDano(3) ;
                        }
                        else
                        {
                            Monstros_jogo[i].SetTipoDano(1) ;
                        }
                    }

                }
                else
                {
                if(i>=7 && i<14)
                {
                    Monstros_jogo[i].SetTipo(2);

                    if(i == 11)
                    {
                        Monstros_jogo[i].SetTipoDano(0) ;
                    }
                    else
                    {
                        if(i == 10)
                        {
                            Monstros_jogo[i].SetTipoDano(1) ;
                        }
                        else
                        {
                            Monstros_jogo[i].SetTipoDano(3) ;
                        }
                    }

                }
                else
                {
                    Monstros_jogo[i].SetTipo(0) ;

                    Monstros_jogo[i].SetTipoDano(3) ;
                }
                }
            }


            //<editor-fold desc="insere o vetor monstros_jogo[] na pilha de monstros

            embaralha<Monstro>(&pilha_monstros, Monstros_jogo, 20) ;
            //</editor-fold>

            pilha_monstros.Desempilha(MonstroAtual) ;

            //</editor-fold>

            //<editor-fold desc="insere as armas no jogo">

            //<editor-fold desc="insere as armas no vetor">
            for(int i = 0; i<10; i++)
            {
                Armas_jogo[i].SetDano(danoarmamedium + rand()%5) ;
                Armas_jogo[i].SetDur(durarmamedium + rand()%2) ;
                ostringstream convert ;
                convert<<"./Armas/"<<i+1<<".png" ;

                Armas_jogo[i].SetTextura(convert.str()) ;

                if(i<5)
                {
                    Armas_jogo[i].SetTipo(3) ;
                }
                else
                {
                    if(i<7)
                    {
                        Armas_jogo[i].SetTipo(1) ;
                    }
                    else
                    {
                        if(i<9)
                        {
                            Armas_jogo[i].SetTipo(2) ;
                        }
                        else
                        {
                            Armas_jogo[i].SetTipo(0) ;
                        }
                    }
                }
            }
            //</editor-fold>

            //<editor-fold desc="embaralha as armas na pilha">

            embaralha<Arma>(&pilha_armas, Armas_jogo, 10) ;

            //</editor-fold>

            //<editor-fold desc="saca as armas iniciais">
            pilha_armas.Desempilha(armas_jogador[0]) ;
            pilha_armas.Desempilha(armas_jogador[1]) ;
            pilha_armas.Desempilha(armas_jogador[2]) ;


            //</editor-fold>

            //</editor-fold>
            
            break ;
            
        case 2:
            
            //<editor-fold desc="insere as armaduras no jogo">

            for(int i = 0; i<10; i++)
            {
                armaduras_jogo[i].SetDur(durarmahard+rand()%3) ;
                armaduras_jogo[i].SetProtecao(protecaoarmadurahard + rand()%4) ;
                ostringstream convert ;
                convert<<"./Armaduras/"<<i<<".png" ;
                armaduras_jogo[i].SetTextura(convert.str()) ;
                convert.clear() ;
                convert.str("") ;
                if(i<3)
                {
                    armaduras_jogo[i].SetTipo(2) ;
                }
                else
                {
                    if(i<7)
                    {
                        armaduras_jogo[i].SetTipo(1) ;
                    }
                    else
                    {
                        armaduras_jogo[i].SetTipo(0) ;
                    }
                }
            }
            embaralha<Armadura>(&pilha_armaduras, armaduras_jogo, 10) ;
            pilha_armaduras.Desempilha(armaduras_jogador[0]) ;
            pilha_armaduras.Desempilha(armaduras_jogador[1]) ;

            //</editor-fold>

            //<editor-fold desc="insere os monstros no jogo">

            //<editor-fold desc="insere os monstros no vetor monstros_jogo[]">
            for(int i = 0; i<20; i++)
            {
                Monstros_jogo[i].SetLvl(p1.GetLvl()+rand()%3) ;
                ostringstream convert ;
                convert<<"./Monstros/" <<i<<".png" ;
                Monstros_jogo[i].SetTextura(convert.str()) ;
                Monstros_jogo[i].SetVida(vidahard+rand()%20) ;
                Monstros_jogo[i].SetAtaque(atkhard+rand()%5) ;

                if(i<7)
                {
                    Monstros_jogo[i].SetTipo(1) ;

                    if(i == 6)
                    {
                        Monstros_jogo[i].SetTipoDano(0) ;
                    }
                    else
                    {
                        if(i== 0 || i== 3)
                        {
                            Monstros_jogo[i].SetTipoDano(3) ;
                        }
                        else
                        {
                            Monstros_jogo[i].SetTipoDano(1) ;
                        }
                    }

                }
                else
                {
                if(i>=7 && i<14)
                {
                    Monstros_jogo[i].SetTipo(2);

                    if(i == 11)
                    {
                        Monstros_jogo[i].SetTipoDano(0) ;
                    }
                    else
                    {
                        if(i == 10)
                        {
                            Monstros_jogo[i].SetTipoDano(1) ;
                        }
                        else
                        {
                            Monstros_jogo[i].SetTipoDano(3) ;
                        }
                    }

                }
                else
                {
                    Monstros_jogo[i].SetTipo(0) ;

                    Monstros_jogo[i].SetTipoDano(3) ;
                }
                }
            }


            //<editor-fold desc="insere o vetor monstros_jogo[] na pilha de monstros

            embaralha<Monstro>(&pilha_monstros, Monstros_jogo, 20) ;
            //</editor-fold>

            pilha_monstros.Desempilha(MonstroAtual) ;

            //</editor-fold>

            //<editor-fold desc="insere as armas no jogo">

            //<editor-fold desc="insere as armas no vetor">
            for(int i = 0; i<10; i++)
            {
                Armas_jogo[i].SetDano(danoarmahard+ rand()%5) ;
                Armas_jogo[i].SetDur(durarmahard + rand()%2) ;
                ostringstream convert ;
                convert<<"./Armas/"<<i+1<<".png" ;

                Armas_jogo[i].SetTextura(convert.str()) ;

                if(i<5)
                {
                    Armas_jogo[i].SetTipo(3) ;
                }
                else
                {
                    if(i<7)
                    {
                        Armas_jogo[i].SetTipo(1) ;
                    }
                    else
                    {
                        if(i<9)
                        {
                            Armas_jogo[i].SetTipo(2) ;
                        }
                        else
                        {
                            Armas_jogo[i].SetTipo(0) ;
                        }
                    }
                }
            }
            //</editor-fold>

            //<editor-fold desc="embaralha as armas na pilha">

            embaralha<Arma>(&pilha_armas, Armas_jogo, 10) ;

            //</editor-fold>

            //<editor-fold desc="saca as armas iniciais">
            pilha_armas.Desempilha(armas_jogador[0]) ;
            pilha_armas.Desempilha(armas_jogador[1]) ;
            pilha_armas.Desempilha(armas_jogador[2]) ;


            //</editor-fold>

            //</editor-fold>
            
            break ;
    }
    //</editor-fold>
    musicgame.play() ;
    musicgame.setLoop(true) ;
    //<editor-fold desc="game loop">
  
    
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode(global_width, global_height), "game", sf::Style::Close);
    texturafundo.loadFromFile("./Fundos/fundo.png") ;
    fundo.setTexture(texturafundo) ;
    
    fundo.setScale(sf::Vector2f((float)global_width/1366, global_height/768));
    cout<<global_width/1366<<endl ;
    cout<<global_width ;
    fundo.setPosition(0, -65*global_height/768) ;
    window.setFramerateLimit(100) ;
    while(window.isOpen())
    {
        //<editor-fold desc="enquanto jogaor está vivo">
        while(p1.GetVida() > 0)
        {
           //<editor-fold desc="inicializa barra de status, texturiza as cartas">
            for(int i = 0; i < 5; i ++)
           {
            cartas[i].setCharacterSize(15*(float)global_width/1366) ;
            cartas[i].setColor(sf::Color::Black) ;
            if(i < 3)
            {
                cartas[i].setPosition(sf::Vector2f(cards_armas[i].getPosition().x +cards_armas[i].getSize().x*0.46, cards_armas[i].getPosition().y+cards_armas[i].getSize().y*0.86)) ;
            }
            else
            {
                cartas[i].setPosition(sf::Vector2f(cards_armaduras[i-3].getPosition().x +cards_armaduras[i-3].getSize().x*0.46, cards_armaduras[i-3].getPosition().y+cards_armaduras[i-3].getSize().y*0.86)) ;
            }
        
           }
           SetStats(p1, MonstroAtual, armas_jogador, armaduras_jogador, stats, vidamonstro, lvlmonstro, cartas) ;
           Texturize <Monstro> (MonstroAtual, NextCard, textura_monstro) ;
           
           //<editor-fold desc="texturizando as imagens de armas e armaduras">
           for(int h = 0; h<2; h++)
           {
               if(armaduras_jogador[h].GetTipo() != 99)
               {
               Texturize <Armadura> (armaduras_jogador[h], cards_armaduras[h], textura_cards[h]) ;
               }
           }
           
           for(int j = 0; j<3; j++)
           {
              
               if(armas_jogador[j].GetTipo() != 99)
               {
               Texturize <Arma> (armas_jogador[j], cards_armas[j], textura_cards[j+2]) ;
               
               }
           }
           //</editor-fold>

          
           //</editor-fold>
        
            //<editor-fold desc="eventos">
           
        while (window.pollEvent(event))
        {
            if(event.type == sf::Event::MouseButtonPressed)
            {
            if( event.mouseButton.button == sf::Mouse::Left)
            
            {
                //<editor-fold desc="selecionar cartas">
                for(int i = 0; i < 3; i++)
                {
                    if(ClickOnElement(cards_armas[i], window) == true && armas_jogador[i].GetTipo() != 99  )
                    {
                        cardsound.play() ;
                        if(last_arma == 10)
                        {
                            cards_armas[i].setOutlineColor(sf::Color::Cyan) ;
                            cards_armas[i].setOutlineThickness(2) ;
                            last_arma = i ;
                        }
                        if(last_arma <10)
                        {
                            cards_armas[last_arma].setOutlineThickness(0);
                            cards_armas[i].setOutlineColor(sf::Color::Cyan) ;
                            cards_armas[i].setOutlineThickness(2) ;
                            last_arma = i ;
                        }
                        
                    }
                    
                    

                }
                
                for(int i = 0 ; i<2; i++)
                {
                    cardsound.play() ;
                        if(ClickOnElement(cards_armaduras[i], window) == true && armaduras_jogador[i].GetTipo() != 99)
                        {
                         if(last_armadura == 10)
                        {
                            cards_armaduras[i].setOutlineColor(sf::Color::Cyan) ;
                            cards_armaduras[i].setOutlineThickness(2) ;
                            last_armadura = i ;
                        }
                        if(last_armadura <10)
                        {
                            cards_armaduras[last_armadura].setOutlineThickness(0);
                            cards_armaduras[i].setOutlineColor(sf::Color::Cyan) ;
                            cards_armaduras[i].setOutlineThickness(2) ;
                            last_armadura = i ;
                        }   
                        }
                        
                        
                }
                if(sf::Mouse::isButtonPressed(sf::Mouse::Left) == true)
                    {
                    for(int i = 0; i<3 ; i++)
                    {
                            cards_armas[i].setPosition(global_width*0.6-150*i*global_width/1366, global_height*0.69) ;
                            cards_armas[i].setSize((sf::Vector2f(cardx, cardy))) ;
                    }
                    for(int i = 0; i<2; i++)
                        
                            {
                                cards_armaduras[i].setPosition(global_width*0.55-160*(i+3)*global_width/1366, global_height*0.69) ;
                                cards_armaduras[i].setSize((sf::Vector2f(cardx, cardy))) ;  
                            }
                            
                    }
                //</editor-fold>
                
                //<editor-fold desc="combate">
                
                if(ClickOnElement(botao, window) == true)
                {
                    
                    if(last_arma  == 10 || last_armadura == 10)
                    {
                        sf::RenderWindow popup(sf::VideoMode(300, 200), "erro, escolha uma arma ou armadura para começar") ;
                        
                        while(popup.isOpen() == true)
                        {
                            sf::Event eventopopup ;
                            popup.clear() ;
                            popup.display();
                            while (popup.pollEvent(eventopopup))
                            {
                                if(eventopopup.type == sf::Event::Closed)
                                    {
                                        popup.close() ;
                                        break ;
                                    }
                            }
                            
                        }
                    }
                    else
                    {
                        int auxiliarvida;
                        auxiliarvida = MonstroAtual.GetVida() ;
                        //<editor-fold desc="caso matou o monstro">
                        if(MonstroAtual.Combate(armas_jogador[last_arma], armaduras_jogador[last_armadura], p1) == true)
                        {
                            
                            
                            popupaviso("Voce matou o monstro", diskontented, window) ;
                            //<editor-fold desc="matou os monstros, ganhou o jogo">
                            if(pilha_monstros.Vazia() == true) 
                            {
                                //ganhou o jogo
                                popupaviso("Parabéns, voce ganhou o jogo, deseja recomeçar ? Y/N", diskontented, window) ;
                                char entrada ;
                                cin>>entrada ;
                                if(entrada == 'y')
                                {
                                    p1.setVida(100) ;
                                    p1.setLvl(p1.GetLvl()+1) ;
                                    //<editor-fold desc="aplica a dificuldade selecionada">
    switch(menuop)
    {
        case 0:
            
            //<editor-fold desc="insere as armaduras no jogo">

            for(int i = 0; i<10; i++)
            {
                armaduras_jogo[i].SetDur(durarmaeasy+rand()%3) ;
                armaduras_jogo[i].SetProtecao(protecaoarmaduraeasy + rand()%4) ;
                ostringstream convert ;
                convert<<"./Armaduras/"<<i<<".png" ;
                armaduras_jogo[i].SetTextura(convert.str()) ;
                convert.clear() ;
                convert.str("") ;
                if(i<3)
                {
                    armaduras_jogo[i].SetTipo(2) ;
                }
                else
                {
                    if(i<7)
                    {
                        armaduras_jogo[i].SetTipo(1) ;
                    }
                    else
                    {
                        armaduras_jogo[i].SetTipo(0) ;
                    }
                }
            }
            embaralha<Armadura>(&pilha_armaduras, armaduras_jogo, 10) ;
            pilha_armaduras.Desempilha(armaduras_jogador[0]) ;
            pilha_armaduras.Desempilha(armaduras_jogador[1]) ;

            //</editor-fold>

            //<editor-fold desc="insere os monstros no jogo">

            //<editor-fold desc="insere os monstros no vetor monstros_jogo[]">
            for(int i = 0; i<20; i++)
            {
                Monstros_jogo[i].SetLvl(p1.GetLvl()+rand()%3) ;
                ostringstream convert ;
                convert<<"./Monstros/" <<i<<".png" ;
                Monstros_jogo[i].SetTextura(convert.str()) ;
                Monstros_jogo[i].SetVida(vidaeasy+rand()%20) ;
                Monstros_jogo[i].SetAtaque(atkeasy+rand()%5) ;

                if(i<7)
                {
                    Monstros_jogo[i].SetTipo(1) ;

                    if(i == 6)
                    {
                        Monstros_jogo[i].SetTipoDano(0) ;
                    }
                    else
                    {
                        if(i== 0 || i== 3)
                        {
                            Monstros_jogo[i].SetTipoDano(3) ;
                        }
                        else
                        {
                            Monstros_jogo[i].SetTipoDano(1) ;
                        }
                    }

                }
                else
                {
                if(i>=7 && i<14)
                {
                    Monstros_jogo[i].SetTipo(2);

                    if(i == 11)
                    {
                        Monstros_jogo[i].SetTipoDano(0) ;
                    }
                    else
                    {
                        if(i == 10)
                        {
                            Monstros_jogo[i].SetTipoDano(1) ;
                        }
                        else
                        {
                            Monstros_jogo[i].SetTipoDano(3) ;
                        }
                    }

                }
                else
                {
                    Monstros_jogo[i].SetTipo(0) ;

                    Monstros_jogo[i].SetTipoDano(3) ;
                }
                }
            }


            //<editor-fold desc="insere o vetor monstros_jogo[] na pilha de monstros

            embaralha<Monstro>(&pilha_monstros, Monstros_jogo, 20) ;
            //</editor-fold>

            pilha_monstros.Desempilha(MonstroAtual) ;

            //</editor-fold>

            //<editor-fold desc="insere as armas no jogo">

            //<editor-fold desc="insere as armas no vetor">
            for(int i = 0; i<10; i++)
            {
                Armas_jogo[i].SetDano(danoarmaeasy + rand()%5) ;
                Armas_jogo[i].SetDur(durarmaeasy + rand()%2) ;
                ostringstream convert ;
                convert<<"./Armas/"<<i+1<<".png" ;

                Armas_jogo[i].SetTextura(convert.str()) ;

                if(i<5)
                {
                    Armas_jogo[i].SetTipo(3) ;
                }
                else
                {
                    if(i<7)
                    {
                        Armas_jogo[i].SetTipo(1) ;
                    }
                    else
                    {
                        if(i<9)
                        {
                            Armas_jogo[i].SetTipo(2) ;
                        }
                        else
                        {
                            Armas_jogo[i].SetTipo(0) ;
                        }
                    }
                }
            }
            //</editor-fold>

            //<editor-fold desc="embaralha as armas na pilha">

            embaralha<Arma>(&pilha_armas, Armas_jogo, 10) ;

            //</editor-fold>

            //<editor-fold desc="saca as armas iniciais">
            pilha_armas.Desempilha(armas_jogador[0]) ;
            pilha_armas.Desempilha(armas_jogador[1]) ;
            pilha_armas.Desempilha(armas_jogador[2]) ;


            //</editor-fold>

            //</editor-fold>
            
            break ;
            
        case 1:
            
            //<editor-fold desc="insere as armaduras no jogo">

            for(int i = 0; i<10; i++)
            {
                armaduras_jogo[i].SetDur(durarmamedium+rand()%3) ;
                armaduras_jogo[i].SetProtecao(protecaoarmaduramedium + rand()%4) ;
                ostringstream convert ;
                convert<<"./Armaduras/"<<i<<".png" ;
                armaduras_jogo[i].SetTextura(convert.str()) ;
                convert.clear() ;
                convert.str("") ;
                if(i<3)
                {
                    armaduras_jogo[i].SetTipo(2) ;
                }
                else
                {
                    if(i<7)
                    {
                        armaduras_jogo[i].SetTipo(1) ;
                    }
                    else
                    {
                        armaduras_jogo[i].SetTipo(0) ;
                    }
                }
            }
            embaralha<Armadura>(&pilha_armaduras, armaduras_jogo, 10) ;
            pilha_armaduras.Desempilha(armaduras_jogador[0]) ;
            pilha_armaduras.Desempilha(armaduras_jogador[1]) ;

            //</editor-fold>

            //<editor-fold desc="insere os monstros no jogo">

            //<editor-fold desc="insere os monstros no vetor monstros_jogo[]">
            for(int i = 0; i<20; i++)
            {
                Monstros_jogo[i].SetLvl(p1.GetLvl()+rand()%3) ;
                ostringstream convert ;
                convert<<"./Monstros/" <<i<<".png" ;
                Monstros_jogo[i].SetTextura(convert.str()) ;
                Monstros_jogo[i].SetVida(vidamedium+rand()%20) ;
                Monstros_jogo[i].SetAtaque(atkmedium+rand()%5) ;

                if(i<7)
                {
                    Monstros_jogo[i].SetTipo(1) ;

                    if(i == 6)
                    {
                        Monstros_jogo[i].SetTipoDano(0) ;
                    }
                    else
                    {
                        if(i== 0 || i== 3)
                        {
                            Monstros_jogo[i].SetTipoDano(3) ;
                        }
                        else
                        {
                            Monstros_jogo[i].SetTipoDano(1) ;
                        }
                    }

                }
                else
                {
                if(i>=7 && i<14)
                {
                    Monstros_jogo[i].SetTipo(2);

                    if(i == 11)
                    {
                        Monstros_jogo[i].SetTipoDano(0) ;
                    }
                    else
                    {
                        if(i == 10)
                        {
                            Monstros_jogo[i].SetTipoDano(1) ;
                        }
                        else
                        {
                            Monstros_jogo[i].SetTipoDano(3) ;
                        }
                    }

                }
                else
                {
                    Monstros_jogo[i].SetTipo(0) ;

                    Monstros_jogo[i].SetTipoDano(3) ;
                }
                }
            }


            //<editor-fold desc="insere o vetor monstros_jogo[] na pilha de monstros

            embaralha<Monstro>(&pilha_monstros, Monstros_jogo, 20) ;
            //</editor-fold>

            pilha_monstros.Desempilha(MonstroAtual) ;

            //</editor-fold>

            //<editor-fold desc="insere as armas no jogo">

            //<editor-fold desc="insere as armas no vetor">
            for(int i = 0; i<10; i++)
            {
                Armas_jogo[i].SetDano(danoarmamedium + rand()%5) ;
                Armas_jogo[i].SetDur(durarmamedium + rand()%2) ;
                ostringstream convert ;
                convert<<"./Armas/"<<i+1<<".png" ;

                Armas_jogo[i].SetTextura(convert.str()) ;

                if(i<5)
                {
                    Armas_jogo[i].SetTipo(3) ;
                }
                else
                {
                    if(i<7)
                    {
                        Armas_jogo[i].SetTipo(1) ;
                    }
                    else
                    {
                        if(i<9)
                        {
                            Armas_jogo[i].SetTipo(2) ;
                        }
                        else
                        {
                            Armas_jogo[i].SetTipo(0) ;
                        }
                    }
                }
            }
            //</editor-fold>

            //<editor-fold desc="embaralha as armas na pilha">

            embaralha<Arma>(&pilha_armas, Armas_jogo, 10) ;

            //</editor-fold>

            //<editor-fold desc="saca as armas iniciais">
            pilha_armas.Desempilha(armas_jogador[0]) ;
            pilha_armas.Desempilha(armas_jogador[1]) ;
            pilha_armas.Desempilha(armas_jogador[2]) ;


            //</editor-fold>

            //</editor-fold>
            
            break ;
            
        case 2:
            
            //<editor-fold desc="insere as armaduras no jogo">

            for(int i = 0; i<10; i++)
            {
                armaduras_jogo[i].SetDur(durarmahard+rand()%3) ;
                armaduras_jogo[i].SetProtecao(protecaoarmadurahard + rand()%4) ;
                ostringstream convert ;
                convert<<"./Armaduras/"<<i<<".png" ;
                armaduras_jogo[i].SetTextura(convert.str()) ;
                convert.clear() ;
                convert.str("") ;
                if(i<3)
                {
                    armaduras_jogo[i].SetTipo(2) ;
                }
                else
                {
                    if(i<7)
                    {
                        armaduras_jogo[i].SetTipo(1) ;
                    }
                    else
                    {
                        armaduras_jogo[i].SetTipo(0) ;
                    }
                }
            }
            embaralha<Armadura>(&pilha_armaduras, armaduras_jogo, 10) ;
            pilha_armaduras.Desempilha(armaduras_jogador[0]) ;
            pilha_armaduras.Desempilha(armaduras_jogador[1]) ;

            //</editor-fold>

            //<editor-fold desc="insere os monstros no jogo">

            //<editor-fold desc="insere os monstros no vetor monstros_jogo[]">
            for(int i = 0; i<20; i++)
            {
                Monstros_jogo[i].SetLvl(p1.GetLvl()+rand()%3) ;
                ostringstream convert ;
                convert<<"./Monstros/" <<i<<".png" ;
                Monstros_jogo[i].SetTextura(convert.str()) ;
                Monstros_jogo[i].SetVida(vidahard+rand()%20) ;
                Monstros_jogo[i].SetAtaque(atkhard+rand()%5) ;

                if(i<7)
                {
                    Monstros_jogo[i].SetTipo(1) ;

                    if(i == 6)
                    {
                        Monstros_jogo[i].SetTipoDano(0) ;
                    }
                    else
                    {
                        if(i== 0 || i== 3)
                        {
                            Monstros_jogo[i].SetTipoDano(3) ;
                        }
                        else
                        {
                            Monstros_jogo[i].SetTipoDano(1) ;
                        }
                    }

                }
                else
                {
                if(i>=7 && i<14)
                {
                    Monstros_jogo[i].SetTipo(2);

                    if(i == 11)
                    {
                        Monstros_jogo[i].SetTipoDano(0) ;
                    }
                    else
                    {
                        if(i == 10)
                        {
                            Monstros_jogo[i].SetTipoDano(1) ;
                        }
                        else
                        {
                            Monstros_jogo[i].SetTipoDano(3) ;
                        }
                    }

                }
                else
                {
                    Monstros_jogo[i].SetTipo(0) ;

                    Monstros_jogo[i].SetTipoDano(3) ;
                }
                }
            }


            //<editor-fold desc="insere o vetor monstros_jogo[] na pilha de monstros

            embaralha<Monstro>(&pilha_monstros, Monstros_jogo, 20) ;
            //</editor-fold>

            pilha_monstros.Desempilha(MonstroAtual) ;

            //</editor-fold>

            //<editor-fold desc="insere as armas no jogo">

            //<editor-fold desc="insere as armas no vetor">
            for(int i = 0; i<10; i++)
            {
                Armas_jogo[i].SetDano(danoarmahard+ rand()%5) ;
                Armas_jogo[i].SetDur(durarmahard + rand()%2) ;
                ostringstream convert ;
                convert<<"./Armas/"<<i+1<<".png" ;

                Armas_jogo[i].SetTextura(convert.str()) ;

                if(i<5)
                {
                    Armas_jogo[i].SetTipo(3) ;
                }
                else
                {
                    if(i<7)
                    {
                        Armas_jogo[i].SetTipo(1) ;
                    }
                    else
                    {
                        if(i<9)
                        {
                            Armas_jogo[i].SetTipo(2) ;
                        }
                        else
                        {
                            Armas_jogo[i].SetTipo(0) ;
                        }
                    }
                }
            }
            //</editor-fold>

            //<editor-fold desc="embaralha as armas na pilha">

            embaralha<Arma>(&pilha_armas, Armas_jogo, 10) ;

            //</editor-fold>

            //<editor-fold desc="saca as armas iniciais">
            pilha_armas.Desempilha(armas_jogador[0]) ;
            pilha_armas.Desempilha(armas_jogador[1]) ;
            pilha_armas.Desempilha(armas_jogador[2]) ;


            //</editor-fold>

            //</editor-fold>
            
            break ;
    }
    //</editor-fold>
                                }
                                else
                                {
                                    window.close() ;
                                    return 0 ;
                                }
                                
                            }
                            //</editor-fold>
                            else
                            {
                                   //<editor-fold desc="50%chance n ganhar arma">
                                    if(rand()%10 <= 6)
                                    {
                                        pilha_monstros.Desempilha(MonstroAtual) ;
                                    }
                                    //</editor-fold>
                                    else
                                    {
                                    
                                           
                                            if(rand()%10 < 6 )
                                            {
                                                
                                            if(n_armas < 3 && n_armaduras == 2)
                                            {
                                                //voce ganhou uma arma
                                                popupaviso("voce ganhou uma arma !", diskontented, window) ;
                                                int n_armas_at = n_armas ;
                                                for(int i=0; i<3; i++)
                                                {
                                                    if(n_armas_at == n_armas)
                                                    {
                                                    if(armas_jogador[i].GetTipo() == 99)
                                                    {
                                                        if(pilha_armas.Vazia() == false)
                                                        {
                                                            pilha_armas.Desempilha(armas_jogador[i]) ;
                                                            n_armas ++ ;
                                                        }
                                                        else
                                                        {
                                                            popupaviso("acabaram as armas", diskontented, window) ;
                                                        }
                                                    }
                                                    }
                                                }
                                                
                                                pilha_monstros.Desempilha(MonstroAtual) ;
                                            }
                                            else
                                            if(n_armaduras<2 && n_armas == 3)
                                            {
                                                //voce ganhou uma armadura
                                                popupaviso("voce ganhou uma armadura !", diskontented, window) ;
                                                int n_armaduras_at = n_armaduras ;
                                                for(int i=0; i<2; i++)
                                                {
                                                    if(n_armaduras_at == n_armaduras)
                                                    {
                                                    if(armaduras_jogador[i].GetTipo() == 99)
                                                    {
                                                        if(pilha_armaduras.Vazia() == false)
                                                        {
                                                            pilha_armaduras.Desempilha(armaduras_jogador[i]) ;
                                                            n_armaduras ++ ;
                                                        }
                                                        else
                                                        {
                                                            popupaviso("acabaram as armaduras :/", diskontented, window) ;
                                                        }
                                                    }
                                                    }
                                                }
                                                pilha_monstros.Desempilha(MonstroAtual) ;
                                            }
                                            else
                                            {
                                                if(n_armas < 3 && n_armaduras < 2)
                                                {
                                                //voce ganhou uma arma ou armadura aleatórea
                                                if(rand()%100 > 49)
                                                {
                                                    //voce ganhou arma
                                                    popupaviso("voce ganhou uma arma", diskontented, window) ;
                                                    int n_armas_at = n_armas ;
                                                for(int i=0; i<3; i++)
                                                {
                                                    if(n_armas_at == n_armas)
                                                    {
                                                    if(armas_jogador[i].GetTipo() == 99)
                                                    {
                                                        if(pilha_armas.Vazia() == false)
                                                        {
                                                            pilha_armas.Desempilha(armas_jogador[i]) ;
                                                            n_armas ++ ;
                                                        }
                                                        else
                                                        {
                                                            popupaviso("acabaram as armas", diskontented, window) ;
                                                        }
                                                    }
                                                    }
                                                }
                                                     pilha_monstros.Desempilha(MonstroAtual) ;
                                                     
                                                }
                                                else
                                                {
                                                    //voce ganhou armadura
                                                     pilha_monstros.Desempilha(MonstroAtual) ;
                                                     int n_armaduras_at = n_armaduras ;
                                                for(int i=0; i<2; i++)
                                                {
                                                    if(n_armaduras_at == n_armaduras)
                                                    {
                                                    if(armaduras_jogador[i].GetTipo() == 99)
                                                    {
                                                        if(pilha_armaduras.Vazia() == false)
                                                        {
                                                            pilha_armaduras.Desempilha(armaduras_jogador[i]) ;
                                                            n_armaduras ++ ;
                                                        }
                                                        else
                                                        {
                                                            popupaviso("acabaram as armaduras :/", diskontented, window) ;
                                                        }
                                                    }
                                                    }
                                                }
                                                }
                                                }
                                                pilha_monstros.Desempilha(MonstroAtual) ;
                                            }
                                            }
                                            else
                                            {
                                                //voce ganhou vida aleatórea
                                                popupaviso("voce ganhou vida aleatoria !", diskontented, window) ;
                                                p1.Mudavida(rand()%30*p1.GetLvl(), true) ;
                                                pilha_monstros.Desempilha(MonstroAtual) ;
                                              }
                                        
                                }
                            }
                        
                        }
                        else
                        {
                            ostringstream conversorvida ;
                            conversorvida<<"-"<<auxiliarvida-MonstroAtual.GetVida() ;
                            
                            popupaviso(conversorvida.str(), diskontented, window) ;
                            conversorvida.clear() ;
                            conversorvida.str("") ;
                        }
                        //</editor-fold>
                        for(int i = 0; i< 20; i++)
                        {
                        
                        }
                        
                    }   
                
                }
            
                
                if(last_armadura != 10)
                {    
                if(armaduras_jogador[last_armadura].GetDur() <= 0)
                {
                    Armadura nulo ;
                    armaduras_jogador[last_armadura] = nulo ;
                    n_armaduras -- ;
                }
                }
                if(last_arma != 10)
                {
                if(armas_jogador[last_arma].GetDur() <= 0)
                {
                    Arma nula ;
                    armas_jogador[last_arma] = nula ;
                    n_armas -- ;
                }
                }
                for(int i = 0; i< 20; i++)
                {
                    
                }
            }
            
            //</editor-fold>
            
                //<editor-fold desc="zoom">
            if(event.mouseButton.button == sf::Mouse::Right)
            {
                for(int i = 0; i<3; i++)
                {
                if(ClickOnElement(cards_armas[i], window))
                   
                {cardsound.play() ;
                    if(armas_jogador[i].GetTipo() != 99)
                    {
                    {
                        do
                        {
                        window.clear(sf::Color::Black) ;
                        cards_armas[i].setSize(sf::Vector2f(global_width*0.35, global_height*0.85)) ;
                        cards_armas[i].setPosition(global_width*0.33, global_height*0.02);
                        
                                
                        cartas[i].setPosition(sf::Vector2f(cards_armas[i].getPosition().x + cards_armas[i].getSize().x*0.45, cards_armas[i].getPosition().y+cards_armas[i].getSize().y*0.83)) ;
                        cartas[i].setCharacterSize(60) ;
                        
                        
                        
                        window.draw(cards_armas[i]) ;
                        window.draw(cartas[i]) ;
                        window.display() ;
                        
                        }while(sf::Mouse::isButtonPressed(sf::Mouse::Left) == false) ;
                        cartas[i].setColor(sf::Color::Transparent) ;
                    }
                    }
                }
                }
                for(int i = 0; i<2; i++)
                {
                    if(ClickOnElement(cards_armaduras[i], window))
                    {
                        cardsound.play() ;
                    if(armaduras_jogador[i].GetTipo() != 99)
                    {
                    
                        do
                        {
                        window.clear(sf::Color::Black) ;
                        cards_armaduras[i].setSize(sf::Vector2f(global_width*0.35, global_height*0.85)) ;
                        cards_armaduras[i].setPosition(global_width*0.33, global_height*0.02);
                        
                                
                        cartas[i+3].setPosition(sf::Vector2f(cards_armaduras[i].getPosition().x + cards_armaduras[i].getSize().x*0.45, cards_armaduras[i].getPosition().y+cards_armaduras[i].getSize().y*0.83)) ;
                        cartas[i+3].setCharacterSize(60) ;
                        
                        
                        
                        window.draw(cards_armaduras[i]) ;
                        window.draw(cartas[i+3]) ;
                        window.display() ;
                        
                        }while(sf::Mouse::isButtonPressed(sf::Mouse::Left) == false) ;
                        cartas[i+3].setColor(sf::Color::Transparent) ;
                    
                    }
                    }
                }
                
            
            //</editor-fold>
            }
            }
            
                
            
            
            
            

            if (event.type == sf::Event::Closed)
            {
                window.close();
              
                return 1;
            }
        
        }
        //</editor-fold>
        
            //<editor-fold desc="draws:">
        window.clear() ;
                    
       
        window.draw(fundo) ;
       window.draw(statsBar);
        window.draw(NextCard) ;
        window.draw(stats) ;
        
             for(int i = 0 ; i<3; i++)
        {
            if(armas_jogador[i].GetTipo() != 99)
            {
                window.draw(cards_armas[i]) ;
                window.draw(cartas[i]) ;
            }
        }
        for(int i = 0 ; i< 2; i ++)
        {
            if(armaduras_jogador[i].GetTipo() != 99)
            {
                window.draw(cards_armaduras[i]) ;
                window.draw(cartas[i+3]);
            }
        }
        
        window.draw(vidamonstro) ;
        window.draw(lvlmonstro) ;
        window.draw(botao) ; 
        window.display() ;
        //</editor-fold>
        }
        //</editor-fold>
        
        
        //<editor-fold desc="caso morra">
        popupaviso("YOU LOOSE, deseja tentar denovo ?", diskontented, window) ;
        char auxiliarchar ;
        cin>>auxiliarchar ;
        if(auxiliarchar == 'y')
        {
            p1.setLvl(1) ;
            p1.setVida(100) ;
            //<editor-fold desc="aplica a dificuldade selecionada">
    switch(menuop)
    {
        case 0:
            
            //<editor-fold desc="insere as armaduras no jogo">

            for(int i = 0; i<10; i++)
            {
                armaduras_jogo[i].SetDur(durarmaeasy+rand()%3) ;
                armaduras_jogo[i].SetProtecao(protecaoarmaduraeasy + rand()%4) ;
                ostringstream convert ;
                convert<<"./Armaduras/"<<i<<".png" ;
                armaduras_jogo[i].SetTextura(convert.str()) ;
                convert.clear() ;
                convert.str("") ;
                if(i<3)
                {
                    armaduras_jogo[i].SetTipo(2) ;
                }
                else
                {
                    if(i<7)
                    {
                        armaduras_jogo[i].SetTipo(1) ;
                    }
                    else
                    {
                        armaduras_jogo[i].SetTipo(0) ;
                    }
                }
            }
            embaralha<Armadura>(&pilha_armaduras, armaduras_jogo, 10) ;
            pilha_armaduras.Desempilha(armaduras_jogador[0]) ;
            pilha_armaduras.Desempilha(armaduras_jogador[1]) ;

            //</editor-fold>

            //<editor-fold desc="insere os monstros no jogo">

            //<editor-fold desc="insere os monstros no vetor monstros_jogo[]">
            for(int i = 0; i<20; i++)
            {
                Monstros_jogo[i].SetLvl(p1.GetLvl()+rand()%3) ;
                ostringstream convert ;
                convert<<"./Monstros/" <<i<<".png" ;
                Monstros_jogo[i].SetTextura(convert.str()) ;
                Monstros_jogo[i].SetVida(vidaeasy+rand()%20) ;
                Monstros_jogo[i].SetAtaque(atkeasy+rand()%5) ;

                if(i<7)
                {
                    Monstros_jogo[i].SetTipo(1) ;

                    if(i == 6)
                    {
                        Monstros_jogo[i].SetTipoDano(0) ;
                    }
                    else
                    {
                        if(i== 0 || i== 3)
                        {
                            Monstros_jogo[i].SetTipoDano(3) ;
                        }
                        else
                        {
                            Monstros_jogo[i].SetTipoDano(1) ;
                        }
                    }

                }
                else
                {
                if(i>=7 && i<14)
                {
                    Monstros_jogo[i].SetTipo(2);

                    if(i == 11)
                    {
                        Monstros_jogo[i].SetTipoDano(0) ;
                    }
                    else
                    {
                        if(i == 10)
                        {
                            Monstros_jogo[i].SetTipoDano(1) ;
                        }
                        else
                        {
                            Monstros_jogo[i].SetTipoDano(3) ;
                        }
                    }

                }
                else
                {
                    Monstros_jogo[i].SetTipo(0) ;

                    Monstros_jogo[i].SetTipoDano(3) ;
                }
                }
            }


            //<editor-fold desc="insere o vetor monstros_jogo[] na pilha de monstros

            embaralha<Monstro>(&pilha_monstros, Monstros_jogo, 20) ;
            //</editor-fold>

            pilha_monstros.Desempilha(MonstroAtual) ;

            //</editor-fold>

            //<editor-fold desc="insere as armas no jogo">

            //<editor-fold desc="insere as armas no vetor">
            for(int i = 0; i<10; i++)
            {
                Armas_jogo[i].SetDano(danoarmaeasy + rand()%5) ;
                Armas_jogo[i].SetDur(durarmaeasy + rand()%2) ;
                ostringstream convert ;
                convert<<"./Armas/"<<i+1<<".png" ;

                Armas_jogo[i].SetTextura(convert.str()) ;

                if(i<5)
                {
                    Armas_jogo[i].SetTipo(3) ;
                }
                else
                {
                    if(i<7)
                    {
                        Armas_jogo[i].SetTipo(1) ;
                    }
                    else
                    {
                        if(i<9)
                        {
                            Armas_jogo[i].SetTipo(2) ;
                        }
                        else
                        {
                            Armas_jogo[i].SetTipo(0) ;
                        }
                    }
                }
            }
            //</editor-fold>

            //<editor-fold desc="embaralha as armas na pilha">

            embaralha<Arma>(&pilha_armas, Armas_jogo, 10) ;

            //</editor-fold>

            //<editor-fold desc="saca as armas iniciais">
            pilha_armas.Desempilha(armas_jogador[0]) ;
            pilha_armas.Desempilha(armas_jogador[1]) ;
            pilha_armas.Desempilha(armas_jogador[2]) ;


            //</editor-fold>

            //</editor-fold>
            
            break ;
            
        case 1:
            
            //<editor-fold desc="insere as armaduras no jogo">

            for(int i = 0; i<10; i++)
            {
                armaduras_jogo[i].SetDur(durarmamedium+rand()%3) ;
                armaduras_jogo[i].SetProtecao(protecaoarmaduramedium + rand()%4) ;
                ostringstream convert ;
                convert<<"./Armaduras/"<<i<<".png" ;
                armaduras_jogo[i].SetTextura(convert.str()) ;
                convert.clear() ;
                convert.str("") ;
                if(i<3)
                {
                    armaduras_jogo[i].SetTipo(2) ;
                }
                else
                {
                    if(i<7)
                    {
                        armaduras_jogo[i].SetTipo(1) ;
                    }
                    else
                    {
                        armaduras_jogo[i].SetTipo(0) ;
                    }
                }
            }
            embaralha<Armadura>(&pilha_armaduras, armaduras_jogo, 10) ;
            pilha_armaduras.Desempilha(armaduras_jogador[0]) ;
            pilha_armaduras.Desempilha(armaduras_jogador[1]) ;

            //</editor-fold>

            //<editor-fold desc="insere os monstros no jogo">

            //<editor-fold desc="insere os monstros no vetor monstros_jogo[]">
            for(int i = 0; i<20; i++)
            {
                Monstros_jogo[i].SetLvl(p1.GetLvl()+rand()%3) ;
                ostringstream convert ;
                convert<<"./Monstros/" <<i<<".png" ;
                Monstros_jogo[i].SetTextura(convert.str()) ;
                Monstros_jogo[i].SetVida(vidamedium+rand()%20) ;
                Monstros_jogo[i].SetAtaque(atkmedium+rand()%5) ;

                if(i<7)
                {
                    Monstros_jogo[i].SetTipo(1) ;

                    if(i == 6)
                    {
                        Monstros_jogo[i].SetTipoDano(0) ;
                    }
                    else
                    {
                        if(i== 0 || i== 3)
                        {
                            Monstros_jogo[i].SetTipoDano(3) ;
                        }
                        else
                        {
                            Monstros_jogo[i].SetTipoDano(1) ;
                        }
                    }

                }
                else
                {
                if(i>=7 && i<14)
                {
                    Monstros_jogo[i].SetTipo(2);

                    if(i == 11)
                    {
                        Monstros_jogo[i].SetTipoDano(0) ;
                    }
                    else
                    {
                        if(i == 10)
                        {
                            Monstros_jogo[i].SetTipoDano(1) ;
                        }
                        else
                        {
                            Monstros_jogo[i].SetTipoDano(3) ;
                        }
                    }

                }
                else
                {
                    Monstros_jogo[i].SetTipo(0) ;

                    Monstros_jogo[i].SetTipoDano(3) ;
                }
                }
            }


            //<editor-fold desc="insere o vetor monstros_jogo[] na pilha de monstros

            embaralha<Monstro>(&pilha_monstros, Monstros_jogo, 20) ;
            //</editor-fold>

            pilha_monstros.Desempilha(MonstroAtual) ;

            //</editor-fold>

            //<editor-fold desc="insere as armas no jogo">

            //<editor-fold desc="insere as armas no vetor">
            for(int i = 0; i<10; i++)
            {
                Armas_jogo[i].SetDano(danoarmamedium + rand()%5) ;
                Armas_jogo[i].SetDur(durarmamedium + rand()%2) ;
                ostringstream convert ;
                convert<<"./Armas/"<<i+1<<".png" ;

                Armas_jogo[i].SetTextura(convert.str()) ;

                if(i<5)
                {
                    Armas_jogo[i].SetTipo(3) ;
                }
                else
                {
                    if(i<7)
                    {
                        Armas_jogo[i].SetTipo(1) ;
                    }
                    else
                    {
                        if(i<9)
                        {
                            Armas_jogo[i].SetTipo(2) ;
                        }
                        else
                        {
                            Armas_jogo[i].SetTipo(0) ;
                        }
                    }
                }
            }
            //</editor-fold>

            //<editor-fold desc="embaralha as armas na pilha">

            embaralha<Arma>(&pilha_armas, Armas_jogo, 10) ;

            //</editor-fold>

            //<editor-fold desc="saca as armas iniciais">
            pilha_armas.Desempilha(armas_jogador[0]) ;
            pilha_armas.Desempilha(armas_jogador[1]) ;
            pilha_armas.Desempilha(armas_jogador[2]) ;


            //</editor-fold>

            //</editor-fold>
            
            break ;
            
        case 2:
            
            //<editor-fold desc="insere as armaduras no jogo">

            for(int i = 0; i<10; i++)
            {
                armaduras_jogo[i].SetDur(durarmahard+rand()%3) ;
                armaduras_jogo[i].SetProtecao(protecaoarmadurahard + rand()%4) ;
                ostringstream convert ;
                convert<<"./Armaduras/"<<i<<".png" ;
                armaduras_jogo[i].SetTextura(convert.str()) ;
                convert.clear() ;
                convert.str("") ;
                if(i<3)
                {
                    armaduras_jogo[i].SetTipo(2) ;
                }
                else
                {
                    if(i<7)
                    {
                        armaduras_jogo[i].SetTipo(1) ;
                    }
                    else
                    {
                        armaduras_jogo[i].SetTipo(0) ;
                    }
                }
            }
            embaralha<Armadura>(&pilha_armaduras, armaduras_jogo, 10) ;
            pilha_armaduras.Desempilha(armaduras_jogador[0]) ;
            pilha_armaduras.Desempilha(armaduras_jogador[1]) ;

            //</editor-fold>

            //<editor-fold desc="insere os monstros no jogo">

            //<editor-fold desc="insere os monstros no vetor monstros_jogo[]">
            for(int i = 0; i<20; i++)
            {
                Monstros_jogo[i].SetLvl(p1.GetLvl()+rand()%3) ;
                ostringstream convert ;
                convert<<"./Monstros/" <<i<<".png" ;
                Monstros_jogo[i].SetTextura(convert.str()) ;
                Monstros_jogo[i].SetVida(vidahard+rand()%20) ;
                Monstros_jogo[i].SetAtaque(atkhard+rand()%5) ;

                if(i<7)
                {
                    Monstros_jogo[i].SetTipo(1) ;

                    if(i == 6)
                    {
                        Monstros_jogo[i].SetTipoDano(0) ;
                    }
                    else
                    {
                        if(i== 0 || i== 3)
                        {
                            Monstros_jogo[i].SetTipoDano(3) ;
                        }
                        else
                        {
                            Monstros_jogo[i].SetTipoDano(1) ;
                        }
                    }

                }
                else
                {
                if(i>=7 && i<14)
                {
                    Monstros_jogo[i].SetTipo(2);

                    if(i == 11)
                    {
                        Monstros_jogo[i].SetTipoDano(0) ;
                    }
                    else
                    {
                        if(i == 10)
                        {
                            Monstros_jogo[i].SetTipoDano(1) ;
                        }
                        else
                        {
                            Monstros_jogo[i].SetTipoDano(3) ;
                        }
                    }

                }
                else
                {
                    Monstros_jogo[i].SetTipo(0) ;

                    Monstros_jogo[i].SetTipoDano(3) ;
                }
                }
            }


            //<editor-fold desc="insere o vetor monstros_jogo[] na pilha de monstros

            embaralha<Monstro>(&pilha_monstros, Monstros_jogo, 20) ;
            //</editor-fold>

            pilha_monstros.Desempilha(MonstroAtual) ;

            //</editor-fold>

            //<editor-fold desc="insere as armas no jogo">

            //<editor-fold desc="insere as armas no vetor">
            for(int i = 0; i<10; i++)
            {
                Armas_jogo[i].SetDano(danoarmahard+ rand()%5) ;
                Armas_jogo[i].SetDur(durarmahard + rand()%2) ;
                ostringstream convert ;
                convert<<"./Armas/"<<i+1<<".png" ;

                Armas_jogo[i].SetTextura(convert.str()) ;

                if(i<5)
                {
                    Armas_jogo[i].SetTipo(3) ;
                }
                else
                {
                    if(i<7)
                    {
                        Armas_jogo[i].SetTipo(1) ;
                    }
                    else
                    {
                        if(i<9)
                        {
                            Armas_jogo[i].SetTipo(2) ;
                        }
                        else
                        {
                            Armas_jogo[i].SetTipo(0) ;
                        }
                    }
                }
            }
            //</editor-fold>

            //<editor-fold desc="embaralha as armas na pilha">

            embaralha<Arma>(&pilha_armas, Armas_jogo, 10) ;

            //</editor-fold>

            //<editor-fold desc="saca as armas iniciais">
            pilha_armas.Desempilha(armas_jogador[0]) ;
            pilha_armas.Desempilha(armas_jogador[1]) ;
            pilha_armas.Desempilha(armas_jogador[2]) ;


            //</editor-fold>

            //</editor-fold>
            
            break ;
    }
    //</editor-fold>
        }
        else
        {
            return 1 ;
            window.close() ;
        }
        
         sf::Event event ;
         while(window.pollEvent(event))
         {
             
             if (event.type == sf::Event::Closed)
            {
                window.close();
              
                return 0;
            }
         }
         //</editor-fold>
     }
    
    //</editor-fold>
    
    return 0;
}

//<editor-fold desc="functions">

template <class tipo>
void draw(pilha <tipo>cards, tipo &cartas)
{
    tipo temp ;
    cards.Desempilha(temp) ;
    cartas = temp ;
}

template <class tipo>
void embaralha(pilha <tipo>* cards, tipo carta[], int tamanhovetor)
{
    int tamanhoatualvetor = tamanhovetor ;
    while(tamanhoatualvetor > 0)
    {
        int randdavez = rand() % tamanhovetor  ;
        if(carta[randdavez].GetTipo() != 99)
        {
        cards->Empilha(carta[randdavez]) ;
        carta[randdavez].SetTipo(99) ;
        tamanhoatualvetor -- ;
        }
    }
}

void SetStats(Jogador p1,Monstro Monstroatual, Arma armas_jogador[], Armadura armaduras_jogador[], sf::Text &stats, sf::Text &vidamonstro, sf::Text &lvlmonstro, sf::Text cartas[])
{
         string lvl ;
         string vida ;        
         ostringstream convert;   // stream usada para conversão
         convert << p1.GetLvl();
         lvl = convert.str() ;
         convert.clear() ;
         convert.str("") ;
         convert<< p1.GetVida() ;
         vida = convert.str() ;
         string status ;
         status = " lvl  :" +lvl +"  ||  vida  :"+vida ;
         stats.setString(status) ;
         convert.clear() ;
         convert.str("") ;
         convert<<Monstroatual.GetLvl();
         lvlmonstro.setString(convert.str()) ;
         convert.clear() ;
         convert.str("") ;
         convert<<Monstroatual.GetVida() ;
         vidamonstro.setString(convert.str()) ;
         for(int i = 0; i<3; i++)
         {
             convert.clear() ;
             convert.str("") ;
             convert<<armas_jogador[i].GetDur()<<"      "<<armas_jogador[i].GetDano() ;
             cartas[i].setString(convert.str()) ;
         }
         for(int i = 3; i<5; i++)
         {
             convert.clear();
             convert.str("");
             convert<<armaduras_jogador[i-3].GetProtecao()<<"      "<<armaduras_jogador[i-3].GetDur() ;
             cartas[i].setString(convert.str()) ;
         }
        
         
}

template <class tipo>
void Texturize(tipo elementoContemTextura, sf::RectangleShape &elementoRecebeTextura, sf::Texture &textura)
{
     
     textura.loadFromFile(elementoContemTextura.get_textura()) ;
     elementoRecebeTextura.setTexture(&textura) ;
}

bool ClickOnElement(sf::RectangleShape shape, sf::RenderWindow &window)
{
    sf::Vector2i mousecoords = sf::Mouse::getPosition(window) ;
    float posx = shape.getPosition().x ;
    float posy = shape.getPosition().y ;
    float sizex = shape.getSize().x ;
    float sizey = shape.getSize().y ;
    
    if(mousecoords.x >= posx && mousecoords.x <= posx+sizex && mousecoords.y >= posy && mousecoords.y <= posy+sizey )
    {
        return true;
    }
    else
    {
        return false; 
    }

}

bool ClickOnElement(sf::Sprite shape, sf::RenderWindow &window)
{
    sf::Vector2i mousecoords = sf::Mouse::getPosition(window) ;
    float posx = shape.getPosition().x ;
    float posy = shape.getPosition().y ;
    float sizex = shape.getGlobalBounds().width ;
    float sizey = shape.getGlobalBounds().height ;
    
    if(mousecoords.x >= posx && mousecoords.x <= posx+sizex && mousecoords.y >= posy && mousecoords.y <= posy+sizey)
    {
        return true;
    }
    else
    {
        return false; 
    }

}

void popupaviso(string textoamostrar, sf::Font diskontented)
{
    
     /* sf::RenderWindow popup(sf::VideoMode(800, 600), "AVISO", sf::Style::Close) ;
         while(popup.isOpen() == true)
                {
                      popup.clear() ;
                     
                sf::Event popupevent;
                   while(popup.pollEvent(popupevent))
                 {
             if(popupevent.type == sf::Event::Closed || popupevent.key.code == sf::Keyboard::Return)
                   {
                 popup.close() ;
                   }
                 }
                                                    
           sf::Text texto;
                texto.setColor(sf::Color::White) ;
                        texto.setFont(diskontented) ;
                  texto.setString(textoamostrar) ;
                  texto.setCharacterSize(50) ;
                  popup.draw(texto) ;
                                                    
              popup.display() ;
                                                    
                                                    
                 }
}
      */
    
}
 
 void popupaviso(string textoamostrar, sf::Font diskontented, sf::RenderWindow &window)
{
     
     if(textoamostrar == "Voce matou o monstro")
     {
         for(int i = 0; i< 40; i++)
     {
             window.clear() ;
        sf::Text texto ;
        texto.setString(textoamostrar) ;
        texto.setFont(diskontented) ;
        texto.setCharacterSize(80) ;
        texto.setColor(sf::Color::Red) ;
        texto.setPosition(sf::VideoMode::getDesktopMode().width*0.30, sf::VideoMode::getDesktopMode().height*0.4) ;
        window.draw(texto) ;
        window.display() ;
     }
         window.clear() ;
     }
         else
         {
     
     for(int i = 0; i< 60; i++)
     {
        sf::Text texto ;
        texto.setString(textoamostrar) ;
        texto.setFont(diskontented) ;
        texto.setCharacterSize(30) ;
        texto.setPosition(0, sf::VideoMode::getDesktopMode().height*0.5) ;
        window.draw(texto) ;
        window.display() ;
     }
     window.clear() ;
     }
     
     /* sf::RenderWindow popup(sf::VideoMode(800, 600), "AVISO", sf::Style::Close) ;
         while(popup.isOpen() == true)
                {
                      popup.clear() ;
                     
                sf::Event popupevent;
                   while(popup.pollEvent(popupevent))
                 {
             if(popupevent.type == sf::Event::Closed || popupevent.key.code == sf::Keyboard::Return)
                   {
                 popup.close() ;
                   }
                 }
                                                    
           sf::Text texto;
                texto.setColor(sf::Color::White) ;
                        texto.setFont(diskontented) ;
                  texto.setString(textoamostrar) ;
                  texto.setCharacterSize(50) ;
                  popup.draw(texto) ;
                                                    
              popup.display() ;
                                                    
                                                    
                 }
}
      */
    
}

void pollrightbutton(sf::Event event, sf::RenderWindow* window, int n_cartas, sf::RectangleShape cards[], int global_width, int global_height )
{
             if(sf::Mouse::isButtonPressed(sf::Mouse::Right))
            {
                for(int i = 0; i<n_cartas; i++)
                {
                if(ClickOnElement(cards[i], *window) == true && sf::Mouse::isButtonPressed(sf::Mouse::Right) == true)
                    {
                        do
                        {
                        window->clear(sf::Color::Black) ;
                        cards[i].setSize(sf::Vector2f(global_width*0.42, global_height*0.9)) ;
                        cards[i].setPosition(global_width*0.3, global_height*0.05);
                        window->draw(cards[i]) ;
                        window->display() ;
                        
                        }while(sf::Mouse::isButtonPressed(sf::Mouse::Left) == false) ;
                    }
                }
                
            }
}

bool isHoveringOver(sf::Sprite& sprite, sf::Window& window)
{
    if(sf::Mouse::getPosition(window).x >= sprite.getPosition().x && sf::Mouse::getPosition(window).x <= sprite.getPosition().x+sprite.getLocalBounds().width 
         &&   sf::Mouse::getPosition(window).y >= sprite.getPosition().y && sf::Mouse::getPosition(window).y <= sprite.getPosition().y+sprite.getLocalBounds().height)
    {
        return true ;
    }
    else
        return false ;
}

 //</editor-fold>