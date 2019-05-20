#include "GameObject.h"
#include "Rect.h"
#include "Macros.h"
#include "Util.h"
#include <cstdio>
#include <iostream>
#include <string>
using std::string;
using std::cout;
using std::endl;
const string GameObject::type("GameObject");
GameObject::GameObject() : isDead(false), box(),started(false) {
    PRINT(this);
}

GameObject::~GameObject() {
    cout << "[" << this->GetType() << "] DESTRUCTOR" << endl;
    //////printf("GO deletado...\n");
    // Liberando em ordem reversa À que foi alocado
    this->components.clear();
    fflush(stdout);
}

void GameObject::Update(double dt) {
    // cout << "GAMEOBJECT " << this <<  " UPDATE" << endl;
    this->currentDt = dt;
    for(auto& comp : this->components) {
        // printf("WILL CALL comp->GetType() of ======> %p\n", comp);
        // cout << "\t[GameObject::Update] type: " << comp->GetType() << ", addr: " << &comp << endl;
        comp->Update(dt);
    }
    // cout << "END GAMEOBJECT " << this <<  " UPDATE" << endl;

}
void GameObject::Render() {
    for(auto& comp : this->components) {
        //////printf("[Component.cpp] COMPONENT TYPE, ADDR |----> %s, %u\n", comp->GetType().c_str(), &comp);
        comp->Render();
    }
    fflush(stdout);
}

bool GameObject::IsDead() {
    return this->isDead;
}
void GameObject::RequestDelete() {
    this->isDead = true;
}
void GameObject::AddComponent(Component* cpt) {
    // BUG POSSIVEL
    // this->components.push_back(cpt);
    this->components.emplace_back(cpt);
    // cout << "[GameObject " << this << "] Emplaced ---> " << cpt->GetType() << endl;
}

void GameObject::RemoveComponent(Component * cpt) {
    std::size_t len = this->components.size();
    for(std::size_t i = 0; i < len; i++ ) {
        if (cpt != this->components[i]) continue;
        this->components.erase(this->components.begin() + i);
        cout << "ERASEDD " << cpt << endl;
        break;
    }
}

Component* GameObject::GetComponent(string type) {
    for(auto* comp : this->components) {
        if(comp->Is(type)) {
            if(type == "Face") {
                printf("I AM FACE : %p\n", comp);
            }
            return comp;
        }
    }
    // LOG("Objeto não existente\n");
    // LOG("Método incompleto!!! Terminna logo  isso..\n");
    // fflush(stdout);
    return nullptr;
}

// t5
void GameObject::Start() {
    /* no Start percorrer os componentes chamando o Start
    deles, setando started;*/
    this->started = true;
    // printf("GameObject::Start %p\n", this);
    for(auto& i : this->components) {
        i->Start();
    }
    // printf("Started all of %p\n", this);
    /*  e depois chamando o Start dos componentes
    adicionados em AddComponent quando Start já tiver sido chamado.  */
    // POSSIVEL BUG [????] [DUVIDA]
}

void GameObject::NotifyCollision(GameObject &other) {
    for(auto i : this->components) {
        i->NotifyCollision(other);
    }
}
