# "/home/globik/kore.io_websocket/uv3","/home/globik/ee.c/deps/list"
# "-Wl,-rpath /home/globik/kore.io_websocket/uv3 -L /home/globik/kore.io_websocket/uv3 -luv_callback","-lee",
# /home/globik/kore-mediasoup/addon/emitter5/sample2/plugin/libecho.so
{
"targets":[{"target_name":"binding","sources":["sample2.c","helper.c"],"cflags":["-fpic"],
"include_dirs":["/usr/include/glib-2.0", "/usr/lib/i386-linux-gnu/glib-2.0/include","./","./plugin"],
"libraries":["-Wl,-rpath /home/globik/kore-mediasoup/addon/emitter5/sample2/plugin -L /home/globik/kore-mediasoup/addon/emitter5/sample2/plugin -lecho","-lglib-2.0","-pthread","-ldl"]
}]
}