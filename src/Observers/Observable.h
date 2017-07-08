#pragma once
#include <vector>

template<class Observer>
class Observable {
protected:
  std::vector<Observer*> observers;
public:
  Observer& addObserver(Observer* observer) {
    observers.push_back(observer);
  }
};
