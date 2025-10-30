#include "gamethread.h"

//Constructor
GameThread::GameThread(QObject *parent) : QThread(parent){
    qInfo() << this << Q_FUNC_INFO;
}

//Destructor
GameThread::~GameThread(){

    mutex.lock();
    abort = true;
    //condition.wakeOne();
    mutex.unlock();
    wait();

    //para que no lo destruya hay que hacer que lo duerma o algo asi

}

//Abort
void GameThread::setAbort(bool opc){
    this->abort = opc;
}



/*  NOTAS
 *  hasta el momento se logro hacer el loop y detenerlo, creo que ya le entiendo un poco y veo esperanza, recuerda el mutex.lock
 *  hasta ahroa parece que cada vez que queramos modificar alguna variable la tenemos que encerrar entre lock y unlock. Por ahora
 *  se trabaja en variables localaes del thread, lo importante aqui es que pueda renderizar el graphicsView (revisa la funciona del
 *  render )
 *
 *  Una idea es el ciclo entre los dos hilos, es decir, termina el calculo y emite la señal para pintar la escena y cuando
 *  termina de pintar la escena emite la señal y continua con el proceso.
 *
 *  Otra idea es la historia de cada celulda y lo que se muestra es una anterior t = 0, mientras se calula la correspondiente
 *  a t = 1 o una cola de escenas
 */


//GAME
void GameThread::run(){
    //TEST LOOP
    QThread::currentThread()->setObjectName("Game Thread");
    qDebug() << QThread::currentThread();
    while(true){
        mutex.lock();
        if(abort){return;}
        qDebug() << " running ... ";

        mutex.unlock();
        int var = 0;
        for(int i = 0; i < 100; i++){
            var+=i;

        }


        //emit done();


        mutex.lock();
        if (restart)
            condition.wait(&mutex);
        restart = false;
        mutex.unlock();
    }

}


