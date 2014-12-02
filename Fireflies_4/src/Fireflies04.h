//
//  Fireflies04.h
//  Fireflies_4
//
//  Created by Kassey Cordova on 11/29/14.
//
//

#ifndef __Fireflies_4__Fireflies04__
#define __Fireflies_4__Fireflies04__

//#include <stdio.h>
#include "ofMain.h"

class FireFlies04{
    
public:     //public vars
    FireFlies04();        //default constructor
    
    ofPoint location;       //ofPoint to describe location
    ofPoint velocity;       //ofPoint to describe velocity
    ofPoint acceleration;   //ofPoint to describe acceleration
    
    float accelerationScaler;   //used to scale our direciton unit vector to increase/decrease steering capability
    float mass;                 //mass of our particle aka a scalar
    
    int s;                  //scalar for our mass
    
    void update();          //update method for movement calculations
    void display();         //draw method
    void edgeCheck();       //check if the particle has gone offscreen
    void applyForce(ofPoint);      //receives a force as a ofPoint and applies it to our acceleration
    void decreaseMass();    //method to decrease the mass by a scalar amount
};

#endif /* defined(__Fireflies_4__Fireflies04__) */
