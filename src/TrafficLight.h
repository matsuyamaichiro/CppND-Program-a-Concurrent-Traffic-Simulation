#ifndef TRAFFICLIGHT_H
#define TRAFFICLIGHT_H

#include <mutex>
#include <deque>
#include <condition_variable>
#include "TrafficObject.h"

// forward declarations to avoid include cycle
class Vehicle;


// FP.3 Define a class „MessageQueue“ which has the public methods send and receive. 
// Send should take an rvalue reference of type TrafficLightPhase whereas receive should return this type. 
// Also, the class should define an std::dequeue called _queue, which stores objects of type TrafficLightPhase. 
// Also, there should be an std::condition_variable as well as an std::mutex as private members. 

template <class T>
class MessageQueue
{
public:
#if 0 // Original
#else // Task FP.3
    void send(T &&message);
    T receive();
#endif

private:
#if 0 // Original
#else // Task FP.3
    std::deque<T> _queue; // std::deque is required by the specification but std::vector is faster
    std::condition_variable _condition;
    std::mutex _mutex;
#endif
    
};

// FP.1 : Define a class „TrafficLight“ which is a child class of TrafficObject. 
// The class shall have the public methods „void waitForGreen()“ and „void simulate()“ 
// as well as „TrafficLightPhase getCurrentPhase()“, where TrafficLightPhase is an enum that 
// can be either „red“ or „green“. Also, add the private method „void cycleThroughPhases()“. 
// Furthermore, there shall be the private member _currentPhase which can take „red“ or „green“ as its value. 
#if 0 // Original
#else // Task FP.1
enum class TrafficLightPhase {
    red,
    green
};
#endif

#if 0 // Original
class TrafficLight
#else // Task FP.1
class TrafficLight : public TrafficObject
#endif
{
public:
#if 0 // Original
    // constructor / desctructor

    // getters / setters

    // typical behaviour methods

#else // Task FP.1
    // constructor / destructor
    TrafficLight();
    // Default destructor is used.

    // getters / setters
    TrafficLightPhase getCurrentPhase();

    // typical behaviour methods
    void waitForGreen();
    void simulate();
#endif

private:
    // typical behaviour methods
#if 0 // Original
#else // Task FP.1
    void cycleThroughPhases();
#endif

    // FP.4b : create a private member of type MessageQueue for messages of type TrafficLightPhase 
    // and use it within the infinite loop to push each new TrafficLightPhase into it by calling 
    // send in conjunction with move semantics.

#if 0 // Original
#else // Task FP.4
    MessageQueue<TrafficLightPhase> _messages;
#endif
    std::condition_variable _condition;
    std::mutex _mutex;
#if 0 // Original
#else // Task FP.1
    TrafficLightPhase _currentPhase;
#endif
};

#endif