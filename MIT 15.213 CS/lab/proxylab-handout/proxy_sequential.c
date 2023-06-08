#include "csapp.h"


/* Recommended max cache and object sizes */
#define MAX_CACHE_SIZE 1049000
#define MAX_OBJECT_SIZE 102400
#define WEB_PREFIX "http://"

/* You won't lose style points for including this long line in your code */
static const char *user_agent_hdr = "User-Agent: Mozilla/5.0 (X11; Linux x86_64; rv:10.0.3) Gecko/20120305 Firefox/10.0.3\r\n";


void proxyerror(int fd, char *cause, char *errnum,
        char *shortmsg, char *longmsg);
void handleRequest(int fd);
int parseRequest(char *buf, char *method, char *uri, char *version,
                char *host, char *port, char *filename);
void forwardRequest(int serverfd, rio_t *rio_client, char *host, char *filename);



int main(int argc, char **argv) {
    struct sockaddr_storage clientaddr;
    char hostname[MAXLINE], port[MAXLINE];
    
    if (argc != 2) {
        fprintf(stderr, "usage: %s <port>\n", argv[0]);
        exit(1);
    }

    int listenfd = Open_listenfd(argv[1]);
    while (1) {
        socklen_t clientlen = sizeof(clientaddr);
        int connfd = Accept(listenfd, (SA *) &clientaddr, &clientlen);
        Getnameinfo((SA *) &clientaddr, clientlen, hostname, MAXLINE,
                    port, MAXLINE, 0);
        printf("proxy: Accepted connect from (%s, %s)\n", hostname, port);
        handleRequest(connfd);
    }
}

void handleRequest(int fd) {
    char buf[MAXLINE], method[MAXLINE], uri[MAXLINE], version[MAXLINE];
    char host[MAXLINE], port[MAXLINE], filename[MAXLINE];
    rio_t rio_client, rio_server;

    
    Rio_readinitb(&rio_client, fd);
    if (Rio_readlineb(&rio_client, buf, MAXLINE) == 0) {
        printf("empty request\n");
        return;
    }

    // parse request
    if (parseRequest(buf, method, uri, version, host, port, filename) < 0) {
        proxyerror(fd, method, "400", "Bad Request",
                    "Proxy cannot understand this request");
        return;
    }

    // forward request
    int serverfd = Open_clientfd(host, port);
    forwardRequest(serverfd, &rio_client, host, filename);

    // receive response from server and forward to client
    Rio_readinitb(&rio_server, serverfd);
    int n;
    while ((n = Rio_readnb(&rio_server, buf, MAXLINE)) != 0) {
        Rio_writen(fd, buf, n);
    }

    // close connection
    Close(serverfd);
    Close(fd);
}


int parseRequest(char *buf, char *method, char *uri, char *version,
                char *host, char *port, char *filename) {
    char *prefix;
    char *hostp, *slash, *colon;
    
    sscanf(buf, "%s %s %s", method, uri, version);
    if (strcasecmp(method, "GET"))
        return -1;
    if ((prefix = strstr(uri, WEB_PREFIX)) == NULL)
        return -1;
    hostp = prefix + strlen(WEB_PREFIX);
    slash = strchr(hostp, '/');
    colon = strchr(hostp, ':');
    if (slash == NULL) {
        slash = hostp + strlen(hostp);
    }
    if (colon == NULL || colon > slash) {
        strcpy(port, "80");
    } else {
        *slash = '\0';
        strcpy(port, colon + 1);
    }
    *colon = '\0';
    strcpy(host, hostp);
    *slash = '/';
    strcpy(filename, slash);
    printf("proxy: host = %s, port = %s, filename = %s\n", host, port, filename);
    return 0;
}

void forwardRequest(int serverfd, rio_t *rio_client, char *host, char *filename)
{
    char buf[MAXLINE];
    ssize_t n;

    // send request to server
    sprintf(buf, "GET %s HTTP/1.0\r\n", filename);
    Rio_writen(serverfd, buf, strlen(buf));
    while ((n = Rio_readlineb(rio_client, buf, MAXLINE)) != 0) {
        if (strcmp(buf, "\r\n") == 0)
            break;
        if (strstr(buf, "Host:")) {
            sprintf(buf, "Host: %s\r\n", host);
        }
        if (strstr(buf, "User-Agent:")) {
            sprintf(buf, "User-Agent: %s\r\n", user_agent_hdr);
        }
        if (strstr(buf, "Connection:")) {
            sprintf(buf, "Connection: close\r\n");
        }
        if (strstr(buf, "Proxy-Connection:")) {
            sprintf(buf, "Proxy-Connection: close\r\n");
        }
        Rio_writen(serverfd, buf, strlen(buf));
    }
    Rio_writen(serverfd, "\r\n", 2);

}

void proxyerror(int fd, char *cause, char *errnum,
        char *shortmsg, char *longmsg)
{
    char buf[MAXLINE];

    /* Print the HTTP respone headers */
    sprintf(buf, "HTTP/1.0 %s %s\r\n", errnum, shortmsg);
    Rio_writen(fd, buf, strlen(buf));
    sprintf(buf, "Content-type: text/html\r\n\r\n");
    Rio_writen(fd, buf, strlen(buf));

    /* Print the HTTP respone body */
    sprintf(buf, "<html><title>Proxy Error</title>");
    Rio_writen(fd, buf, strlen(buf));
    sprintf(buf, "<body bgcolor=""ffffff"">\r\n");
    Rio_writen(fd, buf, strlen(buf));
    sprintf(buf, "%s: %s\r\n", errnum, shortmsg);
    Rio_writen(fd, buf, strlen(buf));
}