#include <iostream>
#include <random>
#include "TrafficLight.h"

/* Implementation of class "MessageQueue" */

// Task FP.4 removed comment out /* 
template <typename T>
T MessageQueue<T>::receive()
{
    // FP.5a : The method receive should use std::unique_lock<std::mutex> and _condition.wait() 
    // to wait for and receive new messages and pull them from the queue using move semantics. 
    // The received object should then be returned by the receive function. 
#if 0 // Original
#else // Task FP.5
    std::unique_lock<std::mutex> uLock(_mutex);
    _condition.wait(uLock, [this] { return !_queue.empty(); });
    T message = std::move(_queue.back()); // to receive latest message
    _queue.clear(); // use clear() to avoid receiving old message (toggle to green) instead of using pop_back()
    return message;
#endif
}

template <typename T>
void MessageQueue<T>::send(T &&message)
{
    // FP.4a : The method send should use the mechanisms std::lock_guard<std::mutex> 
    // as well as _condition.notify_one() to add a new message to the queue and afterwards send a notification.
#if 0 // Original
#else // Task FP.4
    std::lock_guard<std::mutex> uLock(_mutex);
    _queue.push_back(std::move(message));
    _condition.notify_one();
#endif
}
// Task FP.4 removed comment out */

/* Implementation of class "TrafficLight" */

// Task FP.2 /* 
TrafficLight::TrafficLight()
{
    _currentPhase = TrafficLightPhase::red;
}

void TrafficLight::waitForGreen()
{
    // FP.5b : add the implementation of the method waitForGreen, in which an infinite while-loop 
    // runs and repeatedly calls the receive function on the message queue. 
    // Once it receives TrafficLightPhase::green, the method returns.
#if 0 // Original
#else // Task FP.5
    while (true) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
        if (_messages.receive() == TrafficLightPhase::green) {
            break;
        }
    }
#endif
}

TrafficLightPhase TrafficLight::getCurrentPhase()
{
    return _currentPhase;
}

void TrafficLight::simulate()
{
    // FP.2b : Finally, the private method „cycleThroughPhases“ should be started in a thread when the public method „simulate“ is called. To do this, use the thread queue in the base class. 
#if 0 // Original
#else // Task FP.2
    // launch drive function in a thread
    threads.emplace_back(std::thread(&TrafficLight::cycleThroughPhases, this));
#endif
}

// virtual function which is executed in a thread
void TrafficLight::cycleThroughPhases()
{
    // FP.2a : Implement the function with an infinite loop that measures the time between two loop cycles 
    // and toggles the current phase of the traffic light between red and green and sends an update method 
    // to the message queue using move semantics. The cycle duration should be a random value between 4 and 6 seconds. 
    // Also, the while-loop should use std::this_thread::sleep_for to wait 1ms between two cycles. 
#if 0 // Original
#else // Task FP.2
    std::random_device seed_gen;
    std::mt19937 engine(seed_gen());
    std::uniform_int_distribution<> dist(4000, 6000); // 4-6ms random interval is required
    int duration = dist(engine);
    std::chrono::system_clock::time_point lastTimePoint = std::chrono::system_clock::now();
    while (true) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1)); // 1ms check interval is required
        std::chrono::system_clock::time_point currentTimePoint = std::chrono::system_clock::now();
        if (duration <= std::chrono::duration_cast<std::chrono::milliseconds>(currentTimePoint - lastTimePoint).count()) { 
            if (_currentPhase == TrafficLightPhase::red) {
                _currentPhase = TrafficLightPhase::green;
            } else {
                _currentPhase = TrafficLightPhase::red;
            }
#if 0 // Original
#else // Task FP.4
            _messages.send(std::move(_currentPhase));
#endif
            lastTimePoint = currentTimePoint;
            duration = dist(engine);
            std::this_thread::sleep_for(std::chrono::milliseconds(3800)); // to avoid frequent timer check for first 4ms
        }
    }
#endif
}

// Task FP.2 */