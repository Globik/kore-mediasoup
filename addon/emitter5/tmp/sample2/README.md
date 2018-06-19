# Node.js addon C N-API with a glib loop on a dedicated thread

## Proof of concept.

### echo test sample - fake plugin simulation("echo.c") with help of glib ecosystem. Not dynamically loaded.

### run node.js s.js:

```
[../sample1.c]: Thread with a glib loop created! 0
[sample1.c]: Setup Glib.
[echo.c]: Plugin Created!
[helper.c]: Session watchdog started!
[echo.c]: Echo Plugin Initialized!
[s.js]: Here the message from addon on thread created:  created!
[s.js]: from addon on_msg (d):  on_msg_prepare
[sample1.c]: write_start leni: 11
[plugin.c]: Creating plugin result...
[sample1.c]: resu->type=> i'm taking my time
[plugin.c]: j_plugin_res_destroy
[sample1.c]: write start is OK? 0
[echo.c]: Got a message: Hali hallo!
[sample1.c]: The message came from echo plugin: Hali hallo!
[echo.c]: result of gw->push_event: 0
[s.js]: from addon p_send:  null write_result
(node:11080) Warning: N-API is an experimental feature and could change at any time.
[sample.s]: print_to.
[sample1.c]: h->data: 0xb747348, Hali hallo!
[sample1.c]: on_msg_cb
[s.js]: from addon on_msg (d):  Hali hallo!
[s.js]: TIMEOUT. STOPING RIGHT NOW
[sample1.c]: addon_cleanup()
[sample1.c]: gloop_init_success: 1

[sample1.c]: Stopping gateway, please wait...
[sample1.c]: del_ref msgCb is OK.
[s.js]: from addon p_close:  close_result
[sample1.c]: Ending watchdog loop.
[echo.c]: Entering plugin_message_free.
[echo.c]: No msg or no exit_message.
[echo.c]: Leaving echo plugin!
[echo.c]: Echo plugin destroyd!
[sample1.c]: ***Bye!***
[sample1.c]: a on exit 0
[sample.s]: print_to.
[sample1.c]: h->data: 0xb76fadd1, exit
[sample1.c]: on_msg_cb
[sample1.c]: msgEnv is NULL.
[sample1.c]: EXIT!
[sample.c]: on_uv_close handler.


```