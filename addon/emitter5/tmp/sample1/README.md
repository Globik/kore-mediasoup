# Node.js addon C N-API with a glib loop on a dedicated thread

## Proof of concept.

### ping-pong sample - fake plugin simulation("echo.c") with help of glib ecosystem. Not dynamically loaded.

### run node.js s.js:

```
[sample.c]: Thread with a glib loop created! 0
[sample.c]: Setup Glib.
[echo.c]: Plugin Created!
[echo.c]: Echo Plugin Initialized!
[plugin.c]: Creating plugin result...
[sample.c]: resu->type=> i'm taking my time
[plugin.c]: j_plugin_res_destroy
[echo.c]: Got a message: PING!
[sample.c]: The message came from echo plugin: PONG!
[echo.c]: result of gw->push_event: 0
[helper.c]: Session watchdog started!
[s.js]: Here the message from addon on thread created:  created!
(node:20656) Warning: N-API is an experimental feature and could change at any time.
^C
[sample.c]: Stopping gateway, please wait...
[sample.c]: Ending watchdog loop.
[echo.c]: Entering plugin_message_free.
[echo.c]: No msg or no exit_message.
[echo.c]: Leaving echo plugin!
[echo.c]: Echo plugin destroyd!
[sample.c]: ***Bye!***
[sample.s]: print_to.
[sample.c]: on_uv_close handler.

```
It works. I'm son of a bitch. I did it!