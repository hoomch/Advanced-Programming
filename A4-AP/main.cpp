#include <iostream>
#include "interface.hpp"

using namespace std;

int main()
{
    Interface interface;

    interface.addUser("Haruki", "Murakami", "h.murakami@gmail.com", "I dream. Sometimes I think that’s the only right thing to do.");
    interface.addUser("J.K.", "Rowling", "jkr@hotmail.com", "It is our choices that show what we truly are, far more than our abilities.");
    interface.addUser("John", "Green", "john_green@yahoo.com", "If you don’t imagine, nothing ever happens at all.");
    interface.addUser("Dan", "Brown", "dan.brown@gmail.com", "Everything is possible. The impossible just takes longer.");
    interface.addUser("Rene", "Descartes", "rdc@ymail.com", "I think, therefore I am.");

    interface.addCompany("University of Tehran", "Enghelab Square, Tehran", "The best university ever.");
    interface.addCompany("Ofoq Publications", "12 Farvardin Street, Enghelab Square, Tehran", "Ofoq Publishers was founded in 1990 by Reza Hasheminejad");

    interface.addExperience("jkr@hotmail.com", "University of Tehran", "Student", "1/7/1380", "1/4/1395");
    interface.addExperience("jkr@hotmail.com", "University of Tehran", "Professor", "1/7/1395");
    interface.addExperience("dan.brown@gmail.com", "Ofoq Publications", "Author", "1/4/1394", "30/3/1395");
    interface.addExperience("dan.brown@gmail.com", "University of Tehran", "Researcher", "1/4/1395", "1/4/1396");

    interface.assignSkill("jkr@hotmail.com", "Writing");
    interface.assignSkill("jkr@hotmail.com", "Storytelling");
    interface.assignSkill("jkr@hotmail.com", "Editing");
    interface.assignSkill("jkr@hotmail.com", "Proofreading");
    interface.assignSkill("dan.brown@gmail.com", "Writing");
    interface.assignSkill("dan.brown@gmail.com", "Storytelling");
    interface.assignSkill("john_green@yahoo.com", "Writing");
    interface.assignSkill("rdc@ymail.com", "Writing");

    interface.endorseSkill("h.murakami@gmail.com", "jkr@hotmail.com", "Writing");
    interface.endorseSkill("h.murakami@gmail.com", "dan.brown@gmail.com", "Storytelling");

    interface.follow("jkr@hotmail.com", "dan.brown@gmail.com");
    interface.follow("jkr@hotmail.com", "john_green@yahoo.com");

    interface.printUserProfile("jkr@hotmail.com");
    interface.printCompanyProfile("University of Tehran");
}
