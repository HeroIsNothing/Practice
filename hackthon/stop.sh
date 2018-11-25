#!/bin/bash
pid=`ps -ef | grep minicom | grep -v grep | grep -v vi | awk '{print $2}'`
kill -9 $pid
