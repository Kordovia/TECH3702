//
//  Fireflies01.h
//  Final_FirefliesProject002
//
//  Created by Kassey Cordova on 11/29/14.
//
//

#ifndef __Final_FirefliesProject002__Fireflies01__
#define __Final_FirefliesProject002__Fireflies01__

//#include <stdio.h>


#include "ofMain.h"

class Fireflies01{
    
public:
    
    Fireflies01();      //default Vehicle Constructor
    
    ofPoint location;       //location vector/ofPoint
    ofPoint velocity;       //velocity vector/ofPoint
    ofPoint acceleration;   //accerleration vector/ofPoint
    
    ofPoint target;         //target location vector/ofPoint
    
    float mass;     //mass of vehicle
    float maxSpeed; //maximum speed of vehicle
    float maxForce; //sets the maximum steering force possible. Lower = slower steering response & higher = faster
    
    int radius; //radius of our vehicle
    
    void update();  //update method
    void display(); //display method
    // void edgeCheck();  //method to check the screens bound
    void applyForce(ofPoint);   //method that receives a vector and calculates applicable forces and applies to acceleration
    
    void seek();        //method to calculate the steering force given a specific target
    
    void moveTarget(ofPoint);  //method to move the target location to a new random location
    
};


#endif /* defined(__Final_FirefliesProject002__Fireflies01__) */
