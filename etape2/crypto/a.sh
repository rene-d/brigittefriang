#!/bin/sh

openssl aes-256-ecb -e -in getfiles.sh -K $1 | openssl aes-256-ecb -d -K $2
