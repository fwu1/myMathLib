//
//  nngreqrep.c
//  myMathLib
//
//  Created by Samuel Wu on 1/16/19.
//  Copyright © 2019 Samuel Wu. All rights reserved.
//
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include "nngreqrep.h"

#include <nng/nng.h>
#include <nng/protocol/reqrep0/rep.h>
#include <nng/protocol/reqrep0/req.h>

#define NODE0 "node0"
#define NODE1 "node1"
#define DATE "DATE"

void
fatal(const char *func, int rv)
{
    fprintf(stderr, "%s: %s\n", func, nng_strerror(rv));
    exit(1);
}

char errMsg[300];
char dateMsg[300];

char * fatalMessage(const char *func, int rv)
{
    snprintf(errMsg,300, "%s: %s\n", func, nng_strerror(rv));
    return errMsg;
}

char *
date(void)
{
    time_t now = time(&now);
    struct tm *info = localtime(&now);
    char *text = asctime(info);
    text[strlen(text)-1] = '\0'; // remove '\n'
    return (text);
}

int
node0(const char *url)
{
    nng_socket sock;
    int rv;
    
    if ((rv = nng_rep0_open(&sock)) != 0) {
        fatal("nng_rep0_open", rv);
    }
    if ((rv = nng_listen(sock, url, NULL, 0)) != 0) {
        fatal("nng_listen", rv);
    }
    for (;;) {
        char *buf = NULL;
        size_t sz;
        if ((rv = nng_recv(sock, &buf, &sz, NNG_FLAG_ALLOC)) != 0) {
            fatal("nng_recv", rv);
        }
        if ((sz == (strlen(DATE) + 1)) && (strcmp(DATE, buf) == 0)) {
            printf("NODE0: RECEIVED DATE REQUEST\n");
            char *d = date();
            printf("NODE0: SENDING DATE %s\n", d);
            if ((rv = nng_send(sock, d, strlen(d) + 1, 0)) != 0) {
                fatal("nng_send", rv);
            }
        }
        nng_free(buf, sz);
    }
    return 0;
}

char *
node1(const char *url)
{
    nng_socket sock;
    int rv;
    size_t sz;
    char *buf = NULL;
    
    if ((rv = nng_req0_open(&sock)) != 0) {
        return fatalMessage("nng_socket", rv);
    }
    if ((rv = nng_dial(sock, url, NULL, 0)) != 0) {
        return fatalMessage("nng_dial", rv);
    }
    printf("NODE1: SENDING DATE REQUEST %s\n", DATE);
    if ((rv = nng_send(sock, DATE, strlen(DATE)+1, 0)) != 0) {
        return fatalMessage("nng_send", rv);
    }
    if ((rv = nng_recv(sock, &buf, &sz, NNG_FLAG_ALLOC)) != 0) {
        return fatalMessage("nng_recv", rv);
    }
    printf("NODE1: RECEIVED DATE %s\n", buf);
    strncpy(dateMsg,buf,(sz<300)?sz:299);
    nng_free(buf, sz);
    nng_close(sock);
  
    return dateMsg;
}

int reqNode(char* name, char * value)
{
    if (strcmp(NODE0, name) == 0)
        return (node0(value));

    if (strcmp(NODE1, name) == 0)
        return (node1(value));

    return (1);
}

