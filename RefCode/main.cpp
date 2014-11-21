//REFERENCE http://beej.us/guide/bgnet/output/html/singlepage/bgnet.html
//SAMPLE http://coding.debuntu.org/c-linux-socket-programming-tcp-simple-http-client

//HOW TO RESUME http://stackoverflow.com/a/3428963

#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
#include <thread>
#include <iostream>
#include <fstream>


int create_tcp_socket();
addrinfo* get_addrinfo(char* host, char *port);
char *build_get_query(char *host, char *page);
int VROOM();

#define HOST "tastycocoabytes.com";
#define PAGE "_downloads/CPA_131.dmg"
#define PORT "80"
#define USERAGENT "HTMLGET 1.0"
size_t MY_BUFF = 2048;

int main(int argc, char *argv[])
{
    fprintf(stderr, "Application Running at: %s\n", argv[0]);
    std::thread download(VROOM);
    download.join();


    printf("Exiting...");
}

int VROOM()
{
//    std::ofstream myfile;
//    myfile.open ("/Users/qgil/robotium-solo-5.2.1.jar", std::ios::out | std::ios::binary);
    FILE* pFile;
    pFile = fopen("/Users/qgil/robotium-solo-5.2.1.jar2", "wb");

    addrinfo *remote, *p;
    int sockfd;
    size_t tmpres;
    char *get;
    char buf[MY_BUFF+1];
    char *host = HOST;
    char *page = PAGE;

    sockfd = create_tcp_socket();// Simple socket creation call to the method below

    remote = get_addrinfo(host, PORT);

    // loop through all the results and connect to the first we can
    for(p = remote; p != NULL; p = p->ai_next)
    {
        if ((sockfd = socket(p->ai_family, p->ai_socktype,
                p->ai_protocol)) == -1)
        {
            perror("client: socket");
            continue;
        }

        if (connect(sockfd, p->ai_addr, p->ai_addrlen) == -1)
        {
            close(sockfd);
            perror("client: connect");
            continue;
        }

        break;
    }

    if (p == NULL)
    {
        fprintf(stderr, "client: failed to connect\n");
        return 2;
    }

    get = build_get_query(host, page);
    fprintf(stderr, "Query is:\n<<START>>\n%s<<END>>\n", get);

    //Send the query to the server
    int sent = 0;
    while(sent < strlen(get))
    {
        tmpres = send(sockfd, get+sent, strlen(get)-sent, 0);
        if(tmpres == -1)
        {
            perror("Can't send query");
            exit(1);
        }
        sent += tmpres;
    }
    //now it is time to receive the page
    memset(buf, 0, sizeof(buf));
    int htmlstart = 0;
    char *htmlcontent;
    int totSize = 0;
    while((tmpres = recv(sockfd, buf, MY_BUFF, 0)) > 0){
        if(htmlstart == 0)
        {
            /* Under certain conditions this will not work.
            * If the \r\n\r\n part is splitted into two messages
            * it will fail to detect the beginning of HTML content
            */
            htmlcontent = strstr(buf, "\r\n\r\n");
            if(htmlcontent != NULL){
                htmlstart = 1;
                htmlcontent += 4;//Moves past \r\n\r\n
                fwrite(buf, sizeof(char), (htmlcontent - buf), stdout);
                tmpres -= htmlcontent-buf;
            }
        }else{
            htmlcontent = buf;
        }
        if(htmlstart)
        {
            fwrite(htmlcontent, sizeof(char), tmpres, pFile);
            totSize += tmpres;
        }
        memset(buf, 0, tmpres);
    }

    fprintf(stdout, "TotalSize Downloaded:%d\n",totSize);
    if(tmpres < 0)
    {
        perror("Error receiving data");
    }
    //fprintf(stdout, "pre free(get);\n");
    free(get);
    //fprintf(stdout, "pre free(remote);\n");
    free(remote);
    //fprintf(stdout, "pre close(sockfd);\n");
    close(sockfd);
    //fprintf(stdout, "prefile-close\n");
    std::fclose(pFile);


//    fprintf(stdout, "Exiting thread in 5\n");;
//    std::this_thread::sleep_for (std::chrono::seconds(1));
//    fprintf(stdout, "Exiting thread in 4\n");
//    std::this_thread::sleep_for (std::chrono::seconds(1));
//    fprintf(stdout, "Exiting thread in 3\n");
//    std::this_thread::sleep_for (std::chrono::seconds(1));
//    fprintf(stdout, "Exiting thread in 2\n");
//    std::this_thread::sleep_for (std::chrono::seconds(1));
//    fprintf(stdout, "Exiting thread in 0\n");

    fprintf(stdout, "Exiting successfully\n");
    return 0;
}

int create_tcp_socket()
{
    int sock;
    if((sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
    {
        perror("Can't create TCP socket");
        exit(1);
    }
    return sock;
}

addrinfo* get_addrinfo(char* host, char *port)
{

    int status;
    struct addrinfo hints;
    struct addrinfo *servinfo;  // will point to the results

    memset(&hints, 0, sizeof hints); // make sure the struct is empty
    hints.ai_family = AF_UNSPEC;     // don't care IPv4 or IPv6
    hints.ai_socktype = SOCK_STREAM; // TCP stream sockets


    if((status = getaddrinfo(host, port, &hints, &servinfo)) != 0)
    {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(status));
        return NULL;
    }

    return servinfo;
}

char *build_get_query(char *host, char *page)
{
    char *query;
    char *getpage = page;
    char *tpl = "GET /%s HTTP/1.0\r\nHost: %s\r\nUser-Agent: %s\r\nRange: bytes=7250000-7256087\r\n\r\n";//

    if(getpage[0] == '/')
    {
        getpage = getpage + 1;
        fprintf(stderr,"Removing leading \"/\", converting %s to %s\n", page, getpage);
    }
    // -5 is to consider the %s %s %s in tpl and the ending \0
    query = (char *)malloc(strlen(host)+strlen(getpage)+strlen(USERAGENT)+strlen(tpl)-5);
    sprintf(query, tpl, getpage, host, USERAGENT);
    return query;
}