/*Anastasia Young ICS4U November 1, 2018, Mrs. Cullum


This program simulates a RPN Calculator. The uses uses
the Allegro GUI to input number into the calculator
which get stored in a stack. This stack is made up of
an APVECTOR. The user can add, subtract, divide or
multiply the numbers together. The calculator shows the
top two values in the stack. */

#include <iostream>
#include <sstream>
#include <apstring.h>
#include <cstring>
#include <apstring.cpp>
#include "MyStack.h"
#include "Claculator.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

#define COLUMN_MULTIPLIER 91
#define ROW_MULTIPLIER 60

const int SCREEN_W = 500;       // screen width
const int SCREEN_H = 700;       // screen height
const int BOUNCER_SIZE = 32;

ALLEGRO_DISPLAY *display;

using namespace std;

//This function registers the user's mouse click and returns the number they chose on the keypad(or operator)
char getKey(int &charRow, int &charColumn, apstring characters){

    float bouncer_x = 0;
	float bouncer_y = 0;
    ALLEGRO_EVENT_QUEUE *event_queue = NULL;
    char temp;

    //enables finding mouse click coordinates
	event_queue = al_create_event_queue();
	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_mouse_event_source());

    ALLEGRO_EVENT ev;
    ev.type = ALLEGRO_EVENT_MOUSE_ENTER_DISPLAY;

    //wait for event until the mouse is clicked
    while(ev.type != ALLEGRO_EVENT_MOUSE_BUTTON_UP){
        al_wait_for_event(event_queue, &ev);
    }

    bouncer_x = ev.mouse.x;
    bouncer_y = ev.mouse.y;

    //check if mouse click is within the keypad
    if (((bouncer_x >= 115) && (bouncer_x <= 479))
        && ((bouncer_y >= 383) && (bouncer_y <= 683))){
            charColumn = (bouncer_x - 115) / 91;            //find location of key pressed
            charRow = (bouncer_y - 383) / 60;
            temp = characters[charColumn + (charRow * 4)];  //use location to figure out number in array
    }

    //return key chosen
    return temp;

}

int main(){

    srand(-1);

    ALLEGRO_BITMAP *CalcImage;
    ALLEGRO_COLOR fontColour;
    apstring characters = "   /789*456-123+0.==";
    int charRow = 0;
    int charColumn = 0;
    char temp = ' ';
    float f1 = 0;
    apstring input = "";
    MyStack stackOne;
    Calculator calcOne;
    char result[50];

	// Initialize Allegro
	al_init();

	//install mouse
	if(!al_install_mouse()) {
      fprintf(stderr, "failed to initialize the mouse!\n");
      return -1;
   }

	// Initialize display
	display = al_create_display(SCREEN_W, SCREEN_H);
	if (!display) {
    	al_show_native_message_box(display, "Error", "Error", "Failed to initialize display!",
                                 nullptr, ALLEGRO_MESSAGEBOX_ERROR);
       	return -1;
	}
	al_set_window_title(display, "RPN Calculator");

   	// need to add image processor
 	if (!al_init_image_addon()) {
    	al_show_native_message_box(display, "Error", "Error", "Failed to initialize image addon!",
                                 nullptr, ALLEGRO_MESSAGEBOX_ERROR);
    	return 0;
	}

   al_init_font_addon(); // initialize the font addon

   al_init_ttf_addon();// initialize the ttf (True Type Font) addon


   // load the specific font you want

   ALLEGRO_FONT *font = al_load_ttf_font("Neuton-SC-Regular.ttf", 60, 0);

   if (!font){
      al_show_native_message_box(display, "Error", "Error", "Could not load comic.ttf",
                                    nullptr, ALLEGRO_MESSAGEBOX_ERROR);
      return -1;
   }

    //initialize font colour
    fontColour = al_map_rgb(0, 0, 0);

    //initialize Calculator image
    CalcImage = al_load_bitmap("RPNCalculator.bmp");

    //Clear the screen
    al_clear_to_color(al_map_rgb(0,0,0));

    //load RPN Calculator Image
    al_draw_bitmap(CalcImage, 0, 0, 0);

    al_flip_display();

    int displayCoordX = 464;
    float row1 = 0;
    float row2 = 0;

    //This loop registers every key and outputs the number pressed or the result when an operator is chosen
    while (1){

        // update calc display
        al_draw_bitmap(CalcImage, 0, 0, 0);
        row1 = calcOne.pop();
        sprintf(result, "%.3f", row1);

        al_draw_text(font, fontColour, displayCoordX, 213, ALLEGRO_ALIGN_RIGHT, result);
        row2 = calcOne.pop();
        sprintf(result, "%.3f", row2);

        al_draw_text(font, fontColour, displayCoordX, 148, ALLEGRO_ALIGN_RIGHT, result);
        al_flip_display();

        calcOne.push(row2);
        calcOne.push(row1);

        //find key chosen
        temp = getKey(charRow, charColumn, characters);

        //when a number is pressed
        if(charColumn != 3 && charRow != 0 && temp != characters[18]){

            // still entering a number, pop current entry
            if(input != ""){

                calcOne.pop();
            }
            input += temp;

            //convert number to string so as to use method that transforms to number
            string s = input.c_str();
            stringstream inputString(s);

            //transform into float
            inputString >> f1;
            cout << f1 << endl;

            //Push number onto stack
            calcOne.push(f1);

        } else {

            //re-initialize variables to be ready for next number
            input = "";
            f1 = 0;

            // check for an operation
            if(temp == characters[3]){
                calcOne.divide();
            }else if(temp == characters[7]){
                calcOne.multiply();
            }else if(temp == characters[11]){
                calcOne.subtract();
            }else if(temp == characters[15]){
                calcOne.add();
            }

            cout << calcOne.display() << endl;
        }
    }
    return 0;

}
