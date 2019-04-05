#include <unistd.h>
#include "Face.h"
#include "Sound.h"
#include "Component.h"
#include "Macros.h"
Face :: Face(GameObject& associated): 
    Component(associated),
    hitspoints(Face::HEALTH_POINTS){

}

// BUG POSSIVEL
void Face ::  Damage(int damage) {
    this->hitspoints -= damage;
    if(hitspoints < 1) {    // TODO: otimização (usando manipulação e bits)
        this->associated.RequestDelete();
        Component* cmptPtr = this->associated.GetComponent("Sound");
        Sound * sndPtr = (Sound*) cmptPtr;

        if(sndPtr){
            LOG(("The face YES have SOUND!"))
            sndPtr->Play();
            sleep(1);   // TODO: melhorar isso.
        }
        else
            LOG(("The face doesn't have SOUND!"))
    }
}
// Face ::  herda de Componen {


void Face ::  Update(float dt) {
    (void)dt;
}
void Face ::  Render() {
    // Itentionally left empty.
}
bool Face :: Is(std::string type) {
    return type == "Face";
}