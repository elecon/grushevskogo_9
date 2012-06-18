#!/bin/sh
git describe --tags --dirty | awk '{split($0,Name,"-g"); split(Name[2],Dirt,"-"); if ( Dirt[2] ) { diff1="+"; } r=Name[1] diff1; print(r);}'
