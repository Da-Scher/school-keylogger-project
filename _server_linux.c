#include "iterativeserver.h"
#define FIRSTPORT "45898"
#define ADDRESS "localhost"

int main() {
  int socketfd, err;
  struct addrinfo hints, *actualdata;
  struct sockaddr_in *serveaddr;
  socklen_t serveaddrlen;
  
  hints.ai_family = AF_INET;
  hints.ai_socktype = SOCK_STREAM;
  err = getaddrinfo(ADDRESS, FIRSTPORT, &hints, &actualdata);

  socketfd = socket(actualdata->ai_family, actualdata->ai_socktype, 0);
  serveaddr = (struct sockaddr_in*)(actualdata->ai_addr);
  serveaddrlen = actualdata->ai_addrlen;

  bind(socketfd, serveaddr, serveaddrlen);

  int listenfd = listen(socketfd, 1);

  while(1) {
    int acceptfd = accept(socketfd, serveaddr, serveaddrlen);
    write(acceptfd, /*char buffer address which holds the payload*/, /*buffer length*/);
    close(acceptfd);
  }

  close(listenfd);
  close(socketfd);
}
