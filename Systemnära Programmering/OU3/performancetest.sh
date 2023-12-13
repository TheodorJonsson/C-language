#!/usr/bin/bash
for i in {1..10};
do
    echo -e "\nIteration $i"
    time {
        ./mdu -j$i /pkg
    }
done