# Variables

Variables within a `Configuration` class or `RootConfiguration` class will be tracked by `Bleeper` only if they are declared using specific macros.

## Common types

- `intVar`, `floatVar` & `stringVar`  
They all receive two parameters, the first one is the name of the variable and the second one its default value. Default values must be of types `int`, `float` and `String` respectively.

- `persistentIntVar`, `persistentFloatVar` & `persistentStringVar`  
The same as before but they will be persisted on the configured `Bleeper` storage.

```Cpp
class ExampleConfig: public Configuration {
public:
  persistentStringVar(boardName, "Board 1");
  floatVar(threshold, 0.7);
};
```

## Custom types

`Bleeper` allows you to store any type of variable. You only need to be able to serialize & deserialize it to & from a string.

- `var(type, name, default, setBody, getBody)`   
  - `type`: your custom type.
  - `name`: name of your variable.
  - `default`: default value.
  - `setBody`: scope enclosed by curly brackets in which you will have exposed a variable called `name` (your actual variable) and a constant called `nameString` which you will have to make your conversion from.
  - `getBody`: similar to `setBody` but you need to write the variable called `nameString` from your variable `name`.


- `persistentVar(type, name, default, setBody, getBody)`  
The same as before but persistent.

```Cpp
#include "Bleeper.h"

class Point {
public:
  int x, y;

  Point(int x, int y) {
    this->x = x;
    this->y = y;
  }

  Point(String string) {
    auto strings = splitString(string, ",");
    x = strings[0].toInt();
    y = strings[1].toInt();
  }

  String toString() {
    return String(x) + "," + String(y)
  }
}

class ExampleConfig: public Configuration {
public:
  var(Point, point, Point(0, 0),
  {
    point = Point(pointString);
  },
  {
    pointString = point.toString();
  });
};
```        
