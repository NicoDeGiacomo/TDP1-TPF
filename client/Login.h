#ifndef LOGIN_H_
#define LOGIN_H_

#include <SDL2pp/SDL2pp.hh>

class Login {
public:
    Login(SDL2pp::Renderer &renderer);
    void start();
    std::string get_user_name();
private:
    SDL2pp::Renderer &renderer;
    /*  rel_pos_x y rel_pos_y pueden tomar valores entre 0 y 100.
     *  El texto se ubica en la posicion relativa indicada por 
     *  estos parametros.
     *  Por ej: Si ambos parametros son 50, el texto se ubica en 
     *  el centro de la pantalla.
     */
    void insert_text(std::string &text, 
					 int font_size, 
					 int rel_pos_x, 
					 int rel_pos_y);
    void redraw();
    std::string user_name;
};

#endif  // LOGIN_H_
