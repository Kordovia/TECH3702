//
//  FireFlies03.h
//  FireFlies_3
//
//  Created by Kassey Cordova on 11/21/14.
//
//

#ifndef __FireFlies_3__FireFlies03__
#define __FireFlies_3__FireFlies03__

#include "ofMain.h"

class FireFlies03{
    
public:
    
    FireFlies03();      //default Vehicle Constructor
    
    ofPoint location;   //location vector/ofPoint
    ofPoint velocity;   //velocity vector/ofPoint
    ofPoint acceleration;   //accerleration vector/ofPoint
    
    ofPoint target;     //target location vector/ofPoint
    
    float mass; //mass of vehicle
    float maxSpeed; //maximum speed of vehicle
    float maxForce; //sets the maximum steering force possible. Lower = slower steering response & higher = faster
    
    int radius; //radius of our vehicle
    
    void update();  //update method
    void display(); //display method
    void edgeCheck();  //method to check the screens bound
    void applyForce(ofPoint);   //method that receives a vector and calculates applicable forces and applies to acceleration
    
    void seek();        //method to calculate the steering force given a specific target
    
    void moveTarget(ofPoint);  //method to move the target location to a new random location
    
};

#endif /* defined(__FireFlies_3__FireFlies03__) */
