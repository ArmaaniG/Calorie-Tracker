#include <iostream>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <vector>
#include <string>
#include <limits>

// Enum to represent the different application screens
enum Screen {LOGIN, DASHBOARD};
Screen currentScreen = LOGIN;

// Button structure to store information about UI Buttons
struct Button {
    float x, y, width, height;
    const char* text;

    bool contains(float px, float py) const {
        return px >= x && px <= x + width && py >= y && py <= y + height;
    }
};

// Meal strucutre to store information about a meal
struct Meal {
    std::string description;
    int calories;

    // Constructor to initialize a meal with description and calories
    Meal(const std::string &desc, int cal) : description(desc), calories(cal) {}
};

// Vector to store a list of meals
std::vector<Meal> meals;
int totalCalories = 0;

// Function to add a meal to the list of meals
void addMeal(const std::string &description, int calories) {
    meals.push_back(Meal(description, calories));
    totalCalories += calories; //update the calorie total
    std::cout << "Meal added: " << description << ", " << calories << " calories\n";
}

Button usernameButton = {100, 300, 200, 30, "Username"};
Button passwordButton = {100, 250, 200, 30, "Password"};
Button loginButton = {100, 200, 100, 30, "Login"};
Button registerButton = {210, 200, 100, 30, "Register"};

// Class to represent a user with a username and password
class User {
public:
    std::string username;
    std::string password;

    // Constructor to initialize a user with a username and password
    User(const std::string &user, const std::string &pass) : username (user), password(pass) {}

    // Function to check if an input password matches the user's password
    bool checkPassword(const std::string &inputPassword) const {
        return password == inputPassword;
    }
};

User loggedInUser("", "");

std::vector<User> users = {
        //add more users if needed
};

// Function to attempt logging in with a username and password
void attemptLogin(const std::string &enteredUsername, const std::string &enteredPassword) {
    for(const User &user : users) {
        if(user.username == enteredUsername && user.checkPassword(enteredPassword)) {
            std::cout << "Login successful!\n";
            loggedInUser = user;
            currentScreen = DASHBOARD;
            glutPostRedisplay();
            //transition to the main dashboard
            return;
        }
    }
    std::cout << "Login failed. Invalid username or password.\n";
}

Button addMealButton = {100, 100, 100, 30, "Add Meal"};
Button logoutButton = {210, 100, 100, 30, "Logout"};
std::string dashboardTitle = "Dashboard";

// Function to draw a button on the screen
void drawButton(float x, float y, float width, float height, const char* text) {
    glColor3f(0.5, 0.5, 0.5); //set color
    glBegin(GL_QUADS);
    glVertex2f(x, y);
    glVertex2f(x + width, y);
    glVertex2f(x + width, y + height);
    glVertex2f(x, y + height);
    glEnd();

    glColor3f(1.0, 1.0, 1.0); //text color
    glRasterPos2f(x + 10, y + 10);
    for (int i = 0; text[i] != '\0'; i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, text[i]);
    }
}

// Function to draw text on the screen
void drawText(float x, float y, const char* text) {
    glColor3f(1.0, 1.0, 1.0);
    glRasterPos2f(x, y);
    for(int i = 0; text[i] != '\0'; ++i) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, text[i]);
    }
}

std::string enteredUsername;
std::string enteredPassword;
bool usernameFieldActive = false;
bool passwordFieldActive = false;
const std::string mainTitle = "Armaani's Calorie Counter";

void drawMainTitle(float x, float y, const std::string& text) {
    glColor3f(1.0, 1.0, 1.0);
    glRasterPos2f(x, y);
    for(int i = 0; i < text.size(); ++i) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
    }
}

// Main display function that is called to render the application window
void display() {
    glClearColor(0.0f, 0.0f, 1.0f, 1.0f); //set color to blue
    glClear(GL_COLOR_BUFFER_BIT);

    if (currentScreen == LOGIN) {

        drawMainTitle(200, 70, mainTitle);

        //drawing username field
        drawButton(usernameButton.x, usernameButton.y, usernameButton.width, usernameButton.height, "Username");
        drawText(usernameButton.x  + 10, usernameButton.y - 20, enteredUsername.c_str());

        //drawing password field
        //drawButton(100, 250, 200, 30, "Password");
        drawButton(passwordButton.x, passwordButton.y, passwordButton.width, passwordButton.height, "Password");
        drawText(passwordButton.x + 10, passwordButton.y - 20, std::string(enteredPassword.size(), '*').c_str());

        //draw login and register buttons
        drawButton(loginButton.x, loginButton.y, loginButton.width, loginButton.height, loginButton.text);
        drawButton(registerButton.x, registerButton.y, registerButton.width, registerButton.height, registerButton.text);

    } else if (currentScreen == DASHBOARD) {

        //draw title
        glColor3f(1.0, 1.0,1.0);
        glRasterPos2f(150, 500);
        for(int i = 0; dashboardTitle[i] != '\0'; i++) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, dashboardTitle[i]);
        }

        //draw meal details
        float mealY = 400;
        for(const auto& meal : meals) {
            std::string mealText = meal.description + ": " + std::to_string(meal.calories) + " cal";
            glRasterPos2f(100, mealY);
            for (int i = 0; i < mealText.size(); ++i) {
                glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, mealText[i]);
            }
            mealY -= 20;
        }

        //draw total calories
        std::string totalCaloriesText = "Total Calories: " + std::to_string(totalCalories);
        glColor3f(1.0, 1.0, 1.0); //set text color to white
        glRasterPos2f(100, 50); //Set position
        for(int i = 0; i < totalCaloriesText.size(); ++i) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, totalCaloriesText[i]);
        }

        //draw buttons
        drawButton(addMealButton.x, addMealButton.y, addMealButton.width, addMealButton.height, addMealButton.text);
        drawButton(logoutButton.x, logoutButton.y, logoutButton.width, logoutButton.height, logoutButton.text);
    }

    glutSwapBuffers();
}

void onLoginClick();
void onRegisterClick() {
    std::string newUsername;
    std::string newPassword;

    std::cout << "Enter new username: ";
    std::cin >> newUsername;
    std::cout << "Enter new password";
    std::cin >> newPassword;

    //check if username exists
    for(const User &user : users) {
        if(user.username == newUsername) {
            std::cout << "Username already exists. Choose a different username.\n";
            return;
        }
    }

    //add new user to the users vector
    users.push_back(User(newUsername, newPassword));
    std::cout << "User registered successfully!\n";
}

// Function that handles mouse clicks in the application
void mouse(int button, int state, int x, int y) {
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        if (currentScreen == LOGIN) {
            if(usernameButton.contains(x, y)) {
                usernameFieldActive = true;
                passwordFieldActive = false;
                std::cout << "Username field activated.\n";
            } else if (passwordButton.contains(x, y)) {
                usernameFieldActive = false;
                passwordFieldActive = true;
                std::cout << "Password field activated.\n";
            } else if (loginButton.contains(x, y)) {
                onLoginClick();
            } else if (registerButton.contains(x, y)) {
                std::cout << "Register button clicked!\n";
                onRegisterClick();
            }
        } else if (currentScreen == DASHBOARD) {
            if (addMealButton.contains(x, y)) {
                std::cout << "Add Meal button clicked!\n";
                std::string description;
                int calories;

                //get meal description and calorie count
                std::cout << "Enter meal description: ";
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //Clear the input buffer
                std::getline(std::cin, description); //use getline to read the given line

                //std::cin >> description;
                std::cout << "Enter calories: ";
                std::cin >> calories;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //clear the input buffer again

                addMeal(description, calories);
            } else if (logoutButton.contains(x, y)) {
                std::cout << "Logout button clicked!\n";
                currentScreen = LOGIN;
                loggedInUser = User("","");
                meals.clear();
                enteredUsername.clear();
                enteredPassword.clear();
                glutPostRedisplay();
                //loggedInUser = User();
                //meals.clear();
            }
        }
    }
}

void onLoginClick() {
    attemptLogin(enteredUsername, enteredPassword);
}

// Handles keyboard inputs in the application
void keyboard(unsigned char key, int x, int y) {
    if (currentScreen == LOGIN) {
        if (usernameFieldActive) {
            if (key == 8 && !enteredUsername.empty()) {
                enteredUsername.pop_back();
            } else if (key >= 32 && key <= 126) {
                enteredUsername.push_back(key);
            }
            std::cout << "Username: " << enteredUsername << "\n";
        } else if (passwordFieldActive) {
            if (key == 8 && !enteredPassword.empty()) {
                enteredPassword.pop_back();
            } else if (key >= 32 && key <= 126) {
                enteredPassword.push_back(key);
            }
            std::cout << "Password: " << enteredPassword << "\n";
        }

        if (key == 13) {
            if(usernameFieldActive || passwordFieldActive) {
                onLoginClick();
            }
        }
    } else if (currentScreen == DASHBOARD) {
        if(key == '1') {
            addMeal("Breakfast", 300);
            glutPostRedisplay();
        } else if (key == '2') {
            addMeal("Lunch", 500);
            glutPostRedisplay();
        }

    }
}

// Reshapes the application windows when it is resized
void reshape(int width, int height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, width, height, 0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

}

// Main function to initialize and run the application
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Calorie Tracker");

    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutKeyboardFunc(keyboard);
    glutReshapeFunc(reshape);

    glutMainLoop();
    return 0;
}
