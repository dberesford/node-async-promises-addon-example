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
