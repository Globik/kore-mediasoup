cmd_Release/obj.target/binding/plugin/helper.o := cc '-DNODE_GYP_MODULE_NAME=binding' '-DUSING_UV_SHARED=1' '-DUSING_V8_SHARED=1' '-DV8_DEPRECATION_WARNINGS=1' '-D_LARGEFILE_SOURCE' '-D_FILE_OFFSET_BITS=64' '-DBUILDING_NODE_EXTENSION' -I/home/globik/.node-gyp/9.3.0/include/node -I/home/globik/.node-gyp/9.3.0/src -I/home/globik/.node-gyp/9.3.0/deps/uv/include -I/home/globik/.node-gyp/9.3.0/deps/v8/include -I/home/globik/kore.io_websocket/uv3 -I/home/globik/ee.c/deps/list -I/usr/include/glib-2.0 -I/usr/lib/i386-linux-gnu/glib-2.0/include -I../plugin  -pthread -Wall -Wextra -Wno-unused-parameter -m32 -O3 -fno-omit-frame-pointer  -MMD -MF ./Release/.deps/Release/obj.target/binding/plugin/helper.o.d.raw   -c -o Release/obj.target/binding/plugin/helper.o ../plugin/helper.c
Release/obj.target/binding/plugin/helper.o: ../plugin/helper.c \
 ../plugin/helper.h /usr/include/glib-2.0/glib.h \
 /usr/include/glib-2.0/glib/galloca.h /usr/include/glib-2.0/glib/gtypes.h \
 /usr/lib/i386-linux-gnu/glib-2.0/include/glibconfig.h \
 /usr/include/glib-2.0/glib/gmacros.h \
 /usr/include/glib-2.0/glib/gversionmacros.h \
 /usr/include/glib-2.0/glib/garray.h \
 /usr/include/glib-2.0/glib/gasyncqueue.h \
 /usr/include/glib-2.0/glib/gthread.h \
 /usr/include/glib-2.0/glib/gatomic.h /usr/include/glib-2.0/glib/gerror.h \
 /usr/include/glib-2.0/glib/gquark.h \
 /usr/include/glib-2.0/glib/gbacktrace.h \
 /usr/include/glib-2.0/glib/gbase64.h \
 /usr/include/glib-2.0/glib/gbitlock.h \
 /usr/include/glib-2.0/glib/gbookmarkfile.h \
 /usr/include/glib-2.0/glib/gbytes.h \
 /usr/include/glib-2.0/glib/gcharset.h \
 /usr/include/glib-2.0/glib/gchecksum.h \
 /usr/include/glib-2.0/glib/gconvert.h \
 /usr/include/glib-2.0/glib/gdataset.h /usr/include/glib-2.0/glib/gdate.h \
 /usr/include/glib-2.0/glib/gdatetime.h \
 /usr/include/glib-2.0/glib/gtimezone.h /usr/include/glib-2.0/glib/gdir.h \
 /usr/include/glib-2.0/glib/genviron.h \
 /usr/include/glib-2.0/glib/gfileutils.h \
 /usr/include/glib-2.0/glib/ggettext.h /usr/include/glib-2.0/glib/ghash.h \
 /usr/include/glib-2.0/glib/glist.h /usr/include/glib-2.0/glib/gmem.h \
 /usr/include/glib-2.0/glib/gnode.h /usr/include/glib-2.0/glib/ghmac.h \
 /usr/include/glib-2.0/glib/gchecksum.h \
 /usr/include/glib-2.0/glib/ghook.h \
 /usr/include/glib-2.0/glib/ghostutils.h \
 /usr/include/glib-2.0/glib/giochannel.h \
 /usr/include/glib-2.0/glib/gmain.h /usr/include/glib-2.0/glib/gpoll.h \
 /usr/include/glib-2.0/glib/gslist.h /usr/include/glib-2.0/glib/gstring.h \
 /usr/include/glib-2.0/glib/gunicode.h \
 /usr/include/glib-2.0/glib/gutils.h \
 /usr/include/glib-2.0/glib/gkeyfile.h \
 /usr/include/glib-2.0/glib/gmappedfile.h \
 /usr/include/glib-2.0/glib/gmarkup.h \
 /usr/include/glib-2.0/glib/gmessages.h \
 /usr/include/glib-2.0/glib/goption.h \
 /usr/include/glib-2.0/glib/gpattern.h \
 /usr/include/glib-2.0/glib/gprimes.h /usr/include/glib-2.0/glib/gqsort.h \
 /usr/include/glib-2.0/glib/gqueue.h /usr/include/glib-2.0/glib/grand.h \
 /usr/include/glib-2.0/glib/gregex.h \
 /usr/include/glib-2.0/glib/gscanner.h \
 /usr/include/glib-2.0/glib/gsequence.h \
 /usr/include/glib-2.0/glib/gshell.h /usr/include/glib-2.0/glib/gslice.h \
 /usr/include/glib-2.0/glib/gspawn.h \
 /usr/include/glib-2.0/glib/gstrfuncs.h \
 /usr/include/glib-2.0/glib/gstringchunk.h \
 /usr/include/glib-2.0/glib/gtestutils.h \
 /usr/include/glib-2.0/glib/gthreadpool.h \
 /usr/include/glib-2.0/glib/gtimer.h \
 /usr/include/glib-2.0/glib/gtrashstack.h \
 /usr/include/glib-2.0/glib/gtree.h \
 /usr/include/glib-2.0/glib/gurifuncs.h \
 /usr/include/glib-2.0/glib/gvarianttype.h \
 /usr/include/glib-2.0/glib/gvariant.h \
 /usr/include/glib-2.0/glib/gversion.h \
 /usr/include/glib-2.0/glib/deprecated/gallocator.h \
 /usr/include/glib-2.0/glib/deprecated/gcache.h \
 /usr/include/glib-2.0/glib/deprecated/gcompletion.h \
 /usr/include/glib-2.0/glib/deprecated/gmain.h \
 /usr/include/glib-2.0/glib/deprecated/grel.h \
 /usr/include/glib-2.0/glib/deprecated/gthread.h
../plugin/helper.c:
../plugin/helper.h:
/usr/include/glib-2.0/glib.h:
/usr/include/glib-2.0/glib/galloca.h:
/usr/include/glib-2.0/glib/gtypes.h:
/usr/lib/i386-linux-gnu/glib-2.0/include/glibconfig.h:
/usr/include/glib-2.0/glib/gmacros.h:
/usr/include/glib-2.0/glib/gversionmacros.h:
/usr/include/glib-2.0/glib/garray.h:
/usr/include/glib-2.0/glib/gasyncqueue.h:
/usr/include/glib-2.0/glib/gthread.h:
/usr/include/glib-2.0/glib/gatomic.h:
/usr/include/glib-2.0/glib/gerror.h:
/usr/include/glib-2.0/glib/gquark.h:
/usr/include/glib-2.0/glib/gbacktrace.h:
/usr/include/glib-2.0/glib/gbase64.h:
/usr/include/glib-2.0/glib/gbitlock.h:
/usr/include/glib-2.0/glib/gbookmarkfile.h:
/usr/include/glib-2.0/glib/gbytes.h:
/usr/include/glib-2.0/glib/gcharset.h:
/usr/include/glib-2.0/glib/gchecksum.h:
/usr/include/glib-2.0/glib/gconvert.h:
/usr/include/glib-2.0/glib/gdataset.h:
/usr/include/glib-2.0/glib/gdate.h:
/usr/include/glib-2.0/glib/gdatetime.h:
/usr/include/glib-2.0/glib/gtimezone.h:
/usr/include/glib-2.0/glib/gdir.h:
/usr/include/glib-2.0/glib/genviron.h:
/usr/include/glib-2.0/glib/gfileutils.h:
/usr/include/glib-2.0/glib/ggettext.h:
/usr/include/glib-2.0/glib/ghash.h:
/usr/include/glib-2.0/glib/glist.h:
/usr/include/glib-2.0/glib/gmem.h:
/usr/include/glib-2.0/glib/gnode.h:
/usr/include/glib-2.0/glib/ghmac.h:
/usr/include/glib-2.0/glib/gchecksum.h:
/usr/include/glib-2.0/glib/ghook.h:
/usr/include/glib-2.0/glib/ghostutils.h:
/usr/include/glib-2.0/glib/giochannel.h:
/usr/include/glib-2.0/glib/gmain.h:
/usr/include/glib-2.0/glib/gpoll.h:
/usr/include/glib-2.0/glib/gslist.h:
/usr/include/glib-2.0/glib/gstring.h:
/usr/include/glib-2.0/glib/gunicode.h:
/usr/include/glib-2.0/glib/gutils.h:
/usr/include/glib-2.0/glib/gkeyfile.h:
/usr/include/glib-2.0/glib/gmappedfile.h:
/usr/include/glib-2.0/glib/gmarkup.h:
/usr/include/glib-2.0/glib/gmessages.h:
/usr/include/glib-2.0/glib/goption.h:
/usr/include/glib-2.0/glib/gpattern.h:
/usr/include/glib-2.0/glib/gprimes.h:
/usr/include/glib-2.0/glib/gqsort.h:
/usr/include/glib-2.0/glib/gqueue.h:
/usr/include/glib-2.0/glib/grand.h:
/usr/include/glib-2.0/glib/gregex.h:
/usr/include/glib-2.0/glib/gscanner.h:
/usr/include/glib-2.0/glib/gsequence.h:
/usr/include/glib-2.0/glib/gshell.h:
/usr/include/glib-2.0/glib/gslice.h:
/usr/include/glib-2.0/glib/gspawn.h:
/usr/include/glib-2.0/glib/gstrfuncs.h:
/usr/include/glib-2.0/glib/gstringchunk.h:
/usr/include/glib-2.0/glib/gtestutils.h:
/usr/include/glib-2.0/glib/gthreadpool.h:
/usr/include/glib-2.0/glib/gtimer.h:
/usr/include/glib-2.0/glib/gtrashstack.h:
/usr/include/glib-2.0/glib/gtree.h:
/usr/include/glib-2.0/glib/gurifuncs.h:
/usr/include/glib-2.0/glib/gvarianttype.h:
/usr/include/glib-2.0/glib/gvariant.h:
/usr/include/glib-2.0/glib/gversion.h:
/usr/include/glib-2.0/glib/deprecated/gallocator.h:
/usr/include/glib-2.0/glib/deprecated/gcache.h:
/usr/include/glib-2.0/glib/deprecated/gcompletion.h:
/usr/include/glib-2.0/glib/deprecated/gmain.h:
/usr/include/glib-2.0/glib/deprecated/grel.h:
/usr/include/glib-2.0/glib/deprecated/gthread.h:
