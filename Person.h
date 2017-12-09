#ifndef Person_H
#define Person_H

#include <nan.h>

class Person : public Nan::ObjectWrap {
 public:
  static NAN_MODULE_INIT(Init);


  static NAN_METHOD(NewInstance);
  static NAN_METHOD(SayCallback);
  static NAN_METHOD(Say);
  static NAN_METHOD(New);

  explicit Person(std::string name);
  ~Person();

 private:
  std::string _name;
};

#endif  // Person_H
