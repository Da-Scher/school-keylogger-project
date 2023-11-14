#include <stdio.h>
#include <strings.h>
#include <netdb.h>
#include <sockets.h>
#include <arpa/net.h>
#include <unistd.h>

int main() {
  int socketfd, err;
  int connectfd;
  struct addrinfo hints, *actualdata;
  struct sockaddr_in clientaddr;
  socklen_t clientaddrlen;

  hints.ai_family = AF_INET;
  hints.ai_socktype = SOCK_STREAM;

  err = getaddrinfo(ADDRESS, PORT, &hints, &actualdata);
  socketfd = socket();
}
