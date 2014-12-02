//
//  FireFlies02.h
//  Fireflies_2
//
//  Created by Kassey Cordova on 11/19/14.
//
//

#ifndef __Fireflies_2__FireFlies02__
#define __Fireflies_2__FireFlies02__

//#include <stdio.h>
#include "ofMain.h"

class FireFlies04{
    
public:
    
    FireFlies04();      //default Vehicle Constructor
    
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


#endif /* defined(__Fireflies_2__FireFlies02__) */
