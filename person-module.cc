#include <nan.h>
#include <node.h>
#include "Person.h"

NAN_MODULE_INIT(InitAll) {
  Person::Init(target);
  Nan::Set(target,
           Nan::New<v8::String>("create").ToLocalChecked(),
           Nan::GetFunction(Nan::New<v8::FunctionTemplate>(Person::NewInstance)).ToLocalChecked()
           );
}

NODE_MODULE(addon, InitAll)
