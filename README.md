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
In short, SayWorker.cc is still a `Nan::AsyncWorker`, but instead of being passed a callback, . `v8::promise` is passed instead. This is then resolved in the `HandleOKCallback`.

# N-API

N-API is the successor to NaN for creating native node modules. N-API has first class support for promises: https://nodejs.org/api/n-api.html#n_api_promises
