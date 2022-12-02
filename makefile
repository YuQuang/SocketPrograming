GCC 		 := g++
DEPENDENCIES := -lws2_32
CLIENTREXE	 := client.exe
SERVEREXE	 := server.exe

$(SERVEREXE): server.cpp
	$(GCC) server.cpp $(DEPENDENCIES) -o $(SERVEREXE)

$(CLIENTREXE): client.cpp
	$(GCC) client.cpp $(DEPENDENCIES) -o $(CLIENTREXE)

runServer: $(SERVEREXE)
	./$(SERVEREXE)

runClient: $(CLIENTREXE)
	./$(CLIENTREXE)