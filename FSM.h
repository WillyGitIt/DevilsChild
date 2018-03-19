#ifndef FSM_h
#define FSM_h

enum STATE {    

  INITIALISING,

  RUNNING,

  STOPPED

};


STATE initialising();

STATE running();

STATE stopped();



#endif
