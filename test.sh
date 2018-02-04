#!/bin/bash

for f in $(ls input); do
  bin/bf input/$f > tmp/$f
  if diff tmp/$f output/$f ; then
    echo ok
  else
    echo ng
  fi
done
