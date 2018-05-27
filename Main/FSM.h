#ifndef FSM_h
#define FSM_h

enum STATE {    

  INITIALISING,

  RUNNING,

  FIRE,

  STOPPED

};


STATE initialising();

STATE running();

STATE fire();

STATE stopped();

#endif
