#include<iostream>
#include<cstring>
#include<functional>

using namespace std;

struct Buttons{
  bool btn1;
  bool btn2;
  bool btn3;
};

typedef struct CamperState{
  bool water_on;
  int water_pin;
  
  bool lights_on;
  int lights_pin;

  bool gas_on;
  int gas_pin;
} CamperState;


class NetworkingHandler{
    public:
    CamperState *state;
    NetworkingHandler(CamperState *_state):state(_state){}

    void onWifiConnect(int a){
      printf("wifi connectd: %s", a);
    }
    void setup_networking(){
      using namespace std::placeholders; 
      auto onwificonn = bind(&onWifiConnect, this, _1);
      onwificonn(190);
    }
};



void initCamperState(CamperState *camperState_ptr, bool water_on, int water_pin, bool lights_on, 
    int lights_pin, bool gas_on, int gas_pin){
  camperState_ptr->water_on = water_on;
  camperState_ptr->water_pin = water_pin;
  camperState_ptr->lights_on = lights_on;
  camperState_ptr->lights_pin = lights_pin;
  camperState_ptr->gas_on = gas_on;
  camperState_ptr->gas_pin = gas_pin;
};


int main() {
  // printf() displays the string inside quotation
  printf("Hello, World!\n");
  CamperState camperState;
  NetworkingHandler handler(&camperState);


  printf("przed: %d\n", camperState.gas_on);
  initCamperState(&camperState, 1,1,1,1,1,1);
  printf("po: %d\n", camperState.gas_on);

  return 0;
}