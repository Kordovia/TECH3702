//
//  FireFliesTest2.cpp
//  InteractionTest_2
//
//  Created by Kassey Cordova on 11/20/14.
//
//

#include "FireFliesTest2.h"


FireFliesTest2::FireFliesTest2(){
    location = ofPoint(ofRandom(ofGetWidth()),ofRandom(ofGetHeight()));    //generate a random location to start from within the sketch window
    
    //location = ofPoint(0,0);
    
    velocity = ofPoint(0,0);                                //starting with 0 instead
    
    acceleration = ofPoint(0.0,0.0);      //set acceleration to nothing to start so rely purely on incoming forces
    
    mass = 1.0; //equivalent to no mass
    
    target = ofPoint(ofGetWidth()/2,ofGetHeight()/2);   //set the target location to the center of the window
    
    maxSpeed = 4.0; //setting the initial maximum speed
    
    maxForce = 0.1; //setting the maximum steering force to something small
    
    radius = 20;    //radius of our vehicle shape
}


//update - updates the vehicles velocity and applies it to location
void FireFliesTest2::update(){
    
    velocity = velocity+acceleration; //add acceleration to velocity to change over time
    
    velocity.limit(10); //limit velocity to 10. If our velocity hits 10 it will stay at 10.
    
    location = location+velocity;     //add velocity to location to move at a constant velocity.
    
    edgeCheck();    //if past the screen edge reset to opposite end of x or y
    
    acceleration*=0;    //scale acceleration by 0 and assign back to itself so forces do not continue to stack
    
}


//display - method to draw our vehicle and the target on screen
void FireFliesTest2::display(){
    
    ofPushMatrix(); //save our coordinate system
    
    ofTranslate(location);  //move our coordinate system to our ofPoint location
    
    ofRectMode(OF_RECTMODE_CENTER);     //sets our rect to draw form a center point
    
    float rotate = atan2(velocity.y, velocity.x);   //calculate our angle using atan2. atan2 or four-quadrant inverse tanget allows to preserve what quadrant our result is in and therefore heading. Angle returned is in radian. Remember OPPOSITE (Y) then ADJACENT (X)
    
    //cout<<"Rotation in Radians: "<<rotate<<endl;
    //cout<<"Rotation in Degrees: "<<ofRadToDeg(rotate)<<endl;
    
    ofSetColor(255,150);
    ofFill();
    
    ofRotate(ofRadToDeg(rotate));   //rotate our coordinate system based on rotate with conversion from rad to deg
    
    /*
     //ofRotate(90); //if drawn with an upward orientation
     
     //triangle oriented up which requires an additional 90 degree rotation
     ofBeginShape();
     ofVertex(0, -radius/2);
     ofVertex(-radius/2, radius/2);
     ofVertex(radius/2, radius/2);
     ofEndShape();
     */
    
    //triangle on its side which does not require rotating an additional 90 degrees
    ofBeginShape();
    
    float glowTime = ofGetElapsedTimef();       //returns time in seconds
    float value = sin(glowTime*1.5);
    //float v = ofMap(value, -1,1,0,255);     //map to 0-255 for RGB range
    float v = ofMap(value, -1,1,15,80);
    
    ofSetColor(245, 241, 0, v);                  //set the background to the mapped value of v
    //ofSetColor(245, 241, 0,30);             //outer glow
    ofFill();
    ofEllipse(0,0, ofRandom(1,12)*2.5, ofRandom(1,12)*2.5);
    
    
    ofSetColor(245, 241, 0, 100);           //inner glow
    ofFill();
    ofEllipse(0,0, 3*2.5, 3*2.5);
    
    ofSetColor(255,200);
    ofFill();
    ofEllipse(0,0, 3,3);      //white firefly
    
    
    // ofEllipse(0, 0, radius, radius);
    
    ofEndShape();
    
    ofPopMatrix(); //pop back our coordinate system
    
    //draw our target location
    ofSetCircleResolution(200);
    ofEnableSmoothing();
    ofSetColor(255, 0, 0,50);
    //ofSetColor(255, 0, 0);
    //ofSetLineWidth(2.0);
    //ofNoFill();
    ofFill();
    ofCircle(target,20);
}


//seek - method to calculate the desired velocity, set steering and apply the force to acceleration
void FireFliesTest2::seek(){
    ofPoint desire = target - location; //create a new ofPoint desire and assign the resulting vector from subtracting the target location from the location of the vehicle
    
    desire.normalize(); //normalize desire to get pure heading
    
    desire*=maxSpeed;   //scale desire by the maximum speed
    
    ofPoint steer = desire - velocity;  //create ofPoint steer based off the result of velocity subtracted from desire. This is our steering force
    
    steer.limit(maxForce);  //limit our steering to affect the speed at which vehicle can steer
    
    applyForce(steer);      //send our steering force to applyForce method in order to cascade to acceleration->velocity->location
    
}


//applyForce - calculates force and applies to acceleration
void FireFliesTest2::applyForce(ofPoint f){
    
    ofPoint force = f/mass;  //create/init ofPoint force which is set to the incoming force/mass per
    
    acceleration+=force;    //add and assign our force to acceleration, per accumulation of forces
}


//edgeCheck - method to make sure the vehicles are on screen
void FireFliesTest2::edgeCheck(){
    
    //do a bounds check for x. reset to opposite side of screen if out of bounds
    if(location.x > ofGetWidth()){
        location.x = ofGetWidth();
        velocity.x *= -1;       //flip our velocity if at left edge
    }else if(location.x < 0){
        location.x = 0;
        velocity.x *= -1;       //flip our velocity if at right edge
    }
    
    //do a bounds check for y. reset to opposite side of screen if out of bounds
    if(location.y > ofGetHeight()){
        location.y = ofGetHeight();
        velocity.y *= -1;      //flip our velocity if we hit the bottom edge
    }else if(location.y < 0){
        location.y = 0;
        velocity.y *= -1;       //flip our velocity if we hit the top edge
    }
    
}


//moveTarget - method to change the target to a new random location
void FireFliesTest2::moveTarget(ofPoint inTarget){
    
    target = inTarget;  //set the target to the ofPoint provided when called
    
    //target.set(ofRandom(0,ofGetWidth()), ofRandom(0,ofGetHeight()));
    
}
