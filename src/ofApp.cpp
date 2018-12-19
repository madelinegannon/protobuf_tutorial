#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    GOOGLE_PROTOBUF_VERIFY_VERSION;
    
    string filename = "addressbook.data";
    string filepath = ofToDataPath(filename);
    
    // Read the existing address book.
    {
        fstream input(filepath.c_str(), ios::in | ios::binary);
        if (!input) {
            cout << filepath.c_str() << ": File not found.  Creating a new file." << endl;
        } else if (!address_book_write.ParseFromIstream(&input)) {
            cerr << "Failed to parse address book." << endl;
            return -1;
        }
    }

    // Add an address.
    PromptForAddress(address_book_write.add_people());
    
    {
        // Write the new address book back to disk.
        fstream output(filepath.c_str(), ios::out | ios::trunc | ios::binary);
        if (!address_book_write.SerializeToOstream(&output)) {
            cerr << "Failed to write address book." << endl;
            return -1;
        }else{
            cout << "Contact Saved to " << filepath << endl;
        }
    }
    
    {
        fstream input(filepath.c_str(), ios::in | ios::binary);
        if (!input) {
            cout << filepath.c_str() << ": File not found.  Creating a new file." << endl;
        } else if (!address_book_read.ParseFromIstream(&input)) {
            cerr << "Failed to parse address book." << endl;
            return -1;
        }
    }
    
    // Read back the saved addresses
    ListPeople(address_book_read);
    
    // Optional:  Delete all global objects allocated by libprotobuf.
    google::protobuf::ShutdownProtobufLibrary();
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    
    // display the stored contacts in an address book
    stringstream contacts;
    for (int i = 0; i < address_book_read.people_size(); i++) {
        contacts << toString(address_book_read.people(i)) << endl;
    }
    ofDrawBitmapString(contacts.str(), 10, 20);
}

//--------------------------------------------------------------
void ofApp::PromptForAddress(tutorial::Person* person) {
    cout << "Enter person ID number: ";
    int id;
    cin >> id;
    person->set_id(id);
    cin.ignore(256, '\n');
    
    char name[100];
    cout << "Enter name: ";
    cin >> name;
    *person->mutable_name() = name;
    //getline(cin, *person->mutable_name());    // <-- for some reason getline(cin, string) wasn't working
    
    cout << "Enter email address (blank for none): ";
    char email[100];
    //string email;
    cin >> email;
    if (email[0] != NULL)
        person->set_email(email);
    //getline(cin, email);                      // <-- for some reason getline(cin, string) wasn't working
    //if (!email.empty()) {
    //    person->set_email(email);
    //}
    
    cout << "Enter a phone number (or leave blank to finish): ";
    char number[100];
    cin >> number;
    //string number;
    //getline(cin, number);                     // <-- for some reason getline(cin, string) wasn't working
    //if (number.empty()) {
    //    return;
    //}
    
    tutorial::Person::PhoneNumber* phone_number = person->add_phones();
    phone_number->set_number(number);
    
    cout << "Is this a mobile, home, or work phone? ";
    char temp[100];
    cin >> temp;
    string type(temp);
    //getline(cin, type);                       // <-- for some reason getline(cin, string) wasn't working
    if (type == "mobile") {
        phone_number->set_type(tutorial::Person::MOBILE);
    } else if (type == "home") {
        phone_number->set_type(tutorial::Person::HOME);
    } else if (type == "work") {
        phone_number->set_type(tutorial::Person::WORK);
    } else {
        cout << "Unknown phone type.  Using default." << endl;
    }
}

//--------------------------------------------------------------
void ofApp::ListPeople(const tutorial::AddressBook& address_book) {
    for (int i = 0; i < address_book.people_size(); i++) {
        const tutorial::Person& person = address_book.people(i);
        
        cout << "Person ID: " << person.id() << endl;
        cout << "  Name: " << person.name() << endl;
        if (person.email() != "") {
            cout << "  E-mail address: " << person.email() << endl;
        }
        
        for (int j = 0; j < person.phones_size(); j++) {
            const tutorial::Person::PhoneNumber& phone_number = person.phones(j);
            
            switch (phone_number.type()) {
                case tutorial::Person::MOBILE:
                    cout << "  Mobile phone #: ";
                    break;
                case tutorial::Person::HOME:
                    cout << "  Home phone #: ";
                    break;
                case tutorial::Person::WORK:
                    cout << "  Work phone #: ";
                    break;
                default:
                    cout << "  Unknown phone #: ";
                    break;
            }
            cout << phone_number.number() << endl;
        }
        
    }
}

//--------------------------------------------------------------
string ofApp::toString(tutorial::Person person){
    stringstream ss;
    ss << "Person ID: " << person.id() << endl;
    ss << "  Name: " << person.name() << endl;
    if (person.email() != "") {
        ss << "  E-mail address: " << person.email() << endl;
    }
    for (int j = 0; j < person.phones_size(); j++) {
        const tutorial::Person::PhoneNumber& phone_number = person.phones(j);
        
        switch (phone_number.type()) {
            case tutorial::Person::MOBILE:
                ss << "  Mobile phone #: ";
                break;
            case tutorial::Person::HOME:
                ss << "  Home phone #: ";
                break;
            case tutorial::Person::WORK:
                ss << "  Work phone #: ";
                break;
            default:
                ss << "  Unknown phone #: ";
                break;
        }
        ss << phone_number.number() << endl;
    }
    
    return ss.str();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
