#ifndef SayWorker_H
#define SayWorker_H

#include <nan.h>

class SayWorker : public Nan::AsyncWorker {
 public:
  SayWorker(Nan::Persistent<v8::Promise::Resolver> *persistent, std::string name, v8::Local<v8::Object> &whatObj);
  ~SayWorker();
  virtual void Execute();
  virtual void HandleOKCallback ();

 private:
  std::string _name;
  std::string _what;
  std::string _result;
  Nan::Persistent<v8::Promise::Resolver> *_persistent;
};

#endif  // SayWorker_H
