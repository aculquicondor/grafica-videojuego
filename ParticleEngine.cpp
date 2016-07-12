//
// Created by jasillo on 29/04/16.
//

#include "ParticleEngine.h"
default_random_engine generator;

float generate_random(float min, float max)
{
    uniform_real_distribution<float > distribution(min,max);
    return distribution(generator);
}

ParticleEngine::ParticleEngine(int s, glm::vec3 pos, int t, glm::vec3 dir):
                                                                origin(pos),
                                                                typeAnimation(t),
                                                                direction(dir),
                                                                size(s){
    myParticles.resize(s, nullptr);

    for (unsigned int i=0 ; i<myParticles.size() ; ++i){
        myParticles[i] = new Particle;
        createParticle(myParticles[i]);
    }

    AnimationContious = false;
    color = {1.0, 1.0, 0.0};
}

ParticleEngine::~ParticleEngine(){
    for (Particle *p : myParticles)
        delete p;
}

// set particle with initial values
void ParticleEngine::createParticle(Particle* p) {
    p->pos = {origin.x, origin.y, origin.z};
    if (typeAnimation == 0){
        p->velocity = {generate_random(-1.0f,1.0f),
                   generate_random(-1.0f,1.0f),
                   generate_random(-1.0f,1.0f)};
        p->velocity = generate_random(1.0f,8.0f) * glm::normalize(p->velocity);
    }
    else
        p->velocity = {direction.x + generate_random(-2,2),
                       direction.y + generate_random(-2,2),
                       direction.z + generate_random(-2,2)};

    p->timespam = generate_random(1.0f,1.5f);
    p->mass = generate_random(2,4);
    p->size = p->mass * 0.05;
    p->timeAlive = 0;
    p->color = color;
    p->alpha = 1.0;
    p->alive = true;
}

void ParticleEngine::setPoint(float x,float y,  float angle, float distToCenter,bool initial){
    float r = glm::tan(glm::radians(angle))*(distToCenter-origin.z);
    if (initial)
    {
        origin.x = r * x;
        origin.y = r * y;
    }else{
        destiny.x = r * x;
        destiny.y = r * y;
        direction = destiny - origin;
        if (!AnimationContious)
            for (Particle *p : myParticles)
                createParticle(p);
    }
}


void ParticleEngine::step(float lapseTime){
    for (Particle *p : myParticles) {
        if (p->alive) {
            p->timeAlive += lapseTime;
            p->velocity.y -= GRAVITY * lapseTime ;
            p->velocity -= k * lapseTime * p->velocity / p->mass;
            p->pos += p->velocity * lapseTime;

            p->alpha = 1 - p->timeAlive / p->timespam;
            p->color.y = p->alpha * color.y;
            if (p->alpha <= 0)
            {
                --size;
                //createParticle(p); //reset values
                p->alive = false;
            }
        }
    }
}

void ParticleEngine::restartParticles(){
    if (!AnimationContious)
        for (Particle *p : myParticles)
            createParticle(p);
}

void ParticleEngine::setContinuous(bool i){
    AnimationContious = i;
    if (AnimationContious)
        for (Particle *p : myParticles)
            p->alive = true;
}

void ParticleEngine::setTypeAnimation(int i){
    typeAnimation = i;
}

void ParticleEngine::setColor(float x,float y, float z){
    color = {x,y,z};
}

void ParticleEngine::setTexture(GLuint t)
{
    textureId = t;
}

void ParticleEngine::setDistance(float z)
{
    origin.z = z;
    destiny.z = z;
}


