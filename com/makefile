INC = -I ./channel -I .
INC_CPPJSON=-I /home/globik/.local/share/Trash/files/deps.2/jsoncpp/jsoncpp/include
I=$(INC) $(INC_CPPJSON)
a: Notifier.cpp
	g++ -std=c++11 $(I) -c Notifier.cpp
b: Request.cpp
	g++ -std=c++11 $(I) -c Request.cpp