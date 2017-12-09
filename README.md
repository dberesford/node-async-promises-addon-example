# Using Async Promises in native node.js Addons

Small example to demonstrate how to implement promises asynchronously in node.js native c++ addon modules. This addon uses [nan](https://github.com/nodejs/nan) and is targeted at node 8. 

# Example

This addon creates a Person object that has two methods, `say` (which returns a Promise) and also a `sayCallback` that has the same functionality but implemented as a callback for comparison.


```
const person = require('./build/Release/person.node')
const bob = person.create('bob')

async function sayItAsyncAwait () {
  let result

  try {
    result = await bob.say('hello async/await')
  } catch (err) {
    console.error(err)
    throw err
  }

  console.log(result)
}

sayItAsyncAwait()

function sayItPromise () {
  bob.say('hello promise').then(result => {
    console.log(result)
  }).catch(err => {
    console.error(err)
  })
}

sayItPromise()

function sayItCallback () {
  bob.sayCallback('hello callback', function (err, result) {
    if (err) {
      console.error(err)
    } else {
      console.log(result)
    }
  })
}

sayItCallback()

```

# How it works
In short, [SayWorker.cc](https://github.com/dberesford/node-async-promises-addon-example/blob/master/SayWorker.cc) is still a `Nan::AsyncWorker` (as you would do with a [regular callback](https://github.com/dberesford/node-async-promises-addon-example/blob/master/SayWorkerCallback.cc)), but instead of being passed a callback, a `v8::promise` is [passed](https://github.com/dberesford/node-async-promises-addon-example/blob/1ab50a3734b5b8b95a3432030edff41f1b5f0048/SayWorker.cc#L4) instead. This is then resolved in the [`HandleOKCallback`](https://github.com/dberesford/node-async-promises-addon-example/blob/master/SayWorker.cc#L20).

# N-API

[N-API](https://nodejs.org/api/n-api.html) is the successor to NaN for creating native node modules, and has first class support for promises: https://nodejs.org/api/n-api.html#n_api_promises
