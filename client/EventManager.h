//
// Created by ale on 23/11/21.
//

#ifndef QUANTUM_CHESS_EVENTMANAGER_H
#define QUANTUM_CHESS_EVENTMANAGER_H


namespace EventManager {
    //////////////////
    /// * tengo una "Accion". objetos o clases se subscriben a esa accion sobrecargando el "+="
    ///     EventManager::onClickStartButton += metodoQueHandleaLaAccion;
    ///
    /// * creo un boton y on click le seteo una lambda
    ///     boton.onClick([](){ EventManager::clickearonElBotonA(); });
    ///
    /// * hacen un click en un boton, se llama al EventManager::clickearonElBotonA();
    ///     y en este metodo se ejecuta la accion que corresponda
    ///     this->miAccion.Invocar();
    ///
    /// * problema, esta accion deberia tener una "pool" de threads, de esta pool agarro un thread por
    /// objeto subscripto a miAccion y corro el metodo con el que se subscribieron
    /// pero que pasa si no hay mas threads en la pool y tengo que esperar? creo q para eso
    /// necesito un "scheduler" que controle los tiempos de los threads y le aviso que tiene q ejecutar algo cuando pueda
    ///
    /// comment: para no tener este problema puedo hacer q tamaño de la pool sea igual a la cantidad de subscriptos
    /// o limitar la cantidad de los que pueden subscribirse a una accion, ej 2 por accion
    ///
    /// * otro problema, quien joinea los threads de las pools de las acciones para no interrumpir ningun thread importante?
    ///
    /// comment: para hacerlo facil podria ser que haya un thread corriendo escuchando de una Queue de acciones
    /// y cuando se llame a "EventManager::clickearonElBotonA();", se agreguen las acciones a la Queue
    /// y el otro thread va a popear, loopear por todos los subscriptos a la accion y ejecutar el metodo q la handlea
    /// lo malo es q las acciones van a ser recontra secuenciales, no se q tan "orientado a eventos" es esto
    //////////////////
    void OnStartGamePressed();
}


#endif //QUANTUM_CHESS_EVENTMANAGER_H
