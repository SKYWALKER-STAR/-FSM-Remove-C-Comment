/*****************************************************************************
Copyright 2022 - 2029 Ming, <1546274931@qq.com>
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

This program is a complementaion of FSM used to remove comment using
\/\* \*\/ in c progarm. 

This program can not remove single row comment which use symbol '//'

build:
	cc -o remove_comment remove_comment.c
enviroment:
	gcc 9.4.0
	x86_64 
	Ubuntu 20.04.1
	GNU/Linux

*****************************************************************************/

#include <stdio.h>
#include <stdlib.h>

int main(int argc,char **argv)
{
	
	if (argc < 2) {
		fprintf(stderr,
		"Usage : <program> <input C source file with comment>\n");
		exit(-1);
	}
	char c;
	int state;
	FILE *fp = fopen(argv[1],"r");
	state = 0;
	while ((c = fgetc(fp)) != EOF) {
		switch (state) {
		case 0:
			switch(c){
			case '/' : state = 1;			break;
			case '*' : state = 0; printf("%c",c);	break;
			case '"' : state = 4; printf("%c",c);	break;
			default	 : state = 0; printf("%c",c);	break;
			};					break;
		case 1:
			switch(c){
			case '/' : state = 1; printf("/%c",c);	break;
			case '*' : state = 2;			break;
			default	 : printf("%c",c);		break;
			};					break;
		case 2:
			switch(c){
			case '*' : state = 3;			break;
			default	 : state = 2;			break;
			};					break;
		case 3:
			switch(c){
			case '/' : state = 0;			break;
			default  : state = 3;			break;
			};					break;
		case 4:
			switch(c){
			case '"' : state = 0; printf("%c",c);	break;
			default	 : state = 4; printf("%c",c);	break;
			};					break;
		}
	}
}
