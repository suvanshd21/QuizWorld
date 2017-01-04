/*
Quiz World
By Suvansh Dutta & Pranay Jain

This game is based on file handling and classes.
It can accommodate multiple user accounts.
Users can choose to play a quiz from five categories.
Their high scores will be saved and updated.
The administrator can add more questions by pressing 'a' on the welcome page.
He/she can also view the list of high scores in each category.
The admin id is "admin" and password is "admin".
*/

#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <conio.h>
#include <ctime>
#include <windows.h>

using namespace std;

void welcome();
void sign_up();
void login();
void verify_admin();
void password(char pw[50]);
void rules();
void choose_cat(int &choice, int check);
void game(int choice, fstream &q_db);
void admin();
void store_q();
void enter_q(ofstream &q_db);
void disp_leadb(int choice, int adm=0);
void random_gen(int*, int, int, int);
void loading();

char id[50];       //This global variable stores the user id of the currently logged in user,\
                    which is used later to search for the high score.

/*Start of class of users.
This class contains information pertaining to the
users, including their name, password, id and scores.*/
class user
{
    char name[50];
    char password[50];
    char user_id[50];              //Characteristic to each user
    int hscore1;                   //High scores for each category
    int hscore2;
    int hscore3;
    int hscore4;
    int hscore5;

public:

    user();

    void user_create(char uname[50],char pw[50],char id[50]); //Function to copy entered data into object.

    int gethscr(int x);       //Function to return the high scores.

    void puthscr(int x, int y);  //Function to modify high scores.

    char* get_name()          //Function to return the user's name.
    {
        return name;
    }

    char* get_pass()          //Function to return the password.
    {
        return password;
    }

    char* get_id()            //Function to return the user id.
    {
        return user_id;
    }

};

user::user()
{
    strcpy(name,"NULL");
    strcpy(password,"NULL");
    strcpy(user_id,"NULL");
}

void user::user_create(char uname[50],char pw[50],char id[50])
{
    strcpy(name,uname);
    strcpy(password,pw);
    strcpy(user_id,id);
    hscore1=-1;
    hscore2=-1;
    hscore3=-1;
    hscore4=-1;
    hscore5=-1;
}

int user::gethscr(int x)        //Function to return the high scores.
{
    if (x==1)
        return hscore1;
    else if (x==2)
        return hscore2;
    else if (x==3)
        return hscore3;
    else if (x==4)
        return hscore4;
    else if (x==5)
        return hscore5;
}

void user::puthscr(int x, int y)  //Function to modify high scores
{
    if (x==1)
        hscore1=y;
    else if (x==2)
        hscore2=y;
    else if (x==3)
        hscore3=y;
    else if (x==4)
        hscore4=y;
    else if (x==5)
        hscore5=y;
}
/*End of users class*/

/*Start of class for questions.
This class takes in questions and their answers.*/
class question
{
    char ques[250];
    char opt1[50], opt2[50], opt3[50], opt4[50];
    int answer;

public:

    question();

    void disp_q();              //Member function to display a question and the choices.

    void get_q();               //Function to take in the question and choices.

    int get_ans()               //Member function to return the correct choice.
    {
        return answer;
    }

};

question::question()
{
    strcpy(ques,"NULL");
    strcpy(opt1,"NULL");
    strcpy(opt2,"NULL");
    strcpy(opt3,"NULL");
    strcpy(opt4,"NULL");
    answer=-1;
}

void question::get_q()                    //Function to take in the question and choices.
{
    system("cls");

    cout << "\n Enter a question: ";
    cin.getline(ques,sizeof(ques));

    cout << "\n Enter correct answer: ";
    cin.getline(opt1,sizeof(opt1));

    cout << "\n Enter option 2: ";
    cin.getline(opt2,sizeof(opt2));

    cout << "\n Enter option 3: ";
    cin.getline(opt3,sizeof(opt3));

    cout << "\n Enter option 4: ";
    cin.getline(opt4,sizeof(opt4));
}

void question::disp_q()               //Member function to display a question and the choices.
{
    int r[10];

    srand(time(NULL));

    random_gen(r,4,4,1);

    cout << ques;

    cout << endl << endl;

    for(int i=0; i<4; i++)
    {
        if (r[i]==1)
        {
            cout << '\t' << i+1 << ". " << opt1 << "\n";
            answer=i+1;
        }

        if (r[i]==2)
            cout << '\t' << i+1 << ". " << opt2 << "\n";

        if (r[i]==3)
            cout << '\t' << i+1 << ". " << opt3 << "\n";

        if (r[i]==4)
            cout << '\t' << i+1 << ". " << opt4 << "\n";
    }
}

/*End of questions class*/

/*Start of main execution function*/
int main()
{
    welcome();                   //By calling the welcome function, the program is initialized
    return 0;
}
/*End of main execution function*/


/*Start of welcome function.
This menu function allows the user to choose whether to log in or sign up*/
void welcome()
{
    system("cls");

    cout << "\n WELCOME TO QUIZ WORLD!\n";
    cout << "\n Created by Suvansh Dutta and Pranay Jain.\n";
    cout << "\n\n\n New to quiz world? Type 1 to sign up for free!\n";
    cout << "\n Existing user? Type 2 to login!\n\n";
    cout << "\n\n\n\n Type esc to exit.\n";

    char choice;
    choice=getch();

    if (choice=='1')
    {
        sign_up();               //Redirecting to the sign up function
    }

    else if (choice=='2')
        login();                 //Redirecting to the log in function

    else if (choice==27)
    {
        system("cls");
        cout << "\n Goodbye!\n";
        Sleep(2000);
        exit(0);
    }

    else if (choice=='a')
        verify_admin();            //Redirecting to the function to check whether the user is the admin

    else
    {
        cout << "\n Invalid choice. Please choose from the options provided above.";
        cout << "\a";
        Sleep(1000);

        welcome();
    }
}

/*Start of sign-up function.
This function will allow the user to create a new account.*/
void sign_up()
{
    user u_signup;
    char name[50], pw[50], id[50];

    do
    {
        system("cls");

        cout << "\n CREATE A NEW ACCOUNT";
        cout << "\n\n Enter your full name: ";

        cin.getline(name,sizeof(name));
    }
    while(name[0]=='\0');       //To make sure the user doesn't leave the entry blank

    int id_check;               //Flag variable to check for repetition of user id

    do
    {
        do
        {
            system("cls");

            cout << "\n CREATE A NEW ACCOUNT";
            cout << "\n\n Enter a user ID: ";

            cin.getline(id,sizeof(id));
        }
        while(id[0]=='\0');   //To make sure the user doesn't leave the entry blank


        ifstream file("Users.dat",ios::binary);              //The data base of all users

        while(!file.eof())                                   //Checking for repetition of user names
        {
            file.read((char*)&u_signup,sizeof(u_signup));
            if (!strcmpi(u_signup.get_id(),id))
            {
                id_check=1;
                break;
            }

            else
                id_check=0;
        }

        file.close();

        if(id_check==1)
        {
            cout << "\n This ID already exists.\n";
            Sleep(1500);
        }
    }
    while(id_check!=0);

    int valid_pw=0;
    system("cls");

    do
    {
        system("cls");
        cout << "\n CREATE A NEW ACCOUNT";
        cout << "\n\n Enter a password: ";

        password(pw);        //The entered password will be stored in pw
        if(strlen(pw)>=4&&strlen(pw)<=12)        //Checking for validity of password
            valid_pw=1;
        else
        {
            cout << "\n\n INVALID.\n The password must be 4-12 characters long.\n";
            cout << "\a";
            Sleep(1500);
        }
    }
    while(!valid_pw);

    system ("cls");
    cout << endl << endl;
    cout.width(71);
    cout << "CREATING PROFILE";
    loading();

    ofstream u_create("Users.dat",ios::binary|ios::app);        //Adding User to database

    u_signup.user_create(name,pw,id);

    u_create.write((char*)&u_signup,sizeof(u_signup));

    u_create.close();

    system("cls");

    cout << "\n Registration Complete!\n";                //Displaying user info
    /*cout << "\n YOUR INFO";
    cout << "\n Name: " << u_signup.get_name();
    cout << "\n User ID: " << u_signup.get_id();
    cout << "\n Password: " << u_signup.get_pass();*/
    Sleep(1000);

    system ("cls");
    cout << endl << endl;
    cout.width(73);
    cout << "REDIRECTING TO LOGIN";
    loading();
    login();                     //Redirecting to the log in function
}
/*End of sign- up function*/

/*Start of login function.
This function allows the user to log in to his or her already created account*/
void login()
{
    system("cls");

    user u_login;
    char id[50], pw[50];
    int flag=0;

    while(!flag)
    {

        do
        {
            system("cls");

            cout << "\n LOG- IN\n";         //Taking in the ID and Password
            cout << "\n Enter your user ID: ";
            cin.getline(id, sizeof(id));
        }
        while(id[0]=='\0');            //To make sure the user doesn't leave the entry blank
        cout << "\n Enter your password: ";
        password(pw);

        ifstream users("Users.dat",ios::binary);

        while(users.read((char*)&u_login,sizeof(u_login)))      //To check if id and password are correct
        {
            if (!strcmpi(u_login.get_id(),id))
            {
                flag=1;
                break;
            }

            else
                flag=0;
        }

        if(flag==1)
        {
            if (!strcmp(u_login.get_pass(),pw))
            {
                system("cls");
                cout << endl << endl;
                cout.width(69);
                cout <<"LOGGING IN";
                loading();
                strcpy(::id,u_login.get_id());     //Storing the user id of currently logged in user for future reference
                cout << "\n Welcome " << u_login.get_name() << "!\n";
                Sleep(2500);
                users.close();
                rules();                //Re-directing to the next stage
            }

            else
            {
                cout << "\n\n INVALID.\n The password you entered doesn't match the one in our records.";
                cout << "\a";
                flag=0;
                Sleep(1500);
            }
        }

        else
        {
            cout << "\n\n INVALID.\n The user id you entered doesn't match the one in our records.";
            cout << "\a";
            Sleep(1500);
        }
        users.close();
    }
}
/*End of login function*/

/*Start of verify_admin function.
This function checks whether the user IS actually the admin.
The admin id is "admin" and password is "admin"*/
void verify_admin()
{
    char a_id[50], a_pw[50];
    do
    {
        system("cls");
        cout << "\n Enter Administrator ID: ";
        cin.getline(a_id,sizeof(a_id));
    }
    while(a_id[0]=='\0');
    cout << "\n Enter Administrator Password: ";
    password(a_pw);
    if(!strcmp(a_id, "admin"))
    {
        if(!strcmp(a_pw, "admin"))
        {
            system("cls");
            cout << "\n Welcome Admin!";
            Sleep(2000);
            admin();
        }
        else
        {
            system("cls");
            cout << "\n Nice try, imposter. Exiting program...\n";
            Sleep(1500);
            exit(0);
        }
    }
    else
    {
        system("cls");
        cout << "\n Nice try, imposter. Exiting program...\n";
        Sleep(1500);
        exit(0);
    }
}
/*End of verify_admin function.*/

/*Start of Password function.
This function allows the user to enter a password and displays '*' on screen*/
void password(char pw[50])
{
    int i=0;

    while(1)
    {
        pw[i]=getch();

        if (pw[i]==(char)13)            //To check for end of password
            break;

        else if(pw[i]==(char)8)         //To check for backspaces
        {
            if(i==0)
                continue;
            else
            {
                cout << "\b \b";
                i--;
            }
        }
        else
        {
            cout << "*";         //To display a '*' for every entered character
            i++;
        }
    }
    pw[i]='\0';
}
/*End of password function*/

/*Start of rules function.
This function displays the rules of the quiz.*/
void rules()
{
    cout << "\n RULES:\n";
    cout << "\n You can choose a quiz from five different topics.\n There are 10 multiple-choice questions in each quiz.";
    cout << "\n You will have to choose the correct answer from 1, 2, 3 & 4.\n Ten points will be awarded for each correct answer.";
    cout << "\n Three will be deducted for each incorrect answer.\n\n If you want to exit the program at any point, press esc.\n\n ";
    system("pause");

    int x;
    choose_cat(x,1);                            //Redirection to the function to choose a category
}
/*End of rules function.*/

/*Start of function to choose a category.
This function allows the user to choose a category.
It takes in two arguments, choice, and check, which tells the compiler where the user should be directed.
If check is 1, it implies the user is directed to game().
If check is 0, the user/admin will be directed back to the store_q()/disp_leadb().*/
void choose_cat(int &choice, int check)
{
    system("cls");

    char x;

    cout << "\n Choose one of the following categories:\n";
    cout << "\n 1. Math ";
    cout << "\n 2. FIFA World Cup 2014";
    cout << "\n 3. Vocabulary";
    cout << "\n 4. Movies";
    cout << "\n 5. Literature: Classic and Contemporary";

    x=getch();
    system ("cls");
    cout << endl << endl;
    cout.width(69);
    cout << "PLEASE WAIT";
    loading();

    if(x=='1')
    {
        choice=1;
        if(check)
        {
            fstream q_db("Cat1.dat",ios::binary|ios::in|ios::out|ios::ate);
            cout << "\n Solve the following math problems.\n";
            Sleep(2500);
            game(choice,q_db);                  //Redirecting to appropriate quiz.
            q_db.close();
        }
    }
    else if(x=='2')
    {
        choice=2;
        if(check)
        {
            fstream q_db("Cat2.dat",ios::binary|ios::in|ios::out|ios::ate);
            cout << "\n Answer the following questions related to the FIFA World Cup 2014.\n";
            Sleep(2500);
            game(choice,q_db);                  //Redirecting to appropriate quiz.
            q_db.close();
        }
    }
    else if(x=='3')
    {
        choice=3;
        if(check)
        {
            fstream q_db("Cat3.dat",ios::binary|ios::in|ios::out|ios::ate);
            cout << "\n Choose the option which defines the word most accurately.\n";
            Sleep(2500);
            game(choice,q_db);                  //Redirecting to appropriate quiz.
            q_db.close();
        }
    }
    else if(x=='4')
    {
        choice=4;
        if(check)
        {
            fstream q_db("Cat4.dat",ios::binary|ios::in|ios::out|ios::ate);
            cout << "\n Answer the following questions related to movies.\n";
            Sleep(2500);
            game(choice,q_db);                  //Redirecting to appropriate quiz.
            q_db.close();
        }
    }
    else if(x=='5')
    {
        choice=5;
        if(check)
        {
            fstream q_db("Cat5.dat",ios::binary|ios::in|ios::out|ios::ate);
            cout << "\n Answer the following questions on classic and contemporary literature.\n";
            Sleep(2500);
            game(choice,q_db);                  //Redirecting to appropriate quiz.
            q_db.close();
        }
    }

    else if(x==27)                 //To check whether the user wants to exit the program.
    {
        system("cls");
        cout << "\n Thanks for playing! :)\n";
        Sleep(2000);
        system("cls");
        cout << endl << endl;
        cout.width(68);
        cout << "LOGGING OUT";
        loading();
        welcome();
    }
    else
    {
        cout << "\n\n Invalid choice. Please try again.";
        cout << "\a";
        Sleep(1500);
        choose_cat(choice,1);
    }
}
/*End of function to choose a category*/

/*Start of main game function.
This function executes the quiz. It displays a question and takes in an answer.
At the end it displays your score and high score.
The category number and category file have been passed as arguments.*/
void game(int choice, fstream &q_db)
{
    question q;
    int scr=0;
    int c=0;
    q_db.seekp(0,ios::end);
    c=q_db.tellp();
    c=c/sizeof(question);          //Total number of questions in the file.

    int r[10];
    random_gen(r,10,c,0);          //Generating 10 random question.

    for(int i=0; i<10; i++)
    {
        system("cls");

        q_db.seekg(r[i]*sizeof(question));

        q_db.read((char*)&q,sizeof(q));
        cout << "\n Q " << i+1 << ". ";

        q.disp_q();       //Displaying the questions and answers.

        int x;
        char a;
        cout << "\n Enter answer: ";
        a=getche();       //Taking in the user's answer.

        if(a=='1')
            x=1;

        else if(a=='2')
            x=2;

        else if(a=='3')
            x=3;

        else if(a=='4')
            x=4;

        else if(a==27)
        {
            system("cls");
            cout << "\n Thanks for playing! :)\n";
            Sleep(2000);
            system("cls");
            cout << endl << endl;
            cout.width(68);
            cout << "LOGGING OUT";
            loading();
            welcome();
        }

        else
        {
            cout << "\n Invalid choice. Try Again.";
            cout << "\a";
            Sleep(1000);
            i--;
            continue;
        }

        if(x==q.get_ans())                                //Checking if entered answer is correct.
        {
            cout << "\n Correct!\n";
            scr+=10;
            cout << "\n Your score is: " << scr;
            Sleep(2000);
        }

        else
        {
            cout << "\n Incorrect!\n";
            cout << "\n The correct answer is " << q.get_ans();
            scr-=3;
            if(scr<0)
                scr=0;
            cout << "\n Your score is: " << scr;
            Sleep(1500);
        }
    }

    system("cls");
    cout << "\n Congratulations!\n\n Your final score is " << scr;    //End of one round of the quiz.

    fstream u_db("Users.dat",ios::binary|ios::in|ios::out);

    user u;

    while(u_db.read((char*)&u,sizeof(user)))                  //To search for and display the high score.
    {
        if(!strcmp(u.get_id(),id))
        {
            if(u.gethscr(choice)<=scr)              //To check if current score is higher or not.
            {
                int size=-1*sizeof(u);
                u.puthscr(choice,scr);
                u_db.seekp(size,ios::cur);
                u_db.write((char*)&u,sizeof(u));    //Overwriting the record in the file.
            }
            cout << "\n\n Your high score is " << u.gethscr(choice);
        }

    }
    Sleep(2500);
    system("cls");
    disp_leadb(choice);           //To display the leader board.
    u_db.close();
    Sleep(5000);
    system("cls");
    char a;
    cout << "\n Do you want to take another quiz?";    //To check whether the user wants to play again.
    cout << "\n\n Enter choice (y/n): ";
    a=getche();
    system("cls");
    if(a=='y'||a=='Y')
    {
        cout << endl << endl;
        cout.width(69);
        cout << "PLEASE WAIT";
        loading();
        int x;
        choose_cat(x,1);
    }
    else
    {
        system("cls");
        cout << "\n Thanks for playing! :)\n";
        Sleep(2000);
        system("cls");
        cout << endl << endl;
        cout.width(68);
        cout << "LOGGING OUT";
        loading();
        welcome();
    }
}
/*End of main game function*/

/*Start of admin function.
This function will ask the admin what he wants to do.*/
void admin()
{
    system("cls");
    cout << "\n What do you want to do?";
    cout << "\n\n 1. Add a new question.\n\n 2. View high scores of all users in a category.\n\n\n\n To exit, press esc.";
    char choice;
    choice = getch();
    if(choice=='1')
        store_q();                      //Redirects to store_q() function to store questions.
    else if (choice=='2')
    {
        int choice;
        choose_cat(choice,0);
        system("cls");
        disp_leadb(choice,1);           //Redirects to function to display scores of users.
    }
    else if (choice == 27)
    {
        system("cls");
        cout << "\n Goodbye!";
        Sleep(2000);
        exit(0);
    }
    else
    {
        cout << "\n Invalid choice.";
        cout << "\a";
        Sleep(1250);
        admin();
    }
    system("cls");
    cout << "\n Goodbye!";
    Sleep(2000);
    exit(0);
}
/*End of admin function.*/

/*Start of store_q function.
The function allows the admin to choose a category to store questions in
and opens the required file, which is passed to enter_q()*/
void store_q()
{
    cout << endl;
    int x;
    choose_cat(x,0);
    if (x==1)
    {
        ofstream q_db("Cat1.dat",ios::binary|ios::app);
        enter_q(q_db);
    }
    else if (x==2)
    {
        ofstream q_db("Cat2.dat",ios::binary|ios::app);
        enter_q(q_db);
    }
    else if (x==3)
    {
        ofstream q_db("Cat3.dat",ios::binary|ios::app);
        enter_q(q_db);
    }
    else if (x==4)
    {
        ofstream q_db("Cat4.dat",ios::binary|ios::app);
        enter_q(q_db);

    }
    else if (x==5)
    {
        ofstream q_db("Cat5.dat",ios::binary|ios::app);
        enter_q(q_db);
    }

    char z;
    cout << "\n\n Do you want to change the category?";
    cout << "\n\n Enter choice: ";
    z=getche();
    if (z=='Y'||z=='y')
        store_q();
    system("cls");
    cout << "\n\n Do you want to go back to the previous menu?";
    cout << "\n\n Enter choice: ";
    z = getche();
    if(z=='y'||z=='Y')
    {
        system("cls");
        cout << endl << endl;
        cout.width(69);
        cout << "PLEASE WAIT";
        loading();
        admin();
    }
}
/*End of store_q*/

/*Start of enter_q function.
This function takes in questions from the admin and stores them in
the file passed as an argument*/
void enter_q(ofstream &q_db)
{
    char y;
    question q;
    do
    {
        q.get_q();
        q_db.write((char*)&q,sizeof(q));            //Storing the question in the file.
        cout << "\n Do you want to continue? ";
        cout << "\n\n Enter choice: ";
        y=getche();
    }
    while(y=='Y'||y=='y');
}
/*End of enter_q function.*/

/*Start of disp_leadb function.
This function will ask the user to choose a category, and then will display the leader board of that category.
It takes two arguments, the choice of category and adm, which is 1 if the user is the admin
and zero if not. If the user is not the admin, he/she will be sent back to game().*/
void disp_leadb(int choice, int adm)
{
    user u[100];
    ifstream users("users.dat",ios::binary);
    cout << "\n\n";
    cout.width(33);
    cout << "LEADERBOARD";
    cout << "\n\n\n";
    cout.width(20);
    cout << "   PLAYER NAME";
    cout.width(25);
    cout << "HIGH SCORE";
    cout << "\n\n";

    int n=0;

    while(users.read((char*)&u[n],sizeof(user)))
        if(u[n].gethscr(choice)!=-1)      //So that only the scores of those users who have played the quiz are displayed.
            n++;

    for(int i=0; i<n; i++)                //Sorting the array according to high score.
        for (int j=0; j<n-i-1; j++)
            if(u[j].gethscr(choice)>u[j+1].gethscr(choice))
            {
                user t;
                t=u[j];
                u[j]=u[j+1];
                u[j+1]=t;
            }
    for(int i=n-1; i>=0; i--)             //Displaying the scores in a tabular form
    {
        cout.width(7);
        cout << n-i << ". " << u[i].get_name();
        cout.width(33-strlen(u[i].get_name()));
        cout << u[i].gethscr(choice);
        cout << endl;
    }
    if(adm==1)                  //To check whether the user is the admin.
    {
        char ans;
        cout << "\n Do you want to view the scores of another category? ";
        cout << "\n Enter choice: ";
        ans = getche();
        if(ans=='y'||ans=='Y')
        {
            system("cls");
            choose_cat(choice,0);
            disp_leadb(choice,1);
        }
        else
        {
            system("cls");
            cout << "\n Do you want to go back to the previous menu? ";
            cout << "\n Enter choice: ";
            ans = getche();
            if(ans=='y'||ans=='Y')
            {
                system("cls");
                cout << endl << endl;
                cout.width(69);
                cout << "PLEASE WAIT";
                loading();
                admin();
            }
        }
    }
}
/*End of disp_leadb function.*/

/*Start of random number generator function.
This function takes in 4 arguments, which are respectively,
an integer array, the number of random numbers to be generated, the upper limit and the lower limit.
This function has been used in randomizing the order of questions as well as options
in the function game() and member function of question disp_q() respectively.*/
void random_gen(int r[10], int n, int x, int y=0)
{
    srand(time(NULL));
    for(int i=0; i<n; i++)
    {
        int flag=0;
        r[i]=rand()%x+y;

        for(int j=0; j<i; j++)         //To make sure the number isn't being repeated.
            if (r[i]==r[j])
            {
                i--;
                flag=1;
                break;
            }

        if(flag)
            continue;
    }
}
/*End of random number generator function.*/

/*Start of loading function.
This function displays the loading bar.*/
void loading()
{
    srand(time(NULL));
    cout << endl << endl << endl;
    cout.width(40);
    for(int i=0; i<50; i++)
    {
        int r=rand()% 500;
        cout << (char)219;
        if(i<25)
            Sleep(r/7);
        else if(i>=25 && i<35)
            Sleep(r/11);
        else if(i>=35 && i<40)
            Sleep(r/3);
        else if(i>=40)
            Sleep(r/9);
    }
    system("cls");
}
/*End of loading function.*/

/*End of program.*/
