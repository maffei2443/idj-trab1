#include "Minion.h"
#include "GameObject.h"
#include "Vec2.h"
#include <memory>
#include <iostream>
using std::weak_ptr;
using std::string;
using std::cout;
using std::endl;
#include "Sprite.h"
#include "Bullet.h"
#include "Game.h"

double angularSpeed = 0.02;

#include <chrono>
#include <random>


static std::default_random_engine randomGenerator;
static std::uniform_real_distribution<double> minionScale(1.0,1.5);

Minion::Minion (GameObject& associated, weak_ptr<GameObject> alienCenter,
    double arcOffsetDeg, Vec2 initPos) : arc(arcOffsetDeg),Component(associated), alienCenter(*alienCenter.lock().get()) {
    this->mySprite = new Sprite(this->associated, "assets/img/minion.png");
    this->mySprite->angleToRotate = .02;
    initPos.rotate(arcOffsetDeg);
    this->innerPos = initPos;

    this->associated.box.SetXYWH(
        this->alienCenter.box.center.x, 
        this->alienCenter.box.center.y, 
        mySprite->GetWidth(), 
        mySprite->GetHeight()
    ) ;
    // this->associated.box.AddX( arcOffsetDeg ); 
    this->associated.AddComponent(this);
    double scale = minionScale(randomGenerator);
    mySprite->SetScale(scale, scale);
}

Minion::~Minion () {
    printf("MINION OF %p DYINGGGGGGGGGGGGGGG\n", this);
}

// herda de Component
void Minion::Update(double dt) {
    innerPos.rotate(angularSpeed * dt);
    Vec2 newPos =  innerPos 
                   + this->alienCenter.box.center 
                //    - Vec2(this->alienCenter.box.w/2, this->alienCenter.box.h/2) 
                   ;
    this->associated.box.SetCenter(newPos);
    // cout << "??? : " << this->associated.box << endl;
    // OK funcionando
}

void Minion::Render(){ 
    
}

bool Minion::Is(string type){ 
    return type == "Minion";
}


// t5
void Minion::Shoot(Vec2 direction) {
    GameObject* GO_of_bullet = new GameObject;
    direction = direction - Vec2(this->associated.box.center);

    Vec2 vecNormalized = direction.unitary();
    Vec2 myPos = Vec2(this->associated.box);
    double angle = RAD2DEG * atan2(vecNormalized.y, vecNormalized.x) ;
    // cout << "Minion.associated.box == " << this->associated.box << endl;
    int damage = 0;
    double speed = 0.2;
    double maxDistance = 100000;
    new Bullet(*GO_of_bullet, angle, speed, damage, maxDistance,
        "assets/img/minionbullet1.png", 
        this->associated.box.center.x, this->associated.box.center.y);
    // cout << "ADDED BULLET\n";
    Game::GetInstance().GetState().AddObject(GO_of_bullet);

}

void Minion::Start() {
    this->started = true;
}

Rect Minion::GetBox() {
    return this->associated.box;
}