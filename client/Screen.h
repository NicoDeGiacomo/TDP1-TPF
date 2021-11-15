#ifndef _SCREEN_H_
#define _SCREEN_H_

#include <SDL2pp/SDL2pp.hh>

#define A_CENTER 0
#define A_LEFT 1
#define A_RIGHT 2

class Screen {
public:
    Screen(SDL2pp::Renderer &renderer);
    virtual int start() = 0;
protected:
    SDL2pp::Renderer &renderer;
    /*  Se puede elegir la alineación del texto con los flags.
     *  En caso de que la alineación sea A_CENTER, pos_x y pos_y 
     *  pueden tomar valores entre 0 y 100. El texto se ubica en 
     *  la posicion relativa indicada por estos parametros.
     *  Por ej: Si ambos parametros son 50, el texto se ubica en 
     *  el centro de la pantalla.
     *  Para A_LEFT y A_RIGHT, pos_x y pos_y son posiciones absolutas.
     */
    void insert_text(std::string &text, 
					 int font_size, 
					 int pos_x, 
					 int pos_y,
                     int flags);
    virtual void redraw() = 0;
};

#endif  // _SCREEN_H_
