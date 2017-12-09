const test = require('tap').test
const person = require('../build/Release/person.node')

test('promise test', function (t) {
  const bob = person.create('bob')

  bob.say('hello')
    .then(result => {
      t.equal('bob says hello', result)
      t.end()
    })
    .catch(err => {
      t.fail(err)
    })
})

test('async/await test', async function (t) {
  const bob = person.create('bob')
  let result

  try {
    result = await bob.say('hello')
  } catch (err) {
    t.fail(err)
  }

  t.equal('bob says hello', result)
  t.end()
})

test('callback test', function (t) {
  const bob = person.create('bob')
  bob.sayCallback('hello', function (err, result) {
    t.ok(!err)
    t.equal('bob says hello', result)
    t.end()
  })
})
