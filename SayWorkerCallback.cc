#include <nan.h>
#include "SayWorkerCallback.h"

SayWorkerCallback::SayWorkerCallback(Nan::Callback *callback, std::string name, v8::Local<v8::Object> &whatObj)
    : AsyncWorker(callback) {
  _name = name;
  _what = std::string(*Nan::Utf8String(whatObj));
}

SayWorkerCallback::~SayWorkerCallback() {}

void SayWorkerCallback::Execute () {
  _result = _name + " says " + _what;
}

void SayWorkerCallback::HandleOKCallback () {
  Nan::HandleScope scope;
  v8::Local<v8::Value> argv[2] = { Nan::Null(), Nan::Null() };
  argv[1] = Nan::New<v8::String>(_result).ToLocalChecked();
  callback->Call(2, argv);
}
