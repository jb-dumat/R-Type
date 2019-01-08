#!/bin/sh

if echo "$0" | grep -q "scripts"
then
    rm -rf build && rm -rf r-type_server r-type_client
else
    rm -rf ../build && rm -rf ../r-type_server ../r-type_client
fi
