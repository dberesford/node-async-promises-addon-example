#include <nan.h>
#include "SayWorker.h"

SayWorker::SayWorker(Nan::Persistent<v8::Promise::Resolver> *persistent, std::string name, v8::Local<v8::Object> &whatObj)
    : AsyncWorker(NULL) {
  _name = name;
  _what = std::string(*Nan::Utf8String(whatObj));
  _persistent = persistent;
}

SayWorker::~SayWorker() {}

void SayWorker::Execute () {
  _result = _name + " says " + _what;
}

void SayWorker::HandleOKCallback () {
  Nan::HandleScope scope;
  auto resolver = Nan::New(*_persistent);
  resolver->Resolve(Nan::GetCurrentContext(), Nan::New(_result).ToLocalChecked());
}


