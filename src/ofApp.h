#pragma once

#include <fstream>
#include <iostream>
#include "ofMain.h"
#include "addressbook.pb.h"


class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
        // Use 2 address books to verify that data is reading and writing properly
        tutorial::AddressBook address_book_read;
        tutorial::AddressBook address_book_write;
    
        // This function fills in a Person message based on user input.
        void PromptForAddress(tutorial::Person* person);
        // Iterates though all people in the AddressBook and prints info about them.
        void ListPeople(const tutorial::AddressBook& address_book);
        string toString(tutorial::Person person);
    
};
