## Emit some event from a C-addon(n-api).

Inspired from from [https://github.com/NickNaso/addon-event-emitter](https://github.com/NickNaso/addon-event-emitter)

```
OK in a number of argc. A single argument as expected: 1
OK, args[0] is a function.
args[1] is undefined.
On "start" event occured.
should be some string data: 
'Some data string came from a n-api addon in plain C, ***!'
napi_status is OK! Event fired!
(node:22362) Warning: N-API is an experimental feature and could change at any time.

```

## ldd binding.node

```
	linux-gate.so.1 =>  (0xb7777000)
	libc.so.6 => /lib/i386-linux-gnu/libc.so.6 (0xb75a5000)
	/lib/ld-linux.so.2 (0xb7778000)
	
```