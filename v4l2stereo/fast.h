/*
 FAST corner detection
 Based upon code originally written by Ed Rosten
 Copyright (C) 2009 Bob Mottram and Giacomo Spigler
 fuzzgun@gmail.com

 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fstream>
#include <math.h>

#ifndef FAST_H_
#define FAST_H_

#define FAST_MAX_CORNERS 8192
#define FAST_MAX_CORNERS_PREVIOUS 200
#define FAST_MAX_IMAGE_HEIGHT 1024
#define FAST_IMAGE_SCALES 3
#define Compare(X, Y) ((X)>=(Y))

typedef struct { int x, y; } xy;

class fast {
private:
	int corner_score(unsigned char* p, int* pixel, int bstart);
	void detect(unsigned char* im, int xsize, int ysize, int stride, int b, int* ret_num_corners);
	void score(unsigned char* i, int stride, xy* corners, int num_corners, int b);
	void detect_nonmax(unsigned char* im, int xsize, int ysize, int stride, int b, int* ret_num_corners);
	void nonmax_suppression(xy* corners, int* scores, int num_corners);
	void make_offsets(int* pixel, int row_stride);
	void data_association(unsigned char* img_mono, int img_width, int img_height, int current_no_of_corners, xy* current_corners, int prev_no_of_corners, xy* prev_corners, unsigned char* matches, int max_disparity, int temporal);

	int previous_no_of_corners;
	xy* previous_corners;
	xy* corners;
	xy* nonmax;
	int* scores;
	int num_nonmax;
	int* row_start;
	unsigned char* img_mono;
	unsigned char* prev_img_mono;
	int threshold;
	unsigned char* temporal_matches;
	unsigned char* interocular_matches;

public:
	void show(unsigned char *outbuf, int img_width, int img_height);
	int update(unsigned char* img, int img_width, int img_height, int desired_features);
	void save(std::string filename);
	void match_interocular(int img_width, int img_height, int no_of_corners_right, int* corners_right, int max_disparity);
	int get_no_of_corners();
	int* get_corners();

	fast();
	virtual ~fast();
};

#endif /* FAST_H_ */
