#include <node.h>
#include <nan.h>
#include <iostream>
#include "Person.h"
#include "SayWorkerCallback.h"
#include "SayWorker.h"

Nan::Persistent<v8::Function> constructor;

Person::Person(std::string name) {
  _name = name;
}

Person::~Person() {
}

NAN_MODULE_INIT(Person::Init) {
  v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(New);
  tpl->SetClassName(Nan::New("Person").ToLocalChecked());
  tpl->InstanceTemplate()->SetInternalFieldCount(1);

  Nan::SetPrototypeMethod(tpl, "sayCallback", SayCallback);
  Nan::SetPrototypeMethod(tpl, "say", Say);
  constructor.Reset(Nan::GetFunction(tpl).ToLocalChecked());
}

NAN_METHOD(Person::New){
  if (!info.IsConstructCall()) {
    std::vector<v8::Local<v8::Value>> args(info.Length());
    for (std::size_t i = 0; i < args.size(); ++i) args[i] = info[i];
    v8::Local<v8::Function> cons = Nan::New<v8::Function>(constructor);
    v8::Local<v8::Object> instance = Nan::NewInstance(cons, args.size(), args.data()).ToLocalChecked();
    if (!instance.IsEmpty()) info.GetReturnValue().Set(instance);
    return;
  }

  auto name = Nan::To<v8::String>(info[0]).ToLocalChecked();
  auto person = new Person(*Nan::Utf8String(name));

  person->Wrap(info.This());
}

NAN_METHOD(Person::NewInstance) {
  v8::Isolate* isolate = info.GetIsolate();
  const unsigned argc = info.Length();

  v8::Local<v8::Value> *argv = new v8::Local<v8::Value>[argc];
  for (unsigned int i=0; i<argc; i++) {
    argv[i] = info[i];
  }

  v8::Local<v8::Function> cons = Nan::New<v8::Function>(constructor);
  v8::Local<v8::Object> instance;
  v8::Local<v8::Value> err;
  bool hasException = false;
  {
    Nan::TryCatch tc;
    instance = Nan::NewInstance(cons, argc, argv).ToLocalChecked();
    if (tc.HasCaught()) {
      err = tc.Exception();
      hasException = true;
    }
  }

  if (hasException) {
    isolate->ThrowException(err);
  } else {
    info.GetReturnValue().Set(instance);
  }
  delete [] argv;
  argv = NULL;
}

NAN_METHOD(Person::SayCallback){
  int whatIndex = -1;
  int callbackIndex = -1;

  // 2 args, assume value & callback
  if (info.Length() == 2) {
    whatIndex = 0;
    callbackIndex = 1;
  } else {
    Nan::ThrowTypeError("Wrong arguments");
    return;
  }

  Nan::Callback *callback = NULL;
  if (callbackIndex != -1) {
    callback = new Nan::Callback(info[callbackIndex].As<v8::Function>());
  }

  v8::Local<v8::Object> what = info[whatIndex].As<v8::Object>();
  Person* person = ObjectWrap::Unwrap<Person>(info.Holder());

  SayWorkerCallback *sw = new SayWorkerCallback(callback, person->_name, what);
  Nan::AsyncQueueWorker(sw);
}

NAN_METHOD(Person::Say){
  int whatIndex = -1;

  // only 1 argument expected
  if (info.Length() == 1) {
    whatIndex = 0;
  } else {
    Nan::ThrowTypeError("Wrong arguments");
    return;
  }

  v8::Local<v8::Object> what = info[whatIndex].As<v8::Object>();

  Person* person = ObjectWrap::Unwrap<Person>(info.Holder());

  v8::Local<v8::Promise::Resolver> resolver = v8::Promise::Resolver::New(Nan::GetCurrentContext()).ToLocalChecked();
  Nan::Persistent<v8::Promise::Resolver> *persistent = new Nan::Persistent<v8::Promise::Resolver>(resolver);

  SayWorker *sw = new SayWorker(persistent, person->_name, what);
  Nan::AsyncQueueWorker(sw);

  info.GetReturnValue().Set(resolver->GetPromise());
}
