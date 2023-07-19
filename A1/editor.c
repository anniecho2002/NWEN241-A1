#include <stdio.h>
#include <string.h>
#include "editor.h"


/**
 * Task One
 * */
int editor_insert_char(char editing_buffer[], int editing_buflen, char to_insert, int pos){
	int value = 0;
	char prev = to_insert;
	char curr;
	for(int i = pos; i < editing_buflen; i++){
		curr = editing_buffer[i];
		editing_buffer[i] = prev;
		prev = curr;
		value = 1;
	}
	return value;
}


/**
 * Task Two
 * starts at the offset and continues until it finds the first instance of to_delete
 * removes that first instance
 * moves the one ahead of it into the empty space behind
 * changes last value to empty
 * 
 * */

int editor_delete_char(char editing_buffer[], int editing_buflen, char to_delete, int offset){
	int found = 0;
	for(int i = offset; i < editing_buflen - 1; i++){
		if(found == 0 && editing_buffer[i] == to_delete){
			found = 1;
			editing_buffer[i] = editing_buffer[i+1]; // changes first instance it to the one on its right
		}
		else if(found == 1){
			editing_buffer[i] = editing_buffer[i+1];
		}
	}
	if(found == 1){ editing_buffer[editing_buflen - 1] = '\0'; }
	return found;
}




/**
 * Task Three
 * to do: replace the first instance of str with replacement, starting at the offset, adjust the array accordingly (add null/remove excess if less/more)
 * if str is empty, regardless the value of replacement, then nothing should occur
 * if replacement is empty, this is essentially just deleting the str 
 * 
 * */
int editor_replace_str(char editing_buffer[], int editing_buflen, const char *str, const char *replacement, int offset){
	
	int value = -1;
	int str_len = strlen(str);
	int rep_len = strlen(replacement);
	if(str_len == 0){ return value; }
	
	
	int len_diff = 0;
	if(str_len > rep_len){ len_diff = str_len - rep_len; }
	else if(rep_len > str_len){ len_diff = rep_len - str_len; }
	
	
	// go through the editing buffer to find the word
	for(int i = offset; i < editing_buflen; i++){
		
		// if the current editing buffer matches the first letter then check rest of word
		if(editing_buffer[i] == str[0]){
	
			int found = 1;
			for(int check = i; check < i + str_len; check++){
				if(editing_buffer[check] != str[check - i]){
					found = 0;
					break;
				}
			}
			
			
			if(found == 1){
				if(str_len > rep_len){ // move all the characters to the lefts
					int start_shift = i + rep_len;
					for(int j = 0; j < len_diff; j++){
						for(int k = start_shift; k < editing_buflen - 1; k++){ editing_buffer[k] = editing_buffer[k+1]; }
						editing_buffer[editing_buflen - 1] = '\0'; // add null value on end after shifting left
					}
				}
				else if(rep_len > str_len){
					// move all the characters to the right
					int start_shift = i + str_len; // start shifting at first letter + str length by difference
					for(int j = 0; j < len_diff; j++){
						for(int k = editing_buflen - 1; k > start_shift; k--){ editing_buffer[k] = editing_buffer[k - 1]; }
					}
				}

				// after all the surrounding letters have been shifted, put replacement into the editing_buffer
				for(int rep = i; rep < i + rep_len; rep++){ editing_buffer[rep] = replacement[rep - i];	}
				value = i + rep_len - 1;
				if(value > editing_buflen){ value = editing_buflen - 1;}
				break;
			}
		}
	}
	return value;
}


/**
 * Task Four
 * for each letter in the editing buffer, move it into the viewing buffer
 * if it's wrap, then don't start a new line until the '\n' symbol
 * otherwise if the current word that you are on does not fit, then put onto a new line
 * 
 * */
void editor_view(int rows, int cols, char viewing_buffer[rows][cols], const char editing_buffer[], int editing_buflen, int wrap){
	
	for(int row = 0; row < rows; row++){
		for(int col = 0; col < cols - 1; col++){
			viewing_buffer[row][col] = '\0';
		}
	}	
	
	int row = 0;
	int col = 0;
	
	// iterate through the editing buffer
	for(int count = 0; count < editing_buflen; count++){
		if(editing_buffer[count] == '\n'){
			col = 0; // sets the col back to the start
			row++;   // moves to the next row
		}
		else{
			viewing_buffer[row][col] = editing_buffer[count];
			if(col == cols - 2){
				if(wrap == 0){
					while(editing_buffer[count] != '\n'){ count++; } // discard everything that is not needed
				}
				// makes a new line in the viewing buffer (for wrap: after the '\n' symbol, non-wrap: when it is at the end)
				col = 0;
				row++; 
			}
			else{
				col++; // continue adding into the viewing buffer
			}
		}
	}
}





