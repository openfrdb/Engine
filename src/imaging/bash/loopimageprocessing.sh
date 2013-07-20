/*
 * Copyright (c) 2013. David Thomson jdavidthomson<at>hotmail<dot>com
 * Released to public domain under terms of the BSD Simplified license.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *   * Neither the name of the organization nor the names of its contributors
 *     may be used to endorse or promote products derived from this software
 *     without specific prior written permission.
 *
 *   See <http://www.opensource.org/licenses/bsd-license>
 */

#!/bin/bash

shopt -s nullglob

i=1

for f in *.jpg
do
	imageprocessing_witheyes haarcascade_frontalface_alt2.xml haarcascade_eye_tree_eyeglasses.xml haarcascade_mcs_mouth.xml "$f"
	if [ -e face_0.jpg ]; then 
		mv face_0.jpg image_"$i".jpg
		let "i+=1"
	fi
done
