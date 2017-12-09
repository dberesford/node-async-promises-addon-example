#ifndef SayWorkerCallback_H
#define SayWorkerCallback_H

#include <nan.h>

class SayWorkerCallback : public Nan::AsyncWorker {
 public:
  SayWorkerCallback(Nan::Callback *callback, std::string name, v8::Local<v8::Object> &whatObj);
  ~SayWorkerCallback();
  virtual void Execute();
  virtual void HandleOKCallback ();

 private:
  std::string _name;
  std::string _what;
  std::string _result;
};

#endif  // SayWorkerCallback_H
