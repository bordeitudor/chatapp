CLIENT_SUBDIR := client
SERVER_SUBDIR := server

client:
	make --directory=$(CLIENT_SUBDIR)

server:
	make --directory=$(SERVER_SUBDIR)

all: client server
