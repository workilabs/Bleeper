#pragma once

#define UNIQUE_NAME(x) zbleeper ## _ ## x

/******************* MOST COMMON VARS ******************/

#define floatVar(name, initial)   __floatVar__(name, initial, false)
#define stringVar(name, initial)  __stringVar__(name, initial, false)
#define intVar(name, initial)     __intVar__(name, initial, false)

#define persistentFloatVar(name, initial)   __floatVar__(name, initial, true)
#define persistentStringVar(name, initial)  __stringVar__(name, initial, true)
#define persistentIntVar(name, initial)     __intVar__(name, initial, true)

#define var(type, name, initial, setBody, getBody)            __var__(type, name, initial, false, setBody, getBody)
#define persistentVar(type, name, initial, setBody, getBody)  __var__(type, name, initial, true, setBody, getBody)

/******************* MOST COMMON VARS ******************/

#define __floatVar__(name, initial, isPersistent)\
float name = initial;\
FloatVariable* UNIQUE_NAME(var_ ## name) = (new FloatVariable(#name, &name, isPersistent))->addTo<FloatVariable>(vars);

#define __stringVar__(name, initial, isPersistent)\
StringVariable* UNIQUE_NAME(var_ ## name) = (new StringVariable(#name, &name, isPersistent))->addTo<StringVariable>(vars);\
String name = initial;

#define __intVar__(name, initial, isPersistent)\
IntVariable* UNIQUE_NAME(var_ ## name) = (new IntVariable(#name, &name, isPersistent))->addTo<IntVariable>(vars);\
int name = initial;

#define subconfig(type, name)\
type * UNIQUE_NAME(name) = (new type())->withPrefix<type>(#name)->addTo<type>(subConfigs);\
type & name = *UNIQUE_NAME(name);\

/*************** GENERIC TYPE VARIABLES ****************/

#define __var__(type, name, initial, isPersistent, setBody, getBody)\
GenericVariable<type>* UNIQUE_NAME(var_ ## name) = (new GenericVariable<type>(#name, &name, isPersistent, &setterFuncName(name), &getterFuncName(name)))->addTo<GenericVariable<type>>(vars);\
type name = initial;\
setterFunc(type, name, setBody);\
getterFunc(type, name, getBody);\

#define setterFuncName(name) UNIQUE_NAME(set_ ## name)
#define getterFuncName(name) UNIQUE_NAME(get_ ## name)

#define setterFunc(type, name,body)\
static void setterFuncName(name)(type* UNIQUE_NAME(instance), const String& name ## String){\
  auto & name = *UNIQUE_NAME(instance);\
  body;\
}

#define getterFunc(type, name, body)\
static String getterFuncName(name)(type* UNIQUE_NAME(instance)){\
  const auto & name = *UNIQUE_NAME(instance);\
  String name ## String = "STRING_CONVERTER_NOT_IMPLEMENTED";\
  body;\
  return name ## String;\
}
