#ifndef FSM_h
#define FSM_h

enum STATE {    

  INITIALISING,

  SPIRALING,

  AVOIDANCE,

  STOPPED

};

STATE initialising();

STATE spiraling();

STATE avoidance();

STATE stopped();

#endif
