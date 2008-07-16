#!/bin/sh
#script to sign xpi files first argument is private key second is file
openssl dgst -sha1 -sign $1 $2 | openssl enc -base64
