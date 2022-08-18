#include <iostream>
using namespace std;

int string_length (const char *string);
void string_copy (char *string_destination , const char *string_source);
void string_copy_end (char *string_destination , const char *string_source);


/* STRING CLASS */

class String {

public: // make this private

    /* String pointer holding the array address */
    char *string_pointer;

public:
    /*CONSTRUCTOR */
    /* Default constructor [ eg. { String s1; } ] */
    String ();

    /* Parameterised constructor, directly sending a string address [ eg. { String s1 ( "abc" ); } ] */
    explicit String (const char *temp_string );            // woking fine without explicit 

    /* Deep copy constructor, directly object [ eg. { String s1 ( "abc" ) , s2 (s1) ; } ] */
    String (const String & temp_obj );

    String (const char *temp_string1 ,const char *temp_string2 );

    /*MEMBER FUNCTION */
    int length ( ) const;


    /* operator overloading */
    String operator + ( String &temp_obj );

    String operator = ( const String& temp_obj);

    char* operator=(char *temp_string);

    void operator () ( const String &temp_obj );

    /* FRIEND FUNCTIONS */

    friend ostream & operator << (ostream & , const String&);
    friend istream & operator >> (istream & , String&);

    friend String & strcpy( String & , String &);


    /* Destructor */
    virtual ~String();

};
/* FRIEND FUNCTION DECLARATION */

String & strcpy( String & string_destination , String & string_source );
String & strncpy( String & string_destination , String & string_source , int number_of_char = 0);
int strcmp( String string1, String string2 );
int strncmp( String string1, String string2, int number_of_char = 0);
String & strrev (String & string1);
String & strupper (String & string1);
String & strlower (String & string1);

int main(){

    String s1 ("red");
    String s2 ("jet");

    cout << strlower(s1) <<endl;
    cout << strupper(s2) <<endl;

}

/* Global Functions */

int string_length (const char *string) {
    int i;
    for (i=0 ;string[i];i++);
    return i;
}

void string_copy (char *string_destination , const char *string_source) {
    int i;
    for(i=0; string_source[i]; i++){
        string_destination [i] = string_source [i];
    }
    string_destination[i]= '\0';
}

void string_copy_end(char *string_destination, const char *string_source) {
    int i,j;
    for(i=0;string_destination[i];i++);

    for(j=0;string_source[j];j++,i++){
        string_destination[i]=string_source[j];
    }
    string_destination[i]='\0';
}


/* CONSTRUCTOR AND DESTRUCTOR */

String::String() {
    string_pointer=nullptr;
}

String::String (const char *temp_string) {
    int length = string_length( (char *) temp_string) + 1;
    string_pointer = new char [length];
    string_copy(string_pointer , temp_string);
}

String::String(const char *temp_string1, const char *temp_string2) {
    int length1 = string_length(temp_string1);
    int length2 = string_length(temp_string2);
    string_pointer = new char [length1+length2+1];

    string_copy(string_pointer,temp_string1);
    string_copy_end(string_pointer,temp_string2);
}

String::String(const String &temp_obj) {
    string_pointer = new char [string_length( (char *) temp_obj.string_pointer ) + 1 ];
    string_copy( string_pointer , temp_obj.string_pointer );
}

String::~String() {
    delete string_pointer;
}

/* String class member function */

int String::length ( ) const {
    return (string_length((char *)string_pointer));
}


/* Operator Overloading */

String String::operator+(String &temp_obj) {
    String s1(string_pointer,temp_obj.string_pointer);
    return s1;
}

String String::operator = ( const String& temp_obj) {
    string_copy(string_pointer,temp_obj.string_pointer);
    return *this;
}

char* String :: operator= ( char *temp_string) {
    string_pointer = new char [string_length( (char *) temp_string ) +1 ];
    string_copy(string_pointer, temp_string);
    return temp_string;
}

void String::operator()(const String &temp_obj) {
    string_pointer = new char [string_length( (char *) temp_obj.string_pointer ) + 1 ];
    string_copy( string_pointer , temp_obj.string_pointer );
}

ostream & operator << (ostream & out, const String& temp_obj){
    cout<< temp_obj.string_pointer << endl;
    return out;
}

istream & operator >> (istream & in, String& temp_obj){
    char *str = new char[100];
    cin >>str;
    String temp_string_obj(str);
    temp_obj(temp_string_obj);
    return in;
}

String & strcpy(String &string_destination, String &string_source) {
    delete string_destination.string_pointer;
    string_destination.string_pointer = new char [string_length(string_source.string_pointer) + 1 ];
    string_copy(string_destination.string_pointer,string_source.string_pointer);
    return string_destination;
}

String &strncpy(String &string_destination, String &string_source, int number_of_char) {
    delete string_destination.string_pointer;
    string_destination.string_pointer = new char [number_of_char + 1 ];
    for (int i=0; i<number_of_char ; i++){
        string_destination.string_pointer[i]=string_source.string_pointer[i];
    }
    string_destination.string_pointer[number_of_char]='\0';
    return string_destination;
}

int strcmp(String string1, String string2) {
    int i;
    for ( i=0;string1.string_pointer[i];i++ ){
        if ( (int)string1.string_pointer[i] != (int)string2.string_pointer[i]){
            return (int)string1.string_pointer[i] - (int)string2.string_pointer[i];
        }
    }
    return (int)string1.string_pointer[i] - (int)string2.string_pointer[i];
}

int strncmp(String string1, String string2, int number_of_char ) {
    int i;
    for ( i=0; i < number_of_char ;i++ ){
        if ( (int)string1.string_pointer[i] != (int)string2.string_pointer[i]){
            return (int)string1.string_pointer[i] - (int)string2.string_pointer[i];
        }
    }
    return (int)string1.string_pointer[i-1] - (int)string2.string_pointer[i-1];
}

String & strrev(String &string1) {
    int length = string_length(string1.string_pointer);
    char t;
    for (int i=0,j=length-1 ; i<j ; i++,j--){
        t=string1.string_pointer[i];
        string1.string_pointer[i]=string1.string_pointer[j];
        string1.string_pointer[j]=t;
    }
    return string1;
}

String &strupper(String &string1) {
    for(int i=0 ; string1.string_pointer[i]; i++){
        if ( ( ( (int) string1.string_pointer[i] ) >= 97 ) && ( (int) string1.string_pointer[i] ) <= 123 )
            string1.string_pointer[i] &= ~(32);
    }
    return string1;
}

String &strlower(String &string1) {
    for(int i=0 ; string1.string_pointer[i]; i++){
        if ( ( ( (int) string1.string_pointer[i] ) >= 65 ) && ( (int) string1.string_pointer[i] ) <= 91 )
            string1.string_pointer[i] |= (32);
    }
    return string1;
}








