#!/bin/bash
g++ echo_test_server.cpp -c -g -o echo_test_server.o
g++ echo_test_server.o -o echo_test_server -levent -lpthread

g++ echo_test_client.cpp -c -g -o echo_test_client.o
g++ echo_test_client.o -o echo_test_client -levent -lpthread

